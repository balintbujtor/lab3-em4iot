#include "bus.h"


void bus::set_attributes() {}

void bus::initialize() {}

void bus::processing()
{
    const double supercap_limit = 300; // mA for 40s supply
    const double supercap_request_threshold = 50; //above this we use the supercap

    double tot_requested, tot_consumed, tot_batt_requested, tot_sc_requested, tot_scavenged;

    // Compute total current consumption
    tot_consumed = i_mcu.read() + i_rf.read()
                          + i_air_quality_sensor.read()
                          + i_methane_sensor.read()
                          + i_temperature_sensor.read()
                          + i_mic_click_sensor.read()
                          ;
    tot_scavenged = real_i_pv1.read();

    tot_requested = tot_consumed - tot_scavenged;

    double soc_sc = soc_supercap.read();
    double soc_batt = soc_battery.read();

    if(tot_requested > 0){
        // using the energy storage devices
        if(soc_sc > 0.1){
            //if we have enough soc in the capacitor

            if(tot_requested > supercap_request_threshold && tot_requested < supercap_limit){
                //current is classified as spike but not too high
                tot_sc_requested = tot_requested;
                tot_batt_requested = 0;
            }
            else if(tot_requested > supercap_limit) 
            {
                // spike but too high, so battery is needed too
                tot_sc_requested = supercap_limit;
                tot_batt_requested = tot_requested - supercap_limit;
            }
            else {
                //below supercap threshold, not spike, everything by battery
                tot_sc_requested = 0;
                tot_batt_requested = tot_requested;
            }
        }
        else {
            // supercap is not charged enough, we use the battery only
            tot_sc_requested = 0;
            tot_batt_requested = tot_requested;
        }
    }

    else {
        //charging the energy storage devices
        if(soc_batt < 0.1) {
            // if battery is dying we charge only that
            tot_batt_requested = tot_requested;
            tot_sc_requested = 0;
        }
        else{
            // if the battery is not dying we prioritize the supercap
            if(soc_sc < 0.95){
                // if the supercap is not charged enough we charge that up first
                tot_sc_requested = tot_requested;
                tot_batt_requested = 0;
            }
            else {
                // if it is charged up, we charge the battery
                tot_sc_requested = 0;
                tot_batt_requested = tot_requested;
            }
        }
    }

    i_tot_batt.write(tot_batt_requested); // tot_requested >= 0 ? pow_from_battery : pow_to_battery
    i_tot_sc.write(tot_sc_requested); 
}

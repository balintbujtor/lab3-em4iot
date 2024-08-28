#include "bus.h"


void bus::set_attributes() {}

void bus::initialize() {}

void bus::processing()
{
    const double supercap_limit = 225; // mA for 40s supply
    const double supercap_request_threshold = 30; //above this we use the supercap

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

    if(tot_requested > supercap_request_threshold && tot_requested < supercap_limit){
        tot_sc_requested = tot_requested;
        tot_batt_requested = 0;
    }
    else if(tot_requested > supercap_limit) 
    {
        tot_sc_requested = supercap_limit;
        tot_batt_requested = tot_requested - supercap_limit;
    }
    else {
        //below supercap threshold, everything by battery
        tot_sc_requested = 0;
        tot_batt_requested = tot_requested;
    }

    i_tot_batt.write(tot_batt_requested); // tot_requested >= 0 ? pow_from_battery : pow_to_battery
    i_tot_sc.write(tot_sc_requested); 
}

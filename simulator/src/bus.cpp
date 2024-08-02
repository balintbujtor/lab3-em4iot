#include "bus.h"


void bus::set_attributes() {}

void bus::initialize() {}

void bus::processing()
{
    // Compute total current consumption
    double tot_consumed = i_mcu.read()
                          + i_air_quality_sensor.read()
                          ;

    double tot_requested = tot_consumed;
    
    double tot_batt_requested = 0.9 * tot_requested;
    double tot_sc_requested = tot_requested - tot_batt_requested;

    i_tot_batt.write(tot_batt_requested); // tot_requested >= 0 ? pow_from_battery : pow_to_battery
    i_tot_sc.write(tot_sc_requested); 
}

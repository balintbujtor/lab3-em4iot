#include <systemc-ams.h>

#include "config.h"


SCA_TDF_MODULE(bus)
{
    sca_tdf::sca_in<double> i_mcu; // Requested current from MCU
    sca_tdf::sca_in<double> i_rf; // Requested current from RF module
    sca_tdf::sca_in<double> i_air_quality_sensor; // Requested current from air_quality_sensor
    sca_tdf::sca_in<double> i_methane_sensor; // Requested current from methane_sensor
    sca_tdf::sca_in<double> i_temperature_sensor; // Requested current from temperature_sensor
    sca_tdf::sca_in<double> i_mic_click_sensor; // Requested current from mic_click_sensor

    sca_tdf::sca_in<double> soc_supercap; // State of Charge of the supercap to determine operation
    sca_tdf::sca_in<double> soc_battery;
    
    sca_tdf::sca_in<double> real_i_pv1;
    sca_tdf::sca_out<double> i_tot_batt;
    sca_tdf::sca_out<double> i_tot_sc;

    SCA_CTOR(bus): i_tot_batt("i_tot_batt"),
                   i_tot_sc("i_tot_sc"),
                   i_mcu("i_mcu"),
                   i_rf("i_rf"),
                   i_methane_sensor("i_methane_sensor"),
                   i_temperature_sensor("i_temperature_sensor"),
                   i_mic_click_sensor("i_mic_click_sensor"),
                   real_i_pv1("real_i_pv1"),
                   i_air_quality_sensor("i_air_quality_sensor"),
                   soc_supercap("soc_supercap") {};

    void set_attributes();
    void initialize();
    void processing();
};
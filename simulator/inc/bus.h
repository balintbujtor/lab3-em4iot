#include <systemc-ams.h>

#include "config.h"


SCA_TDF_MODULE(bus)
{
    sca_tdf::sca_in<double> i_mcu; // Requested current from MCU
    sca_tdf::sca_in<double> i_air_quality_sensor; // Requested current from air_quality_sensor

    sca_tdf::sca_out<double> i_tot_batt;
    sca_tdf::sca_out<double> i_tot_sc;

    SCA_CTOR(bus): i_tot_batt("i_tot_batt"),
                   i_tot_sc("i_tot_sc"),
                   i_mcu("i_mcu"),
                   i_air_quality_sensor("i_air_quality_sensor") {};

    void set_attributes();
    void initialize();
    void processing();
};
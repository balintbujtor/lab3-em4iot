#include <systemc-ams.h>

#include "battery.h"
#include "bus.h"
#include "converter_battery.h"
#include "mcu.h"
#include "air_quality_sensor.h"
#include "supercap.h"

int sc_main(int argc, char* argv[])
{
    // Instantiate signals
    sca_tdf::sca_signal<double> i_batt, v_batt, soc;
    sca_tdf::sca_signal<double> i_air_quality_sensor; 
    sca_tdf::sca_signal<double> i_mcu;
    sca_tdf::sca_signal<double> i_tot_batt, i_tot_sc;

    sca_tdf::sca_signal<double> i_sc, v_sc, e_sc, soc_sc;

    // Instantiate modules
    bus bus("bus");
    battery battery("battery");
    converter_battery converter_battery("converter_battery");
    mcu mcu("mcu");
    air_quality_sensor air_quality_sensor("air_quality_sensor");

    supercapacitor sc_module("supercapacitor");

    sc_module.pI_in(i_tot_sc);
    sc_module.pV_out(v_sc);
    sc_module.pE_out(e_sc);
    sc_module.pSoC_out(soc_sc);

    // Connect signals to modules
    battery.i_batt(i_batt);
    battery.v_batt(v_batt);
    battery.soc(soc);

    converter_battery.i_bus(i_tot_batt);
    converter_battery.v_batt(v_batt);
    converter_battery.i_batt(i_batt);
    
    air_quality_sensor.i(i_air_quality_sensor);
    mcu.i(i_mcu);
    

    bus.i_mcu(i_mcu);
    bus.i_tot_batt(i_tot_batt);
    bus.i_tot_sc(i_tot_sc);
    bus.i_air_quality_sensor(i_air_quality_sensor);
    
    // define simulation file
    sca_util::sca_trace_file* atf = sca_util::sca_create_tabular_trace_file("sim_trace.txt");

    // the following signals will be traced. Comment any signal you don't want to trace     
    sca_util::sca_trace(atf, i_tot_sc, "i_tot_sc" );
    sca_util::sca_trace(atf, i_sc, "i_sc" );
    sca_util::sca_trace(atf, v_sc, "v_sc" );
    sca_util::sca_trace(atf, e_sc, "e_sc" );
    sca_util::sca_trace(atf, soc_sc, "soc_sc" );

    cout<<"The simulation starts!"<<endl;

    sc_start(SIM_LEN, sc_core::SC_SEC); // Set the simulation length

    cout<<"The simulation ends @ "<<sc_time_stamp()<<endl;

    sca_util::sca_close_tabular_trace_file(atf);

    return 0;
}
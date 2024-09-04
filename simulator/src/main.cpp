#include <systemc-ams.h>

#include "battery.h"
#include "bus.h"
#include "converter_battery.h"
#include "converter_pv.h"
#include "mcu.h"
#include "pv_panel.h"
#include "rf.h"
#include "air_quality_sensor.h"
#include "methane_sensor.h"
#include "temperature_sensor.h"
#include "mic_click_sensor.h"
#include "supercap.h"
#include "supercap_converter.h"

int sc_main(int argc, char* argv[])
{
    // Instantiate signals
    sca_tdf::sca_signal<double> i_batt, v_batt, soc;
    sca_tdf::sca_signal<double> i_air_quality_sensor;
    sca_tdf::sca_signal<double> i_methane_sensor; 
    sca_tdf::sca_signal<double> i_temperature_sensor; 
    sca_tdf::sca_signal<double> i_mic_click_sensor;  
    sca_tdf::sca_signal<double> i_mcu;
    sca_tdf::sca_signal<double> i_rf;
    sca_tdf::sca_signal<double> v_pv1, i_pv1, real_i_pv1;
    sca_tdf::sca_signal<double> i_tot_batt, i_tot_sc;

    sca_tdf::sca_signal<double> i_supercap, v_supercap, e_supercap, soc_supercap;


    // Instantiate modules
    bus bus("bus");
    battery battery("battery");
    converter_battery converter_battery("converter_battery");
    pv_panel pv_panel1("pv_panel1");
    converter_pv conv_pv1("converter_pv1");
    mcu mcu("mcu");
    rf rf("rf");
    air_quality_sensor air_quality_sensor("air_quality_sensor");
    methane_sensor methane_sensor("methane_sensor");
    temperature_sensor temperature_sensor("temperature_sensor");
    mic_click_sensor mic_click_sensor("mic_click_sensor");

    supercap supercap_module("supercap");
    supercap_converter supercap_converter_module("supercap_converter");

    supercap_converter_module.pI_bus(i_tot_sc);
    supercap_converter_module.pI_sc(i_supercap);

    supercap_module.pI_in(i_supercap);
    supercap_module.pV_out(v_supercap);
    supercap_module.pE_out(e_supercap);
    supercap_module.pSoC_out(soc_supercap);

    // Connect signals to modules
    battery.i_batt(i_batt);
    battery.v_batt(v_batt);
    battery.soc(soc);

    converter_battery.i_bus(i_tot_batt);
    converter_battery.v_batt(v_batt);
    converter_battery.i_batt(i_batt);

    pv_panel1.i(i_pv1);
    pv_panel1.v(v_pv1);
    
    conv_pv1.i_in(i_pv1);
    conv_pv1.v_in(v_pv1);
    conv_pv1.i_out(real_i_pv1);
    
    air_quality_sensor.i(i_air_quality_sensor);
    methane_sensor.i(i_methane_sensor);
    temperature_sensor.i(i_temperature_sensor);
    mic_click_sensor.i(i_mic_click_sensor);

    mcu.i(i_mcu);
    
    rf.i(i_rf);

    bus.i_mcu(i_mcu);
    bus.i_rf(i_rf);
    bus.real_i_pv1(real_i_pv1);
    bus.i_tot_batt(i_tot_batt);
    bus.i_tot_sc(i_tot_sc);
    bus.i_air_quality_sensor(i_air_quality_sensor);
    bus.i_methane_sensor(i_methane_sensor);
    bus.i_temperature_sensor(i_temperature_sensor);
    bus.i_mic_click_sensor(i_mic_click_sensor);
    bus.soc_battery(soc);
    bus.soc_supercap(soc_supercap);

    // define simulation file
    sca_util::sca_trace_file* atf = sca_util::sca_create_tabular_trace_file("sim_trace.txt");

    // the following signals will be traced. Comment any signal you don't want to trace
    sca_util::sca_trace(atf, real_i_pv1, "real_i_pv1" );
    sca_util::sca_trace(atf, i_tot_batt, "Requested I batt |");    
    sca_util::sca_trace(atf, i_tot_sc, "Requested I SC |" );
    sca_util::sca_trace(atf, i_supercap, "Actual I SC (A) |");
    sca_util::sca_trace(atf, v_supercap, "V SC |" );
    sca_util::sca_trace(atf, soc_supercap, "SoC SC |" );
    sca_util::sca_trace(atf, soc, "SoC Batt |");

    cout<<"The simulation starts!"<<endl;

    sc_start(SIM_LEN, sc_core::SC_SEC); // Set the simulation length

    cout<<"The simulation ends @ "<<sc_time_stamp()<<endl;

    sca_util::sca_close_tabular_trace_file(atf);

    return 0;
}
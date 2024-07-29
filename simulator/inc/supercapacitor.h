#ifndef SUPERCAPACITOR_H
#define SUPERCAPACITOR_H

#include <systemc-ams.h>


SC_MODULE(supercapacitor_eln)
{
    // Interface and internal components declaration
    sca_tdf::sca_in<double> I; // Requested supercapacitor current
    sca_tdf::sca_out<double> V; // Provided supercapacitor voltage

    // transformers bw ELN and TDF
    sca_eln::sca_tdf::sca_isource iin;
    sca_eln::sca_tdf::sca_vsink vout;

    sca_eln::sca_c C_sc; // Capacitance (for supercap)
    sca_eln::sca_r R_l; // Leakage resistance
    sca_eln::sca_r R_s; // Series resistance

    // Constructor
    supercapacitor_eln( 
        sc_core::sc_module_name nm,
        double C_val = 3,
        double Rl_val = 500000,
        double Rs_val = 0.08
    );

    // internal node and ref node
    private:
        sca_eln::sca_node node_top, node_mid;
        sca_eln::sca_node_ref gnd;

};

SC_MODULE(supercapacitor)
{
    // component values
    const double C = 3; // Capacitance (F)
    const double Rl = 500000; // Leakage resistance (Ohm)
    const double Rs = 0.08; // Series resistance (Ohm)

    sca_tdf::sca_in<double> i; //incoming current
    sca_tdf::sca_out<double> v; //outgoing voltage
    sca_tdf::sca_out<double> e; //current energy
    sca_tdf::sca_out<double> soc; //state of charge

    supercapacitor_eln supercapacitor_eln_inst("supercapacitor_eln_inst", C, Rl, Rs);

    // Constructor
    supercapacitor(sc_core::sc_module_name nm):
        i("i"),
        v("v"),
        e("e"),
        soc("soc")
    {
        supercapacitor_eln_inst.I(i);
        supercapacitor_eln_inst.V(v);
    }
    
    void set_attributes();
    void initialize();
    void processing();

}

#endif // SUPERCAPACITOR_H
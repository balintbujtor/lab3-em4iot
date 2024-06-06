#ifndef SUPERCAPACITOR_H
#define SUPERCAPACITOR_H

#include <systemc-ams.h>


SC_MODULE(supercapacitor)
{
    // Interface and internal components declaration
    sca_tdf::sca_in<double> in; // Requested supercapacitor current
    sca_tdf::sca_out<double> out; // Provided supercapacitor voltage

    // transformers bw ELN and TDF
    sca_eln::sca_tdf::sca_isource iin;
    sca_eln::sca_tdf::sca_vsink vout;

    sca_eln::sca_c C_sc; // Capacitance (for supercap)
    sca_eln::sca_r R_l; // Leakage resistance
    sca_eln::sca_r R_s; // Series resistance

    // component values
    const double C = 3; // Capacitance (F)
    const double Rl = 500000; // Leakage resistance (Ohm)
    const double Rs = 0.08; // Series resistance (Ohm)

    // Constructor
    supercapacitor( 
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

#endif // SUPERCAPACITOR_H
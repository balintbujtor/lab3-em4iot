#ifndef SUPERCAP_ELN_H
#define SUPERCAP_ELN_H

#include <systemc-ams.h>
#include "config.h"


SC_MODULE(supercap_eln)
{
    public:
        // Interface and internal components declaration
        sca_tdf::sca_in<double> pI_in; // Requested supercapacitor current
        sca_tdf::sca_out<double> pV_out; // Provided supercapacitor voltage

        // transformers bw ELN and TDF
        sca_eln::sca_tdf::sca_isource iin;
        sca_eln::sca_tdf::sca_vsink vout;

        // ELN components
        sca_eln::sca_c C_sc; // Capacitance (for supercap)
        sca_eln::sca_r R_l; // Leakage resistance
        sca_eln::sca_r R_s; // Series resistance

        // Constructor
        supercap_eln( sc_core::sc_module_name nm, double c_par, double r_l_par, double r_s_par, double v_max_par):
            pI_in("pI_in"),
            pV_out("pV_out"),
            iin("iin"),
            vout("vout"),
            MAX_V(v_max_par),
            C_sc("C_sc", c_par, c_par * v_max_par),
            R_l("R_l", r_l_par),
            R_s("R_s", r_s_par),
            node_top("node_top"),
            node_mid("node_mid"),
            gnd("gnd")
        {
            iin.inp(pI_in);
            iin.p(node_top);
            iin.n(gnd);

            vout.p(node_top);
            vout.n(gnd);
            vout.outp(pV_out);

            C_sc.p(node_top);
            C_sc.n(node_mid);

            R_l.p(node_top);
            R_l.n(node_mid);

            R_s.p(node_mid);
            R_s.n(gnd);

            cout << "Supercapacitor created, C:" << C_sc.value << ", R_l:" << R_l.value << ", R_s:" << R_s.value << endl;
        }

    private:
        const double MAX_V;

        // internal node and ref node
        sca_eln::sca_node node_top, node_mid;
        sca_eln::sca_node_ref gnd;
};

#endif
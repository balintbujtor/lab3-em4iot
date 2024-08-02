#include <systemc-ams.h>


class sc_eln : public sca_tdf::sca_module
{
    public:
        // Interface and internal components declaration
        sca_tdf::sca_in<double> pI_in; // Requested supercapacitor current
        sca_tdf::sca_out<double> pV_out; // Provided supercapacitor voltage

        // transformers bw ELN and TDF
        sca_eln::sca_tdf::sca_isource* iin;
        sca_eln::sca_tdf::sca_vsink* vout;

        // ELN components
        sca_eln::sca_c* C_sc; // Capacitance (for supercap)
        sca_eln::sca_r* R_l; // Leakage resistance
        sca_eln::sca_r* R_s; // Series resistance

        // internal node and ref node
        sca_eln::sca_node node_top, node_mid;
        sca_eln::sca_node_ref gnd;

        // Constructor
        sc_eln( sc_core::sc_module_name nm, double c_par, double r_l_par, double r_s_par):
            pI_in("pI_in"),
            pV_out("pV_out"),
            C_val(c_par),
            Rl_val(r_l_par),
            Rs_val(r_s_par)
        {
            iin = new sca_eln::sca_tdf::sca_isource("iin");
            iin->inp(pI_in);
            iin->p(node_top);
            iin->n(gnd);

            vout = new sca_eln::sca_tdf::sca_vsink("vout");
            vout->p(node_top);
            vout->n(gnd);
            vout->outp(pV_out);

            C_sc = new sca_eln::sca_c("C_sc", C_val);
            C_sc->p(node_top);
            C_sc->n(node_mid);

            R_l = new sca_eln::sca_r("R_l", Rl_val);
            R_l->p(node_top);
            R_l->n(node_mid);

            R_s = new sca_eln::sca_r("R_s", Rs_val);
            R_s->p(node_mid);
            R_s->n(gnd);
        }

    private:
        double C_val;
        double Rl_val;
        double Rs_val;
};
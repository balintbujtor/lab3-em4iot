#include <systemc-ams.h>
#include "sc_eln.h"
#include "sc_tdf.h"
#include "config.h"

SC_MODULE(supercapacitor)
{
    public:
        sca_tdf::sca_in<double> pI_in; // Battery current
        sca_tdf::sca_out<double> pV_out; // Voltage
        sca_tdf::sca_out<double> pE_out; // Energy
        sca_tdf::sca_out<double> pSoC_out; // State of Charge

        // connecting signals
        sca_tdf::sca_signal<double> sVoltage;

        sc_eln* eln_module;
        sc_tdf* tdf_module;

        supercapacitor( sc_core::sc_module_name nm, double c_par = 3.0, double r_l_par = 500000.0, double r_s_par = 0.08): 
                                pI_in("pI_in"),
                                pV_out("pV_out"),
                                pE_out("pE_out"),
                                pSoC_out("pSoC_out"),
                                eln_module(new sc_eln("eln_module", c_par, r_l_par, r_s_par)),
                                tdf_module(new sc_tdf("tdf_module", c_par))
        {
            //eln_module = new sc_eln('eln_module', c_val, r_l_val, r_s_val);
            //tdf_module = new sc_tdf('tdf_module', c_val);

            eln_module->pI_in(pI_in);
            eln_module->pV_out(sVoltage);

            tdf_module->pV_in(sVoltage);
            tdf_module->pV_out(pV_out);
            tdf_module->pE_out(pE_out);
            tdf_module->pSoC_out(pSoC_out);
        }

};


//TODO: test manually
//TODO: test with the simulator
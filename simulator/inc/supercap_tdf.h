#ifndef SUPERCAP_TDF_H
#define SUPERCAP_TDF_H

#include <systemc-ams.h>
#include "config.h"

SCA_TDF_MODULE(supercap_tdf)
{
    public:
        // Ports
        sca_tdf::sca_in<double> pV_in; //incoming voltage

        sca_tdf::sca_out<double> pV_out; //forwarded voltage
        sca_tdf::sca_out<double> pE_out; //current energy
        sca_tdf::sca_out<double> pSoC_out; //state of charge

        supercap_tdf( sc_core::sc_module_name nm, double c_par, double v_max_par): 
                                pV_in("pV_in"),
                                pV_out("pV_out"), 
                                pE_out("pE_out"),
                                pSoC_out("pSoC_out"),
                                C(c_par),
                                MAX_V(v_max_par),
                                MAX_E(0.5 * C * v_max_par * v_max_par),
                                SoC_val(SOC_INIT),
                                E_val(SoC_val * MAX_E) 
        {
            cout << "Supercapacitor TDF created, C:"<< C << ", max V:" << MAX_V << ", MAX_E:" << MAX_E << ", SoC:" << SoC_val << ", E:" << E_val << endl;

        }

        void set_attributes();
        void initialize();
        void processing();

    private:
        const double C;
        const double MAX_V;
        const double MAX_E;
        double SoC_val;
        double E_val;
};

#endif
#include <systemc-ams.h>
#include "config.h"

SC_MODULE(sc_tdf)
{
    public:
        // Ports
        sca_tdf::sca_in<double> pV_in; //incoming voltage

        sca_tdf::sca_out<double> pV_out; //forwarded voltage
        sca_tdf::sca_out<double> pE_out; //current energy
        sca_tdf::sca_out<double> pSoC_out; //state of charge

        sc_tdf( sc_core::sc_module_name nm, double c_par): 
                                pV_in("pV_in"),
                                pV_out("pV_out"), 
                                pE_out("pE_out"),
                                pSoC_out("pSoC_out"),
                                C(c_par),
                                MAX_E(0.5 * C * VREF_BUS * VREF_BUS),
                                SoC_val(SOC_INIT),
                                E_val(SoC_val * MAX_E) 
        {

        }

        void set_attributes();
        void initialize();
        void processing();

    private:
        const double C;
        const double MAX_E;
        double SoC_val;
        double E_val;
};

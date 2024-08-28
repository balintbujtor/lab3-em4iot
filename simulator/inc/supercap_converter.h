#include <systemc-ams.h>
#include "config.h"


SCA_TDF_MODULE(supercap_converter)
{
    sca_tdf::sca_in<double> pI_bus; // Current requested/delivered to supercapacitor
    sca_tdf::sca_out<double> pI_sc; // Supercapacitor current

    SCA_CTOR(supercap_converter): pI_bus("pI_bus"),
                            pI_sc("pI_sc") {};

    void set_attributes();
    void initialize();
    void processing();

    private:
        const double eta = 0.9; // Efficiency
        double i_bus_tmp;
        double v_sc_tmp;
};
#include <systemc-ams.h>
#include "config.h"


SCA_TDF_MODULE(converter_supercapacitor)
{
    sca_tdf::sca_in<double> i_bus; // Current requested/delivered to supercapacitor
    sca_tdf::sca_in<double> v_sc; //  Supercapacitor voltage
    sca_tdf::sca_out<double> i_sc; // Supercapacitor current

    SCA_CTOR(converter_supercapacitor): i_bus("i_bus"),
                                        v_sc("v_sc"),
                                        i_sc("i_sc") {};

    void set_attributes();
    void initialize();
    void processing();

    private:
        const double eta = 0.9; // Efficiency
        double i_bus_tmp;
        double v_sc_tmp;
};
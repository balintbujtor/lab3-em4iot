#include <math.h>
#include "converter_supercapacitor.h"


void converter_supercapacitor::set_attributes()
{
    i_sc.set_timestep(SIM_STEP, sc_core::SC_SEC);
    i_sc.set_delay(1);
}

void converter_supercapacitor::initialize() {}

void converter_supercapacitor::processing()
{
    // Read input quantities
    i_bus_tmp = i_bus.read();
    v_sc_tmp = v_sc.read();

    i_sc.write(i_bus_tmp * VREF_BUS / (eta * v_sc_tmp));
    // Read input quantities
    double E_tmp = 0.5 * 3 * v_sc_tmp * v_sc_tmp;
    double E_max = 0.5 * 3 * 2.7 * 2.7;

    cout << "E_tmp: " << E_tmp << " SOC: " << E_tmp / E_max << endl;

}
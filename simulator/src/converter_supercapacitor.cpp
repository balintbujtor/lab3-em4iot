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
    const double eta = 0.75; // Efficiency
    double i_bus_tmp;
    double v_sc_tmp;

    // Read input quantities
    i_bus_tmp = i_bus.read();
    v_sc_tmp = v_sc.read();

    // Avoid div by zero
    if (v_sc_tmp == 0)
    {
        v_sc_tmp = 2.7; //maybe has to be changed
    }

    i_sc.write(i_bus_tmp * VREF_BUS / (eta * v_sc_tmp));

#include <math.h>
#include "supercap_converter.h"


void supercap_converter::set_attributes()
{
    pI_sc.set_timestep(SIM_STEP, sc_core::SC_SEC);
}

void supercap_converter::initialize() {}

void supercap_converter::processing()
{
    // Read input quantities
    // div by 1000 because the bus requests in milliamper but the ELN module work in Amps
    i_bus_tmp = pI_bus.read() / 1000;

    pI_sc.write(i_bus_tmp / eta);

}
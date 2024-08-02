#include <math.h>
#include "sc_converter.h"


void sc_converter::set_attributes()
{
    pI_sc.set_timestep(SIM_STEP, sc_core::SC_SEC);
    pI_sc.set_delay(1);
}

void sc_converter::initialize() {}

void sc_converter::processing()
{
    // Read input quantities
    i_bus_tmp = pI_bus.read();
    v_sc_tmp = pV_sc.read();

    pI_sc.write(i_bus_tmp / eta);

    cout << "V: " << v_sc_tmp << endl;

}
#include "supercap_tdf.h"

void supercap_tdf::set_attributes()
{
    pE_out.set_timestep(SIM_STEP, sc_core::SC_SEC);
    pSoC_out.set_timestep(SIM_STEP, sc_core::SC_SEC);
    pV_out.set_timestep(SIM_STEP, sc_core::SC_SEC);

}

void supercap_tdf::initialize(){}

void supercap_tdf::processing()
{

    double tmp_v;

    tmp_v = pV_in.read();

    if(tmp_v <= 0)
    {
        cout << "ERROR: 0 or less voltage value" << " @" << sc_time_stamp() << "Value V=" << tmp_v << endl;
        sc_stop();
    }
    if(tmp_v > MAX_V)
    {
        //? if the voltage can be set from eln maybe this is not needed
        cout << "Voltage is greatar than maximum V of supercap" << " @" << sc_time_stamp() << "Value V=" << tmp_v << endl;
        tmp_v = MAX_V;
    }

    pV_out.write(tmp_v);

    E_val = 0.5 * C * tmp_v * tmp_v;
    
    pE_out.write(E_val);

    SoC_val = E_val / MAX_E;
    
    if(SoC_val <= 0.01)
    {
        cout << "SC SOC is less than or equal to 1%:" << " @" << sc_time_stamp() << endl;
        sc_stop();
    }

    pSoC_out.write(SoC_val);

}
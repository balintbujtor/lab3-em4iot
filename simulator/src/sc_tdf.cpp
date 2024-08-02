#include "sc_tdf.h"

void sc_tdf::set_attributes()
{
    pV_in.set_timestep(SIM_STEP, sc_core::SC_SEC);
    pE_out.set_timestep(SIM_STEP, sc_core::SC_SEC);
    pSoC_out.set_timestep(SIM_STEP, sc_core::SC_SEC);
    pV_out.set_timestep(SIM_STEP, sc_core::SC_SEC);

    pV_in.set_delay(1);
    pE_out.set_delay(1);
    pSoC_out.set_delay(1);
    pV_out.set_delay(1);
    // TODO: check if the delay is needed
}

void sc_tdf::initialize(){}
// TODO: check if the initialization is needed

void sc_tdf::processing()
{

    double tmp_v;

    tmp_v = pV_in.read();

    if(tmp_v <= 0)
    {
        cout << "ERROR: 0 or less voltage value" << " @" << sc_time_stamp() << "Value V=" << tmp_v << endl;
        sc_stop();
    }
    if(tmp_v > VREF_BUS)
    {
        cout << "Voltage is greatar than VREF_BUS" << " @" << sc_time_stamp() << "Value V=" << tmp_v << endl;
        tmp_v = VREF_BUS;
    }

    pV_out.write(tmp_v);

    E_val = 0.5 * C * tmp_v * tmp_v;
    
    pE_out.write(E_val);

    SoC_val = E_val / MAX_E;
    
    if(SoC_val <= 0.01)
    {
        cout << "SOC is less than or equal to 1%:" << " @" << sc_time_stamp() << endl;
        sc_stop();
    }

    pSoC_out.write(SoC_val);

}
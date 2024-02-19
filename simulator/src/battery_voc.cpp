#include "battery_voc.h"
#include <math.h>

void battery_voc::set_attributes()
{
    v_oc.set_timestep(SIM_STEP, sc_core::SC_SEC);
    r_s.set_timestep(SIM_STEP, sc_core::SC_SEC);
    soc.set_timestep(SIM_STEP, sc_core::SC_SEC);
    r_s.set_delay(1);
    soc.set_delay(1);
}

void battery_voc::initialize() {}

void battery_voc::processing()
{
    double tmpcurrent; // Battery current, if negative, the battery is charged 
    
    // Read input current
    tmpcurrent = i.read(); // Battery current, if negative, the battery is charged 

    /* 
    Compute actual state-of-charge solving the integral:
    SOC_t = SOC_{t-1} - \int^{t}_{-inf} i(\tau) / C d\tau
    */
    
    c_nom = 3200;
    tmpsoc -= (((tmpcurrent + prev_i_batt) * SIM_STEP) / (2 * 3600 * c_nom)); // 3600 * Cnom, mAh to mAs cause [sim step] = [s]
    prev_i_batt = tmpcurrent; // Update

    // Each instant the battery self-discharge a bit
    tmpsoc = (1.0 - SELFDISCH_FACTOR) * tmpsoc;

    // Output the battery SOC
    if(tmpsoc >= 1) // Not let the SOC overflow
    {
        soc.write(1);
        tmpsoc = 1;
    }
    else
    {
        soc.write(tmpsoc);
    }

    // SOC and battery Voc relationship
    //p1*x^3 + p2*x^2 + p3*x + p4
    v_oc.write(1.819*pow(tmpsoc,3) - 3.048*pow(tmpsoc,2) + 2.458*tmpsoc + 2.927);


    // SOC and battery internal resistance relationship
    // p1*x^3 + p2*x^2 + p3*x + p4
    r_s.write(2.832e-05*pow(tmpsoc,3) + 3.447e-05*pow(tmpsoc,2) - 0.0001233*tmpsoc + 0.0001255);

    // When the battery SOC decreases under 1%, the simulation stops.	
    if(tmpsoc <= 0.01)
    {
        cout << "SOC is less than or equal to 1%:" << " @" << sc_time_stamp() << endl;
        sc_stop();
    }
}

#include "supercapacitor.h"

supercapacitor::supercapacitor( 
    sc_core::sc_module_name nm,
    double C_val,
    double Rl_val,
    double Rs_val 
):
    I("I"),
    V("V"),
    iin("iin"),
    vout("vout"),
    C_sc("C_sc", C_val),
    R_l("R_l", Rl_val),
    R_s("R_s", Rs_val),
    node_top("node_top"),
    node_mid("node_mid"),
    gnd("gnd")

{
    // Connect the in and out interfaces
    iin.inp(I);
    iin.p(node_top);
    iin.n(gnd);

    vout.p(node_top);
    vout.n(gnd);
    vout.outp(V);

    // Connect the components
    C_sc.p(node_top);
    C_sc.n(node_mid);

    R_l.p(node_top);
    R_l.n(node_mid);

    R_s.p(node_mid);
    R_s.n(gnd);

}
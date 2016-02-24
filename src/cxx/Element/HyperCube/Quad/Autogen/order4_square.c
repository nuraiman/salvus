/******************************************************************************
 *                     Code generated with sympy 0.7.6.1                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                       This file is part of 'project'                       *
 ******************************************************************************/
#include "order4_square.h"
#include <math.h>

void interpolate_order4_square(double epsilon, double eta, double *out_5590410397267881018) {

   out_5590410397267881018[0] = 0.765625*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977);
   out_5590410397267881018[1] = -1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977);
   out_5590410397267881018[2] = 2.04166666666667*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977);
   out_5590410397267881018[3] = -1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977);
   out_5590410397267881018[4] = 0.765625*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977);
   out_5590410397267881018[5] = -1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0);
   out_5590410397267881018[6] = 4.16840277777778*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0);
   out_5590410397267881018[7] = -4.76388888888889*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0);
   out_5590410397267881018[8] = 4.16840277777778*epsilon*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0);
   out_5590410397267881018[9] = -1.78645833333333*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0);
   out_5590410397267881018[10] = 2.04166666666667*epsilon*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);
   out_5590410397267881018[11] = -4.76388888888889*epsilon*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);
   out_5590410397267881018[12] = 5.44444444444445*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);
   out_5590410397267881018[13] = -4.76388888888889*epsilon*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);
   out_5590410397267881018[14] = 2.04166666666667*epsilon*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);
   out_5590410397267881018[15] = -1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0);
   out_5590410397267881018[16] = 4.16840277777778*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0);
   out_5590410397267881018[17] = -4.76388888888889*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0);
   out_5590410397267881018[18] = 4.16840277777778*epsilon*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0);
   out_5590410397267881018[19] = -1.78645833333333*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0);
   out_5590410397267881018[20] = 0.765625*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);
   out_5590410397267881018[21] = -1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);
   out_5590410397267881018[22] = 2.04166666666667*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);
   out_5590410397267881018[23] = -1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);
   out_5590410397267881018[24] = 0.765625*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);

}

void interpolate_eps_derivative_order4_square(double epsilon, double eta, double *out_9048464668387216643) {

   out_9048464668387216643[0] = 0.765625*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) + 0.765625*epsilon*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) + 0.765625*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) + 0.765625*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977);
   out_9048464668387216643[1] = -1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) - 1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) - 1.78645833333333*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) - 1.78645833333333*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977);
   out_9048464668387216643[2] = 2.04166666666667*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) + 2.04166666666667*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) + 2.04166666666667*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) + 2.04166666666667*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977);
   out_9048464668387216643[3] = -1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) - 1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) - 1.78645833333333*epsilon*eta*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) - 1.78645833333333*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977);
   out_9048464668387216643[4] = 0.765625*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) + 0.765625*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) + 0.765625*epsilon*eta*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) + 0.765625*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977);
   out_9048464668387216643[5] = -1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0) - 1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0) - 1.78645833333333*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0) - 1.78645833333333*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0);
   out_9048464668387216643[6] = 4.16840277777778*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0) + 4.16840277777778*epsilon*eta*(epsilon - 1.0)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0) + 4.16840277777778*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0) + 4.16840277777778*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0);
   out_9048464668387216643[7] = -4.76388888888889*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0) - 4.76388888888889*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0) - 4.76388888888889*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0) - 4.76388888888889*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0);
   out_9048464668387216643[8] = 4.16840277777778*epsilon*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0) + 4.16840277777778*epsilon*eta*(epsilon - 1.0)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0) + 4.16840277777778*epsilon*eta*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0) + 4.16840277777778*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0);
   out_9048464668387216643[9] = -1.78645833333333*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0) - 1.78645833333333*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0) - 1.78645833333333*epsilon*eta*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0) - 1.78645833333333*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0);
   out_9048464668387216643[10] = 2.04166666666667*epsilon*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) + 2.04166666666667*epsilon*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) + 2.04166666666667*epsilon*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) + 2.04166666666667*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);
   out_9048464668387216643[11] = -4.76388888888889*epsilon*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) - 4.76388888888889*epsilon*(epsilon - 1.0)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) - 4.76388888888889*epsilon*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) - 4.76388888888889*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);
   out_9048464668387216643[12] = 5.44444444444445*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) + 5.44444444444445*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) + 5.44444444444445*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) + 5.44444444444445*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);
   out_9048464668387216643[13] = -4.76388888888889*epsilon*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) - 4.76388888888889*epsilon*(epsilon - 1.0)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) - 4.76388888888889*epsilon*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) - 4.76388888888889*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);
   out_9048464668387216643[14] = 2.04166666666667*epsilon*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) + 2.04166666666667*epsilon*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) + 2.04166666666667*epsilon*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) + 2.04166666666667*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);
   out_9048464668387216643[15] = -1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0) - 1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0) - 1.78645833333333*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0) - 1.78645833333333*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0);
   out_9048464668387216643[16] = 4.16840277777778*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0) + 4.16840277777778*epsilon*eta*(epsilon - 1.0)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0) + 4.16840277777778*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0) + 4.16840277777778*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0);
   out_9048464668387216643[17] = -4.76388888888889*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0) - 4.76388888888889*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0) - 4.76388888888889*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0) - 4.76388888888889*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0);
   out_9048464668387216643[18] = 4.16840277777778*epsilon*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0) + 4.16840277777778*epsilon*eta*(epsilon - 1.0)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0) + 4.16840277777778*epsilon*eta*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0) + 4.16840277777778*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0);
   out_9048464668387216643[19] = -1.78645833333333*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0) - 1.78645833333333*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0) - 1.78645833333333*epsilon*eta*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0) - 1.78645833333333*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0);
   out_9048464668387216643[20] = 0.765625*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) + 0.765625*epsilon*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) + 0.765625*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) + 0.765625*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);
   out_9048464668387216643[21] = -1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) - 1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) - 1.78645833333333*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) - 1.78645833333333*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);
   out_9048464668387216643[22] = 2.04166666666667*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) + 2.04166666666667*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) + 2.04166666666667*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) + 2.04166666666667*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);
   out_9048464668387216643[23] = -1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) - 1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) - 1.78645833333333*epsilon*eta*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) - 1.78645833333333*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);
   out_9048464668387216643[24] = 0.765625*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) + 0.765625*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) + 0.765625*epsilon*eta*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) + 0.765625*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);

}

void interpolate_eta_derivative_order4_square(double epsilon, double eta, double *out_6330729362090964521) {

   out_6330729362090964521[0] = 0.765625*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977) + 0.765625*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta + 0.654653670707977) + 0.765625*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 0.654653670707977)*(eta + 0.654653670707977) + 0.765625*epsilon*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977);
   out_6330729362090964521[1] = -1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977) - 1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977) - 1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) - 1.78645833333333*epsilon*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977);
   out_6330729362090964521[2] = 2.04166666666667*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977) + 2.04166666666667*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977) + 2.04166666666667*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) + 2.04166666666667*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977);
   out_6330729362090964521[3] = -1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977) - 1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977) - 1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) - 1.78645833333333*epsilon*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977);
   out_6330729362090964521[4] = 0.765625*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977) + 0.765625*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977) + 0.765625*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) + 0.765625*epsilon*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977);
   out_6330729362090964521[5] = -1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977) - 1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta + 1.0) - 1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 0.654653670707977)*(eta + 1.0) - 1.78645833333333*epsilon*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0);
   out_6330729362090964521[6] = 4.16840277777778*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977) + 4.16840277777778*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 1.0) + 4.16840277777778*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 1.0) + 4.16840277777778*epsilon*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0);
   out_6330729362090964521[7] = -4.76388888888889*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977) - 4.76388888888889*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 1.0) - 4.76388888888889*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 1.0) - 4.76388888888889*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0);
   out_6330729362090964521[8] = 4.16840277777778*epsilon*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977) + 4.16840277777778*epsilon*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 1.0) + 4.16840277777778*epsilon*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 1.0) + 4.16840277777778*epsilon*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0);
   out_6330729362090964521[9] = -1.78645833333333*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977) - 1.78645833333333*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 1.0) - 1.78645833333333*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 1.0) - 1.78645833333333*epsilon*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0);
   out_6330729362090964521[10] = 2.04166666666667*epsilon*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) + 2.04166666666667*epsilon*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0) + 2.04166666666667*epsilon*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0) + 2.04166666666667*epsilon*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);
   out_6330729362090964521[11] = -4.76388888888889*epsilon*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) - 4.76388888888889*epsilon*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0) - 4.76388888888889*epsilon*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0) - 4.76388888888889*epsilon*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);
   out_6330729362090964521[12] = 5.44444444444445*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) + 5.44444444444445*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0) + 5.44444444444445*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0) + 5.44444444444445*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);
   out_6330729362090964521[13] = -4.76388888888889*epsilon*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) - 4.76388888888889*epsilon*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0) - 4.76388888888889*epsilon*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0) - 4.76388888888889*epsilon*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);
   out_6330729362090964521[14] = 2.04166666666667*epsilon*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) + 2.04166666666667*epsilon*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta - 0.654653670707977)*(eta + 1.0) + 2.04166666666667*epsilon*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0) + 2.04166666666667*epsilon*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);
   out_6330729362090964521[15] = -1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta + 0.654653670707977) - 1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta + 1.0) - 1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) - 1.78645833333333*epsilon*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0);
   out_6330729362090964521[16] = 4.16840277777778*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977) + 4.16840277777778*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 1.0) + 4.16840277777778*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta + 0.654653670707977)*(eta + 1.0) + 4.16840277777778*epsilon*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0);
   out_6330729362090964521[17] = -4.76388888888889*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977) - 4.76388888888889*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 1.0) - 4.76388888888889*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta + 0.654653670707977)*(eta + 1.0) - 4.76388888888889*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0);
   out_6330729362090964521[18] = 4.16840277777778*epsilon*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977) + 4.16840277777778*epsilon*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 1.0) + 4.16840277777778*epsilon*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta + 0.654653670707977)*(eta + 1.0) + 4.16840277777778*epsilon*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0);
   out_6330729362090964521[19] = -1.78645833333333*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977) - 1.78645833333333*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 1.0) - 1.78645833333333*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta + 0.654653670707977)*(eta + 1.0) - 1.78645833333333*epsilon*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 1.0)*(eta + 0.654653670707977)*(eta + 1.0);
   out_6330729362090964521[20] = 0.765625*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 0.654653670707977)*(eta + 0.654653670707977) + 0.765625*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 0.654653670707977)*(eta + 1.0) + 0.765625*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0) + 0.765625*epsilon*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);
   out_6330729362090964521[21] = -1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) - 1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 1.0) - 1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta + 0.654653670707977)*(eta + 1.0) - 1.78645833333333*epsilon*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);
   out_6330729362090964521[22] = 2.04166666666667*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) + 2.04166666666667*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 1.0) + 2.04166666666667*eta*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta + 0.654653670707977)*(eta + 1.0) + 2.04166666666667*(epsilon - 1.0)*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);
   out_6330729362090964521[23] = -1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) - 1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 1.0) - 1.78645833333333*epsilon*eta*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta + 0.654653670707977)*(eta + 1.0) - 1.78645833333333*epsilon*(epsilon - 1.0)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);
   out_6330729362090964521[24] = 0.765625*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977) + 0.765625*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 1.0) + 0.765625*epsilon*eta*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta + 0.654653670707977)*(eta + 1.0) + 0.765625*epsilon*(epsilon - 0.654653670707977)*(epsilon + 0.654653670707977)*(epsilon + 1.0)*(eta - 0.654653670707977)*(eta + 0.654653670707977)*(eta + 1.0);

}

void closure_mapping_order4_square(int *out_100609879691116384) {

   out_100609879691116384[0] = 6;
   out_100609879691116384[1] = 11;
   out_100609879691116384[2] = 16;
   out_100609879691116384[3] = 7;
   out_100609879691116384[4] = 12;
   out_100609879691116384[5] = 17;
   out_100609879691116384[6] = 8;
   out_100609879691116384[7] = 13;
   out_100609879691116384[8] = 18;
   out_100609879691116384[9] = 9;
   out_100609879691116384[10] = 14;
   out_100609879691116384[11] = 19;
   out_100609879691116384[12] = 23;
   out_100609879691116384[13] = 22;
   out_100609879691116384[14] = 21;
   out_100609879691116384[15] = 15;
   out_100609879691116384[16] = 10;
   out_100609879691116384[17] = 5;
   out_100609879691116384[18] = 1;
   out_100609879691116384[19] = 2;
   out_100609879691116384[20] = 3;
   out_100609879691116384[21] = 4;
   out_100609879691116384[22] = 24;
   out_100609879691116384[23] = 20;
   out_100609879691116384[24] = 0;

}

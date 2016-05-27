/******************************************************************************
 *                      Code generated with sympy 0.7.6                       *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                       This file is part of 'Salvus'                        *
 ******************************************************************************/
#include "Element/Simplex/Autogen/p3_triangle.h"
#include <math.h>

void coordinates_p3_triangle_rn(double *out_3397332268056792470) {

   out_3397332268056792470[0] = -0.5853;
   out_3397332268056792470[1] = 0.1706;
   out_3397332268056792470[2] = -0.5853;
   out_3397332268056792470[3] = -0.413;
   out_3397332268056792470[4] = 0.413;
   out_3397332268056792470[5] = 0.413;
   out_3397332268056792470[6] = -0.413;
   out_3397332268056792470[7] = -1.0;
   out_3397332268056792470[8] = -1.0;
   out_3397332268056792470[9] = -1.0;
   out_3397332268056792470[10] = 1.0;
   out_3397332268056792470[11] = -1.0;

}

void coordinates_p3_triangle_sn(double *out_2167128771406464040) {

   out_2167128771406464040[0] = -0.5853;
   out_2167128771406464040[1] = -0.5853;
   out_2167128771406464040[2] = 0.1706;
   out_2167128771406464040[3] = -1.0;
   out_2167128771406464040[4] = -1.0;
   out_2167128771406464040[5] = -0.413;
   out_2167128771406464040[6] = 0.413;
   out_2167128771406464040[7] = 0.413;
   out_2167128771406464040[8] = -0.413;
   out_2167128771406464040[9] = -1.0;
   out_2167128771406464040[10] = -1.0;
   out_2167128771406464040[11] = 1.0;

}

void quadrature_weights_p3_triangle(double *out_1773045392417392299) {

   out_1773045392417392299[0] = (84*sqrt(7) + 294)/(400*sqrt(7) + 1280);
   out_1773045392417392299[1] = (84*sqrt(7) + 294)/(400*sqrt(7) + 1280);
   out_1773045392417392299[2] = (84*sqrt(7) + 294)/(400*sqrt(7) + 1280);
   out_1773045392417392299[3] = 2*sqrt(7)*pow(2 + sqrt(7), 4)/(9520*sqrt(7) + 25280);
   out_1773045392417392299[4] = 2*sqrt(7)*pow(2 + sqrt(7), 4)/(9520*sqrt(7) + 25280);
   out_1773045392417392299[5] = 2*sqrt(7)*pow(2 + sqrt(7), 4)/(9520*sqrt(7) + 25280);
   out_1773045392417392299[6] = 2*sqrt(7)*pow(2 + sqrt(7), 4)/(9520*sqrt(7) + 25280);
   out_1773045392417392299[7] = 2*sqrt(7)*pow(2 + sqrt(7), 4)/(9520*sqrt(7) + 25280);
   out_1773045392417392299[8] = 2*sqrt(7)*pow(2 + sqrt(7), 4)/(9520*sqrt(7) + 25280);
   out_1773045392417392299[9] = (1838*sqrt(7) + 4942)/(124080*sqrt(7) + 330960);
   out_1773045392417392299[10] = (1838*sqrt(7) + 4942)/(124080*sqrt(7) + 330960);
   out_1773045392417392299[11] = (1838*sqrt(7) + 4942)/(124080*sqrt(7) + 330960);

}

void dphi_dr_rsn_p3_triangle(double *out_8669386580824837528) {

   out_8669386580824837528[0] = 0.234192637493774;
   out_8669386580824837528[1] = 1.32292631300434;
   out_8669386580824837528[2] = -3.68594044175552e-14;
   out_8669386580824837528[3] = -1.33226762955019e-15;
   out_8669386580824837528[4] = -2.88657986402541e-15;
   out_8669386580824837528[5] = -0.390203015780592;
   out_8669386580824837528[6] = 0.0673464686156444;
   out_8669386580824837528[7] = 0.190103149653879;
   out_8669386580824837528[8] = -1.10145080847061;
   out_8669386580824837528[9] = -0.189001999965482;
   out_8669386580824837528[10] = -0.0669563722754837;
   out_8669386580824837528[11] = -0.0669563722754841;
   out_8669386580824837528[12] = -1.32292631300435;
   out_8669386580824837528[13] = -0.234192637493756;
   out_8669386580824837528[14] = -3.24185123190546e-14;
   out_8669386580824837528[15] = -5.77315972805081e-15;
   out_8669386580824837528[16] = -1.11022302462516e-15;
   out_8669386580824837528[17] = 1.10145080847061;
   out_8669386580824837528[18] = -0.190103149653899;
   out_8669386580824837528[19] = -0.0673464686156395;
   out_8669386580824837528[20] = 0.390203015780594;
   out_8669386580824837528[21] = 0.0669563722754893;
   out_8669386580824837528[22] = 0.189001999965489;
   out_8669386580824837528[23] = 0.0669563722754908;
   out_8669386580824837528[24] = -1.32292631300434;
   out_8669386580824837528[25] = 1.32292631300433;
   out_8669386580824837528[26] = 4.88498130835069e-15;
   out_8669386580824837528[27] = 0.457549484396227;
   out_8669386580824837528[28] = -0.457549484396241;
   out_8669386580824837528[29] = -0.190103149653912;
   out_8669386580824837528[30] = 1.1014508084706;
   out_8669386580824837528[31] = -1.10145080847061;
   out_8669386580824837528[32] = 0.190103149653899;
   out_8669386580824837528[33] = 1.26287869051112e-15;
   out_8669386580824837528[34] = 2.05391259555654e-15;
   out_8669386580824837528[35] = -4.9960036108132e-16;
   out_8669386580824837528[36] = 5.77315972805081e-15;
   out_8669386580824837528[37] = 3.10862446895044e-15;
   out_8669386580824837528[38] = -6.97220059464598e-14;
   out_8669386580824837528[39] = -0.214790323760068;
   out_8669386580824837528[40] = 1.21065375302663;
   out_8669386580824837528[41] = 6.66133814775094e-15;
   out_8669386580824837528[42] = 3.77475828372553e-15;
   out_8669386580824837528[43] = -1.79856129989275e-14;
   out_8669386580824837528[44] = -1.35447209004269e-14;
   out_8669386580824837528[45] = -0.703577512776825;
   out_8669386580824837528[46] = -0.292285916489729;
   out_8669386580824837528[47] = 7.66053886991358e-15;
   out_8669386580824837528[48] = 9.32587340685131e-15;
   out_8669386580824837528[49] = 6.66133814775094e-15;
   out_8669386580824837528[50] = -7.14983627858601e-14;
   out_8669386580824837528[51] = -1.21065375302665;
   out_8669386580824837528[52] = 0.214790323760075;
   out_8669386580824837528[53] = 1.37667655053519e-14;
   out_8669386580824837528[54] = -5.10702591327572e-15;
   out_8669386580824837528[55] = 1.3988810110277e-14;
   out_8669386580824837528[56] = 1.66533453693773e-14;
   out_8669386580824837528[57] = 0.292285916489739;
   out_8669386580824837528[58] = 0.703577512776835;
   out_8669386580824837528[59] = 9.99200722162641e-16;
   out_8669386580824837528[60] = 2.26033787672902;
   out_8669386580824837528[61] = -5.44127152722104;
   out_8669386580824837528[62] = -0.939127601062011;
   out_8669386580824837528[63] = -0.428966864153795;
   out_8669386580824837528[64] = 0.781841062294105;
   out_8669386580824837528[65] = 4.15155406736436;
   out_8669386580824837528[66] = -0.178195490899103;
   out_8669386580824837528[67] = 0.428966864153786;
   out_8669386580824837528[68] = -0.78175093685464;
   out_8669386580824837528[69] = 1.30451205393456e-15;
   out_8669386580824837528[70] = 0.103581766327251;
   out_8669386580824837528[71] = 0.0430307833220793;
   out_8669386580824837528[72] = 2.26033787672902;
   out_8669386580824837528[73] = -0.939127601062004;
   out_8669386580824837528[74] = -5.44127152722104;
   out_8669386580824837528[75] = -0.781750936854656;
   out_8669386580824837528[76] = 0.428966864153778;
   out_8669386580824837528[77] = 1.03245826212752;
   out_8669386580824837528[78] = 3.93676374360428;
   out_8669386580824837528[79] = 0.781841062294102;
   out_8669386580824837528[80] = -0.428966864153782;
   out_8669386580824837528[81] = 1.0547118733939e-15;
   out_8669386580824837528[82] = -0.249255133167659;
   out_8669386580824837528[83] = -0.599995746449582;
   out_8669386580824837528[84] = 0.939127601062052;
   out_8669386580824837528[85] = -2.26033787672907;
   out_8669386580824837528[86] = 5.44127152722106;
   out_8669386580824837528[87] = -0.428966864153803;
   out_8669386580824837528[88] = 0.78175093685463;
   out_8669386580824837528[89] = 0.428966864153744;
   out_8669386580824837528[90] = -0.781841062294102;
   out_8669386580824837528[91] = -3.93676374360427;
   out_8669386580824837528[92] = -1.03245826212753;
   out_8669386580824837528[93] = 0.249255133167663;
   out_8669386580824837528[94] = 6.21724893790088e-15;
   out_8669386580824837528[95] = 0.599995746449579;
   out_8669386580824837528[96] = 5.44127152722107;
   out_8669386580824837528[97] = -2.26033787672906;
   out_8669386580824837528[98] = 0.939127601061963;
   out_8669386580824837528[99] = -0.781841062294108;
   out_8669386580824837528[100] = 0.428966864153786;
   out_8669386580824837528[101] = 0.78175093685463;
   out_8669386580824837528[102] = -0.428966864153778;
   out_8669386580824837528[103] = 0.178195490899075;
   out_8669386580824837528[104] = -4.15155406736435;
   out_8669386580824837528[105] = -0.103581766327242;
   out_8669386580824837528[106] = 6.82787160144471e-15;
   out_8669386580824837528[107] = -0.0430307833220734;
   out_8669386580824837528[108] = 3.99680288865056e-15;
   out_8669386580824837528[109] = 1.33226762955019e-15;
   out_8669386580824837528[110] = -6.26165785888588e-14;
   out_8669386580824837528[111] = 4.12488501883008;
   out_8669386580824837528[112] = -1.71359342254299;
   out_8669386580824837528[113] = 1.33226762955019e-15;
   out_8669386580824837528[114] = 9.99200722162641e-15;
   out_8669386580824837528[115] = -5.08482145278322e-14;
   out_8669386580824837528[116] = -3.66373598126302e-14;
   out_8669386580824837528[117] = -2.91129159628708;
   out_8669386580824837528[118] = 0.500000000000013;
   out_8669386580824837528[119] = 1.32116539930394e-14;
   out_8669386580824837528[120] = 1.11022302462516e-14;
   out_8669386580824837528[121] = 8.43769498715119e-15;
   out_8669386580824837528[122] = -6.61692922676593e-14;
   out_8669386580824837528[123] = 1.71359342254296;
   out_8669386580824837528[124] = -4.12488501883006;
   out_8669386580824837528[125] = 1.90958360235527e-14;
   out_8669386580824837528[126] = -1.04360964314765e-14;
   out_8669386580824837528[127] = 2.90878432451791e-14;
   out_8669386580824837528[128] = 3.97459842815806e-14;
   out_8669386580824837528[129] = -0.499999999999994;
   out_8669386580824837528[130] = 2.91129159628709;
   out_8669386580824837528[131] = -3.21964677141295e-15;
   out_8669386580824837528[132] = 7.32747196252603e-14;
   out_8669386580824837528[133] = 1.33226762955019e-15;
   out_8669386580824837528[134] = 4.75175454539567e-14;
   out_8669386580824837528[135] = -5.81756864903582e-14;
   out_8669386580824837528[136] = -2.33146835171283e-14;
   out_8669386580824837528[137] = -1.71359342254306;
   out_8669386580824837528[138] = 4.12488501883009;
   out_8669386580824837528[139] = -4.12488501883007;
   out_8669386580824837528[140] = 1.713593422543;
   out_8669386580824837528[141] = -0.499999999999998;
   out_8669386580824837528[142] = 0.500000000000011;
   out_8669386580824837528[143] = -3.44169137633799e-15;

}

void dphi_ds_rsn_p3_triangle(double *out_7436755633191263298) {

   out_7436755633191263298[0] = 0.234192637493772;
   out_7436755633191263298[1] = -2.66453525910038e-14;
   out_7436755633191263298[2] = 1.32292631300435;
   out_7436755633191263298[3] = -1.10145080847061;
   out_7436755633191263298[4] = 0.190103149653906;
   out_7436755633191263298[5] = 0.0673464686156466;
   out_7436755633191263298[6] = -0.390203015780609;
   out_7436755633191263298[7] = 2.88657986402541e-15;
   out_7436755633191263298[8] = 4.66293670342566e-15;
   out_7436755633191263298[9] = -0.189001999965485;
   out_7436755633191263298[10] = -0.0669563722754877;
   out_7436755633191263298[11] = -0.0669563722754838;
   out_7436755633191263298[12] = -1.32292631300434;
   out_7436755633191263298[13] = 1.55431223447522e-14;
   out_7436755633191263298[14] = 1.32292631300434;
   out_7436755633191263298[15] = 0.190103149653894;
   out_7436755633191263298[16] = -1.10145080847062;
   out_7436755633191263298[17] = 1.1014508084706;
   out_7436755633191263298[18] = -0.19010314965392;
   out_7436755633191263298[19] = -0.45754948439624;
   out_7436755633191263298[20] = 0.457549484396232;
   out_7436755633191263298[21] = -1.49880108324396e-15;
   out_7436755633191263298[22] = -2.77555756156289e-16;
   out_7436755633191263298[23] = 1.99840144432528e-15;
   out_7436755633191263298[24] = -1.32292631300436;
   out_7436755633191263298[25] = -2.1316282072803e-14;
   out_7436755633191263298[26] = -0.234192637493746;
   out_7436755633191263298[27] = 0.390203015780592;
   out_7436755633191263298[28] = -0.0673464686156493;
   out_7436755633191263298[29] = -0.190103149653891;
   out_7436755633191263298[30] = 1.1014508084706;
   out_7436755633191263298[31] = -2.22044604925031e-15;
   out_7436755633191263298[32] = -2.66453525910038e-15;
   out_7436755633191263298[33] = 0.0669563722754889;
   out_7436755633191263298[34] = 0.0669563722754905;
   out_7436755633191263298[35] = 0.189001999965488;
   out_7436755633191263298[36] = 5.44127152722107;
   out_7436755633191263298[37] = 0.939127601061975;
   out_7436755633191263298[38] = -2.26033787672905;
   out_7436755633191263298[39] = -4.15155406736436;
   out_7436755633191263298[40] = 0.178195490899111;
   out_7436755633191263298[41] = -0.428966864153778;
   out_7436755633191263298[42] = 0.781750936854617;
   out_7436755633191263298[43] = 0.428966864153788;
   out_7436755633191263298[44] = -0.781841062294095;
   out_7436755633191263298[45] = -0.103581766327251;
   out_7436755633191263298[46] = -0.0430307833220779;
   out_7436755633191263298[47] = 6.66133814775094e-15;
   out_7436755633191263298[48] = 0.93912760106205;
   out_7436755633191263298[49] = 5.44127152722108;
   out_7436755633191263298[50] = -2.26033787672905;
   out_7436755633191263298[51] = -1.03245826212754;
   out_7436755633191263298[52] = -3.93676374360431;
   out_7436755633191263298[53] = -0.781841062294102;
   out_7436755633191263298[54] = 0.428966864153739;
   out_7436755633191263298[55] = 0.781750936854624;
   out_7436755633191263298[56] = -0.428966864153786;
   out_7436755633191263298[57] = 0.249255133167654;
   out_7436755633191263298[58] = 0.599995746449581;
   out_7436755633191263298[59] = 6.21724893790088e-15;
   out_7436755633191263298[60] = 2.26033787672902;
   out_7436755633191263298[61] = -5.44127152722103;
   out_7436755633191263298[62] = -0.939127601061995;
   out_7436755633191263298[63] = -0.428966864153788;
   out_7436755633191263298[64] = 0.781841062294088;
   out_7436755633191263298[65] = 3.93676374360428;
   out_7436755633191263298[66] = 1.03245826212752;
   out_7436755633191263298[67] = 0.428966864153775;
   out_7436755633191263298[68] = -0.78175093685465;
   out_7436755633191263298[69] = -2.4980018054066e-16;
   out_7436755633191263298[70] = -0.599995746449581;
   out_7436755633191263298[71] = -0.249255133167659;
   out_7436755633191263298[72] = 2.26033787672902;
   out_7436755633191263298[73] = -0.939127601062001;
   out_7436755633191263298[74] = -5.44127152722103;
   out_7436755633191263298[75] = -0.781750936854643;
   out_7436755633191263298[76] = 0.428966864153774;
   out_7436755633191263298[77] = -0.178195490899097;
   out_7436755633191263298[78] = 4.15155406736434;
   out_7436755633191263298[79] = 0.7818410622941;
   out_7436755633191263298[80] = -0.42896686415379;
   out_7436755633191263298[81] = -8.88178419700125e-16;
   out_7436755633191263298[82] = 0.0430307833220791;
   out_7436755633191263298[83] = 0.103581766327251;
   out_7436755633191263298[84] = 1.02140518265514e-14;
   out_7436755633191263298[85] = -5.99520433297585e-14;
   out_7436755633191263298[86] = 1.50990331349021e-14;
   out_7436755633191263298[87] = 1.4210854715202e-14;
   out_7436755633191263298[88] = -1.64313007644523e-14;
   out_7436755633191263298[89] = 1.17683640610267e-14;
   out_7436755633191263298[90] = -8.88178419700125e-15;
   out_7436755633191263298[91] = 0.214790323760066;
   out_7436755633191263298[92] = -1.21065375302665;
   out_7436755633191263298[93] = 0.292285916489737;
   out_7436755633191263298[94] = 3.33066907387547e-15;
   out_7436755633191263298[95] = 0.703577512776834;
   out_7436755633191263298[96] = 8.43769498715119e-15;
   out_7436755633191263298[97] = -5.95079541199084e-14;
   out_7436755633191263298[98] = 1.33226762955019e-14;
   out_7436755633191263298[99] = -1.68753899743024e-14;
   out_7436755633191263298[100] = 1.53210777398272e-14;
   out_7436755633191263298[101] = 1.06581410364015e-14;
   out_7436755633191263298[102] = -1.59872115546023e-14;
   out_7436755633191263298[103] = 1.21065375302664;
   out_7436755633191263298[104] = -0.214790323760065;
   out_7436755633191263298[105] = -0.703577512776827;
   out_7436755633191263298[106] = 3.33066907387547e-15;
   out_7436755633191263298[107] = -0.29228591648973;
   out_7436755633191263298[108] = 5.77315972805081e-15;
   out_7436755633191263298[109] = -5.55111512312578e-14;
   out_7436755633191263298[110] = 1.15463194561016e-14;
   out_7436755633191263298[111] = -3.77475828372553e-14;
   out_7436755633191263298[112] = 4.01900734914307e-14;
   out_7436755633191263298[113] = 1.08801856413265e-14;
   out_7436755633191263298[114] = -2.04281036531029e-14;
   out_7436755633191263298[115] = -1.71359342254298;
   out_7436755633191263298[116] = 4.12488501883009;
   out_7436755633191263298[117] = -2.91129159628708;
   out_7436755633191263298[118] = 4.10782519111308e-15;
   out_7436755633191263298[119] = 0.500000000000012;
   out_7436755633191263298[120] = 6.97220059464598e-14;
   out_7436755633191263298[121] = 5.6399329650958e-14;
   out_7436755633191263298[122] = 7.99360577730113e-15;
   out_7436755633191263298[123] = 1.71359342254298;
   out_7436755633191263298[124] = -4.12488501883016;
   out_7436755633191263298[125] = 4.12488501883009;
   out_7436755633191263298[126] = -1.71359342254306;
   out_7436755633191263298[127] = -3.75255382323303e-14;
   out_7436755633191263298[128] = -2.59792187762287e-14;
   out_7436755633191263298[129] = -0.500000000000007;
   out_7436755633191263298[130] = 3.88578058618805e-15;
   out_7436755633191263298[131] = 0.500000000000012;
   out_7436755633191263298[132] = 1.28785870856518e-14;
   out_7436755633191263298[133] = -5.32907051820075e-14;
   out_7436755633191263298[134] = 1.86517468137026e-14;
   out_7436755633191263298[135] = 3.86357612569554e-14;
   out_7436755633191263298[136] = -4.01900734914307e-14;
   out_7436755633191263298[137] = 1.15463194561016e-14;
   out_7436755633191263298[138] = -2.66453525910038e-15;
   out_7436755633191263298[139] = -4.12488501883009;
   out_7436755633191263298[140] = 1.71359342254297;
   out_7436755633191263298[141] = -0.500000000000005;
   out_7436755633191263298[142] = 4.21884749357559e-15;
   out_7436755633191263298[143] = 2.91129159628709;

}

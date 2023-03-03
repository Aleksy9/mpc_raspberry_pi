/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: state_update_3D_model.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "state_update_3D_model.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const double states[16]
 *                const double inputs[4]
 *                double statederiv[16]
 * Return Type  : void
 */
void state_deriv(const double states[16], const double inputs[4],
                 double statederiv[16])
{
  double T1;
  double T1_tmp;
  double T2;
  double T2_tmp;
  double absxk;
  double b_T1_tmp;
  double b_T2_tmp;
  double b_statederiv_tmp;
  double c_T1_tmp;
  double c_statederiv_tmp;
  double d_T1_tmp;
  double d_statederiv_tmp;
  double e_T1_tmp;
  double e_statederiv_tmp;
  double f_T1_tmp;
  double f_statederiv_tmp;
  double g_T1_tmp;
  double g_statederiv_tmp;
  double h_statederiv_tmp;
  double i_statederiv_tmp;
  double j_statederiv_tmp;
  double k_statederiv_tmp;
  double l_statederiv_tmp;
  double scale;
  double statederiv_tmp;
  double tempquat_idx_0;
  double tempquat_idx_1;
  double tempquat_idx_2;
  double v_e;
  /*  This function will simulate the dynamics of the tailsitter. An important
   */
  /*  note is the use of quaternions to represent the orientation of the */
  /*  tailsitter. If Euler angles are used, they will be derived from the */
  /*  quaternion. This is done to avoid singularities in the calculations. */
  /*  State = {x,y,z,vx,vy,vz,q0,qx,qy,qz,p,q,r,wx,wy,wz} */
  /*  Inputs = {T1,T2,at1,at2} */
  /*  wx,... are the wind velocity components */
  /*  Assign states */
  /*  Assign inputs  */
  /*  [m] Propeller Pitch */
  v_e = inputs[0] / 6.2831853071795862 * 0.127;
  /*          if inflow_vel <= 0 */
  /*              inflow_vel = 0; */
  /*          end */
  T1_tmp = 2.0 * states[7] * states[9];
  b_T1_tmp = states[3] - states[13];
  c_T1_tmp = states[4] - states[14];
  d_T1_tmp = states[6] * states[6];
  e_T1_tmp = states[7] * states[7];
  scale = states[8] * states[8];
  absxk = states[9] * states[9];
  f_T1_tmp = states[5] - states[15];
  g_T1_tmp =
      ((((d_T1_tmp + e_T1_tmp) - scale) - absxk) * b_T1_tmp +
       (2.0 * states[6] * states[9] + 2.0 * states[7] * states[8]) * c_T1_tmp) +
      (-2.0 * states[6] * states[8] + T1_tmp) * f_T1_tmp;
  T1_tmp = ((2.0 * states[6] * states[8] + T1_tmp) * b_T1_tmp +
            (-2.0 * states[6] * states[7] + 2.0 * states[8] * states[9]) *
                c_T1_tmp) +
           (((d_T1_tmp - e_T1_tmp) - scale) + absxk) * f_T1_tmp;
  d_T1_tmp = sin(inputs[2]);
  e_T1_tmp = cos(inputs[2]);
  T1 = ((5.0E-6 * (inputs[0] * inputs[0]) - 0.0008 * inputs[0]) + 0.1034) *
       (v_e - (e_T1_tmp * g_T1_tmp + d_T1_tmp * T1_tmp)) / v_e;
  /*          if omega_act <= 0.1 */
  /*              T_act = T_0; */
  /*          else  */
  /*              T_act = T_0 * (v_e-inflow_vel)/v_e; */
  /*          end */
  /*  [m] Propeller Pitch */
  v_e = inputs[1] / 6.2831853071795862 * 0.127;
  /*          if inflow_vel <= 0 */
  /*              inflow_vel = 0; */
  /*          end */
  T2_tmp = sin(inputs[3]);
  b_T2_tmp = cos(inputs[3]);
  T2 = ((5.0E-6 * (inputs[1] * inputs[1]) - 0.0008 * inputs[1]) + 0.1034) *
       (v_e - (b_T2_tmp * g_T1_tmp + T2_tmp * T1_tmp)) / v_e;
  /*          if omega_act <= 0.1 */
  /*              T_act = T_0; */
  /*          else  */
  /*              T_act = T_0 * (v_e-inflow_vel)/v_e; */
  /*          end */
  /*  Create required variables */
  /*  Normalise quaternion */
  scale = 3.3121686421112381E-170;
  absxk = fabs(states[6]);
  if (absxk > 3.3121686421112381E-170) {
    T1_tmp = 1.0;
    scale = absxk;
  } else {
    v_e = absxk / 3.3121686421112381E-170;
    T1_tmp = v_e * v_e;
  }
  absxk = fabs(states[7]);
  if (absxk > scale) {
    v_e = scale / absxk;
    T1_tmp = T1_tmp * v_e * v_e + 1.0;
    scale = absxk;
  } else {
    v_e = absxk / scale;
    T1_tmp += v_e * v_e;
  }
  absxk = fabs(states[8]);
  if (absxk > scale) {
    v_e = scale / absxk;
    T1_tmp = T1_tmp * v_e * v_e + 1.0;
    scale = absxk;
  } else {
    v_e = absxk / scale;
    T1_tmp += v_e * v_e;
  }
  absxk = fabs(states[9]);
  if (absxk > scale) {
    v_e = scale / absxk;
    T1_tmp = T1_tmp * v_e * v_e + 1.0;
    scale = absxk;
  } else {
    v_e = absxk / scale;
    T1_tmp += v_e * v_e;
  }
  T1_tmp = scale * sqrt(T1_tmp);
  tempquat_idx_0 = states[6] / T1_tmp;
  tempquat_idx_1 = states[7] / T1_tmp;
  tempquat_idx_2 = states[8] / T1_tmp;
  v_e = states[9] / T1_tmp;
  /*  State Derivatives calculations (Done symbolically in Maple and imported)
   */
  T1_tmp = tempquat_idx_0 * tempquat_idx_0;
  g_T1_tmp = tempquat_idx_1 * tempquat_idx_1;
  scale = tempquat_idx_2 * tempquat_idx_2;
  absxk = v_e * v_e;
  statederiv_tmp = ((T1_tmp + g_T1_tmp) - scale) - absxk;
  b_statederiv_tmp = 2.0 * tempquat_idx_1 * tempquat_idx_2;
  c_statederiv_tmp = -2.0 * tempquat_idx_0 * v_e + b_statederiv_tmp;
  d_statederiv_tmp = -states[3] + states[13];
  e_statederiv_tmp = -states[4] + states[14];
  f_statederiv_tmp = -states[5] + states[15];
  g_statederiv_tmp = 2.0 * tempquat_idx_1 * v_e;
  h_statederiv_tmp = 2.0 * tempquat_idx_0 * tempquat_idx_2 + g_statederiv_tmp;
  i_statederiv_tmp = 2.0 * tempquat_idx_2 * v_e;
  j_statederiv_tmp = T1_tmp - g_T1_tmp;
  b_statederiv_tmp += 2.0 * tempquat_idx_0 * v_e;
  T1_tmp = -2.0 * tempquat_idx_0 * tempquat_idx_2 + g_statederiv_tmp;
  g_statederiv_tmp = (statederiv_tmp * d_statederiv_tmp +
                      b_statederiv_tmp * e_statederiv_tmp) +
                     T1_tmp * f_statederiv_tmp;
  k_statederiv_tmp = (j_statederiv_tmp + scale) - absxk;
  g_T1_tmp = 2.0 * tempquat_idx_0 * tempquat_idx_1 + i_statederiv_tmp;
  l_statederiv_tmp = (c_statederiv_tmp * d_statederiv_tmp +
                      k_statederiv_tmp * e_statederiv_tmp) +
                     g_T1_tmp * f_statederiv_tmp;
  i_statederiv_tmp += -2.0 * tempquat_idx_0 * tempquat_idx_1;
  scale = (j_statederiv_tmp - scale) + absxk;
  d_statederiv_tmp = (h_statederiv_tmp * d_statederiv_tmp +
                      i_statederiv_tmp * e_statederiv_tmp) +
                     scale * f_statederiv_tmp;
  e_statederiv_tmp =
      sqrt((b_T1_tmp * b_T1_tmp + c_T1_tmp * c_T1_tmp) + f_T1_tmp * f_T1_tmp);
  f_statederiv_tmp = 0.15925000000000003 * e_statederiv_tmp;
  statederiv[3] =
      (0.78740157480314954 * statederiv_tmp *
           ((T1 * e_T1_tmp + T2 * b_T2_tmp) +
            f_statederiv_tmp * 0.05 * g_statederiv_tmp) +
       0.78740157480314954 * c_statederiv_tmp * 0.15925000000000003 *
           e_statederiv_tmp * 0.05 * l_statederiv_tmp) +
      0.78740157480314954 * h_statederiv_tmp *
          ((-T1 * d_T1_tmp - T2 * T2_tmp) +
           f_statederiv_tmp * 4.05 * d_statederiv_tmp);
  statederiv_tmp = (T1 * cos(inputs[2]) + T2 * cos(inputs[3])) +
                   0.15925000000000003 *
                       sqrt((b_T1_tmp * b_T1_tmp + c_T1_tmp * c_T1_tmp) +
                            f_T1_tmp * f_T1_tmp) *
                       0.05 * g_statederiv_tmp;
  c_statederiv_tmp = (-T1 * sin(inputs[2]) - T2 * sin(inputs[3])) +
                     0.15925000000000003 *
                         sqrt((b_T1_tmp * b_T1_tmp + c_T1_tmp * c_T1_tmp) +
                              f_T1_tmp * f_T1_tmp) *
                         4.05 * d_statederiv_tmp;
  statederiv[4] =
      (0.78740157480314954 * b_statederiv_tmp * statederiv_tmp +
       0.78740157480314954 * k_statederiv_tmp * 0.15925000000000003 *
           e_statederiv_tmp * 0.05 * l_statederiv_tmp) +
      0.78740157480314954 * i_statederiv_tmp * c_statederiv_tmp;
  statederiv[5] = ((0.78740157480314954 * T1_tmp * statederiv_tmp +
                    0.78740157480314954 * g_T1_tmp * 0.15925000000000003 *
                        e_statederiv_tmp * 0.05 * l_statederiv_tmp) +
                   0.78740157480314954 * scale * c_statederiv_tmp) +
                  9.81;
  statederiv[6] =
      (-tempquat_idx_1 * states[10] / 2.0 - tempquat_idx_2 * states[11] / 2.0) -
      v_e * states[12] / 2.0;
  statederiv[7] = (tempquat_idx_0 * states[10] / 2.0 - v_e * states[11] / 2.0) +
                  tempquat_idx_2 * states[12] / 2.0;
  statederiv[8] = (v_e * states[10] / 2.0 + tempquat_idx_0 * states[11] / 2.0) -
                  tempquat_idx_1 * states[12] / 2.0;
  statederiv[9] =
      (-tempquat_idx_2 * states[10] / 2.0 + tempquat_idx_1 * states[11] / 2.0) +
      tempquat_idx_0 * states[12] / 2.0;
  statederiv_tmp = 0.0 * e_statederiv_tmp;
  b_statederiv_tmp = statederiv_tmp * 0.05;
  statederiv[10] =
      15.384615384615383 * (((0.3 * T1 * d_T1_tmp - 0.3 * T2 * T2_tmp) +
                             statederiv_tmp * 4.05 * d_statederiv_tmp) -
                            b_statederiv_tmp * l_statederiv_tmp);
  statederiv_tmp = -0.0023887500000000002 * e_statederiv_tmp;
  b_statederiv_tmp *= g_statederiv_tmp;
  statederiv[11] =
      111.11111111111111 *
      (((((0.135 * T1 * d_T1_tmp + 0.0 * T1 * e_T1_tmp) + 0.135 * T2 * T2_tmp) +
         0.0 * T2 * b_T2_tmp) -
        statederiv_tmp * 4.05 * d_statederiv_tmp) +
       b_statederiv_tmp);
  statederiv[12] =
      15.105740181268883 * (((0.3 * T1 * e_T1_tmp - 0.3 * T2 * b_T2_tmp) +
                             statederiv_tmp * 0.05 * l_statederiv_tmp) -
                            b_statederiv_tmp);
  statederiv[0] = states[3];
  statederiv[1] = states[4];
  statederiv[2] = states[5];
  statederiv[13] = 0.0;
  statederiv[14] = 0.0;
  statederiv[15] = 0.0;
  /*      fyb = qdyn * sqrt((vx - wx) ^ 2 + (vy - wy) ^ 2 + (vz - wz) ^ 2) * Cy0
   * * ((-2 * q0 * qz + 2 * qx * qy) * (-vx + wx) + (q0 ^ 2 - qx ^ 2 + qy ^ 2 -
   * qz ^ 2) * (-vy + wy) + (2 * q0 * qx + 2 * qy * qz) * (-vz + wz)); */
}

/*
 * File trailer for state_update_3D_model.c
 *
 * [EOF]
 */

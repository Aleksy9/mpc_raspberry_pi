/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: cost_fct_3D_model.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "cost_fct_3D_model.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * UNTITLED Summary of this function goes here
 *    Detailed explanation goes here
 *
 * Arguments    : const double X[176]
 *                const double data_References[160]
 * Return Type  : double
 */
double cost_fct_3D_model(const double X[176], const double data_References[160])
{
  double y[10];
  double b_y;
  double c_y;
  double d_y;
  double e_y;
  double f_y;
  double varargin_1;
  int k;
  /*  U1 = U(2:p+1,data.MVIndex(1)); */
  /*  U2 = U(2:p+1,data.MVIndex(2)); */
  /*  disp(U1) */
  /*  disp(U2) */
  for (k = 0; k < 10; k++) {
    varargin_1 = data_References[k + 30] - X[k + 34];
    y[k] = varargin_1 * varargin_1;
  }
  b_y = y[0];
  for (k = 0; k < 9; k++) {
    b_y += y[k + 1];
  }
  for (k = 0; k < 10; k++) {
    varargin_1 = data_References[k + 40] - X[k + 45];
    y[k] = varargin_1 * varargin_1;
  }
  c_y = y[0];
  for (k = 0; k < 9; k++) {
    c_y += y[k + 1];
  }
  for (k = 0; k < 10; k++) {
    varargin_1 = data_References[k + 50] - X[k + 56];
    y[k] = varargin_1 * varargin_1;
  }
  d_y = y[0];
  for (k = 0; k < 9; k++) {
    d_y += y[k + 1];
  }
  for (k = 0; k < 10; k++) {
    varargin_1 = X[k + 111];
    y[k] = varargin_1 * varargin_1;
  }
  e_y = y[0];
  for (k = 0; k < 9; k++) {
    e_y += y[k + 1];
  }
  for (k = 0; k < 10; k++) {
    varargin_1 = X[k + 122];
    y[k] = varargin_1 * varargin_1;
  }
  f_y = y[0];
  for (k = 0; k < 9; k++) {
    f_y += y[k + 1];
  }
  for (k = 0; k < 10; k++) {
    varargin_1 = X[k + 133];
    y[k] = varargin_1 * varargin_1;
  }
  varargin_1 = y[0];
  for (k = 0; k < 9; k++) {
    varargin_1 += y[k + 1];
  }
  return ((((1000.0 * b_y + 1000.0 * c_y) + 1000.0 * d_y) + 500.0 * e_y) +
          500.0 * f_y) +
         500.0 * varargin_1;
  /*      + gain_T*(sum(sum((T1).^2))+sum(sum((T2).^2))); */
  /*   */
  /*  disp("Vx") */
  /*  disp(sum(sum((ref4-X4).^2))) */
  /*  disp(ref4) */
  /*  disp(X4) */
  /*  disp(gain*sum(sum((ref4-X4).^2))) */
  /*  disp("Vy") */
  /*  disp(sum(sum((ref5-X5).^2))) */
  /*  disp(ref5) */
  /*  disp(X5) */
  /*  disp(gain*sum(sum((ref5-X5).^2))) */
  /*   */
  /*  disp("Vz") */
  /*  disp(sum(sum((ref6-X6).^2))) */
  /*  disp(ref6) */
  /*  disp(X6) */
  /*  disp(gain*sum(sum((ref6-X6).^2))) */
  /*  J = 0.01*sum(U1.^2) + 0.01*sum(U2.^2) ... */
  /*   + gain_alpha*(sum(sum((alpha_t1).^2))+sum(sum((alpha_t2).^2)))  */
  /*  J = 1*sum(sum((ref3-X3).^2)) + 1*sum(sum((ref4-X4).^2)); */
}

/*
 * File trailer for cost_fct_3D_model.c
 *
 * [EOF]
 */

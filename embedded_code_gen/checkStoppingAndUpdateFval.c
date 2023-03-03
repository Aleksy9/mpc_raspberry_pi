/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: checkStoppingAndUpdateFval.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "checkStoppingAndUpdateFval.h"
#include "computeFval_ReuseHx.h"
#include "feasibleX0ForWorkingSet.h"
#include "maxConstraintViolation.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : int *activeSetChangeID
 *                const double f_data[]
 *                c_struct_T *solution
 *                e_struct_T *memspace
 *                const d_struct_T *objective
 *                f_struct_T *workingset
 *                g_struct_T *qrmanager
 *                double options_ObjectiveLimit
 *                int runTimeOptions_MaxIterations
 *                bool updateFval
 * Return Type  : void
 */
void checkStoppingAndUpdateFval(int *activeSetChangeID, const double f_data[],
                                c_struct_T *solution, e_struct_T *memspace,
                                const d_struct_T *objective,
                                f_struct_T *workingset, g_struct_T *qrmanager,
                                double options_ObjectiveLimit,
                                int runTimeOptions_MaxIterations,
                                bool updateFval)
{
  double y_data[1803];
  solution->iterations++;
  if ((solution->iterations >= runTimeOptions_MaxIterations) &&
      ((solution->state != 1) || (objective->objtype == 5))) {
    solution->state = 0;
  }
  if (solution->iterations - solution->iterations / 50 * 50 == 0) {
    double tempMaxConstr;
    solution->maxConstr =
        maxConstraintViolation(workingset, solution->xstar.data);
    tempMaxConstr = solution->maxConstr;
    if (objective->objtype == 5) {
      tempMaxConstr =
          solution->maxConstr - solution->xstar.data[objective->nvar - 1];
    }
    if (tempMaxConstr > 1.0E-6) {
      int loop_ub;
      int y_size;
      bool nonDegenerateWset;
      y_size = solution->searchDir.size[0];
      loop_ub = solution->searchDir.size[0];
      if (loop_ub - 1 >= 0) {
        memcpy(&y_data[0], &solution->searchDir.data[0],
               (unsigned int)loop_ub * sizeof(double));
      }
      loop_ub = (unsigned short)objective->nvar;
      if (loop_ub - 1 >= 0) {
        memcpy(&y_data[0], &solution->xstar.data[0],
               (unsigned int)loop_ub * sizeof(double));
      }
      solution->searchDir.size[0] = y_size;
      if (y_size - 1 >= 0) {
        memcpy(&solution->searchDir.data[0], &y_data[0],
               (unsigned int)y_size * sizeof(double));
      }
      nonDegenerateWset = feasibleX0ForWorkingSet(
          memspace->workspace_double.data, memspace->workspace_double.size,
          solution->searchDir.data, workingset, qrmanager);
      if ((!nonDegenerateWset) && (solution->state != 0)) {
        solution->state = -2;
      }
      *activeSetChangeID = 0;
      tempMaxConstr =
          maxConstraintViolation(workingset, solution->searchDir.data);
      if (tempMaxConstr < solution->maxConstr) {
        if (loop_ub - 1 >= 0) {
          memcpy(&solution->xstar.data[0], &solution->searchDir.data[0],
                 (unsigned int)loop_ub * sizeof(double));
        }
        solution->maxConstr = tempMaxConstr;
      }
    }
  }
  if (updateFval && (options_ObjectiveLimit > rtMinusInf)) {
    solution->fstar =
        computeFval_ReuseHx(objective, memspace->workspace_double.data, f_data,
                            solution->xstar.data);
    if ((solution->fstar < options_ObjectiveLimit) &&
        ((solution->state != 0) || (objective->objtype != 5))) {
      solution->state = 2;
    }
  }
}

/*
 * File trailer for checkStoppingAndUpdateFval.c
 *
 * [EOF]
 */

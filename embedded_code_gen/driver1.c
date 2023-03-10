/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: driver1.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "driver1.h"
#include "PresolveWorkingSet.h"
#include "computeFval.h"
#include "iterate.h"
#include "maxConstraintViolation.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "phaseone.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const double H[32761]
 *                const double f_data[]
 *                c_struct_T *solution
 *                e_struct_T *memspace
 *                f_struct_T *workingset
 *                g_struct_T *qrmanager
 *                h_struct_T *cholmanager
 *                d_struct_T *objective
 *                m_struct_T *options
 *                m_struct_T *runTimeOptions
 * Return Type  : void
 */
void b_driver(const double H[32761], const double f_data[],
              c_struct_T *solution, e_struct_T *memspace,
              f_struct_T *workingset, g_struct_T *qrmanager,
              h_struct_T *cholmanager, d_struct_T *objective,
              m_struct_T *options, m_struct_T *runTimeOptions)
{
  double y_data[1803];
  int i;
  int idx;
  int nVar;
  bool guard1 = false;
  solution->iterations = 0;
  nVar = workingset->nVar;
  guard1 = false;
  if (workingset->probType == 3) {
    i = (unsigned short)workingset->sizes[0];
    for (idx = 0; idx < i; idx++) {
      solution->xstar.data[workingset->indexFixed.data[idx] - 1] =
          workingset->ub.data[workingset->indexFixed.data[idx] - 1];
    }
    i = (unsigned short)workingset->sizes[3];
    for (idx = 0; idx < i; idx++) {
      if (workingset->isActiveConstr
              .data[(workingset->isActiveIdx[3] + idx) - 1]) {
        solution->xstar.data[workingset->indexLB.data[idx] - 1] =
            -workingset->lb.data[workingset->indexLB.data[idx] - 1];
      }
    }
    i = (unsigned short)workingset->sizes[4];
    for (idx = 0; idx < i; idx++) {
      if (workingset->isActiveConstr
              .data[(workingset->isActiveIdx[4] + idx) - 1]) {
        solution->xstar.data[workingset->indexUB.data[idx] - 1] =
            workingset->ub.data[workingset->indexUB.data[idx] - 1];
      }
    }
    PresolveWorkingSet(solution, memspace, workingset, qrmanager);
    if (solution->state >= 0) {
      guard1 = true;
    }
  } else {
    solution->state = 82;
    guard1 = true;
  }
  if (guard1) {
    solution->iterations = 0;
    solution->maxConstr =
        maxConstraintViolation(workingset, solution->xstar.data);
    if (solution->maxConstr > 1.0E-6) {
      phaseone(H, f_data, solution, memspace, workingset, qrmanager,
               cholmanager, objective, options, runTimeOptions);
      if (solution->state != 0) {
        solution->maxConstr =
            maxConstraintViolation(workingset, solution->xstar.data);
        if (solution->maxConstr > 1.0E-6) {
          idx = workingset->mConstrMax;
          memset(&solution->lambda.data[0], 0,
                 (unsigned int)idx * sizeof(double));
          solution->fstar =
              computeFval(objective, memspace->workspace_double.data, H, f_data,
                          solution->xstar.data);
          solution->state = -2;
        } else {
          if (solution->maxConstr > 0.0) {
            double maxConstr_new;
            int loop_ub;
            idx = solution->searchDir.size[0];
            loop_ub = solution->searchDir.size[0];
            if (loop_ub - 1 >= 0) {
              memcpy(&y_data[0], &solution->searchDir.data[0],
                     (unsigned int)loop_ub * sizeof(double));
            }
            i = (unsigned short)nVar;
            if (i - 1 >= 0) {
              memcpy(&y_data[0], &solution->xstar.data[0],
                     (unsigned int)i * sizeof(double));
            }
            solution->searchDir.size[0] = idx;
            if (idx - 1 >= 0) {
              memcpy(&solution->searchDir.data[0], &y_data[0],
                     (unsigned int)idx * sizeof(double));
            }
            PresolveWorkingSet(solution, memspace, workingset, qrmanager);
            maxConstr_new =
                maxConstraintViolation(workingset, solution->xstar.data);
            if (maxConstr_new >= solution->maxConstr) {
              solution->maxConstr = maxConstr_new;
              idx = solution->xstar.size[0];
              loop_ub = solution->xstar.size[0];
              if (loop_ub - 1 >= 0) {
                memcpy(&y_data[0], &solution->xstar.data[0],
                       (unsigned int)loop_ub * sizeof(double));
              }
              if (i - 1 >= 0) {
                memcpy(&y_data[0], &solution->searchDir.data[0],
                       (unsigned int)i * sizeof(double));
              }
              solution->xstar.size[0] = idx;
              if (idx - 1 >= 0) {
                memcpy(&solution->xstar.data[0], &y_data[0],
                       (unsigned int)idx * sizeof(double));
              }
            }
          }
          iterate(H, f_data, solution, memspace, workingset, qrmanager,
                  cholmanager, objective, options->SolverName,
                  options->StepTolerance, options->ObjectiveLimit,
                  runTimeOptions->MaxIterations);
        }
      }
    } else {
      iterate(H, f_data, solution, memspace, workingset, qrmanager, cholmanager,
              objective, options->SolverName, options->StepTolerance,
              options->ObjectiveLimit, runTimeOptions->MaxIterations);
    }
  }
}

/*
 * File trailer for driver1.c
 *
 * [EOF]
 */

/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: phaseone.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

/* Include Files */
#include "phaseone.h"
#include "computeFval.h"
#include "iterate.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "removeConstr.h"
#include "rt_nonfinite.h"
#include "setProblemType.h"
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
 *                const m_struct_T *runTimeOptions
 * Return Type  : void
 */
void phaseone(const double H[32761], const double f_data[],
              c_struct_T *solution, e_struct_T *memspace,
              f_struct_T *workingset, g_struct_T *qrmanager,
              h_struct_T *cholmanager, d_struct_T *objective,
              m_struct_T *options, const m_struct_T *runTimeOptions)
{
  int PROBTYPE_ORIG;
  int idxStartIneq;
  int idx_global;
  int mEqFixed;
  int nVar_tmp;
  PROBTYPE_ORIG = workingset->probType;
  nVar_tmp = workingset->nVar;
  solution->xstar.data[workingset->nVar] = solution->maxConstr + 1.0;
  if (workingset->probType == 3) {
    idxStartIneq = 1;
  } else {
    idxStartIneq = 4;
  }
  setProblemType(workingset, idxStartIneq);
  idxStartIneq = (workingset->nWConstr[0] + workingset->nWConstr[1]) + 1;
  mEqFixed = workingset->nActiveConstr;
  for (idx_global = idxStartIneq; idx_global <= mEqFixed; idx_global++) {
    workingset->isActiveConstr.data
        [(workingset->isActiveIdx[workingset->Wid.data[idx_global - 1] - 1] +
          workingset->Wlocalidx.data[idx_global - 1]) -
         2] = false;
  }
  workingset->nWConstr[2] = 0;
  workingset->nWConstr[3] = 0;
  workingset->nWConstr[4] = 0;
  workingset->nActiveConstr = workingset->nWConstr[0] + workingset->nWConstr[1];
  objective->prev_objtype = objective->objtype;
  objective->prev_nvar = objective->nvar;
  objective->prev_hasLinear = objective->hasLinear;
  objective->objtype = 5;
  objective->nvar = nVar_tmp + 1;
  objective->gammaScalar = 1.0;
  objective->hasLinear = true;
  options->ObjectiveLimit = 1.0E-6;
  options->StepTolerance = 1.4901161193847657E-10;
  solution->fstar = computeFval(objective, memspace->workspace_double.data, H,
                                f_data, solution->xstar.data);
  solution->state = 5;
  iterate(H, f_data, solution, memspace, workingset, qrmanager, cholmanager,
          objective, options->SolverName, options->StepTolerance,
          options->ObjectiveLimit, runTimeOptions->MaxIterations);
  if (workingset->isActiveConstr
          .data[(workingset->isActiveIdx[3] + workingset->sizes[3]) - 2]) {
    bool exitg1;
    idxStartIneq = workingset->sizes[0] + 161;
    exitg1 = false;
    while ((!exitg1) && (idxStartIneq <= workingset->nActiveConstr)) {
      if ((workingset->Wid.data[idxStartIneq - 1] == 4) &&
          (workingset->Wlocalidx.data[idxStartIneq - 1] ==
           workingset->sizes[3])) {
        removeConstr(workingset, idxStartIneq);
        exitg1 = true;
      } else {
        idxStartIneq++;
      }
    }
  }
  idxStartIneq = workingset->nActiveConstr;
  mEqFixed = workingset->sizes[0] + 160;
  while ((idxStartIneq > mEqFixed) && (idxStartIneq > nVar_tmp)) {
    removeConstr(workingset, idxStartIneq);
    idxStartIneq--;
  }
  solution->maxConstr = solution->xstar.data[nVar_tmp];
  setProblemType(workingset, PROBTYPE_ORIG);
  objective->objtype = objective->prev_objtype;
  objective->nvar = objective->prev_nvar;
  objective->hasLinear = objective->prev_hasLinear;
  options->ObjectiveLimit = rtMinusInf;
  options->StepTolerance = 1.0E-6;
}

/*
 * File trailer for phaseone.c
 *
 * [EOF]
 */

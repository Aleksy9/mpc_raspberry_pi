/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: nlmpcmoveCodeGeneration_internal_types.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 22-Feb-2023 11:48:20
 */

#ifndef NLMPCMOVECODEGENERATION_INTERNAL_TYPES_H
#define NLMPCMOVECODEGENERATION_INTERNAL_TYPES_H

/* Include Files */
#include "nlmpcmoveCodeGeneration_types.h"
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_struct_T
#define typedef_struct_T
typedef struct {
  double penaltyParam;
  double threshold;
  int nPenaltyDecreases;
  double linearizedConstrViol;
  double initFval;
  double initConstrViolationEq;
  double initConstrViolationIneq;
  double phi;
  double phiPrimePlus;
  double phiFullStep;
  double feasRelativeFactor;
  double nlpPrimalFeasError;
  double nlpDualFeasError;
  double nlpComplError;
  double firstOrderOpt;
  bool hasObjective;
} struct_T;
#endif /* typedef_struct_T */

#ifndef typedef_b_struct_T
#define typedef_b_struct_T
typedef struct {
  bool gradOK;
  bool fevalOK;
  bool done;
  bool stepAccepted;
  bool failedLineSearch;
  int stepType;
} b_struct_T;
#endif /* typedef_b_struct_T */

#ifndef struct_emxArray_real_T_480
#define struct_emxArray_real_T_480
struct emxArray_real_T_480 {
  double data[480];
  int size[1];
};
#endif /* struct_emxArray_real_T_480 */
#ifndef typedef_emxArray_real_T_480
#define typedef_emxArray_real_T_480
typedef struct emxArray_real_T_480 emxArray_real_T_480;
#endif /* typedef_emxArray_real_T_480 */

#ifndef struct_emxArray_real_T_982
#define struct_emxArray_real_T_982
struct emxArray_real_T_982 {
  double data[982];
  int size[1];
};
#endif /* struct_emxArray_real_T_982 */
#ifndef typedef_emxArray_real_T_982
#define typedef_emxArray_real_T_982
typedef struct emxArray_real_T_982 emxArray_real_T_982;
#endif /* typedef_emxArray_real_T_982 */

#ifndef struct_emxArray_real_T_1803
#define struct_emxArray_real_T_1803
struct emxArray_real_T_1803 {
  double data[1803];
  int size[1];
};
#endif /* struct_emxArray_real_T_1803 */
#ifndef typedef_emxArray_real_T_1803
#define typedef_emxArray_real_T_1803
typedef struct emxArray_real_T_1803 emxArray_real_T_1803;
#endif /* typedef_emxArray_real_T_1803 */

#ifndef struct_emxArray_int32_T_1803
#define struct_emxArray_int32_T_1803
struct emxArray_int32_T_1803 {
  int data[1803];
  int size[1];
};
#endif /* struct_emxArray_int32_T_1803 */
#ifndef typedef_emxArray_int32_T_1803
#define typedef_emxArray_int32_T_1803
typedef struct emxArray_int32_T_1803 emxArray_int32_T_1803;
#endif /* typedef_emxArray_int32_T_1803 */

#ifndef struct_emxArray_real_T_982x320
#define struct_emxArray_real_T_982x320
struct emxArray_real_T_982x320 {
  double data[314240];
  int size[2];
};
#endif /* struct_emxArray_real_T_982x320 */
#ifndef typedef_emxArray_real_T_982x320
#define typedef_emxArray_real_T_982x320
typedef struct emxArray_real_T_982x320 emxArray_real_T_982x320;
#endif /* typedef_emxArray_real_T_982x320 */

#ifndef struct_emxArray_real_T_982x160
#define struct_emxArray_real_T_982x160
struct emxArray_real_T_982x160 {
  double data[157120];
  int size[2];
};
#endif /* struct_emxArray_real_T_982x160 */
#ifndef typedef_emxArray_real_T_982x160
#define typedef_emxArray_real_T_982x160
typedef struct emxArray_real_T_982x160 emxArray_real_T_982x160;
#endif /* typedef_emxArray_real_T_982x160 */

#ifndef typedef_c_struct_T
#define typedef_c_struct_T
typedef struct {
  int nVarMax;
  int mNonlinIneq;
  int mNonlinEq;
  int mIneq;
  int mEq;
  int iNonIneq0;
  int iNonEq0;
  double sqpFval;
  double sqpFval_old;
  double xstarsqp[181];
  double xstarsqp_old[181];
  emxArray_real_T_480 cIneq;
  emxArray_real_T_480 cIneq_old;
  double cEq[160];
  double cEq_old[160];
  emxArray_real_T_982 grad;
  emxArray_real_T_982 grad_old;
  int FunctionEvaluations;
  int sqpIterations;
  int sqpExitFlag;
  emxArray_real_T_1803 lambdasqp;
  emxArray_real_T_1803 lambdaStopTest;
  emxArray_real_T_1803 lambdaStopTestPrev;
  double steplength;
  emxArray_real_T_982 delta_x;
  emxArray_real_T_982 socDirection;
  emxArray_int32_T_1803 workingset_old;
  emxArray_real_T_982x320 JacCineqTrans_old;
  emxArray_real_T_982x160 JacCeqTrans_old;
  emxArray_real_T_982 gradLag;
  emxArray_real_T_982 delta_gradLag;
  emxArray_real_T_982 xstar;
  double fstar;
  double firstorderopt;
  emxArray_real_T_1803 lambda;
  int state;
  double maxConstr;
  int iterations;
  emxArray_real_T_982 searchDir;
} c_struct_T;
#endif /* typedef_c_struct_T */

#ifndef struct_emxArray_real_T_981
#define struct_emxArray_real_T_981
struct emxArray_real_T_981 {
  double data[981];
  int size[1];
};
#endif /* struct_emxArray_real_T_981 */
#ifndef typedef_emxArray_real_T_981
#define typedef_emxArray_real_T_981
typedef struct emxArray_real_T_981 emxArray_real_T_981;
#endif /* typedef_emxArray_real_T_981 */

#ifndef typedef_d_struct_T
#define typedef_d_struct_T
typedef struct {
  emxArray_real_T_982 grad;
  emxArray_real_T_981 Hx;
  bool hasLinear;
  int nvar;
  int maxVar;
  double beta;
  double rho;
  int objtype;
  int prev_objtype;
  int prev_nvar;
  bool prev_hasLinear;
  double gammaScalar;
} d_struct_T;
#endif /* typedef_d_struct_T */

#ifndef struct_emxArray_real_T_1803x982
#define struct_emxArray_real_T_1803x982
struct emxArray_real_T_1803x982 {
  double data[1770546];
  int size[2];
};
#endif /* struct_emxArray_real_T_1803x982 */
#ifndef typedef_emxArray_real_T_1803x982
#define typedef_emxArray_real_T_1803x982
typedef struct emxArray_real_T_1803x982 emxArray_real_T_1803x982;
#endif /* typedef_emxArray_real_T_1803x982 */

#ifndef typedef_e_struct_T
#define typedef_e_struct_T
typedef struct {
  emxArray_real_T_1803x982 workspace_double;
  emxArray_int32_T_1803 workspace_int;
  emxArray_int32_T_1803 workspace_sort;
} e_struct_T;
#endif /* typedef_e_struct_T */

#ifndef struct_emxArray_real_T_471360
#define struct_emxArray_real_T_471360
struct emxArray_real_T_471360 {
  double data[471360];
  int size[1];
};
#endif /* struct_emxArray_real_T_471360 */
#ifndef typedef_emxArray_real_T_471360
#define typedef_emxArray_real_T_471360
typedef struct emxArray_real_T_471360 emxArray_real_T_471360;
#endif /* typedef_emxArray_real_T_471360 */

#ifndef struct_emxArray_real_T_157120
#define struct_emxArray_real_T_157120
struct emxArray_real_T_157120 {
  double data[157120];
  int size[1];
};
#endif /* struct_emxArray_real_T_157120 */
#ifndef typedef_emxArray_real_T_157120
#define typedef_emxArray_real_T_157120
typedef struct emxArray_real_T_157120 emxArray_real_T_157120;
#endif /* typedef_emxArray_real_T_157120 */

#ifndef struct_emxArray_int32_T_982
#define struct_emxArray_int32_T_982
struct emxArray_int32_T_982 {
  int data[982];
  int size[1];
};
#endif /* struct_emxArray_int32_T_982 */
#ifndef typedef_emxArray_int32_T_982
#define typedef_emxArray_int32_T_982
typedef struct emxArray_int32_T_982 emxArray_int32_T_982;
#endif /* typedef_emxArray_int32_T_982 */

#ifndef struct_emxArray_real_T_1770546
#define struct_emxArray_real_T_1770546
struct emxArray_real_T_1770546 {
  double data[1770546];
  int size[1];
};
#endif /* struct_emxArray_real_T_1770546 */
#ifndef typedef_emxArray_real_T_1770546
#define typedef_emxArray_real_T_1770546
typedef struct emxArray_real_T_1770546 emxArray_real_T_1770546;
#endif /* typedef_emxArray_real_T_1770546 */

#ifndef struct_emxArray_boolean_T_1803
#define struct_emxArray_boolean_T_1803
struct emxArray_boolean_T_1803 {
  bool data[1803];
  int size[1];
};
#endif /* struct_emxArray_boolean_T_1803 */
#ifndef typedef_emxArray_boolean_T_1803
#define typedef_emxArray_boolean_T_1803
typedef struct emxArray_boolean_T_1803 emxArray_boolean_T_1803;
#endif /* typedef_emxArray_boolean_T_1803 */

#ifndef typedef_f_struct_T
#define typedef_f_struct_T
typedef struct {
  int mConstr;
  int mConstrOrig;
  int mConstrMax;
  int nVar;
  int nVarOrig;
  int nVarMax;
  int ldA;
  emxArray_real_T_471360 Aineq;
  emxArray_real_T_480 bineq;
  emxArray_real_T_157120 Aeq;
  double beq[160];
  emxArray_real_T_982 lb;
  emxArray_real_T_982 ub;
  emxArray_int32_T_982 indexLB;
  emxArray_int32_T_982 indexUB;
  emxArray_int32_T_982 indexFixed;
  int mEqRemoved;
  int indexEqRemoved[160];
  emxArray_real_T_1770546 ATwset;
  emxArray_real_T_1803 bwset;
  int nActiveConstr;
  emxArray_real_T_1803 maxConstrWorkspace;
  int sizes[5];
  int sizesNormal[5];
  int sizesPhaseOne[5];
  int sizesRegularized[5];
  int sizesRegPhaseOne[5];
  int isActiveIdx[6];
  int isActiveIdxNormal[6];
  int isActiveIdxPhaseOne[6];
  int isActiveIdxRegularized[6];
  int isActiveIdxRegPhaseOne[6];
  emxArray_boolean_T_1803 isActiveConstr;
  emxArray_int32_T_1803 Wid;
  emxArray_int32_T_1803 Wlocalidx;
  int nWConstr[5];
  int probType;
  double SLACK0;
} f_struct_T;
#endif /* typedef_f_struct_T */

#ifndef struct_emxArray_real_T_1803x1803
#define struct_emxArray_real_T_1803x1803
struct emxArray_real_T_1803x1803 {
  double data[3250809];
  int size[2];
};
#endif /* struct_emxArray_real_T_1803x1803 */
#ifndef typedef_emxArray_real_T_1803x1803
#define typedef_emxArray_real_T_1803x1803
typedef struct emxArray_real_T_1803x1803 emxArray_real_T_1803x1803;
#endif /* typedef_emxArray_real_T_1803x1803 */

#ifndef typedef_g_struct_T
#define typedef_g_struct_T
typedef struct {
  int ldq;
  emxArray_real_T_1803x1803 QR;
  emxArray_real_T_1803x1803 Q;
  emxArray_int32_T_1803 jpvt;
  int mrows;
  int ncols;
  emxArray_real_T_1803 tau;
  int minRowCol;
  bool usedPivoting;
} g_struct_T;
#endif /* typedef_g_struct_T */

#ifndef typedef_h_struct_T
#define typedef_h_struct_T
typedef struct {
  emxArray_real_T_1803x1803 FMat;
  int ldm;
  int ndims;
  int info;
  double scaleFactor;
  bool ConvexCheck;
  double regTol_;
  double workspace_;
  double workspace2_;
} h_struct_T;
#endif /* typedef_h_struct_T */

#ifndef typedef_i_struct_T
#define typedef_i_struct_T
typedef struct {
  double x[16];
  double lastMV[4];
  double ref[160];
  double OutputWeights[160];
  double MVWeights[40];
  double MVRateWeights[40];
  double ECRWeight;
  double OutputMin[160];
  double OutputMax[160];
  double StateMin[160];
  double StateMax[160];
  double MVMin[40];
  double MVMax[40];
  double MVRateMin[40];
  double MVRateMax[40];
  double MVScaledTarget[40];
  double Parameters[1];
} i_struct_T;
#endif /* typedef_i_struct_T */

#ifndef typedef_j_struct_T
#define typedef_j_struct_T
typedef struct {
  double Ts;
  double CurrentStates[16];
  double LastMV[4];
  double References[160];
  double MVTarget[40];
  double PredictionHorizon;
  double NumOfStates;
  double NumOfOutputs;
  double NumOfInputs;
  double MVIndex[4];
  double InputPassivityIndex;
  double OutputPassivityIndex;
  bool PassivityUsePredictedX;
} j_struct_T;
#endif /* typedef_j_struct_T */

#ifndef typedef_k_struct_T
#define typedef_k_struct_T
typedef struct {
  i_struct_T runtimedata;
  j_struct_T userdata;
} k_struct_T;
#endif /* typedef_k_struct_T */

#ifndef typedef_anonymous_function
#define typedef_anonymous_function
typedef struct {
  k_struct_T workspace;
} anonymous_function;
#endif /* typedef_anonymous_function */

#ifndef typedef_coder_internal_stickyStruct
#define typedef_coder_internal_stickyStruct
typedef struct {
  anonymous_function value;
} coder_internal_stickyStruct;
#endif /* typedef_coder_internal_stickyStruct */

#ifndef typedef_b_coder_internal_stickyStruct
#define typedef_b_coder_internal_stickyStruct
typedef struct {
  anonymous_function value;
  coder_internal_stickyStruct next;
} b_coder_internal_stickyStruct;
#endif /* typedef_b_coder_internal_stickyStruct */

#ifndef typedef_c_coder_internal_stickyStruct
#define typedef_c_coder_internal_stickyStruct
typedef struct {
  b_coder_internal_stickyStruct next;
} c_coder_internal_stickyStruct;
#endif /* typedef_c_coder_internal_stickyStruct */

#ifndef typedef_d_coder_internal_stickyStruct
#define typedef_d_coder_internal_stickyStruct
typedef struct {
  int value;
  c_coder_internal_stickyStruct next;
} d_coder_internal_stickyStruct;
#endif /* typedef_d_coder_internal_stickyStruct */

#ifndef typedef_e_coder_internal_stickyStruct
#define typedef_e_coder_internal_stickyStruct
typedef struct {
  d_coder_internal_stickyStruct next;
} e_coder_internal_stickyStruct;
#endif /* typedef_e_coder_internal_stickyStruct */

#ifndef typedef_f_coder_internal_stickyStruct
#define typedef_f_coder_internal_stickyStruct
typedef struct {
  e_coder_internal_stickyStruct next;
} f_coder_internal_stickyStruct;
#endif /* typedef_f_coder_internal_stickyStruct */

#ifndef typedef_g_coder_internal_stickyStruct
#define typedef_g_coder_internal_stickyStruct
typedef struct {
  f_coder_internal_stickyStruct next;
} g_coder_internal_stickyStruct;
#endif /* typedef_g_coder_internal_stickyStruct */

#ifndef typedef_h_coder_internal_stickyStruct
#define typedef_h_coder_internal_stickyStruct
typedef struct {
  g_coder_internal_stickyStruct next;
} h_coder_internal_stickyStruct;
#endif /* typedef_h_coder_internal_stickyStruct */

#ifndef typedef_i_coder_internal_stickyStruct
#define typedef_i_coder_internal_stickyStruct
typedef struct {
  h_coder_internal_stickyStruct next;
} i_coder_internal_stickyStruct;
#endif /* typedef_i_coder_internal_stickyStruct */

#ifndef typedef_l_struct_T
#define typedef_l_struct_T
typedef struct {
  double iterations;
  double constrviolation;
} l_struct_T;
#endif /* typedef_l_struct_T */

#ifndef typedef_m_struct_T
#define typedef_m_struct_T
typedef struct {
  char SolverName[7];
  int MaxIterations;
  double StepTolerance;
  double ObjectiveLimit;
} m_struct_T;
#endif /* typedef_m_struct_T */

#endif
/*
 * File trailer for nlmpcmoveCodeGeneration_internal_types.h
 *
 * [EOF]
 */

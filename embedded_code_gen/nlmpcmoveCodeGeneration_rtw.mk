###########################################################################
## Makefile generated for component 'nlmpcmoveCodeGeneration'. 
## 
## Makefile     : nlmpcmoveCodeGeneration_rtw.mk
## Generated on : Wed Feb 22 11:49:01 2023
## Final product: ./nlmpcmoveCLIB.lib
## Product type : static-library
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# MODELLIB                Static library target

PRODUCT_NAME              = nlmpcmoveCodeGeneration
MAKEFILE                  = nlmpcmoveCodeGeneration_rtw.mk
MATLAB_ROOT               = C:/PROGRA~1/MATLAB/R2022b
MATLAB_BIN                = C:/PROGRA~1/MATLAB/R2022b/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/win64
START_DIR                 = C:/Users/AlexisPC/Documents/GitHub/thesis/matlab_models/simulation/mpc/embedded_code_gen
TGT_FCN_LIB               = ISO_C
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 
RELATIVE_PATH_TO_ANCHOR   = .
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 
MODELLIB                  = nlmpcmoveCLIB.lib

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          Linaro Toolchain v4.8
# Supported Version(s):    
# ToolchainInfo Version:   2022b
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# TARGET_LOAD_CMD_ARGS
# TARGET_PKG_INSTALLDIR
# LINARO_TOOLCHAIN_4_8

#-----------
# MACROS
#-----------

SHELL                 = %SystemRoot%/system32/cmd.exe
CCOUTPUTFLAG          = --output_file=
LDOUTPUTFLAG          = --output_file=

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = -lm -lm

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# Assembler: Linaro Toolchain4.8 Assembler
AS_PATH = $(LINARO_TOOLCHAIN_4_8)
AS = "$(AS_PATH)/arm-linux-gnueabihf-as"

# C Compiler: Linaro Toolchain4.8 C Compiler
CC_PATH = $(LINARO_TOOLCHAIN_4_8)
CC = "$(CC_PATH)/arm-linux-gnueabihf-gcc"

# Linker: Linaro Toolchain4.8 Linker
LD_PATH = $(LINARO_TOOLCHAIN_4_8)
LD = "$(LD_PATH)/arm-linux-gnueabihf-gcc"

# C++ Compiler: Linaro Toolchain4.8 C++ Compiler
CPP_PATH = $(LINARO_TOOLCHAIN_4_8)
CPP = "$(CPP_PATH)/arm-linux-gnueabihf-g++"

# C++ Linker: Linaro Toolchain4.8 C++ Linker
CPP_LD_PATH = $(LINARO_TOOLCHAIN_4_8)
CPP_LD = "$(CPP_LD_PATH)/arm-linux-gnueabihf-g++"

# Archiver: Linaro Toolchain4.8 Archiver
AR_PATH = $(LINARO_TOOLCHAIN_4_8)
AR = "$(AR_PATH)/arm-linux-gnueabihf-ar"

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Download: Download
DOWNLOAD_PATH = $(TARGET_PKG_INSTALLDIR)
DOWNLOAD = "$(DOWNLOAD_PATH)/ssh_download.bat"

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%\bin\win64
MAKE = "$(MAKE_PATH)/gmake"


#-------------------------
# Directives/Utilities
#-------------------------

ASDEBUG             = -g
AS_OUTPUT_FLAG      = -o
CDEBUG              = -g
C_OUTPUT_FLAG       = -o
LDDEBUG             = -g
OUTPUT_FLAG         = -o
CPPDEBUG            = -g
CPP_OUTPUT_FLAG     = -o
CPPLDDEBUG          = -g
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG =
MEX_DEBUG           = -g
RM                  = @del /F
ECHO                = @echo
MV                  = @move
RUN                 =

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              = -ruvs
ASFLAGS              = -c \
                       $(ASFLAGS_ADDITIONAL) \
                       $(INCLUDES)
CFLAGS               = -c \
                       -MMD -MP -MF"$(@:%.o=%.dep)" -MT"$@"  \
                       -O2
CPPFLAGS             = -c \
                       -MMD -MP -MF"$(@:%.o=%.dep)" -MT"$@"  \
                       -O2
CPP_LDFLAGS          = -lm -lrt -lpthread -ldl
CPP_SHAREDLIB_LDFLAGS  = -shared  \
                         -lm -lrt -lpthread -ldl
DOWNLOAD_FLAGS       = $(TARGET_LOAD_CMD_ARGS) $(PRODUCT)
EXECUTE_FLAGS        =
LDFLAGS              = -lm -lrt -lpthread -ldl
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -shared  \
                       -lm -lrt -lpthread -ldl



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = ./nlmpcmoveCLIB.lib
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR) -IC:/Users/AlexisPC/DOCUME~1/GitHub/thesis/MATLAB~1/SIMULA~1/mpc -I$(MATLAB_ROOT)/extern/include

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_CUSTOM = 
DEFINES_STANDARD = -DMODEL=nlmpcmoveCLIB

DEFINES = $(DEFINES_CUSTOM) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/nlmpcmoveCodeGeneration_data.c $(START_DIR)/rt_nonfinite.c $(START_DIR)/rtGetNaN.c $(START_DIR)/rtGetInf.c $(START_DIR)/nlmpcmoveCodeGeneration_initialize.c $(START_DIR)/nlmpcmoveCodeGeneration_terminate.c $(START_DIR)/cost_fct_3D_model.c $(START_DIR)/mtimes.c $(START_DIR)/fmincon.c $(START_DIR)/nlmpcmoveCodeGeneration.c $(START_DIR)/state_update_3D_model.c $(START_DIR)/all.c $(START_DIR)/znlmpc_confun.c $(START_DIR)/factoryConstruct.c $(START_DIR)/factoryConstruct1.c $(START_DIR)/checkVectorNonFinite.c $(START_DIR)/computeDualFeasError.c $(START_DIR)/computeComplError.c $(START_DIR)/xnrm2.c $(START_DIR)/computePrimalFeasError.c $(START_DIR)/strcmp.c $(START_DIR)/loadProblem.c $(START_DIR)/setProblemType.c $(START_DIR)/modifyOverheadPhaseOne_.c $(START_DIR)/driver.c $(START_DIR)/test_exit.c $(START_DIR)/xgeqp3.c $(START_DIR)/xzgeqp3.c $(START_DIR)/xzlarfg.c $(START_DIR)/xzlarf.c $(START_DIR)/xgerc.c $(START_DIR)/xorgqr.c $(START_DIR)/xgemv.c $(START_DIR)/sortLambdaQP.c $(START_DIR)/step.c $(START_DIR)/normal.c $(START_DIR)/driver1.c $(START_DIR)/PresolveWorkingSet.c $(START_DIR)/RemoveDependentEq_.c $(START_DIR)/countsort.c $(START_DIR)/removeConstr.c $(START_DIR)/feasibleX0ForWorkingSet.c $(START_DIR)/factorQR.c $(START_DIR)/maxConstraintViolation.c $(START_DIR)/phaseone.c $(START_DIR)/computeFval.c $(START_DIR)/linearForm_.c $(START_DIR)/iterate.c $(START_DIR)/computeGrad_StoreHx.c $(START_DIR)/computeFval_ReuseHx.c $(START_DIR)/xrotg.c $(START_DIR)/deleteColMoveEnd.c $(START_DIR)/compute_deltax.c $(START_DIR)/xpotrf.c $(START_DIR)/solve.c $(START_DIR)/xgemm.c $(START_DIR)/addBoundToActiveSetMatrix_.c $(START_DIR)/checkStoppingAndUpdateFval.c $(START_DIR)/addAeqConstr.c $(START_DIR)/relaxed.c $(START_DIR)/soc.c $(START_DIR)/linesearch.c $(START_DIR)/BFGSUpdate.c $(START_DIR)/evalObjAndConstrAndDerivatives.c $(START_DIR)/computeConstraintsAndUserJacobian_.c $(START_DIR)/saveJacobian.c $(START_DIR)/updateWorkingSetForNewQP.c $(START_DIR)/evalObjAndConstr.c $(START_DIR)/computeLinearResiduals.c $(START_DIR)/computeGradLag.c $(START_DIR)/feasibleratiotest.c $(START_DIR)/partialColLDL3_.c $(START_DIR)/fullColLDL2_.c

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = nlmpcmoveCodeGeneration_data.c.o rt_nonfinite.c.o rtGetNaN.c.o rtGetInf.c.o nlmpcmoveCodeGeneration_initialize.c.o nlmpcmoveCodeGeneration_terminate.c.o cost_fct_3D_model.c.o mtimes.c.o fmincon.c.o nlmpcmoveCodeGeneration.c.o state_update_3D_model.c.o all.c.o znlmpc_confun.c.o factoryConstruct.c.o factoryConstruct1.c.o checkVectorNonFinite.c.o computeDualFeasError.c.o computeComplError.c.o xnrm2.c.o computePrimalFeasError.c.o strcmp.c.o loadProblem.c.o setProblemType.c.o modifyOverheadPhaseOne_.c.o driver.c.o test_exit.c.o xgeqp3.c.o xzgeqp3.c.o xzlarfg.c.o xzlarf.c.o xgerc.c.o xorgqr.c.o xgemv.c.o sortLambdaQP.c.o step.c.o normal.c.o driver1.c.o PresolveWorkingSet.c.o RemoveDependentEq_.c.o countsort.c.o removeConstr.c.o feasibleX0ForWorkingSet.c.o factorQR.c.o maxConstraintViolation.c.o phaseone.c.o computeFval.c.o linearForm_.c.o iterate.c.o computeGrad_StoreHx.c.o computeFval_ReuseHx.c.o xrotg.c.o deleteColMoveEnd.c.o compute_deltax.c.o xpotrf.c.o solve.c.o xgemm.c.o addBoundToActiveSetMatrix_.c.o checkStoppingAndUpdateFval.c.o addAeqConstr.c.o relaxed.c.o soc.c.o linesearch.c.o BFGSUpdate.c.o evalObjAndConstrAndDerivatives.c.o computeConstraintsAndUserJacobian_.c.o saveJacobian.c.o updateWorkingSetForNewQP.c.o evalObjAndConstr.c.o computeLinearResiduals.c.o computeGradLag.c.o feasibleratiotest.c.o partialColLDL3_.c.o fullColLDL2_.c.o

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = 

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CPPFLAGS += $(CPPFLAGS_BASIC)

###########################################################################
## INLINED COMMANDS
###########################################################################


ALL_DEPS:=$(patsubst %.o,%.dep,$(ALL_OBJS))
all:




-include codertarget_assembly_flags.mk
-include ../codertarget_assembly_flags.mk
-include ../../codertarget_assembly_flags.mk
-include $(ALL_DEPS)


###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute


all : build
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


prebuild : 


download : $(PRODUCT)


execute : download


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	@echo "### Creating static library "$(PRODUCT)" ..."
	$(AR) $(ARFLAGS)  $(PRODUCT) $(OBJS)
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.c.o : %.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : %.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.pp.o : %.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.c.o : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : $(RELATIVE_PATH_TO_ANCHOR)/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.pp.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.c.o : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : $(START_DIR)/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.pp.o : $(START_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.c.o : C:/Users/AlexisPC/Documents/GitHub/thesis/matlab_models/simulation/mpc/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : C:/Users/AlexisPC/Documents/GitHub/thesis/matlab_models/simulation/mpc/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.pp.o : C:/Users/AlexisPC/Documents/GitHub/thesis/matlab_models/simulation/mpc/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


nlmpcmoveCodeGeneration_data.c.o : $(START_DIR)/nlmpcmoveCodeGeneration_data.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rt_nonfinite.c.o : $(START_DIR)/rt_nonfinite.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rtGetNaN.c.o : $(START_DIR)/rtGetNaN.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rtGetInf.c.o : $(START_DIR)/rtGetInf.c
	$(CC) $(CFLAGS) -o "$@" "$<"


nlmpcmoveCodeGeneration_initialize.c.o : $(START_DIR)/nlmpcmoveCodeGeneration_initialize.c
	$(CC) $(CFLAGS) -o "$@" "$<"


nlmpcmoveCodeGeneration_terminate.c.o : $(START_DIR)/nlmpcmoveCodeGeneration_terminate.c
	$(CC) $(CFLAGS) -o "$@" "$<"


cost_fct_3D_model.c.o : $(START_DIR)/cost_fct_3D_model.c
	$(CC) $(CFLAGS) -o "$@" "$<"


mtimes.c.o : $(START_DIR)/mtimes.c
	$(CC) $(CFLAGS) -o "$@" "$<"


fmincon.c.o : $(START_DIR)/fmincon.c
	$(CC) $(CFLAGS) -o "$@" "$<"


nlmpcmoveCodeGeneration.c.o : $(START_DIR)/nlmpcmoveCodeGeneration.c
	$(CC) $(CFLAGS) -o "$@" "$<"


state_update_3D_model.c.o : $(START_DIR)/state_update_3D_model.c
	$(CC) $(CFLAGS) -o "$@" "$<"


all.c.o : $(START_DIR)/all.c
	$(CC) $(CFLAGS) -o "$@" "$<"


znlmpc_confun.c.o : $(START_DIR)/znlmpc_confun.c
	$(CC) $(CFLAGS) -o "$@" "$<"


factoryConstruct.c.o : $(START_DIR)/factoryConstruct.c
	$(CC) $(CFLAGS) -o "$@" "$<"


factoryConstruct1.c.o : $(START_DIR)/factoryConstruct1.c
	$(CC) $(CFLAGS) -o "$@" "$<"


checkVectorNonFinite.c.o : $(START_DIR)/checkVectorNonFinite.c
	$(CC) $(CFLAGS) -o "$@" "$<"


computeDualFeasError.c.o : $(START_DIR)/computeDualFeasError.c
	$(CC) $(CFLAGS) -o "$@" "$<"


computeComplError.c.o : $(START_DIR)/computeComplError.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xnrm2.c.o : $(START_DIR)/xnrm2.c
	$(CC) $(CFLAGS) -o "$@" "$<"


computePrimalFeasError.c.o : $(START_DIR)/computePrimalFeasError.c
	$(CC) $(CFLAGS) -o "$@" "$<"


strcmp.c.o : $(START_DIR)/strcmp.c
	$(CC) $(CFLAGS) -o "$@" "$<"


loadProblem.c.o : $(START_DIR)/loadProblem.c
	$(CC) $(CFLAGS) -o "$@" "$<"


setProblemType.c.o : $(START_DIR)/setProblemType.c
	$(CC) $(CFLAGS) -o "$@" "$<"


modifyOverheadPhaseOne_.c.o : $(START_DIR)/modifyOverheadPhaseOne_.c
	$(CC) $(CFLAGS) -o "$@" "$<"


driver.c.o : $(START_DIR)/driver.c
	$(CC) $(CFLAGS) -o "$@" "$<"


test_exit.c.o : $(START_DIR)/test_exit.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xgeqp3.c.o : $(START_DIR)/xgeqp3.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xzgeqp3.c.o : $(START_DIR)/xzgeqp3.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xzlarfg.c.o : $(START_DIR)/xzlarfg.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xzlarf.c.o : $(START_DIR)/xzlarf.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xgerc.c.o : $(START_DIR)/xgerc.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xorgqr.c.o : $(START_DIR)/xorgqr.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xgemv.c.o : $(START_DIR)/xgemv.c
	$(CC) $(CFLAGS) -o "$@" "$<"


sortLambdaQP.c.o : $(START_DIR)/sortLambdaQP.c
	$(CC) $(CFLAGS) -o "$@" "$<"


step.c.o : $(START_DIR)/step.c
	$(CC) $(CFLAGS) -o "$@" "$<"


normal.c.o : $(START_DIR)/normal.c
	$(CC) $(CFLAGS) -o "$@" "$<"


driver1.c.o : $(START_DIR)/driver1.c
	$(CC) $(CFLAGS) -o "$@" "$<"


PresolveWorkingSet.c.o : $(START_DIR)/PresolveWorkingSet.c
	$(CC) $(CFLAGS) -o "$@" "$<"


RemoveDependentEq_.c.o : $(START_DIR)/RemoveDependentEq_.c
	$(CC) $(CFLAGS) -o "$@" "$<"


countsort.c.o : $(START_DIR)/countsort.c
	$(CC) $(CFLAGS) -o "$@" "$<"


removeConstr.c.o : $(START_DIR)/removeConstr.c
	$(CC) $(CFLAGS) -o "$@" "$<"


feasibleX0ForWorkingSet.c.o : $(START_DIR)/feasibleX0ForWorkingSet.c
	$(CC) $(CFLAGS) -o "$@" "$<"


factorQR.c.o : $(START_DIR)/factorQR.c
	$(CC) $(CFLAGS) -o "$@" "$<"


maxConstraintViolation.c.o : $(START_DIR)/maxConstraintViolation.c
	$(CC) $(CFLAGS) -o "$@" "$<"


phaseone.c.o : $(START_DIR)/phaseone.c
	$(CC) $(CFLAGS) -o "$@" "$<"


computeFval.c.o : $(START_DIR)/computeFval.c
	$(CC) $(CFLAGS) -o "$@" "$<"


linearForm_.c.o : $(START_DIR)/linearForm_.c
	$(CC) $(CFLAGS) -o "$@" "$<"


iterate.c.o : $(START_DIR)/iterate.c
	$(CC) $(CFLAGS) -o "$@" "$<"


computeGrad_StoreHx.c.o : $(START_DIR)/computeGrad_StoreHx.c
	$(CC) $(CFLAGS) -o "$@" "$<"


computeFval_ReuseHx.c.o : $(START_DIR)/computeFval_ReuseHx.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xrotg.c.o : $(START_DIR)/xrotg.c
	$(CC) $(CFLAGS) -o "$@" "$<"


deleteColMoveEnd.c.o : $(START_DIR)/deleteColMoveEnd.c
	$(CC) $(CFLAGS) -o "$@" "$<"


compute_deltax.c.o : $(START_DIR)/compute_deltax.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xpotrf.c.o : $(START_DIR)/xpotrf.c
	$(CC) $(CFLAGS) -o "$@" "$<"


solve.c.o : $(START_DIR)/solve.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xgemm.c.o : $(START_DIR)/xgemm.c
	$(CC) $(CFLAGS) -o "$@" "$<"


addBoundToActiveSetMatrix_.c.o : $(START_DIR)/addBoundToActiveSetMatrix_.c
	$(CC) $(CFLAGS) -o "$@" "$<"


checkStoppingAndUpdateFval.c.o : $(START_DIR)/checkStoppingAndUpdateFval.c
	$(CC) $(CFLAGS) -o "$@" "$<"


addAeqConstr.c.o : $(START_DIR)/addAeqConstr.c
	$(CC) $(CFLAGS) -o "$@" "$<"


relaxed.c.o : $(START_DIR)/relaxed.c
	$(CC) $(CFLAGS) -o "$@" "$<"


soc.c.o : $(START_DIR)/soc.c
	$(CC) $(CFLAGS) -o "$@" "$<"


linesearch.c.o : $(START_DIR)/linesearch.c
	$(CC) $(CFLAGS) -o "$@" "$<"


BFGSUpdate.c.o : $(START_DIR)/BFGSUpdate.c
	$(CC) $(CFLAGS) -o "$@" "$<"


evalObjAndConstrAndDerivatives.c.o : $(START_DIR)/evalObjAndConstrAndDerivatives.c
	$(CC) $(CFLAGS) -o "$@" "$<"


computeConstraintsAndUserJacobian_.c.o : $(START_DIR)/computeConstraintsAndUserJacobian_.c
	$(CC) $(CFLAGS) -o "$@" "$<"


saveJacobian.c.o : $(START_DIR)/saveJacobian.c
	$(CC) $(CFLAGS) -o "$@" "$<"


updateWorkingSetForNewQP.c.o : $(START_DIR)/updateWorkingSetForNewQP.c
	$(CC) $(CFLAGS) -o "$@" "$<"


evalObjAndConstr.c.o : $(START_DIR)/evalObjAndConstr.c
	$(CC) $(CFLAGS) -o "$@" "$<"


computeLinearResiduals.c.o : $(START_DIR)/computeLinearResiduals.c
	$(CC) $(CFLAGS) -o "$@" "$<"


computeGradLag.c.o : $(START_DIR)/computeGradLag.c
	$(CC) $(CFLAGS) -o "$@" "$<"


feasibleratiotest.c.o : $(START_DIR)/feasibleratiotest.c
	$(CC) $(CFLAGS) -o "$@" "$<"


partialColLDL3_.c.o : $(START_DIR)/partialColLDL3_.c
	$(CC) $(CFLAGS) -o "$@" "$<"


fullColLDL2_.c.o : $(START_DIR)/fullColLDL2_.c
	$(CC) $(CFLAGS) -o "$@" "$<"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo "### PRODUCT = $(PRODUCT)"
	@echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@echo "### BUILD_TYPE = $(BUILD_TYPE)"
	@echo "### INCLUDES = $(INCLUDES)"
	@echo "### DEFINES = $(DEFINES)"
	@echo "### ALL_SRCS = $(ALL_SRCS)"
	@echo "### ALL_OBJS = $(ALL_OBJS)"
	@echo "### LIBS = $(LIBS)"
	@echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	@echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@echo "### ASFLAGS = $(ASFLAGS)"
	@echo "### CFLAGS = $(CFLAGS)"
	@echo "### LDFLAGS = $(LDFLAGS)"
	@echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "### CPPFLAGS = $(CPPFLAGS)"
	@echo "### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@echo "### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@echo "### ARFLAGS = $(ARFLAGS)"
	@echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	@echo "### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@echo "### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	$(RM) $(subst /,\,$(PRODUCT))
	$(RM) $(subst /,\,$(ALL_OBJS))
	$(RM) *.c.dep
	$(RM) *.cpp.dep
	$(RM) *.s.dep
	$(ECHO) "### Deleted all derived files."



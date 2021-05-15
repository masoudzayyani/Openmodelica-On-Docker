/* Main Simulation File */

#if defined(__cplusplus)
extern "C" {
#endif

#include "System_model.h"
#include "simulation/solver/events.h"

#define prefixedName_performSimulation System_performSimulation
#define prefixedName_updateContinuousSystem System_updateContinuousSystem
#include <simulation/solver/perform_simulation.c.inc>

#define prefixedName_performQSSSimulation System_performQSSSimulation
#include <simulation/solver/perform_qss_simulation.c.inc>


/* dummy VARINFO and FILEINFO */
const FILE_INFO dummyFILE_INFO = omc_dummyFileInfo;
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;

int System_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int System_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int System_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int System_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int System_data_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  TRACE_POP
  return 0;
}

int System_dataReconciliationInputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int System_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int System_setc_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/*
equation index: 4
type: ALGORITHM

  x := pre(x);
  $whenCondition1 := pre($whenCondition1);
  $whenCondition1 := sample(1, 1.0, 2.0);
  when $whenCondition1 then
    x := next(pre(x));
  end when;
*/
void System_eqFunction_4(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,4};
  data->localData[0]->integerVars[0] /* x DISCRETE */ = data->simulationInfo->integerVarsPre[0] /* x DISCRETE */;

  data->localData[0]->booleanVars[0] /* $whenCondition1 DISCRETE */ = data->simulationInfo->booleanVarsPre[0] /* $whenCondition1 DISCRETE */;

  data->localData[0]->booleanVars[0] /* $whenCondition1 DISCRETE */ = data->simulationInfo->samples[0];

  if(data->simulationInfo->discreteCall == 1)
  {
    if((data->localData[0]->booleanVars[0] /* $whenCondition1 DISCRETE */ && !data->simulationInfo->booleanVarsPre[0] /* $whenCondition1 DISCRETE */ /* edge */))
    {
      data->localData[0]->integerVars[0] /* x DISCRETE */ = omc_next(threadData, data->simulationInfo->integerVarsPre[0] /* x DISCRETE */);
    }
  }
  TRACE_POP
}

OMC_DISABLE_OPT
int System_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_DAE);
#endif

  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  System_functionLocalKnownVars(data, threadData);
  System_eqFunction_4(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_DAE);
#endif
  TRACE_POP
  return 0;
}


int System_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


int System_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_FUNCTION_ODE);
#endif

  
  data->simulationInfo->callStatistics.functionODE++;
  
  System_functionLocalKnownVars(data, threadData);
  /* no ODE systems */

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_FUNCTION_ODE);
#endif

  TRACE_POP
  return 0;
}

/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "System_12jac.h"
#include "System_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks System_callback = {
   (int (*)(DATA *, threadData_t *, void *)) System_performSimulation,    /* performSimulation */
   (int (*)(DATA *, threadData_t *, void *)) System_performQSSSimulation,    /* performQSSSimulation */
   System_updateContinuousSystem,    /* updateContinuousSystem */
   System_callExternalObjectDestructors,    /* callExternalObjectDestructors */
   NULL,    /* initialNonLinearSystem */
   NULL,    /* initialLinearSystem */
   NULL,    /* initialMixedSystem */
   #if !defined(OMC_NO_STATESELECTION)
   System_initializeStateSets,
   #else
   NULL,
   #endif    /* initializeStateSets */
   System_initializeDAEmodeData,
   System_functionODE,
   System_functionAlgebraics,
   System_functionDAE,
   System_functionLocalKnownVars,
   System_input_function,
   System_input_function_init,
   System_input_function_updateStartValues,
   System_data_function,
   System_output_function,
   System_setc_function,
   System_function_storeDelayed,
   System_updateBoundVariableAttributes,
   System_functionInitialEquations,
   1, /* useHomotopy - 0: local homotopy (equidistant lambda), 1: global homotopy (equidistant lambda), 2: new global homotopy approach (adaptive lambda), 3: new local homotopy approach (adaptive lambda)*/
   NULL,
   System_functionRemovedInitialEquations,
   System_updateBoundParameters,
   System_checkForAsserts,
   System_function_ZeroCrossingsEquations,
   System_function_ZeroCrossings,
   System_function_updateRelations,
   System_zeroCrossingDescription,
   System_relationDescription,
   System_function_initSample,
   System_INDEX_JAC_A,
   System_INDEX_JAC_B,
   System_INDEX_JAC_C,
   System_INDEX_JAC_D,
   System_INDEX_JAC_F,
   System_initialAnalyticJacobianA,
   System_initialAnalyticJacobianB,
   System_initialAnalyticJacobianC,
   System_initialAnalyticJacobianD,
   System_initialAnalyticJacobianF,
   System_functionJacA_column,
   System_functionJacB_column,
   System_functionJacC_column,
   System_functionJacD_column,
   System_functionJacF_column,
   System_linear_model_frame,
   System_linear_model_datarecovery_frame,
   System_mayer,
   System_lagrange,
   System_pickUpBoundsForInputsInOptimization,
   System_setInputData,
   System_getTimeGrid,
   System_symbolicInlineSystem,
   System_function_initSynchronous,
   System_function_updateSynchronous,
   System_function_equationsSynchronous,
   System_inputNames,
   System_dataReconciliationInputNames,
   NULL,
   NULL,
   NULL,
   -1

};

#define _OMC_LIT_RESOURCE_0_name_data "Complex"
#define _OMC_LIT_RESOURCE_0_dir_data "/usr/lib/omlibrary"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_0_name,7,_OMC_LIT_RESOURCE_0_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir,18,_OMC_LIT_RESOURCE_0_dir_data);

#define _OMC_LIT_RESOURCE_1_name_data "Modelica"
#define _OMC_LIT_RESOURCE_1_dir_data "/usr/lib/omlibrary/Modelica 4.0.0"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_1_name,8,_OMC_LIT_RESOURCE_1_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir,33,_OMC_LIT_RESOURCE_1_dir_data);

#define _OMC_LIT_RESOURCE_2_name_data "ModelicaServices"
#define _OMC_LIT_RESOURCE_2_dir_data "/usr/lib/omlibrary/ModelicaServices 4.0.0"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_2_name,16,_OMC_LIT_RESOURCE_2_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir,41,_OMC_LIT_RESOURCE_2_dir_data);

#define _OMC_LIT_RESOURCE_3_name_data "System"
#define _OMC_LIT_RESOURCE_3_dir_data "/home/openmodelicausers/tests"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_name,6,_OMC_LIT_RESOURCE_3_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir,29,_OMC_LIT_RESOURCE_3_dir_data);

#define _OMC_LIT_RESOURCE_4_name_data "TrafficLightSignal"
#define _OMC_LIT_RESOURCE_4_dir_data "/home/openmodelicausers/tests"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_4_name,18,_OMC_LIT_RESOURCE_4_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir,29,_OMC_LIT_RESOURCE_4_dir_data);

#define _OMC_LIT_RESOURCE_5_name_data "next"
#define _OMC_LIT_RESOURCE_5_dir_data "/home/openmodelicausers/tests"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_5_name,4,_OMC_LIT_RESOURCE_5_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_5_dir,29,_OMC_LIT_RESOURCE_5_dir_data);

static const MMC_DEFSTRUCTLIT(_OMC_LIT_RESOURCES,12,MMC_ARRAY_TAG) {MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_dir)}};
void System_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  threadData->localRoots[LOCAL_ROOT_SIMULATION_DATA] = data;
  data->callback = &System_callback;
  OpenModelica_updateUriMapping(threadData, MMC_REFSTRUCTLIT(_OMC_LIT_RESOURCES));
  data->modelData->modelName = "System";
  data->modelData->modelFilePrefix = "System";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "/home/openmodelicausers/tests";
  data->modelData->modelGUID = "{25413a19-db43-4060-bfd7-da508ea4f89b}";
  #if defined(OPENMODELICA_XML_FROM_FILE_AT_RUNTIME)
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData = NULL;
  #else
  #if defined(_MSC_VER) /* handle joke compilers */
  {
  /* for MSVC we encode a string like char x[] = {'a', 'b', 'c', '\0'} */
  /* because the string constant limit is 65535 bytes */
  static const char contents_init[] =
    #include "System_init.c"
    ;
  static const char contents_info[] =
    #include "System_info.c"
    ;
    data->modelData->initXMLData = contents_init;
    data->modelData->modelDataXml.infoXMLData = contents_info;
  }
  #else /* handle real compilers */
  data->modelData->initXMLData =
  #include "System_init.c"
    ;
  data->modelData->modelDataXml.infoXMLData =
  #include "System_info.c"
    ;
  #endif /* defined(_MSC_VER) */
  #endif /* defined(OPENMODELICA_XML_FROM_FILE_AT_RUNTIME) */
  data->modelData->runTestsuite = 0;
  
  data->modelData->nStates = 0;
  data->modelData->nVariablesReal = 0;
  data->modelData->nDiscreteReal = 0;
  data->modelData->nVariablesInteger = 1;
  data->modelData->nVariablesBoolean = 1;
  data->modelData->nVariablesString = 0;
  data->modelData->nParametersReal = 0;
  data->modelData->nParametersInteger = 0;
  data->modelData->nParametersBoolean = 0;
  data->modelData->nParametersString = 0;
  data->modelData->nInputVars = 0;
  data->modelData->nOutputVars = 0;
  
  data->modelData->nAliasReal = 0;
  data->modelData->nAliasInteger = 0;
  data->modelData->nAliasBoolean = 0;
  data->modelData->nAliasString = 0;
  
  data->modelData->nZeroCrossings = 0;
  data->modelData->nSamples = 1;
  data->modelData->nRelations = 0;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 0;
  
  data->modelData->modelDataXml.fileName = "System_info.json";
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 1;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 6;
  data->modelData->nMixedSystems = 0;
  data->modelData->nLinearSystems = 0;
  data->modelData->nNonLinearSystems = 0;
  data->modelData->nStateSets = 0;
  data->modelData->nJacobians = 5;
  data->modelData->nOptimizeConstraints = 0;
  data->modelData->nOptimizeFinalConstraints = 0;
  
  data->modelData->nDelayExpressions = 0;
  
  data->modelData->nClocks = 0;
  data->modelData->nSubClocks = 0;
  
  data->modelData->nSensitivityVars = 0;
  data->modelData->nSensitivityParamVars = 0;
  data->modelData->nSetcVars = 0;
  data->modelData->ndataReconVars = 0;
  data->modelData->linearizationDumpLanguage =
  OMC_LINEARIZE_DUMP_LANGUAGE_MODELICA;
}

static int rml_execution_failed()
{
  fflush(NULL);
  fprintf(stderr, "Execution failed!\n");
  fflush(NULL);
  return 1;
}

#if defined(threadData)
#undef threadData
#endif
/* call the simulation runtime main from our main! */
int main(int argc, char**argv)
{
  int res;
  DATA data;
  MODEL_DATA modelData;
  SIMULATION_INFO simInfo;
  data.modelData = &modelData;
  data.simulationInfo = &simInfo;
  measure_time_flag = 0;
  compiledInDAEMode = 0;
  compiledWithSymSolver = 0;
  MMC_INIT(0);
  omc_alloc_interface.init();
  {
    MMC_TRY_TOP()
  
    MMC_TRY_STACK()
  
    System_setupDataStruc(&data, threadData);
    res = _main_SimulationRuntime(argc, argv, &data, threadData);
    
    MMC_ELSE()
    rml_execution_failed();
    fprintf(stderr, "Stack overflow detected and was not caught.\nSend us a bug report at https://trac.openmodelica.org/OpenModelica/newticket\n    Include the following trace:\n");
    printStacktraceMessages();
    fflush(NULL);
    return 1;
    MMC_CATCH_STACK()
    
    MMC_CATCH_TOP(return rml_execution_failed());
  }

  fflush(NULL);
  EXIT(res);
  return res;
}

#ifdef __cplusplus
}
#endif



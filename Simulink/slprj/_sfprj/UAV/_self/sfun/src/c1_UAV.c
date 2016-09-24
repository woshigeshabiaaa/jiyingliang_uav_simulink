/* Include files */

#include "blascompat32.h"
#include "UAV_sfun.h"
#include "c1_UAV.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "UAV_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c1_debug_family_names[11] = { "ANG_course", "bu", "ZBw",
  "ZW", "XC", "YW", "XW", "nargin", "nargout", "u", "y" };

/* Function Declarations */
static void initialize_c1_UAV(SFc1_UAVInstanceStruct *chartInstance);
static void initialize_params_c1_UAV(SFc1_UAVInstanceStruct *chartInstance);
static void enable_c1_UAV(SFc1_UAVInstanceStruct *chartInstance);
static void disable_c1_UAV(SFc1_UAVInstanceStruct *chartInstance);
static void c1_update_debugger_state_c1_UAV(SFc1_UAVInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c1_UAV(SFc1_UAVInstanceStruct *chartInstance);
static void set_sim_state_c1_UAV(SFc1_UAVInstanceStruct *chartInstance, const
  mxArray *c1_st);
static void finalize_c1_UAV(SFc1_UAVInstanceStruct *chartInstance);
static void sf_c1_UAV(SFc1_UAVInstanceStruct *chartInstance);
static void c1_chartstep_c1_UAV(SFc1_UAVInstanceStruct *chartInstance);
static void initSimStructsc1_UAV(SFc1_UAVInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static void c1_emlrt_marshallIn(SFc1_UAVInstanceStruct *chartInstance, const
  mxArray *c1_y, const char_T *c1_identifier, real_T c1_b_y[9]);
static void c1_b_emlrt_marshallIn(SFc1_UAVInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[9]);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_c_emlrt_marshallIn(SFc1_UAVInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_d_emlrt_marshallIn(SFc1_UAVInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[3]);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[29]);
static void c1_eml_int_forloop_overflow_check(SFc1_UAVInstanceStruct
  *chartInstance);
static void c1_cross(SFc1_UAVInstanceStruct *chartInstance, real_T c1_a[3],
                     real_T c1_b[3], real_T c1_c[3]);
static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_e_emlrt_marshallIn(SFc1_UAVInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static uint8_T c1_f_emlrt_marshallIn(SFc1_UAVInstanceStruct *chartInstance,
  const mxArray *c1_b_is_active_c1_UAV, const char_T *c1_identifier);
static uint8_T c1_g_emlrt_marshallIn(SFc1_UAVInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void init_dsm_address_info(SFc1_UAVInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c1_UAV(SFc1_UAVInstanceStruct *chartInstance)
{
  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c1_is_active_c1_UAV = 0U;
}

static void initialize_params_c1_UAV(SFc1_UAVInstanceStruct *chartInstance)
{
}

static void enable_c1_UAV(SFc1_UAVInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c1_UAV(SFc1_UAVInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c1_update_debugger_state_c1_UAV(SFc1_UAVInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c1_UAV(SFc1_UAVInstanceStruct *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  int32_T c1_i0;
  real_T c1_u[9];
  const mxArray *c1_b_y = NULL;
  uint8_T c1_hoistedGlobal;
  uint8_T c1_b_u;
  const mxArray *c1_c_y = NULL;
  real_T (*c1_d_y)[9];
  c1_d_y = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellarray(2), FALSE);
  for (c1_i0 = 0; c1_i0 < 9; c1_i0++) {
    c1_u[c1_i0] = (*c1_d_y)[c1_i0];
  }

  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_hoistedGlobal = chartInstance->c1_is_active_c1_UAV;
  c1_b_u = c1_hoistedGlobal;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  sf_mex_assign(&c1_st, c1_y, FALSE);
  return c1_st;
}

static void set_sim_state_c1_UAV(SFc1_UAVInstanceStruct *chartInstance, const
  mxArray *c1_st)
{
  const mxArray *c1_u;
  real_T c1_dv0[9];
  int32_T c1_i1;
  real_T (*c1_y)[9];
  c1_y = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c1_doneDoubleBufferReInit = TRUE;
  c1_u = sf_mex_dup(c1_st);
  c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 0)), "y",
                      c1_dv0);
  for (c1_i1 = 0; c1_i1 < 9; c1_i1++) {
    (*c1_y)[c1_i1] = c1_dv0[c1_i1];
  }

  chartInstance->c1_is_active_c1_UAV = c1_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 1)), "is_active_c1_UAV");
  sf_mex_destroy(&c1_u);
  c1_update_debugger_state_c1_UAV(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_UAV(SFc1_UAVInstanceStruct *chartInstance)
{
}

static void sf_c1_UAV(SFc1_UAVInstanceStruct *chartInstance)
{
  int32_T c1_i2;
  int32_T c1_i3;
  real_T (*c1_y)[9];
  real_T (*c1_u)[4];
  c1_y = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_u = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  for (c1_i2 = 0; c1_i2 < 4; c1_i2++) {
    _SFD_DATA_RANGE_CHECK((*c1_u)[c1_i2], 0U);
  }

  for (c1_i3 = 0; c1_i3 < 9; c1_i3++) {
    _SFD_DATA_RANGE_CHECK((*c1_y)[c1_i3], 1U);
  }

  chartInstance->c1_sfEvent = CALL_EVENT;
  c1_chartstep_c1_UAV(chartInstance);
  sf_debug_check_for_state_inconsistency(_UAVMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c1_chartstep_c1_UAV(SFc1_UAVInstanceStruct *chartInstance)
{
  int32_T c1_i4;
  real_T c1_u[4];
  uint32_T c1_debug_family_var_map[11];
  real_T c1_ANG_course;
  real_T c1_bu;
  real_T c1_ZBw[3];
  real_T c1_ZW[3];
  real_T c1_XC[3];
  real_T c1_YW[3];
  real_T c1_XW[3];
  real_T c1_nargin = 1.0;
  real_T c1_nargout = 1.0;
  real_T c1_y[9];
  real_T c1_b_u[3];
  int32_T c1_i5;
  int32_T c1_i6;
  real_T c1_x[3];
  real_T c1_b_y;
  real_T c1_scale;
  int32_T c1_k;
  int32_T c1_b_k;
  real_T c1_b_x;
  real_T c1_c_x;
  real_T c1_absxk;
  real_T c1_t;
  int32_T c1_i7;
  real_T c1_c_y;
  real_T c1_d_y;
  int32_T c1_i8;
  real_T c1_d_x;
  real_T c1_e_x;
  real_T c1_f_x;
  real_T c1_g_x;
  real_T c1_h_x[3];
  int32_T c1_i9;
  int32_T c1_i10;
  real_T c1_b_ZW[3];
  int32_T c1_i11;
  real_T c1_b_XC[3];
  real_T c1_dv1[3];
  int32_T c1_i12;
  int32_T c1_i13;
  real_T c1_b_YW[3];
  int32_T c1_i14;
  real_T c1_c_ZW[3];
  real_T c1_dv2[3];
  int32_T c1_i15;
  int32_T c1_i16;
  int32_T c1_i17;
  int32_T c1_i18;
  int32_T c1_i19;
  real_T (*c1_e_y)[9];
  real_T (*c1_c_u)[4];
  c1_e_y = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_c_u = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  for (c1_i4 = 0; c1_i4 < 4; c1_i4++) {
    c1_u[c1_i4] = (*c1_c_u)[c1_i4];
  }

  sf_debug_symbol_scope_push_eml(0U, 11U, 11U, c1_debug_family_names,
    c1_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c1_ANG_course, 0U,
    c1_c_sf_marshallOut, c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_bu, 1U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_ZBw, 2U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_ZW, 3U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_XC, 4U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_YW, 5U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_XW, 6U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargin, 7U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargout, 8U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(c1_u, 9U, c1_b_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c1_y, 10U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 6);
  c1_ANG_course = c1_u[3];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 7);
  c1_bu = c1_ANG_course - 1.5707963267948966;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 8);
  c1_b_u[0] = c1_u[0];
  c1_b_u[1] = c1_u[1];
  c1_b_u[2] = c1_u[2];
  for (c1_i5 = 0; c1_i5 < 3; c1_i5++) {
    c1_ZBw[c1_i5] = c1_b_u[c1_i5];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 11);
  for (c1_i6 = 0; c1_i6 < 3; c1_i6++) {
    c1_x[c1_i6] = c1_ZBw[c1_i6];
  }

  c1_b_y = 0.0;
  c1_scale = 2.2250738585072014E-308;
  c1_eml_int_forloop_overflow_check(chartInstance);
  for (c1_k = 1; c1_k < 4; c1_k++) {
    c1_b_k = c1_k;
    c1_b_x = c1_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c1_b_k), 1, 3, 1, 0) - 1];
    c1_c_x = c1_b_x;
    c1_absxk = muDoubleScalarAbs(c1_c_x);
    if (c1_absxk > c1_scale) {
      c1_t = c1_scale / c1_absxk;
      c1_b_y = 1.0 + c1_b_y * c1_t * c1_t;
      c1_scale = c1_absxk;
    } else {
      c1_t = c1_absxk / c1_scale;
      c1_b_y += c1_t * c1_t;
    }
  }

  c1_b_y = c1_scale * muDoubleScalarSqrt(c1_b_y);
  for (c1_i7 = 0; c1_i7 < 3; c1_i7++) {
    c1_x[c1_i7] = -c1_ZBw[c1_i7];
  }

  c1_c_y = c1_b_y;
  c1_d_y = c1_c_y;
  for (c1_i8 = 0; c1_i8 < 3; c1_i8++) {
    c1_ZW[c1_i8] = c1_x[c1_i8] / c1_d_y;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 12);
  c1_d_x = c1_ANG_course;
  c1_e_x = c1_d_x;
  c1_e_x = muDoubleScalarCos(c1_e_x);
  c1_f_x = c1_ANG_course;
  c1_g_x = c1_f_x;
  c1_g_x = muDoubleScalarSin(c1_g_x);
  c1_h_x[0] = c1_e_x;
  c1_h_x[1] = c1_g_x;
  c1_h_x[2] = 0.0;
  for (c1_i9 = 0; c1_i9 < 3; c1_i9++) {
    c1_XC[c1_i9] = c1_h_x[c1_i9];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 13);
  for (c1_i10 = 0; c1_i10 < 3; c1_i10++) {
    c1_b_ZW[c1_i10] = c1_ZW[c1_i10];
  }

  for (c1_i11 = 0; c1_i11 < 3; c1_i11++) {
    c1_b_XC[c1_i11] = c1_XC[c1_i11];
  }

  c1_cross(chartInstance, c1_b_ZW, c1_b_XC, c1_dv1);
  for (c1_i12 = 0; c1_i12 < 3; c1_i12++) {
    c1_YW[c1_i12] = c1_dv1[c1_i12];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 14);
  for (c1_i13 = 0; c1_i13 < 3; c1_i13++) {
    c1_b_YW[c1_i13] = c1_YW[c1_i13];
  }

  for (c1_i14 = 0; c1_i14 < 3; c1_i14++) {
    c1_c_ZW[c1_i14] = c1_ZW[c1_i14];
  }

  c1_cross(chartInstance, c1_b_YW, c1_c_ZW, c1_dv2);
  for (c1_i15 = 0; c1_i15 < 3; c1_i15++) {
    c1_XW[c1_i15] = c1_dv2[c1_i15];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 15);
  for (c1_i16 = 0; c1_i16 < 3; c1_i16++) {
    c1_y[c1_i16] = c1_XW[c1_i16];
  }

  for (c1_i17 = 0; c1_i17 < 3; c1_i17++) {
    c1_y[c1_i17 + 3] = c1_YW[c1_i17];
  }

  for (c1_i18 = 0; c1_i18 < 3; c1_i18++) {
    c1_y[c1_i18 + 6] = c1_ZW[c1_i18];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -15);
  sf_debug_symbol_scope_pop();
  for (c1_i19 = 0; c1_i19 < 9; c1_i19++) {
    (*c1_e_y)[c1_i19] = c1_y[c1_i19];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
}

static void initSimStructsc1_UAV(SFc1_UAVInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber)
{
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i20;
  int32_T c1_i21;
  int32_T c1_i22;
  real_T c1_b_inData[9];
  int32_T c1_i23;
  int32_T c1_i24;
  int32_T c1_i25;
  real_T c1_u[9];
  const mxArray *c1_y = NULL;
  SFc1_UAVInstanceStruct *chartInstance;
  chartInstance = (SFc1_UAVInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i20 = 0;
  for (c1_i21 = 0; c1_i21 < 3; c1_i21++) {
    for (c1_i22 = 0; c1_i22 < 3; c1_i22++) {
      c1_b_inData[c1_i22 + c1_i20] = (*(real_T (*)[9])c1_inData)[c1_i22 + c1_i20];
    }

    c1_i20 += 3;
  }

  c1_i23 = 0;
  for (c1_i24 = 0; c1_i24 < 3; c1_i24++) {
    for (c1_i25 = 0; c1_i25 < 3; c1_i25++) {
      c1_u[c1_i25 + c1_i23] = c1_b_inData[c1_i25 + c1_i23];
    }

    c1_i23 += 3;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_emlrt_marshallIn(SFc1_UAVInstanceStruct *chartInstance, const
  mxArray *c1_y, const char_T *c1_identifier, real_T c1_b_y[9])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_y), &c1_thisId, c1_b_y);
  sf_mex_destroy(&c1_y);
}

static void c1_b_emlrt_marshallIn(SFc1_UAVInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[9])
{
  real_T c1_dv3[9];
  int32_T c1_i26;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv3, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c1_i26 = 0; c1_i26 < 9; c1_i26++) {
    c1_y[c1_i26] = c1_dv3[c1_i26];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_y;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_b_y[9];
  int32_T c1_i27;
  int32_T c1_i28;
  int32_T c1_i29;
  SFc1_UAVInstanceStruct *chartInstance;
  chartInstance = (SFc1_UAVInstanceStruct *)chartInstanceVoid;
  c1_y = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_y), &c1_thisId, c1_b_y);
  sf_mex_destroy(&c1_y);
  c1_i27 = 0;
  for (c1_i28 = 0; c1_i28 < 3; c1_i28++) {
    for (c1_i29 = 0; c1_i29 < 3; c1_i29++) {
      (*(real_T (*)[9])c1_outData)[c1_i29 + c1_i27] = c1_b_y[c1_i29 + c1_i27];
    }

    c1_i27 += 3;
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i30;
  real_T c1_b_inData[4];
  int32_T c1_i31;
  real_T c1_u[4];
  const mxArray *c1_y = NULL;
  SFc1_UAVInstanceStruct *chartInstance;
  chartInstance = (SFc1_UAVInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i30 = 0; c1_i30 < 4; c1_i30++) {
    c1_b_inData[c1_i30] = (*(real_T (*)[4])c1_inData)[c1_i30];
  }

  for (c1_i31 = 0; c1_i31 < 4; c1_i31++) {
    c1_u[c1_i31] = c1_b_inData[c1_i31];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 4), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_UAVInstanceStruct *chartInstance;
  chartInstance = (SFc1_UAVInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_c_emlrt_marshallIn(SFc1_UAVInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d0, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_nargout;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_UAVInstanceStruct *chartInstance;
  chartInstance = (SFc1_UAVInstanceStruct *)chartInstanceVoid;
  c1_nargout = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_nargout), &c1_thisId);
  sf_mex_destroy(&c1_nargout);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i32;
  real_T c1_b_inData[3];
  int32_T c1_i33;
  real_T c1_u[3];
  const mxArray *c1_y = NULL;
  SFc1_UAVInstanceStruct *chartInstance;
  chartInstance = (SFc1_UAVInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i32 = 0; c1_i32 < 3; c1_i32++) {
    c1_b_inData[c1_i32] = (*(real_T (*)[3])c1_inData)[c1_i32];
  }

  for (c1_i33 = 0; c1_i33 < 3; c1_i33++) {
    c1_u[c1_i33] = c1_b_inData[c1_i33];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_d_emlrt_marshallIn(SFc1_UAVInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[3])
{
  real_T c1_dv4[3];
  int32_T c1_i34;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv4, 1, 0, 0U, 1, 0U, 1, 3);
  for (c1_i34 = 0; c1_i34 < 3; c1_i34++) {
    c1_y[c1_i34] = c1_dv4[c1_i34];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_XW;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[3];
  int32_T c1_i35;
  SFc1_UAVInstanceStruct *chartInstance;
  chartInstance = (SFc1_UAVInstanceStruct *)chartInstanceVoid;
  c1_XW = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_XW), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_XW);
  for (c1_i35 = 0; c1_i35 < 3; c1_i35++) {
    (*(real_T (*)[3])c1_outData)[c1_i35] = c1_y[c1_i35];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

const mxArray *sf_c1_UAV_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo;
  c1_ResolvedFunctionInfo c1_info[29];
  const mxArray *c1_m0 = NULL;
  int32_T c1_i36;
  c1_ResolvedFunctionInfo *c1_r0;
  c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  c1_info_helper(c1_info);
  sf_mex_assign(&c1_m0, sf_mex_createstruct("nameCaptureInfo", 1, 29), FALSE);
  for (c1_i36 = 0; c1_i36 < 29; c1_i36++) {
    c1_r0 = &c1_info[c1_i36];
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->context)), "context", "nameCaptureInfo",
                    c1_i36);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c1_r0->name)), "name", "nameCaptureInfo", c1_i36);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c1_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c1_i36);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->resolved)), "resolved", "nameCaptureInfo",
                    c1_i36);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c1_i36);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c1_i36);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c1_i36);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c1_i36);
  }

  sf_mex_assign(&c1_nameCaptureInfo, c1_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c1_nameCaptureInfo);
  return c1_nameCaptureInfo;
}

static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[29])
{
  c1_info[0].context = "";
  c1_info[0].name = "mrdivide";
  c1_info[0].dominantType = "double";
  c1_info[0].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c1_info[0].fileTimeLo = 1325098938U;
  c1_info[0].fileTimeHi = 0U;
  c1_info[0].mFileTimeLo = 1319708366U;
  c1_info[0].mFileTimeHi = 0U;
  c1_info[1].context =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c1_info[1].name = "rdivide";
  c1_info[1].dominantType = "double";
  c1_info[1].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[1].fileTimeLo = 1286797244U;
  c1_info[1].fileTimeHi = 0U;
  c1_info[1].mFileTimeLo = 0U;
  c1_info[1].mFileTimeHi = 0U;
  c1_info[2].context =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[2].name = "eml_div";
  c1_info[2].dominantType = "double";
  c1_info[2].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_div.m";
  c1_info[2].fileTimeLo = 1313326210U;
  c1_info[2].fileTimeHi = 0U;
  c1_info[2].mFileTimeLo = 0U;
  c1_info[2].mFileTimeHi = 0U;
  c1_info[3].context = "";
  c1_info[3].name = "norm";
  c1_info[3].dominantType = "double";
  c1_info[3].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/norm.m";
  c1_info[3].fileTimeLo = 1286797226U;
  c1_info[3].fileTimeHi = 0U;
  c1_info[3].mFileTimeLo = 0U;
  c1_info[3].mFileTimeHi = 0U;
  c1_info[4].context =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c1_info[4].name = "eml_index_class";
  c1_info[4].dominantType = "";
  c1_info[4].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[4].fileTimeLo = 1286797178U;
  c1_info[4].fileTimeHi = 0U;
  c1_info[4].mFileTimeLo = 0U;
  c1_info[4].mFileTimeHi = 0U;
  c1_info[5].context =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c1_info[5].name = "eml_xnrm2";
  c1_info[5].dominantType = "int32";
  c1_info[5].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c1_info[5].fileTimeLo = 1299051576U;
  c1_info[5].fileTimeHi = 0U;
  c1_info[5].mFileTimeLo = 0U;
  c1_info[5].mFileTimeHi = 0U;
  c1_info[6].context =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c1_info[6].name = "eml_blas_inline";
  c1_info[6].dominantType = "";
  c1_info[6].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c1_info[6].fileTimeLo = 1299051568U;
  c1_info[6].fileTimeHi = 0U;
  c1_info[6].mFileTimeLo = 0U;
  c1_info[6].mFileTimeHi = 0U;
  c1_info[7].context =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m";
  c1_info[7].name = "eml_refblas_xnrm2";
  c1_info[7].dominantType = "int32";
  c1_info[7].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c1_info[7].fileTimeLo = 1299051584U;
  c1_info[7].fileTimeHi = 0U;
  c1_info[7].mFileTimeLo = 0U;
  c1_info[7].mFileTimeHi = 0U;
  c1_info[8].context =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c1_info[8].name = "realmin";
  c1_info[8].dominantType = "char";
  c1_info[8].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/realmin.m";
  c1_info[8].fileTimeLo = 1307629642U;
  c1_info[8].fileTimeHi = 0U;
  c1_info[8].mFileTimeLo = 0U;
  c1_info[8].mFileTimeHi = 0U;
  c1_info[9].context =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/realmin.m";
  c1_info[9].name = "eml_realmin";
  c1_info[9].dominantType = "char";
  c1_info[9].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c1_info[9].fileTimeLo = 1307629644U;
  c1_info[9].fileTimeHi = 0U;
  c1_info[9].mFileTimeLo = 0U;
  c1_info[9].mFileTimeHi = 0U;
  c1_info[10].context =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c1_info[10].name = "eml_float_model";
  c1_info[10].dominantType = "char";
  c1_info[10].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c1_info[10].fileTimeLo = 1307629642U;
  c1_info[10].fileTimeHi = 0U;
  c1_info[10].mFileTimeLo = 0U;
  c1_info[10].mFileTimeHi = 0U;
  c1_info[11].context =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c1_info[11].name = "eml_index_class";
  c1_info[11].dominantType = "";
  c1_info[11].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[11].fileTimeLo = 1286797178U;
  c1_info[11].fileTimeHi = 0U;
  c1_info[11].mFileTimeLo = 0U;
  c1_info[11].mFileTimeHi = 0U;
  c1_info[12].context =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c1_info[12].name = "eml_index_minus";
  c1_info[12].dominantType = "int32";
  c1_info[12].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c1_info[12].fileTimeLo = 1286797178U;
  c1_info[12].fileTimeHi = 0U;
  c1_info[12].mFileTimeLo = 0U;
  c1_info[12].mFileTimeHi = 0U;
  c1_info[13].context =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c1_info[13].name = "eml_index_class";
  c1_info[13].dominantType = "";
  c1_info[13].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[13].fileTimeLo = 1286797178U;
  c1_info[13].fileTimeHi = 0U;
  c1_info[13].mFileTimeLo = 0U;
  c1_info[13].mFileTimeHi = 0U;
  c1_info[14].context =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c1_info[14].name = "eml_index_times";
  c1_info[14].dominantType = "int32";
  c1_info[14].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c1_info[14].fileTimeLo = 1286797180U;
  c1_info[14].fileTimeHi = 0U;
  c1_info[14].mFileTimeLo = 0U;
  c1_info[14].mFileTimeHi = 0U;
  c1_info[15].context =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c1_info[15].name = "eml_index_class";
  c1_info[15].dominantType = "";
  c1_info[15].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[15].fileTimeLo = 1286797178U;
  c1_info[15].fileTimeHi = 0U;
  c1_info[15].mFileTimeLo = 0U;
  c1_info[15].mFileTimeHi = 0U;
  c1_info[16].context =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c1_info[16].name = "eml_index_plus";
  c1_info[16].dominantType = "int32";
  c1_info[16].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c1_info[16].fileTimeLo = 1286797178U;
  c1_info[16].fileTimeHi = 0U;
  c1_info[16].mFileTimeLo = 0U;
  c1_info[16].mFileTimeHi = 0U;
  c1_info[17].context =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c1_info[17].name = "eml_index_class";
  c1_info[17].dominantType = "";
  c1_info[17].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[17].fileTimeLo = 1286797178U;
  c1_info[17].fileTimeHi = 0U;
  c1_info[17].mFileTimeLo = 0U;
  c1_info[17].mFileTimeHi = 0U;
  c1_info[18].context =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c1_info[18].name = "eml_int_forloop_overflow_check";
  c1_info[18].dominantType = "";
  c1_info[18].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c1_info[18].fileTimeLo = 1311233716U;
  c1_info[18].fileTimeHi = 0U;
  c1_info[18].mFileTimeLo = 0U;
  c1_info[18].mFileTimeHi = 0U;
  c1_info[19].context =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c1_info[19].name = "intmax";
  c1_info[19].dominantType = "char";
  c1_info[19].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/intmax.m";
  c1_info[19].fileTimeLo = 1311233716U;
  c1_info[19].fileTimeHi = 0U;
  c1_info[19].mFileTimeLo = 0U;
  c1_info[19].mFileTimeHi = 0U;
  c1_info[20].context =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c1_info[20].name = "abs";
  c1_info[20].dominantType = "double";
  c1_info[20].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[20].fileTimeLo = 1286797094U;
  c1_info[20].fileTimeHi = 0U;
  c1_info[20].mFileTimeLo = 0U;
  c1_info[20].mFileTimeHi = 0U;
  c1_info[21].context =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[21].name = "eml_scalar_abs";
  c1_info[21].dominantType = "double";
  c1_info[21].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c1_info[21].fileTimeLo = 1286797112U;
  c1_info[21].fileTimeHi = 0U;
  c1_info[21].mFileTimeLo = 0U;
  c1_info[21].mFileTimeHi = 0U;
  c1_info[22].context = "";
  c1_info[22].name = "rdivide";
  c1_info[22].dominantType = "double";
  c1_info[22].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[22].fileTimeLo = 1286797244U;
  c1_info[22].fileTimeHi = 0U;
  c1_info[22].mFileTimeLo = 0U;
  c1_info[22].mFileTimeHi = 0U;
  c1_info[23].context = "";
  c1_info[23].name = "cos";
  c1_info[23].dominantType = "double";
  c1_info[23].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/cos.m";
  c1_info[23].fileTimeLo = 1286797106U;
  c1_info[23].fileTimeHi = 0U;
  c1_info[23].mFileTimeLo = 0U;
  c1_info[23].mFileTimeHi = 0U;
  c1_info[24].context =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/cos.m";
  c1_info[24].name = "eml_scalar_cos";
  c1_info[24].dominantType = "double";
  c1_info[24].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c1_info[24].fileTimeLo = 1286797122U;
  c1_info[24].fileTimeHi = 0U;
  c1_info[24].mFileTimeLo = 0U;
  c1_info[24].mFileTimeHi = 0U;
  c1_info[25].context = "";
  c1_info[25].name = "sin";
  c1_info[25].dominantType = "double";
  c1_info[25].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/sin.m";
  c1_info[25].fileTimeLo = 1286797150U;
  c1_info[25].fileTimeHi = 0U;
  c1_info[25].mFileTimeLo = 0U;
  c1_info[25].mFileTimeHi = 0U;
  c1_info[26].context =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/sin.m";
  c1_info[26].name = "eml_scalar_sin";
  c1_info[26].dominantType = "double";
  c1_info[26].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  c1_info[26].fileTimeLo = 1286797136U;
  c1_info[26].fileTimeHi = 0U;
  c1_info[26].mFileTimeLo = 0U;
  c1_info[26].mFileTimeHi = 0U;
  c1_info[27].context = "";
  c1_info[27].name = "cross";
  c1_info[27].dominantType = "double";
  c1_info[27].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/specfun/cross.m";
  c1_info[27].fileTimeLo = 1286797242U;
  c1_info[27].fileTimeHi = 0U;
  c1_info[27].mFileTimeLo = 0U;
  c1_info[27].mFileTimeHi = 0U;
  c1_info[28].context =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/specfun/cross.m";
  c1_info[28].name = "mtimes";
  c1_info[28].dominantType = "double";
  c1_info[28].resolved =
    "[ILXE]E:/Program Files/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[28].fileTimeLo = 1289494492U;
  c1_info[28].fileTimeHi = 0U;
  c1_info[28].mFileTimeLo = 0U;
  c1_info[28].mFileTimeHi = 0U;
}

static void c1_eml_int_forloop_overflow_check(SFc1_UAVInstanceStruct
  *chartInstance)
{
}

static void c1_cross(SFc1_UAVInstanceStruct *chartInstance, real_T c1_a[3],
                     real_T c1_b[3], real_T c1_c[3])
{
  real_T c1_b_a;
  real_T c1_b_b;
  real_T c1_y;
  real_T c1_c_a;
  real_T c1_c_b;
  real_T c1_b_y;
  real_T c1_c1;
  real_T c1_d_a;
  real_T c1_d_b;
  real_T c1_c_y;
  real_T c1_e_a;
  real_T c1_e_b;
  real_T c1_d_y;
  real_T c1_c2;
  real_T c1_f_a;
  real_T c1_f_b;
  real_T c1_e_y;
  real_T c1_g_a;
  real_T c1_g_b;
  real_T c1_f_y;
  real_T c1_c3;
  c1_b_a = c1_a[1];
  c1_b_b = c1_b[2];
  c1_y = c1_b_a * c1_b_b;
  c1_c_a = c1_a[2];
  c1_c_b = c1_b[1];
  c1_b_y = c1_c_a * c1_c_b;
  c1_c1 = c1_y - c1_b_y;
  c1_d_a = c1_a[2];
  c1_d_b = c1_b[0];
  c1_c_y = c1_d_a * c1_d_b;
  c1_e_a = c1_a[0];
  c1_e_b = c1_b[2];
  c1_d_y = c1_e_a * c1_e_b;
  c1_c2 = c1_c_y - c1_d_y;
  c1_f_a = c1_a[0];
  c1_f_b = c1_b[1];
  c1_e_y = c1_f_a * c1_f_b;
  c1_g_a = c1_a[1];
  c1_g_b = c1_b[0];
  c1_f_y = c1_g_a * c1_g_b;
  c1_c3 = c1_e_y - c1_f_y;
  c1_c[0] = c1_c1;
  c1_c[1] = c1_c2;
  c1_c[2] = c1_c3;
}

static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_UAVInstanceStruct *chartInstance;
  chartInstance = (SFc1_UAVInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static int32_T c1_e_emlrt_marshallIn(SFc1_UAVInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i37;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i37, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i37;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_UAVInstanceStruct *chartInstance;
  chartInstance = (SFc1_UAVInstanceStruct *)chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent),
    &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static uint8_T c1_f_emlrt_marshallIn(SFc1_UAVInstanceStruct *chartInstance,
  const mxArray *c1_b_is_active_c1_UAV, const char_T *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_is_active_c1_UAV),
    &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_UAV);
  return c1_y;
}

static uint8_T c1_g_emlrt_marshallIn(SFc1_UAVInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void init_dsm_address_info(SFc1_UAVInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c1_UAV_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2404384282U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1551649206U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(761906591U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3305483463U);
}

mxArray *sf_c1_UAV_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("KKNwwzEkM6ifVkWdpc5dYH");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(3);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

static const mxArray *sf_get_sim_state_info_c1_UAV(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"y\",},{M[8],M[0],T\"is_active_c1_UAV\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_UAV_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_UAVInstanceStruct *chartInstance;
    chartInstance = (SFc1_UAVInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart(_UAVMachineNumber_,
          1,
          1,
          1,
          2,
          0,
          0,
          0,
          0,
          0,
          &(chartInstance->chartNumber),
          &(chartInstance->instanceNumber),
          ssGetPath(S),
          (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_UAVMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting(_UAVMachineNumber_,
            chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(_UAVMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"u");
          _SFD_SET_DATA_PROPS(1,2,0,1,"y");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,308);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)
            c1_sf_marshallIn);
        }

        {
          real_T (*c1_u)[4];
          real_T (*c1_y)[9];
          c1_y = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
          c1_u = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c1_u);
          _SFD_SET_DATA_VALUE_PTR(1U, *c1_y);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_UAVMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization()
{
  return "IMwp5uM8v6c77W6cg401I";
}

static void sf_opaque_initialize_c1_UAV(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_UAVInstanceStruct*) chartInstanceVar)->S,0);
  initialize_params_c1_UAV((SFc1_UAVInstanceStruct*) chartInstanceVar);
  initialize_c1_UAV((SFc1_UAVInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_UAV(void *chartInstanceVar)
{
  enable_c1_UAV((SFc1_UAVInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_UAV(void *chartInstanceVar)
{
  disable_c1_UAV((SFc1_UAVInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_UAV(void *chartInstanceVar)
{
  sf_c1_UAV((SFc1_UAVInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c1_UAV(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c1_UAV((SFc1_UAVInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_UAV();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c1_UAV(SimStruct* S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_UAV();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c1_UAV((SFc1_UAVInstanceStruct*)chartInfo->chartInstance,
                       mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c1_UAV(SimStruct* S)
{
  return sf_internal_get_sim_state_c1_UAV(S);
}

static void sf_opaque_set_sim_state_c1_UAV(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c1_UAV(S, st);
}

static void sf_opaque_terminate_c1_UAV(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_UAVInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c1_UAV((SFc1_UAVInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }

  unload_UAV_optimization_info();
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_UAV((SFc1_UAVInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_UAV(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_UAV((SFc1_UAVInstanceStruct*)(((ChartInfoStruct *)
      ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_UAV(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_UAV_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,1,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,1,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,1,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,1,1);
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(520911333U));
  ssSetChecksum1(S,(445379532U));
  ssSetChecksum2(S,(3981950658U));
  ssSetChecksum3(S,(592869877U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c1_UAV(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_UAV(SimStruct *S)
{
  SFc1_UAVInstanceStruct *chartInstance;
  chartInstance = (SFc1_UAVInstanceStruct *)malloc(sizeof(SFc1_UAVInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_UAVInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c1_UAV;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c1_UAV;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c1_UAV;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_UAV;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_UAV;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c1_UAV;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c1_UAV;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c1_UAV;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_UAV;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_UAV;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c1_UAV;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c1_UAV_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_UAV(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_UAV(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_UAV(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_UAV_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}

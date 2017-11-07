// This file is released under the 3-clause BSD license. See COPYING-BSD.
// Generated by builder.sce : Please, do not edit this file
// ----------------------------------------------------------------------------
//
if win64() then
  warning(_("This module requires a Windows x86 platform."));
  return
end
//
General_x86_path = get_absolute_file_path('loader_x86.sce');
//
// ulink previous function with same name
[bOK, ilib] = c_link('x2c_And_FiP8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_And_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_And_FiP32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_AutoSwitch_FiP8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_AutoSwitch_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_AutoSwitch_FiP32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_AutoSwitch_Float32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_AutoSwitch_Float64_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Constant_FiP8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Constant_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Constant_FiP32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Constant_Float32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Constant_Float64_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Gain_FiP8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Gain_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Gain_FiP32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Gain_Float32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Gain_Float64_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Inport_int8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Inport_int16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Inport_int32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Inport_float32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Inport_float64_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Int2Re_FiP8_Float32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Int2Re_FiP16_Float32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Int2Re_FiP32_Float32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Int2Re_FiP8_Float64_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Int2Re_FiP16_Float64_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Int2Re_FiP32_Float64_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Limitation_FiP8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Limitation_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Limitation_FiP32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Limitation_Float32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Limitation_Float64_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_LookupTable_FiP8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_LookupTable_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_LookupTable_FiP32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_LoopBreaker_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_LoopBreaker_FiP32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_LoopBreaker_Float32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_LoopBreaker_Float64_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_ManualSwitch_FiP8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_ManualSwitch_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_ManualSwitch_FiP32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_ManualSwitch_Float32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_ManualSwitch_Float64_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Maximum_FiP8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Maximum_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Maximum_FiP32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Maximum_Float32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Maximum_Float64_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Minimum_FiP8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Minimum_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Minimum_FiP32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Minimum_Float32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Minimum_Float64_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_MinMaxPeriod_FiP8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_MinMaxPeriod_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_MinMaxPeriod_FiP32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_MinMaxPeriod_Float32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_MinMaxPeriod_Float64_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Not_FiP8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Not_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Not_FiP32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Or_FiP8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Or_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Or_FiP32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Outport_int8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Outport_int16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Outport_int32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Outport_float32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Outport_float64_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_RateLimiter_FiP8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_RateLimiter_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_RateLimiter_FiP32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_RateLimiter_Float32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_RateLimiter_Float64_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Real2I_Float32_FiP8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Real2I_Float32_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Real2I_Float32_FiP32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Real2I_Float64_FiP8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Real2I_Float64_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Real2I_Float64_FiP32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Saturation_FiP8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Saturation_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Saturation_FiP32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Saturation_Float32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Saturation_Float64_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_SaveSignal_FiP8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_SaveSignal_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_SaveSignal_FiP32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_SaveSignal_Float32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_SaveSignal_Float64_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Selector_FiP8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Selector_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Selector_FiP32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Selector_Float32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Selector_Float64_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Sequencer_FiP8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Sequencer_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Sequencer_FiP32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Sequencer_Float32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Sequencer_Float64_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Sin2Limiter_FiP8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Sin2Limiter_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Sin2Limiter_FiP32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Sin2Limiter_Float32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Sin2Limiter_Float64_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Sin3Gen_FiP8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Sin3Gen_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Sin3Gen_FiP32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Sin3Gen_Float32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Sin3Gen_Float64_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_SinGen_FiP8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_SinGen_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_SinGen_FiP32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_SinGen_Float32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_SinGen_Float64_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_TypeConv_FiP8_16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_TypeConv_FiP8_32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_TypeConv_FiP16_8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_TypeConv_FiP16_32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_TypeConv_FiP32_8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_TypeConv_FiP32_16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_uConstant_FiP8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_uConstant_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_uConstant_FiP32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_uConstant_Float32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_uConstant_Float64_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_uGain_FiP8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_uGain_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_uGain_FiP32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_uGain_Float32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_uGain_Float64_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_uRateLimiter_FiP8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_uRateLimiter_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_uRateLimiter_FiP32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_uRateLimiter_Float32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_uRateLimiter_Float64_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_uSaveSignal_FiP8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_uSaveSignal_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_uSaveSignal_FiP32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_uSaveSignal_Float32_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_uSaveSignal_Float64_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Xor_FiP8_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Xor_FiP16_C');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('x2c_Xor_FiP32_C');
if bOK then
  ulink(ilib);
end
//
link(General_x86_path + 'libGeneral_x86' + getdynlibext(), ['x2c_And_FiP8_C','x2c_And_FiP16_C','x2c_And_FiP32_C','x2c_AutoSwitch_FiP8_C','x2c_AutoSwitch_FiP16_C','x2c_AutoSwitch_FiP32_C','x2c_AutoSwitch_Float32_C','x2c_AutoSwitch_Float64_C','x2c_Constant_FiP8_C','x2c_Constant_FiP16_C','x2c_Constant_FiP32_C','x2c_Constant_Float32_C','x2c_Constant_Float64_C','x2c_Gain_FiP8_C','x2c_Gain_FiP16_C','x2c_Gain_FiP32_C','x2c_Gain_Float32_C','x2c_Gain_Float64_C','x2c_Inport_int8_C','x2c_Inport_int16_C','x2c_Inport_int32_C','x2c_Inport_float32_C','x2c_Inport_float64_C','x2c_Int2Re_FiP8_Float32_C','x2c_Int2Re_FiP16_Float32_C','x2c_Int2Re_FiP32_Float32_C','x2c_Int2Re_FiP8_Float64_C','x2c_Int2Re_FiP16_Float64_C','x2c_Int2Re_FiP32_Float64_C','x2c_Limitation_FiP8_C','x2c_Limitation_FiP16_C','x2c_Limitation_FiP32_C','x2c_Limitation_Float32_C','x2c_Limitation_Float64_C','x2c_LookupTable_FiP8_C','x2c_LookupTable_FiP16_C','x2c_LookupTable_FiP32_C','x2c_LoopBreaker_FiP16_C','x2c_LoopBreaker_FiP32_C','x2c_LoopBreaker_Float32_C','x2c_LoopBreaker_Float64_C','x2c_ManualSwitch_FiP8_C','x2c_ManualSwitch_FiP16_C','x2c_ManualSwitch_FiP32_C','x2c_ManualSwitch_Float32_C','x2c_ManualSwitch_Float64_C','x2c_Maximum_FiP8_C','x2c_Maximum_FiP16_C','x2c_Maximum_FiP32_C','x2c_Maximum_Float32_C','x2c_Maximum_Float64_C','x2c_Minimum_FiP8_C','x2c_Minimum_FiP16_C','x2c_Minimum_FiP32_C','x2c_Minimum_Float32_C','x2c_Minimum_Float64_C','x2c_MinMaxPeriod_FiP8_C','x2c_MinMaxPeriod_FiP16_C','x2c_MinMaxPeriod_FiP32_C','x2c_MinMaxPeriod_Float32_C','x2c_MinMaxPeriod_Float64_C','x2c_Not_FiP8_C','x2c_Not_FiP16_C','x2c_Not_FiP32_C','x2c_Or_FiP8_C','x2c_Or_FiP16_C','x2c_Or_FiP32_C','x2c_Outport_int8_C','x2c_Outport_int16_C','x2c_Outport_int32_C','x2c_Outport_float32_C','x2c_Outport_float64_C','x2c_RateLimiter_FiP8_C','x2c_RateLimiter_FiP16_C','x2c_RateLimiter_FiP32_C','x2c_RateLimiter_Float32_C','x2c_RateLimiter_Float64_C','x2c_Real2I_Float32_FiP8_C','x2c_Real2I_Float32_FiP16_C','x2c_Real2I_Float32_FiP32_C','x2c_Real2I_Float64_FiP8_C','x2c_Real2I_Float64_FiP16_C','x2c_Real2I_Float64_FiP32_C','x2c_Saturation_FiP8_C','x2c_Saturation_FiP16_C','x2c_Saturation_FiP32_C','x2c_Saturation_Float32_C','x2c_Saturation_Float64_C','x2c_SaveSignal_FiP8_C','x2c_SaveSignal_FiP16_C','x2c_SaveSignal_FiP32_C','x2c_SaveSignal_Float32_C','x2c_SaveSignal_Float64_C','x2c_Selector_FiP8_C','x2c_Selector_FiP16_C','x2c_Selector_FiP32_C','x2c_Selector_Float32_C','x2c_Selector_Float64_C','x2c_Sequencer_FiP8_C','x2c_Sequencer_FiP16_C','x2c_Sequencer_FiP32_C','x2c_Sequencer_Float32_C','x2c_Sequencer_Float64_C','x2c_Sin2Limiter_FiP8_C','x2c_Sin2Limiter_FiP16_C','x2c_Sin2Limiter_FiP32_C','x2c_Sin2Limiter_Float32_C','x2c_Sin2Limiter_Float64_C','x2c_Sin3Gen_FiP8_C','x2c_Sin3Gen_FiP16_C','x2c_Sin3Gen_FiP32_C','x2c_Sin3Gen_Float32_C','x2c_Sin3Gen_Float64_C','x2c_SinGen_FiP8_C','x2c_SinGen_FiP16_C','x2c_SinGen_FiP32_C','x2c_SinGen_Float32_C','x2c_SinGen_Float64_C','x2c_TypeConv_FiP8_16_C','x2c_TypeConv_FiP8_32_C','x2c_TypeConv_FiP16_8_C','x2c_TypeConv_FiP16_32_C','x2c_TypeConv_FiP32_8_C','x2c_TypeConv_FiP32_16_C','x2c_uConstant_FiP8_C','x2c_uConstant_FiP16_C','x2c_uConstant_FiP32_C','x2c_uConstant_Float32_C','x2c_uConstant_Float64_C','x2c_uGain_FiP8_C','x2c_uGain_FiP16_C','x2c_uGain_FiP32_C','x2c_uGain_Float32_C','x2c_uGain_Float64_C','x2c_uRateLimiter_FiP8_C','x2c_uRateLimiter_FiP16_C','x2c_uRateLimiter_FiP32_C','x2c_uRateLimiter_Float32_C','x2c_uRateLimiter_Float64_C','x2c_uSaveSignal_FiP8_C','x2c_uSaveSignal_FiP16_C','x2c_uSaveSignal_FiP32_C','x2c_uSaveSignal_Float32_C','x2c_uSaveSignal_Float64_C','x2c_Xor_FiP8_C','x2c_Xor_FiP16_C','x2c_Xor_FiP32_C'],'c');
// remove temp. variables on stack
clear General_x86_path;
clear bOK;
clear ilib;
// ----------------------------------------------------------------------------
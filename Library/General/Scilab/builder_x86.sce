// This file was generated by createLibraryBuilder.sce on 03-03-2017 01:15

funcprot(0);
jimport at.lcm.x2c.utils.Utils;
msvc = findmsvccompiler();
if(msvc ~= "unknown") then 
    bOK = configure_msvc();
end
if ~haveacompiler() then
    mprintf("Building General library for x86 system skipped (no compiler found).\n");
    [compileCompFDone] = return(%f)
end

X2C_ROOT = jinvoke(jinvoke(Utils, "getRootDirectory"), "toString");
X2C_LIB_PATH = get_absolute_file_path("builder_x86.sce");
X2C_LIB_PATH = dirname(X2C_LIB_PATH);

// delete "is-compiled" marker
mdelete("Library_is_compiled_for_x86.txt");

names = [ "x2c_And_FiP8_C" "x2c_And_FiP16_C" "x2c_And_FiP32_C" "x2c_AutoSwitch_FiP8_C" "x2c_AutoSwitch_FiP16_C" "x2c_AutoSwitch_FiP32_C" "x2c_AutoSwitch_Float32_C" "x2c_AutoSwitch_Float64_C" "x2c_Constant_FiP8_C" "x2c_Constant_FiP16_C" "x2c_Constant_FiP32_C" "x2c_Constant_Float32_C" "x2c_Constant_Float64_C" "x2c_Gain_FiP8_C" "x2c_Gain_FiP16_C" "x2c_Gain_FiP32_C" "x2c_Gain_Float32_C" "x2c_Gain_Float64_C" "x2c_Inport_int8_C" "x2c_Inport_int16_C" "x2c_Inport_int32_C" "x2c_Inport_float32_C" "x2c_Inport_float64_C" "x2c_Int2Re_FiP8_Float32_C" "x2c_Int2Re_FiP16_Float32_C" "x2c_Int2Re_FiP32_Float32_C" "x2c_Int2Re_FiP8_Float64_C" "x2c_Int2Re_FiP16_Float64_C" "x2c_Int2Re_FiP32_Float64_C" "x2c_Limitation_FiP8_C" "x2c_Limitation_FiP16_C" "x2c_Limitation_FiP32_C" "x2c_Limitation_Float32_C" "x2c_Limitation_Float64_C" "x2c_LookupTable_FiP8_C" "x2c_LookupTable_FiP16_C" "x2c_LookupTable_FiP32_C" "x2c_LoopBreaker_FiP16_C" "x2c_LoopBreaker_FiP32_C" "x2c_LoopBreaker_Float32_C" "x2c_LoopBreaker_Float64_C" "x2c_ManualSwitch_FiP8_C" "x2c_ManualSwitch_FiP16_C" "x2c_ManualSwitch_FiP32_C" "x2c_ManualSwitch_Float32_C" "x2c_ManualSwitch_Float64_C" "x2c_Maximum_FiP8_C" "x2c_Maximum_FiP16_C" "x2c_Maximum_FiP32_C" "x2c_Maximum_Float32_C" "x2c_Maximum_Float64_C" "x2c_Minimum_FiP8_C" "x2c_Minimum_FiP16_C" "x2c_Minimum_FiP32_C" "x2c_Minimum_Float32_C" "x2c_Minimum_Float64_C" "x2c_MinMaxPeriod_FiP8_C" "x2c_MinMaxPeriod_FiP16_C" "x2c_MinMaxPeriod_FiP32_C" "x2c_MinMaxPeriod_Float32_C" "x2c_MinMaxPeriod_Float64_C" "x2c_Not_FiP8_C" "x2c_Not_FiP16_C" "x2c_Not_FiP32_C" "x2c_Or_FiP8_C" "x2c_Or_FiP16_C" "x2c_Or_FiP32_C" "x2c_Outport_int8_C" "x2c_Outport_int16_C" "x2c_Outport_int32_C" "x2c_Outport_float32_C" "x2c_Outport_float64_C" "x2c_RateLimiter_FiP8_C" "x2c_RateLimiter_FiP16_C" "x2c_RateLimiter_FiP32_C" "x2c_RateLimiter_Float32_C" "x2c_RateLimiter_Float64_C" "x2c_Real2I_Float32_FiP8_C" "x2c_Real2I_Float32_FiP16_C" "x2c_Real2I_Float32_FiP32_C" "x2c_Real2I_Float64_FiP8_C" "x2c_Real2I_Float64_FiP16_C" "x2c_Real2I_Float64_FiP32_C" "x2c_Saturation_FiP8_C" "x2c_Saturation_FiP16_C" "x2c_Saturation_FiP32_C" "x2c_Saturation_Float32_C" "x2c_Saturation_Float64_C" "x2c_SaveSignal_FiP8_C" "x2c_SaveSignal_FiP16_C" "x2c_SaveSignal_FiP32_C" "x2c_SaveSignal_Float32_C" "x2c_SaveSignal_Float64_C" "x2c_Selector_FiP8_C" "x2c_Selector_FiP16_C" "x2c_Selector_FiP32_C" "x2c_Selector_Float32_C" "x2c_Selector_Float64_C" "x2c_Sequencer_FiP8_C" "x2c_Sequencer_FiP16_C" "x2c_Sequencer_FiP32_C" "x2c_Sequencer_Float32_C" "x2c_Sequencer_Float64_C" "x2c_Sin2Limiter_FiP8_C" "x2c_Sin2Limiter_FiP16_C" "x2c_Sin2Limiter_FiP32_C" "x2c_Sin2Limiter_Float32_C" "x2c_Sin2Limiter_Float64_C" "x2c_Sin3Gen_FiP8_C" "x2c_Sin3Gen_FiP16_C" "x2c_Sin3Gen_FiP32_C" "x2c_Sin3Gen_Float32_C" "x2c_Sin3Gen_Float64_C" "x2c_SinGen_FiP8_C" "x2c_SinGen_FiP16_C" "x2c_SinGen_FiP32_C" "x2c_SinGen_Float32_C" "x2c_SinGen_Float64_C" "x2c_TypeConv_FiP8_16_C" "x2c_TypeConv_FiP8_32_C" "x2c_TypeConv_FiP16_8_C" "x2c_TypeConv_FiP16_32_C" "x2c_TypeConv_FiP32_8_C" "x2c_TypeConv_FiP32_16_C" "x2c_uConstant_FiP8_C" "x2c_uConstant_FiP16_C" "x2c_uConstant_FiP32_C" "x2c_uConstant_Float32_C" "x2c_uConstant_Float64_C" "x2c_uGain_FiP8_C" "x2c_uGain_FiP16_C" "x2c_uGain_FiP32_C" "x2c_uGain_Float32_C" "x2c_uGain_Float64_C" "x2c_uRateLimiter_FiP8_C" "x2c_uRateLimiter_FiP16_C" "x2c_uRateLimiter_FiP32_C" "x2c_uRateLimiter_Float32_C" "x2c_uRateLimiter_Float64_C" "x2c_uSaveSignal_FiP8_C" "x2c_uSaveSignal_FiP16_C" "x2c_uSaveSignal_FiP32_C" "x2c_uSaveSignal_Float32_C" "x2c_uSaveSignal_Float64_C" "x2c_Xor_FiP8_C" "x2c_Xor_FiP16_C" "x2c_Xor_FiP32_C"];
files = ["x2c_Utils.c" "x2c_And_FiP8_C.c" "x2c_And_FiP16_C.c" "x2c_And_FiP32_C.c" "x2c_AutoSwitch_FiP8_C.c" "x2c_AutoSwitch_FiP16_C.c" "x2c_AutoSwitch_FiP32_C.c" "x2c_AutoSwitch_Float32_C.c" "x2c_AutoSwitch_Float64_C.c" "x2c_Constant_FiP8_C.c" "x2c_Constant_FiP16_C.c" "x2c_Constant_FiP32_C.c" "x2c_Constant_Float32_C.c" "x2c_Constant_Float64_C.c" "x2c_Gain_FiP8_C.c" "x2c_Gain_FiP16_C.c" "x2c_Gain_FiP32_C.c" "x2c_Gain_Float32_C.c" "x2c_Gain_Float64_C.c" "x2c_Inport_int8_C.c" "x2c_Inport_int16_C.c" "x2c_Inport_int32_C.c" "x2c_Inport_float32_C.c" "x2c_Inport_float64_C.c" "x2c_Int2Re_FiP8_Float32_C.c" "x2c_Int2Re_FiP16_Float32_C.c" "x2c_Int2Re_FiP32_Float32_C.c" "x2c_Int2Re_FiP8_Float64_C.c" "x2c_Int2Re_FiP16_Float64_C.c" "x2c_Int2Re_FiP32_Float64_C.c" "x2c_Limitation_FiP8_C.c" "x2c_Limitation_FiP16_C.c" "x2c_Limitation_FiP32_C.c" "x2c_Limitation_Float32_C.c" "x2c_Limitation_Float64_C.c" "x2c_LookupTable_FiP8_C.c" "x2c_LookupTable_FiP16_C.c" "x2c_LookupTable_FiP32_C.c" "x2c_LoopBreaker_FiP16_C.c" "x2c_LoopBreaker_FiP32_C.c" "x2c_LoopBreaker_Float32_C.c" "x2c_LoopBreaker_Float64_C.c" "x2c_ManualSwitch_FiP8_C.c" "x2c_ManualSwitch_FiP16_C.c" "x2c_ManualSwitch_FiP32_C.c" "x2c_ManualSwitch_Float32_C.c" "x2c_ManualSwitch_Float64_C.c" "x2c_Maximum_FiP8_C.c" "x2c_Maximum_FiP16_C.c" "x2c_Maximum_FiP32_C.c" "x2c_Maximum_Float32_C.c" "x2c_Maximum_Float64_C.c" "x2c_Minimum_FiP8_C.c" "x2c_Minimum_FiP16_C.c" "x2c_Minimum_FiP32_C.c" "x2c_Minimum_Float32_C.c" "x2c_Minimum_Float64_C.c" "x2c_MinMaxPeriod_FiP8_C.c" "x2c_MinMaxPeriod_FiP16_C.c" "x2c_MinMaxPeriod_FiP32_C.c" "x2c_MinMaxPeriod_Float32_C.c" "x2c_MinMaxPeriod_Float64_C.c" "x2c_Not_FiP8_C.c" "x2c_Not_FiP16_C.c" "x2c_Not_FiP32_C.c" "x2c_Or_FiP8_C.c" "x2c_Or_FiP16_C.c" "x2c_Or_FiP32_C.c" "x2c_Outport_int8_C.c" "x2c_Outport_int16_C.c" "x2c_Outport_int32_C.c" "x2c_Outport_float32_C.c" "x2c_Outport_float64_C.c" "x2c_RateLimiter_FiP8_C.c" "x2c_RateLimiter_FiP16_C.c" "x2c_RateLimiter_FiP32_C.c" "x2c_RateLimiter_Float32_C.c" "x2c_RateLimiter_Float64_C.c" "x2c_Real2I_Float32_FiP8_C.c" "x2c_Real2I_Float32_FiP16_C.c" "x2c_Real2I_Float32_FiP32_C.c" "x2c_Real2I_Float64_FiP8_C.c" "x2c_Real2I_Float64_FiP16_C.c" "x2c_Real2I_Float64_FiP32_C.c" "x2c_Saturation_FiP8_C.c" "x2c_Saturation_FiP16_C.c" "x2c_Saturation_FiP32_C.c" "x2c_Saturation_Float32_C.c" "x2c_Saturation_Float64_C.c" "x2c_SaveSignal_FiP8_C.c" "x2c_SaveSignal_FiP16_C.c" "x2c_SaveSignal_FiP32_C.c" "x2c_SaveSignal_Float32_C.c" "x2c_SaveSignal_Float64_C.c" "x2c_Selector_FiP8_C.c" "x2c_Selector_FiP16_C.c" "x2c_Selector_FiP32_C.c" "x2c_Selector_Float32_C.c" "x2c_Selector_Float64_C.c" "x2c_Sequencer_FiP8_C.c" "x2c_Sequencer_FiP16_C.c" "x2c_Sequencer_FiP32_C.c" "x2c_Sequencer_Float32_C.c" "x2c_Sequencer_Float64_C.c" "x2c_Sin2Limiter_FiP8_C.c" "x2c_Sin2Limiter_FiP16_C.c" "x2c_Sin2Limiter_FiP32_C.c" "x2c_Sin2Limiter_Float32_C.c" "x2c_Sin2Limiter_Float64_C.c" "x2c_Sin3Gen_FiP8_C.c" "x2c_Sin3Gen_FiP16_C.c" "x2c_Sin3Gen_FiP32_C.c" "x2c_Sin3Gen_Float32_C.c" "x2c_Sin3Gen_Float64_C.c" "x2c_SinGen_FiP8_C.c" "x2c_SinGen_FiP16_C.c" "x2c_SinGen_FiP32_C.c" "x2c_SinGen_Float32_C.c" "x2c_SinGen_Float64_C.c" "x2c_TypeConv_FiP8_16_C.c" "x2c_TypeConv_FiP8_32_C.c" "x2c_TypeConv_FiP16_8_C.c" "x2c_TypeConv_FiP16_32_C.c" "x2c_TypeConv_FiP32_8_C.c" "x2c_TypeConv_FiP32_16_C.c" "x2c_uConstant_FiP8_C.c" "x2c_uConstant_FiP16_C.c" "x2c_uConstant_FiP32_C.c" "x2c_uConstant_Float32_C.c" "x2c_uConstant_Float64_C.c" "x2c_uGain_FiP8_C.c" "x2c_uGain_FiP16_C.c" "x2c_uGain_FiP32_C.c" "x2c_uGain_Float32_C.c" "x2c_uGain_Float64_C.c" "x2c_uRateLimiter_FiP8_C.c" "x2c_uRateLimiter_FiP16_C.c" "x2c_uRateLimiter_FiP32_C.c" "x2c_uRateLimiter_Float32_C.c" "x2c_uRateLimiter_Float64_C.c" "x2c_uSaveSignal_FiP8_C.c" "x2c_uSaveSignal_FiP16_C.c" "x2c_uSaveSignal_FiP32_C.c" "x2c_uSaveSignal_Float32_C.c" "x2c_uSaveSignal_Float64_C.c" "x2c_Xor_FiP8_C.c" "x2c_Xor_FiP16_C.c" "x2c_Xor_FiP32_C.c"];
flag = "c";
loadername = "loader_x86.sce";
libname = "General_x86";
ldflags = SCI + "\bin\scicos.lib";
cflags = "-I" + SCI + "\modules\scicos_blocks\includes" + " -I" + SCI + "\modules\scicos\includes" + " -I" + X2C_ROOT + "\Controller\Common" + " -I" + X2C_LIB_PATH + "\Controller\src" + " -I" + X2C_LIB_PATH + "\Controller\inc";
ilib_for_link(names, files, [], flag, "", loadername, libname, ldflags, cflags);

// delete temporary files
if isdir("Debug") then
  rmdir("Debug","s");
end
if isdir("Release") then
  rmdir("Release","s");
end
mdelete("cleaner.sce")
mdelete("Makelib.mak")

// create "is-compiled" marker
currentTime=clock();
save("Library_is_compiled_for_x86.txt", "currentTime");

mprintf("Library General for x86 system built.\n");

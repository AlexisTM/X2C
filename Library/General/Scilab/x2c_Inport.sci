// This file was generated by createIFunctionIO.sci on 03-03-2017 01:17

function [x_sci,y_sci,typ_sci] = x2c_Inport(job, arg1, arg2)

//import necessary java classes;
jimport at.lcm.x2c.parameterEditor.X2cParameterEditor_Xcos;
jimport at.lcm.x2c.utils.Utils;

thisBlockData.Library = "General";
thisBlockData.block_type_name = "Inport";
thisBlockData.block_xcosfilename = "x2c_Inport";

x_sci = [];
y_sci = [];
typ_sci = [];
X2CRootDir = jinvoke(jinvoke(Utils, "getRootDirectory"), "toString");
X2CRootDir = strsubst(X2CRootDir, "\", "/");

select job
case "plot" then
    standard_draw(arg1)

case "getinputs" then
    [x_sci,y_sci,typ_sci] = standard_inputs(arg1);

case "getoutputs" then
    [x_sci,y_sci,typ_sci] = standard_outputs(arg1);

case "getorigin" then
    [x_sci,y_sci] = standard_origin(arg1);

case "set" then
    x_sci = arg1;
    block_graphics = arg1.graphics;
    block_model = arg1.model;
    exprs = block_graphics.exprs;
    xcosBlockId = block_model.uid;
    while %t do
        if exists("X2C_sampleTime") then
            X2C_sampleTime_tmp = X2C_sampleTime;
        else
            X2C_sampleTime_tmp = -1;
        end
        x2cPEdit = jnewInstance(X2cParameterEditor_Xcos, exprs, xcosBlockId, X2C_sampleTime_tmp);
        if ~ exists("%scicos_prob") then
            // double click on icon
            ok = jinvoke(x2cPEdit, "runGUI");
        else
            ok = %t;
        end
        
        if ~ok then
            break;
        end
        
        impl = jinvoke(x2cPEdit, "getUsedImplementationName");
        block_model.sim = list("x2c_Inport_"  + impl + "_C", 4);
        
        exprs = jinvoke(x2cPEdit, "getXcosExprs")';
        
        block_graphics.exprs = exprs;
        x_sci.graphics = block_graphics;
        x_sci.model = block_model;
    
        break;
    end
    
case "define" then
    if exists("X2C_sampleTime") then
        X2C_sampleTime_tmp = X2C_sampleTime;
    else
        X2C_sampleTime_tmp = -1;
    end
    x2cPEdit = jnewInstance(X2cParameterEditor_Xcos, thisBlockData.block_type_name, X2C_sampleTime_tmp);
    
    inport_labels = jinvoke(x2cPEdit, "getBlockInportNames");
    outport_labels = jinvoke(x2cPEdit, "getBlockOutportNames");
    
    // see: help scicos_model
    model = scicos_model();
    
    impl = jinvoke(x2cPEdit, "getUsedImplementationName");
    model.sim = list("x2c_Inport_"  + impl + "_C", 4);
    model.in = 1;
    model.evtin = [1];
    model.out = 1;
    model.state = [];   // continuous states
    model.dstate = [];  // discrete-time states
    
    model.ipar = [];
    model.rpar = [];
    model.blocktype = "c";
    model.nmode = 0;
    model.nzcross = 0;
    model.dep_ut = [%t %t];
    
    exprs = jinvoke(x2cPEdit, "getXcosExprs")';
    
    gr_i = [];
    x_sci = standard_define([3 2], model, exprs, gr_i);
    
    // see help: graphics structure
    x_sci.graphics.in_label = inport_labels; // labels of regular input ports
    x_sci.graphics.out_label = outport_labels; // labels of regular output ports
    x_sci.graphics.out_style = "textOpacity=0";// hide input port label
    x_sci.graphics.in_style = "textOpacity=0";// hide output port label
    
    
end

endfunction

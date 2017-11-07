// Copyright (c) 2017, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
// All rights reserved.
//
// This file is licensed according to the BSD 3-clause license as follows:
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the "Linz Center of Mechatronics GmbH" and "LCM" nor
//       the names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL "Linz Center of Mechatronics GmbH" BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// This file is part of X2C. http://www.mechatronic-simulation.org/
// $LastChangedRevision: 1111 $
// $LastChangedDate:: 2017-02-28 14:18:07 +0100#$
//
// Creates interface function for Xcos.
// Parameters:
// libName - Library name
// block - Java X2C block object
// varargin - (optional) project root directory for external blocks

function [] = createIFunction(libName, block, varargin)
funcprot(0);

//------------------------------------------------------------------------------
// Get relevant block information
//------------------------------------------------------------------------------
if length(varargin) == 0 then
    // internal library
    blockInfo = getBlockInfo(libName, block);
else
    // external library
    blockInfo = getBlockInfo(libName, block, varargin(1));
end

//------------------------------------------------------------------------------
// Create file
//------------------------------------------------------------------------------
try
    // open/create file
    fileName = blockInfo.scilabDir + blockInfo.xcosName + ".sci";
    fileID = mopen(fileName, "wt");

    // print header
    time = datevec(datenum());
    mfprintf(fileID, "// This file was generated by %s on %02d-%02d-%04d %02d:%02d\n\n", "createIFunction.sci", time(3), time(2), time(1), time(4), time(5));
    // TODO: expand file header (e.g. with license)

    mfprintf(fileID, "function [x_sci,y_sci,typ_sci] = %s(job, arg1, arg2)\n", blockInfo.xcosName);
    mfprintf(fileID, "\n");
    mfprintf(fileID, "thisBlockData.Library = '"%s'"\n", libName);
    mfprintf(fileID, "thisBlockData.block_type_name = '"%s'"\n", blockInfo.blockName);
    mfprintf(fileID, "thisBlockData.block_xcosfilename = '"%s'"\n", blockInfo.xcosName);
    mfprintf(fileID, "\n");
    mfprintf(fileID, "jimport('"at.lcm.x2c.parameterEditor.X2cParameterEditor_Xcos'");\n");
    mfprintf(fileID, "jimport('"at.lcm.x2c.utils.Utils'");\n");
    mfprintf(fileID, "\n");
    mfprintf(fileID, "x_sci = [];\n");
    mfprintf(fileID, "y_sci = [];\n");
    mfprintf(fileID, "typ_sci = [];\n");
    mfprintf(fileID, "X2CRootDir = jinvoke(jinvoke(Utils, '"getRootDirectory'"), '"toString'");\n");
    mfprintf(fileID, "X2CRootDir = strsubst(X2CRootDir, '"\\'", '"/'");\n");
    
    mfprintf(fileID, "\n");
    mfprintf(fileID, "select job\n");

    mfprintf(fileID, "case '"plot'" then\n");
    mfprintf(fileID, "// ++ BlockGenerator: Plot Section\n");
    if ~isempty(blockInfo.Visualization.PlotSection) then
        // TODO: is this all necessary? wouldn't last line be sufficient?
        mfprintf(fileID, "    block_graphics = arg1.graphics;\n");
        mfprintf(fileID, "    block_model = arg1.model;\n");
        mfprintf(fileID, "    exprs = block_graphics.exprs;\n");
        mfprintf(fileID, "    xcosBlockId = block_model.uid;\n");
        mfprintf(fileID, "    if exists('"X2C_sampleTime'") then\n");
        mfprintf(fileID, "        X2C_sampleTime_tmp = X2C_sampleTime;\n");
        mfprintf(fileID, "    else\n");
        mfprintf(fileID, "        X2C_sampleTime_tmp = -1;\n");
        mfprintf(fileID, "    end\n");
        mfprintf(fileID, "    x2cPEdit = jnewInstance(X2cParameterEditor_Xcos, exprs, xcosBlockId, X2C_sampleTime_tmp);\n");
        mfprintf(fileID, "    %s\n", blockInfo.Visualization.PlotSection);
    else
        mfprintf(fileID, "    standard_draw(arg1);\n");
    end
    mfprintf(fileID, "// -- BlockGenerator: Plot Section\n");
    mfprintf(fileID, "\n");

    mfprintf(fileID, "case '"getinputs'" then\n");
    mfprintf(fileID, "    [x_sci,y_sci,typ_sci] = standard_inputs(arg1);\n");
    mfprintf(fileID, "\n");
    
    mfprintf(fileID, "case '"getoutputs'" then\n");
    mfprintf(fileID, "    [x_sci,y_sci,typ_sci] = standard_outputs(arg1);\n");
    mfprintf(fileID, "\n");
    
    mfprintf(fileID, "case '"getorigin'" then\n");
    mfprintf(fileID, "    [x_sci,y_sci] = standard_origin(arg1);\n");
    mfprintf(fileID, "\n");
    
    mfprintf(fileID, "case '"set'" then\n");
    mfprintf(fileID, "    x_sci = arg1;\n");
    mfprintf(fileID, "    block_graphics = arg1.graphics;\n");
    mfprintf(fileID, "    block_model = arg1.model;\n");
    mfprintf(fileID, "    exprs = block_graphics.exprs;\n");
    mfprintf(fileID, "    xcosBlockId = block_model.uid;\n");
    mfprintf(fileID, "    while %%t do\n");
    mfprintf(fileID, "        if exists('"X2C_sampleTime'") then\n");
    mfprintf(fileID, "            X2C_sampleTime_tmp = X2C_sampleTime;\n");
    mfprintf(fileID, "        else\n");
    mfprintf(fileID, "            X2C_sampleTime_tmp = -1;\n");
    mfprintf(fileID, "        end\n");
    mfprintf(fileID, "        x2cPEdit = jnewInstance(X2cParameterEditor_Xcos, exprs, xcosBlockId, X2C_sampleTime_tmp);\n");
    mfprintf(fileID, "        thisBlock_isPartOfModel = jinvoke(x2cPEdit, '"isBlockPartOfModel'");\n");
    mfprintf(fileID, "        if (~ exists('"X2C_sampleTime'")) & (~ thisBlock_isPartOfModel) then\n");
    mfprintf(fileID, "            warning('"X2C_sampleTime is not set; default is used'");\n");
    mfprintf(fileID, "        elseif (exists('"X2C_sampleTime'")) & (thisBlock_isPartOfModel) then\n");
    mfprintf(fileID, "            warning('"X2C_sampleTime is set; but model sampleTime is used'");\n");
    mfprintf(fileID, "        end\n");
    mfprintf(fileID, "        if ~ exists('"%%scicos_prob'") then\n");
    mfprintf(fileID, "            // double click on icon\n");
    mfprintf(fileID, "        \n");
    mfprintf(fileID, "            ok = jinvoke(x2cPEdit, '"runGUI'");\n");
    mfprintf(fileID, "        else\n");
    mfprintf(fileID, "            ok = %%t;\n");
    mfprintf(fileID, "        end\n");
    mfprintf(fileID, "        \n");
    mfprintf(fileID, "        if ~ok then\n");
    mfprintf(fileID, "            break;\n");
    mfprintf(fileID, "        end\n");
    mfprintf(fileID, "        \n");
    mfprintf(fileID, "        impl = jinvoke(x2cPEdit, '"getUsedImplementationName'");\n");
    mfprintf(fileID, "        block_model.sim = list('"%s_'"  + impl + '"_C'", 4);\n", blockInfo.xcosName);
    mfprintf(fileID, "        \n");
    mfprintf(fileID, "        xcp = jinvoke(x2cPEdit, '"getControlerParameter'");\n");
    mfprintf(fileID, "        \n");
    mfprintf(fileID, "        block_model.ipar = double(jinvoke(xcp, '"getIntegerParameter_values'"));\n");
    mfprintf(fileID, "        block_model.rpar = double(jinvoke(xcp, '"getDoubleParameter_values'"));\n");
    mfprintf(fileID, "        po = jinvoke(x2cPEdit, '"getControlerParameter_DoubleArrayParameter_values'");\n");
    mfprintf(fileID, "        otab = list();\n");
    mfprintf(fileID, "        \n");
    mfprintf(fileID, "        for i=0:jinvoke(po, '"size'")-1\n");
    mfprintf(fileID, "            otab($+1) = jinvoke(po, '"get'", i);\n");
    mfprintf(fileID, "        end\n");
    mfprintf(fileID, "        block_model.opar = otab;\n");
    mfprintf(fileID, "        \n");
    mfprintf(fileID, "        exprs = jinvoke(x2cPEdit, '"getXcosExprs'")'';\n");
    mfprintf(fileID, "        \n");
    mfprintf(fileID, "        block_graphics.exprs = exprs;\n");
    mfprintf(fileID, "        x_sci.graphics = block_graphics;\n");
    mfprintf(fileID, "        x_sci.model = block_model;\n");
    
    mfprintf(fileID, "    \n");
    mfprintf(fileID, "// ++ BlockGenerator: Define Section\n");
    if ~isempty(blockInfo.Visualization.DefineSection) then
        mfprintf(fileID, "%s\n", blockInfo.Visualization.DefineSection);
    else
        // print nothing
    end
    mfprintf(fileID, "// -- BlockGenerator: Define Section\n");
    mfprintf(fileID, "    \n");
    
    mfprintf(fileID, "        break;\n");
    mfprintf(fileID, "    end\n");
    mfprintf(fileID, "    \n");

    mfprintf(fileID, "case '"define'" then\n");
    mfprintf(fileID, "    if exists('"X2C_sampleTime'") then\n");
    mfprintf(fileID, "        X2C_sampleTime_tmp = X2C_sampleTime;\n");
    mfprintf(fileID, "    else\n");
    mfprintf(fileID, "        X2C_sampleTime_tmp = -1;\n");
    mfprintf(fileID, "    end\n");
    mfprintf(fileID, "    x2cPEdit = jnewInstance(X2cParameterEditor_Xcos, thisBlockData.block_type_name, X2C_sampleTime_tmp);\n");
    mfprintf(fileID, "    \n");
    mfprintf(fileID, "    inport_labels = jinvoke(x2cPEdit, '"getBlockInportNames'");\n");
    mfprintf(fileID, "    outport_labels = jinvoke(x2cPEdit, '"getBlockOutportNames'");\n");
    mfprintf(fileID, "    \n");
    mfprintf(fileID, "    // see: help scicos_model\n");
    mfprintf(fileID, "    model = scicos_model();\n");
    mfprintf(fileID, "    impl = jinvoke(x2cPEdit, '"getUsedImplementationName'");\n");
    mfprintf(fileID, "    model.sim = list('"%s_'"  + impl + '"_C'", 4);\n", blockInfo.xcosName);
    mfprintf(fileID, "    model.in = jinvoke(x2cPEdit, '"getBlockInport_xcosDef'");\n");
    if  blockInfo.TimeDependency then
        mfprintf(fileID, "    model.evtin = [1];\n");
    else
        mfprintf(fileID, "    model.evtin = [];\n");
    end
    mfprintf(fileID, "    \n");
    mfprintf(fileID, "    model.out = jinvoke(x2cPEdit, '"getBlockOutport_xcosDef'");\n");
    mfprintf(fileID, "    model.state = [];   // continuous states\n");
    mfprintf(fileID, "    model.dstate = [];  // discrete-time states\n");
    mfprintf(fileID, "    \n");
    mfprintf(fileID, "    model.ipar = double(jinvoke(x2cPEdit, '"getControlerParameter_IntegerParameter_values'")'');\n");
    mfprintf(fileID, "    model.rpar = double(jinvoke(x2cPEdit, '"getControlerParameter_DoubleParameter_values'")'');\n");
    mfprintf(fileID, "    model.blocktype = '"c'";\n");
    mfprintf(fileID, "    model.nmode = 0;\n");
    mfprintf(fileID, "    model.nzcross = 0;\n");
    if blockInfo.DirectFeedThrough then
        mfprintf(fileID, "    model.dep_ut = [%%t %%f];\n");
    else
        mfprintf(fileID, "    model.dep_ut = [%%f %%f];\n");
    end
    mfprintf(fileID, "    \n");
    mfprintf(fileID, "    exprs = jinvoke(x2cPEdit, '"getXcosExprs'")'';\n");
    mfprintf(fileID, "    \n");
    mfprintf(fileID, "// ++ BlockGenerator: BlockIconDefaultSize\n");
    if ~isempty(blockInfo.Visualization.BlockIconDefaultSize) then
        mfprintf(fileID, "    blockIconDefaultSize = %s;\n", blockInfo.Visualization.BlockIconDefaultSize);
    else
        mfprintf(fileID, "    blockIconDefaultSize = %s;\n", ["[5, " + string(2 + blockInfo.maxPorts) + "]"]);
    end
    mfprintf(fileID, "// -- BlockGenerator: BlockIconDefaultSize\n");
    mfprintf(fileID, "    \n");
//    mfprintf(fileID, "// ++ BlockGenerator: Define Section\n");
//    if ~isempty(blockInfo.Visualization.DefineSection) then
//        mfprintf(fileID, "    %s\n", blockInfo.Visualization.DefineSection);
//    else
//        mfprintf(fileID, "    gr_i = [];\n")
//    end
//    mfprintf(fileID, "// -- BlockGenerator: Define Section\n");
//    mfprintf(fileID, "    \n");
    mfprintf(fileID, "    gr_i = [];\n")
    mfprintf(fileID, "    \n");
    
    mfprintf(fileID, "    x_sci = standard_define(blockIconDefaultSize, model, exprs, gr_i);\n");
    mfprintf(fileID, "    \n");
    mfprintf(fileID, "    // see help: graphics structure\n");
    mfprintf(fileID, "    x_sci.graphics.in_label = inport_labels; // labels of regular input ports\n");
    mfprintf(fileID, "    x_sci.graphics.out_label = outport_labels; // labels of regular output ports\n");
    //mfprintf(fileID, "    x_sci.graphics.style = '"noLabel=0;displayedLabel=%%11$s %%10$s;'" // display first parameter (will be hidden by starter file, unless block visualization says something different)\n");
    
//    mfprintf(fileID, "// ++ BlockGenerator: Plot Section\n");
//    if ~isempty(blockInfo.Visualization.PlotSection) then
//        mfprintf(fileID, "    %s\n", blockInfo.Visualization.PlotSection);
//    else
//        // print nothing
//    end
//    mfprintf(fileID, "// -- BlockGenerator: Plot Section\n");
    
    mfprintf(fileID, "    \n");
        mfprintf(fileID, "// ++ BlockGenerator: Define Section\n");
    if ~isempty(blockInfo.Visualization.DefineSection) then
        mfprintf(fileID, "%s\n", blockInfo.Visualization.DefineSection);
    else
        // print nothing
    end
    mfprintf(fileID, "// -- BlockGenerator: Define Section\n");
    mfprintf(fileID, "    \n");
    
    mfprintf(fileID, "    \n");
    mfprintf(fileID, "end\n");
    mfprintf(fileID, "\n");
    mfprintf(fileID, "endfunction\n");
    
    // close file
    mclose(fileID);
    mprintf("Interface function %s successfully written.\n", fileName);

catch
    // some error creating the file occured
    mclose(fileID); // try to close the file
    disp("Error creating interface function for block " + blockInfo.blockName + ": " + lasterror());
end

endfunction

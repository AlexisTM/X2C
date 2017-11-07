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
// Function to create Xcos model from XML file.
// Parameters:
// xmlName - XML name

function [] = createModel(xmlName)
funcprot(0);

// import necessary java classes
jimport at.lcm.x2c.core.structure.Model;
jimport at.lcm.x2c.core.structure.ControlBlock;

// get file separator
fs = filesep();

// get current directory
curDir = pwd();

try
    // get model information
    newModel = jnewInstance(Model);
    jinvoke(newModel, "readFromXml", xmlName);
    modelName = jinvoke(newModel, "getModelName");
catch
    mprintf("Error reading xml %s\n", xmlName);
    mprintf("ERROR: %s\n", lasterror());
    return;
end

// Scaling factor for block size
scale = 20;

try
    
    // setup diagram structure
    scs_m = scicos_diagram();       // create diagram
    scs_m.props.title = modelName;   // give diagram a name
    cnt = 0;
    
    // add blocks from X2C Basic library
    cnt = cnt + 1;
    execstr("scs_m.objs(" + string(cnt) + ") = x2c_CommunicatorStart('"define'");");  // load block into model
    sz = scs_m.objs(cnt).graphics.sz * scale;
    scs_m.objs(cnt).graphics.sz = sz;                                   // resize block to a suitable size
    scs_m.objs(cnt).graphics.orig = [0*scale, sz(2)+2*scale];          // set position of block in model
    
    cnt = cnt + 1;
    execstr("scs_m.objs(" + string(cnt) + ") = x2c_ModelTransformation('"define'");");  // load block into model
    sz = scs_m.objs(cnt).graphics.sz * scale;
    scs_m.objs(cnt).graphics.sz = sz;                                   // resize block to a suitable size
    scs_m.objs(cnt).graphics.orig = [10*scale, sz(2)+2*scale];          // set position of block in model
    
    cnt = cnt + 1;
    execstr("scs_m.objs(" + string(cnt) + ") = x2c_ProjectDocumentation('"define'");");  // load block into model
    sz = scs_m.objs(cnt).graphics.sz * scale;
    scs_m.objs(cnt).graphics.sz = sz;                                   // resize block to a suitable size
    scs_m.objs(cnt).graphics.orig = [20*scale, sz(2)+2*scale];          // set position of block in model
    
    
    // add main system clock
    cnt = cnt + 1;
    execstr("scs_m.objs(" + string(cnt) + ") = CLOCK_c('"define'");");  // load block into model
    sz = scs_m.objs(cnt).graphics.sz * scale;
    scs_m.objs(cnt).graphics.sz = sz;                                   // resize block to a suitable size
    scs_m.objs(cnt).graphics.orig = [30*scale, sz(2)+2*scale];          // set position of block in model
    Ts = jinvoke(newModel, "getSampleTime");
    // TODO: enter sample time in clock
    //scs_m.objs(cnt).graphics.exprs = Ts;
    

    // process all inports
    Inports = jinvoke(newModel, "getInports");
    vertOffset = 0;
    horiOffset = 0;
    //for i = 1:Inports.length  // NOTE: for some strange reason this does not work!
    i=0;
    while i < Inports.length
        i = i + 1;
        cnt = cnt + 1;
        // get general block information
        curBlockLib = jinvoke(Inports(i), "getLibraryName");
        curBlockType = jinvoke(Inports(i), "getName");
        curBlockMask = jinvoke(Inports(i), "getMask");
        curBlockName = jinvoke(Inports(i), "getMaskName");
        curXcosName = getXcosBlockName(curBlockLib, curBlockType);
        
        // get scilab block information
        execstr("scs_m.objs(" + string(cnt) + ") = "+ curXcosName + "('"define'");");    // load block into model
        sz = scs_m.objs(cnt).graphics.sz * scale;
        vertOffset = vertOffset - (sz(2)+scale); 
        exprs = scs_m.objs(cnt).graphics.exprs;
        
        // set block label
        exprs(4) = curBlockName;    // fourth entry is the block label
        
        // set parameter values (implementation and sample time factor )
        curMaskParameterNames = jinvoke(curBlockMask, "getMaskParameterNames");
        len = size(curMaskParameterNames);
        if len(2) == 2
            // first parameter is DataType
            curMaskParam = jinvoke(curBlockMask, "getMaskParameter", curMaskParameterNames(1));
            curMaskParamVal = jinvoke(curMaskParam, "getValue");
            exprs(7) = curMaskParamVal;     // 7th entry is implementation
            // TODO: check if ok (visiualization seems odd, is code generation possible?)
            
            // second parameter is ts_fact
            curMaskParam = jinvoke(curBlockMask, "getMaskParameter", curMaskParameterNames(2));
            curMaskParamVal = jinvoke(curMaskParam, "getValue");
            exprs(10) = curMaskParamVal;    // 10th entry is adjustable field of first parameter
        else
            disp('Warning: Parameter ' + curMaskParameterNames(j) + 'could not be entered for block ' + curBlockName + " because data structure of Inports has changed!")
        end
        
        // position block in model
        scs_m.objs(cnt).graphics.sz = sz;                           // resize block to a suitable size
        scs_m.objs(cnt).graphics.orig = [horiOffset, vertOffset];   // set position of block in model
        scs_m.objs(cnt).graphics.exprs = exprs;                     // set block name
    end
    
    // process all regular blocks
    Blocks = jinvoke(newModel, "getControlBlocks");
    vertOffset = 0;
    horiOffset = 15*scale;
    //for i = 1:Blocks.length  // NOTE: for some strange reason this does not work!
    i=0;
    while i < Blocks.length
        i = i + 1;
        cnt = cnt + 1;
        // get general block information
        curBlockLib = jinvoke(Blocks(i), "getLibraryName");
        curBlockType = jinvoke(Blocks(i), "getName");
        curBlockMask = jinvoke(Blocks(i), "getMask");
        curBlockName = jinvoke(Blocks(i), "getMaskName");
        curXcosName = getXcosBlockName(curBlockLib, curBlockType);
        
        // get scilab block information
        execstr("scs_m.objs(" + string(cnt) + ") = "+ curXcosName + "('"define'");");    // load block into model
        sz = scs_m.objs(cnt).graphics.sz * scale;
        vertOffset = vertOffset - (sz(2)+scale); 
        exprs = scs_m.objs(cnt).graphics.exprs;
        
        // set block label
        exprs(4) = curBlockName;    // fourth entry is the block label // TODO: consider subsystems/superblocks!
        
        // set implementation
        exprs(7) = jinvoke(Blocks(i), "getUsedImplName");
        
        // set parameter values (sample time factor included)
        curMaskParameterNames = jinvoke(curBlockMask, "getMaskParameterNames");
        len = size(curMaskParameterNames);
        for j=1:len(2)
            curMaskParam = jinvoke(curBlockMask, "getMaskParameter", curMaskParameterNames(j));
            curMaskParamVal = jinvoke(curMaskParam, "getValue");
            if isnum(curMaskParamVal)
                exprs(10+(j-1)*4) = curMaskParamVal; // 10th entry is adjustable field of first parameter // TODO: check for arrays!
            else
                exprs(11+(j-1)*4) = curMaskParamVal; // 11th entry is value field of first parameter // TODO: check for combo boxes!
            end
        end
        
        // position block in model
        scs_m.objs(cnt).graphics.sz = sz;                           // resize block to a suitable size
        scs_m.objs(cnt).graphics.orig = [horiOffset, vertOffset];   // set position of block in model
        scs_m.objs(cnt).graphics.exprs = exprs;                     // set block name
    end
    
    // process all outports
    Outports = jinvoke(newModel, "getOutports");
    vertOffset = 0;
    horiOffset = 30*scale;
    //for i = 1:Outports.length  // NOTE: for some strange reason this does not work!
    i=0;
    while i < Outports.length
        i = i + 1;
        cnt = cnt + 1;
        // get general block information
        curBlockLib = jinvoke(Outports(i), "getLibraryName");
        curBlockType = jinvoke(Outports(i), "getName");
        curBlockMask = jinvoke(Outports(i), "getMask");
        curBlockName = jinvoke(Outports(i), "getMaskName");
        curXcosName = getXcosBlockName(curBlockLib, curBlockType);
        
        // get scilab block information
        execstr("scs_m.objs(" + string(cnt) + ") = "+ curXcosName + "('"define'");");    // load block into model
        sz = scs_m.objs(cnt).graphics.sz * scale;
        vertOffset = vertOffset - (sz(2)+scale); 
        exprs = scs_m.objs(cnt).graphics.exprs;
        
        // set block label
        exprs(4) = curBlockName;    // fourth entry is the block label
        
        // set parameter values (implementation and sample time factor )
        curMaskParameterNames = jinvoke(curBlockMask, "getMaskParameterNames");
        len = size(curMaskParameterNames);
        if len(2) == 2
            // first parameter is DataType
            curMaskParam = jinvoke(curBlockMask, "getMaskParameter", curMaskParameterNames(1));
            curMaskParamVal = jinvoke(curMaskParam, "getValue");
            exprs(7) = curMaskParamVal;     // 7th entry is implementation
            // TODO: check if ok (visiualization seems odd, is code generation possible?)
            
            // second parameter is ts_fact
            curMaskParam = jinvoke(curBlockMask, "getMaskParameter", curMaskParameterNames(2));
            curMaskParamVal = jinvoke(curMaskParam, "getValue");
            exprs(10) = curMaskParamVal;    // 10th entry is adjustable field of first parameter
        else
            disp('Warning: Parameter ' + curMaskParameterNames(j) + 'could not be entered for block ' + curBlockName + " because data structure of Outports has changed!")
        end
        
        // position block in model
        scs_m.objs(cnt).graphics.sz = sz;                           // resize block to a suitable size
        scs_m.objs(cnt).graphics.orig = [horiOffset, vertOffset];   // set position of block in model
        scs_m.objs(cnt).graphics.exprs = exprs;                     // set block name
    end
    
    // open Xcos model
    xcos(scs_m);
    

//    // create Xcos instance
//    sdh = jinvoke(ScilabDirectHandler, "acquire")
//    diagram = jnewInstance(XcosDiagram);
//    diag = jinvoke(sdh, "readDiagram", diagram, "scs_m");
//    
//    jinvoke(diag, "saveDiagram");
//    
//    // release instance
//    jinvoke(sdh, "release");
//
//    mprintf("Xcos model %s successfully created.\n",modelName);
catch
    mprintf("Error creating model %s\n", modelName);
    mprintf("ERROR: %s\n", lasterror());
end


endfunction


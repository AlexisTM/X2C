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
// Helper script to gather block information from java block object needed for
// several scripts like createIFunction.sci, createCFunction.sci,...
// Parameters:
// libName - Library name
// block - Java X2C block object
// varargin - (optional) project root directory for external blocks

function [blockInfo] = getBlockInfo(libName, block, varargin)
funcprot(0);

// import necessary java classes
jimport at.lcm.x2c.core.structure.ControlBlock;
jimport at.lcm.x2c.utils.LibraryUtils;

fs = filesep(); // get file separator

// block name
blockInfo.blockName = jinvoke(block, "getName");

if length(varargin) == 0 then
    // internal library
    xmlPath = jinvoke(LibraryUtils, "getXmlDirectory", libName);
else
    // external library
    libRoot = jinvoke(LibraryUtils, "getLibraryRootDirectory", varargin(1))
    libRoot = jinvoke(libRoot, "toString");
    xmlPath = jinvoke(LibraryUtils, "getXmlDirectory", libName, libRoot);
end
xmlDir = jinvoke(xmlPath, "toString");

xmlName = [xmlDir + blockInfo.blockName + ".xml"];
if ~isfile(xmlName) then
    disp("Error: could not find file " + xmlName);
    return; // exit script
end

if length(varargin) == 0 then
    // internal library
    blockInfo.xcosName = getXcosBlockName(libName, blockInfo.blockName);
else
     // external library
     blockInfo.xcosName = getXcosBlockName(libName, blockInfo.blockName, varargin(1));
end

// get/create scilab directory
blockInfo.scilabDir = strsubst(xmlDir, ["XML" + fs], ["Scilab" + fs]);

// general block information:
blockInfo.DirectFeedThrough = jinvoke(block, "isDirectFeedThrough");
blockInfo.TimeDependency = jinvoke(block, "isTimeDependent");
blockInfo.Implementations = jinvoke(block, "getExistingImplementationNames");

// block mask in-/outports
mask = jinvoke(block, "getMask");
maskInportNames = jinvoke(mask, "getMaskInportNames");
maskOutportNames = jinvoke(mask, "getMaskOutportNames");
[dummy, NrOfInports] = size(maskInportNames)
[dummy, NrOfOutports] = size(maskOutportNames)
blockInfo.maxPorts = max(NrOfInports, NrOfOutports);

// block visualization
blockInfo.Visualization.DefineSection = [];
blockInfo.Visualization.BlockIconDefaultSize = ["[5, " + string(2 + blockInfo.maxPorts) + "]"];
blockInfo.Visualization.PlotSection = [];
blockInfo.Visualization.Style = [];
try
    visual = jinvoke(mask, "getVisualizationScilabXcos");
    blockInfo.Visualization.DefineSection = jinvoke(visual, "getScriptDefineSection");
    blockInfo.Visualization.BlockIconDefaultSize = jinvoke(visual, "getBlockIconDefaultSize");
    blockInfo.Visualization.PlotSection = jinvoke(visual, "getScriptPlotSection");
    blockInfo.Visualization.Style = jinvoke(visual, "getScriptStyle");
catch
    // block has no Scilab/Xcos visualization -> fall back to default values
end

endfunction

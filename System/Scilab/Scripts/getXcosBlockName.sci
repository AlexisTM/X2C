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
// Returns used block name in Xcos. Scilab restriction: variable or function
// names can't be longer than 24 characters, otherwise name will be truncated.
// Therefore Xcos block name is different (truncated) to X2C name.
// Parameters:
// XcosName - Block name used in Xcos
// libraryName - Library name
// blockName - Block name
// varargin - (optional) project root directory for external blocks

function [XcosName] = getXcosBlockName(libName, blockName, varargin)
funcprot(0);

// import necessary java classes
jimport at.lcm.x2c.utils.LibraryUtils;
jimport at.lcm.x2c.utils.ControllerDataType;
jimport at.lcm.x2c.core.structure.ControlBlock;
jimport at.lcm.x2c.core.structure.IoBlock;
jimport at.lcm.x2c.core.structure.Block;

// default name
XcosName = "";

try
    // get XML file name
    if length(varargin) == 0 then
        // internal library
        xmlPath = jinvoke(LibraryUtils, "getXmlDirectory", libName);
    else
        // external library
        libRoot = jinvoke(LibraryUtils, 'getLibraryRootDirectory', varargin(1))
        libRoot = jinvoke(libRoot, 'toString');
        xmlPath = jinvoke(LibraryUtils, 'getXmlDirectory', libName, libRoot);
    end
    xmlName = jinvoke(xmlPath, "toString") + blockName + ".xml";

    // read block XML file
    blockObj = jinvoke(Block, "loadBlockXML", xmlName);
    blockType = jinvoke(jinvoke(blockObj, "getClass"), "toString");

    // check block type
    if ~strcmp(blockType, "class at.lcm.x2c.core.structure.ControlBlock") then
        // standard block
        blockObj = jcast(blockObj, ControlBlock);
       
        // get implementation names
        ImplNames = jinvoke(blockObj, "getExistingImplementationNames");
    else
        // IO block
        blockObj = jcast(blockObj, IoBlock);
        
        // get datatype names
        val = jinvoke(ControllerDataType, "values");    // get list with elements of ControllerDataType enum
        ImplNames = [];
        for i=1:val.length
            ImplNames = [ImplNames, jinvoke(val(i), "getName")];
        end
    end
   
    // get number of implementations/datatypes
    [dummy, NrOfImpl] = size(ImplNames)
    
    s = [];
    // get max length of implementation/datatype name
    for j=1:NrOfImpl
        s(j) = length(ImplNames(j));
    end
    maxLength = max(s);
    
    // determine block name
    if maxLength + length(blockName) > 19 then    // 19 = 24 - length("x2c_") - length("_")
        blockName = part(blockName, [1:(19-maxLength)]);
    end
    XcosName = "x2c_" + blockName;
    
catch
    disp('Error getting Xcos block name: ' + lasterror());
end

endfunction



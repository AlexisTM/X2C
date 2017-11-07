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
// Function to create tex source for block documentation and also the html docu-
// mentation.
// Parameters:
// libName - Library name
// blockObj - Java X2C block object
// varargin - (optional) project root directory for external blocks

function [] = createBlockDocu(libName, blockObj, varargin)
funcprot(0);

// import necessary java classes
jimport at.lcm.x2c.utils.LibraryUtils;
jimport at.lcm.x2c.docu.BlockDocu;

try
    if length(varargin) == 0 then
        // internal library
        blockDocu = jnewInstance(BlockDocu, blockObj);
    elseif length(varargin) == 1 then
        // external library
        blockDocu = jnewInstance(BlockDocu, blockObj, varargin(1));
    else
        error("Invalid number of input arguments");
    end
    jinvoke(blockDocu, "write");
    mprintf("Tex file for block %s successfully written.\n", blockObj.name);
    
    // HTML documentation
    docDir = jinvoke(LibraryUtils, "getDocumentationDirectory", libName);
    jinvoke(blockDocu, "generateHtml" , [docDir + blockObj.name + ".tex"]);
    mprintf("HTML file for block %s successfully written.\n", blockObj.name);

catch 
    disp("Error creating documentation files for block " + blockObj.name + ": " + lasterror());
end

endfunction


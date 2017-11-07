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
// Function to create java test templates for CUnit testing.
// Parameters:
// libName - Library name
// blockObj - Java X2C block object
// varargin - (optional) project root directory for external blocks

function [] = createTestTemplate(libName, blockObj, varargin)
funcprot(0);

// import necessary java classes
jimport at.lcm.x2c.core.structure.ControlBlock;
jimport at.lcm.x2c.blocktest.TestTemplateWriter;

try
    existingImpNames = jinvoke(blockObj, "getExistingImplementationNames");
    [NrOfImpl dummy] = size(existingImpNames);
    for j=1:NrOfImpl
        curImp = jinvoke(blockObj, "getExistingImplementation", existingImpNames(j));

        if length(varargin) == 0 then
            // internal library
            testWriter = jnewInstance(TestTemplateWriter, blockObj, jinvoke(curImp, "getName"));
        elseif length(varargin) == 1 then
            // external library
            testWriter = jnewInstance(TestTemplateWriter, blockObj, jinvoke(curImp, "getName"), varargin(1));
        else
            error("Invalid number of input arguments");
        end

        jinvoke(testWriter, "writeTemplate");
        mprintf("Test template for " + jinvoke(curImp, "getFullName") + " created.\n");
      end

catch 
    disp("Error creating test templates for block " + jinvoke(blockObj, "getName") + ": " + lasterror());
end

endfunction


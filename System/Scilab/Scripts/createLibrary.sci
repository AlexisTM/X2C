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
// Function to create and build all necessary files for a X2C library
// Parameters:
// libName - Library name
// varargin - (optional) project root directory for external blocks

function [] = createLibrary(libName, varargin)
funcprot(0);

// import necessary java classes
jimport at.lcm.x2c.core.structure.ControlBlock;
jimport at.lcm.x2c.core.structure.Block;
jimport at.lcm.x2c.utils.LibraryUtils;

// get current directory
curDir = pwd();

// get file separator
fs = filesep(); 

// get system architecture
arch = getArchitecture();

// get XML file names
if length(varargin) == 0 then
    // internal library
    xmlPath = jinvoke(LibraryUtils, "getXmlDirectory", libName);
elseif length(varargin) == 1 then
    // external library
    libRoot = jinvoke(LibraryUtils, "getLibraryRootDirectory", varargin(1))
    libRoot = jinvoke(libRoot, "toString");
    xmlPath = jinvoke(LibraryUtils, "getXmlDirectory", libName, libRoot);
else
    error("Invalid number of input arguments");
end

// get all XML files
xmlDir = jinvoke(xmlPath, "toString");
xmlFiles = dir(xmlDir + "*.xml");
xmlFiles = xmlFiles(2)';
xmlList = [];

// go through XML list
for curXML = xmlFiles
    if ~strcmp(part(curXML, $-3:$), ".xml") then
        // add file name with *.xml ending
        xmlList = [xmlList, curXML];
    end
end


// get/create scilab directory
scilabDir = strsubst(xmlDir, ["XML" + fs], ["Scilab" + fs]);
if ~isdir(scilabDir) then
    mkdir(scilabDir)
end

// go through all blocks in library
for curXml = xmlList
        // read block XML file
        x2cBlock = jinvoke(Block, "loadBlockXML", curXml);
        blockType = jinvoke(jinvoke(x2cBlock, "getClass"), "toString");

        // check block type
        if ~strcmp(blockType, "class at.lcm.x2c.core.structure.ControlBlock") then // normal Block
            blockObj = jnewInstance(ControlBlock);
            jinvoke(blockObj, "readBlockXml", curXml);
            
            if length(varargin) == 0 then   // internal library
                // create x2c_<block>.sci file
                createIFunction(libName, blockObj);
                
                // create x2c_<block>_<impl>_C.c files
                createCFunction(libName, blockObj);
                
                // create tex and html files
                //createBlockDocu(libName, blockObj); NOTE: files should already exist
            else                            // external library
                // create x2c_<block>.sci file
                createIFunction(libName, blockObj, varargin(1));
                
                // create x2c_<block>_<impl>_C.c files
                createCFunction(libName, blockObj, varargin(1));
                
                // create tex and html files
                createBlockDocu(libName, blockObj, varargin(1));
            end
            
        else        // IO-Block
            // do nothing for IO-Blocks
        end
end

// create some extra stuff for General library
if ~strcmp(libName, "General") then
    // create additional interface functions (Inport, Outport)
    createIFunctionIO();
    
    // create additional computational functions (Inport, Outport)
    createCFunctionIO();
end

if length(varargin) == 0 then   // internal library
    // create starter.sce file
    createLibraryStarter(libName);
                    
    // create builder_<arch>.sce file
    createLibraryBuilder(libName);
else                            // external library
    // create starter.sce file
    createLibraryStarter(libName, varargin(1));
                    
    // create builder_<arch>.sce file
    createLibraryBuilder(libName, varargin(1));
end

// compile library
chdir(scilabDir)
exec([scilabDir + "builder_" + arch + ".sce"], -1);
chdir(curDir)


endfunction


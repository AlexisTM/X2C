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
// Creates Xcos block. Parameters:
// libName - Library name
// blockName - Block name
// varargin - (optional) project root directory for external blocks

function [] = createXcosBlock(libName, blockName, varargin)

// import necessary java classes
jimport("at.lcm.x2c.core.structure.ControlBlock");
jimport("at.lcm.x2c.core.structure.Block");
jimport("at.lcm.x2c.utils.LibraryUtils");
jimport("at.lcm.x2c.core.structure.VisualizationScilabXcos");


// get file separator
fs = filesep();

// get current directory
currentDir = pwd();

// get system architecture
arch = getArchitecture();

// check library type
if length(varargin) == 0 then
    // internal library
    isIntern = %t;
elseif length(varargin) == 1 then
    // external library
    isIntern = %f;
else
    error("Invalid number of input arguments");
end

// get XML file name
if isIntern then
    // internal library
    xmlPath = jinvoke(LibraryUtils, "getXmlDirectory", libName);
else
    // external library
    libRoot = jinvoke(LibraryUtils, "getLibraryRootDirectory", varargin(1))
    libRoot = jinvoke(libRoot, "toString");
    xmlPath = jinvoke(LibraryUtils, "getXmlDirectory", libName, libRoot);
end

xmlDir = jinvoke(xmlPath, "toString");
xmlName = [xmlDir + blockName + ".xml"];


// get/create scilab directory
scilabDir = strsubst(xmlDir, ["XML" + fs], ["Scilab" + fs]);
if ~isdir(scilabDir) then
    mkdir(scilabDir)
end


// read block XML file
x2cBlock = jinvoke(Block, "loadBlockXML", xmlName);
blockType = jinvoke(jinvoke(x2cBlock, "getClass"), "toString");

// check block type
if ~strcmp(blockType, "class at.lcm.x2c.core.structure.ControlBlock") then
    blockObj = jnewInstance(ControlBlock);
    jinvoke(blockObj, "readBlockXml", xmlName);
    
    //--------------------------------------------------------------------------
    // create files
    //--------------------------------------------------------------------------
    if isIntern then   // internal library
        // create x2c_<block>.sci file
        createIFunction(libName, blockObj);
        
        // create x2c_<block>_<impl>_C.c files
        createCFunction(libName, blockObj);
        
        // create tex and html files
        //createBlockDocu(libName, blockObj); NOTE: files should already exist
        
        // create test files
        //createTestTemplate(libName, blockObj); NOTE: files should already exist
    else                            // external library
        // create x2c_<block>.sci file
        createIFunction(libName, blockObj, varargin(1));
        
        // create x2c_<block>_<impl>_C.c files
        createCFunction(libName, blockObj, varargin(1));
        
        // create tex and html files
        createBlockDocu(libName, blockObj, varargin(1));
        
        // create test files
        createTestTemplate(libName, blockObj, varargin(1));
    end
    
else
    // do nothing for IO-Blocks
end

//------------------------------------------------------------------------------
// Cleanup library
//------------------------------------------------------------------------------
try
    // Remove outdated files
    mdelete(scilabDir + libName + ".xpal");
    mdelete(scilabDir + "loader_" + arch + ".sce");
    mdelete(scilabDir + "builder_" + arch + ".sce");
    mprintf("Library %s cleaned.\n", libName)
    
    //remove palette from browser
    try
        xcosPalDelete(["X2C"  libName]);
    catch
        // palette couldn't be remove, probably because library doesn't exist yet
    end
    
catch
    disp("Error cleaning up library " + libName + ": " + lasterror());
end


//------------------------------------------------------------------------------
// Update library
//------------------------------------------------------------------------------
try
    // Update/recreate library builder and starter
    if isIntern then
        // internal library
        createLibraryBuilder(libName);
        createLibraryStarter(libName);

    else
        // external library
        createLibraryBuilder(libName, varargin(1));
        createLibraryStarter(libName, varargin(1));
    end
     mprintf("Library %s updated.\n", libName)
catch
    disp("Error updating library " + libName + ": " + lasterror());
end

//------------------------------------------------------------------------------
// Setup library
//------------------------------------------------------------------------------
try
    // Build library
    chdir(scilabDir);
    exec("builder_" + arch + ".sce", -1);
    chdir(currentDir);
    
    if isIntern then
        mprintf("Finished! Please restart Scilab to load library.")
    else
        mprintf("Finished! Please execute '"initProject.sce'" to load library.")
    end
   
    

catch
    chdir(currentDir); // try to go back to start directory
    disp("Error setting up library " + libName + ": " + lasterror());
end

endfunction

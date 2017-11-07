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
// Function to generate palette icons for all libraries
// Parameters:
// none

function [] = createAllLibraryIcons()
funcprot(0);

jimport at.lcm.x2c.utils.Utils;

// get file separator
fs = filesep(); 

    
// get system architecture
arch = getArchitecture();

X2CRootDir = jinvoke(jinvoke(Utils, "getRootDirectory"), "toString");

X2CLibraryPaths = [];
libs = ls([X2CRootDir + "Library"])';
for curLib=libs
    if isfile([X2CRootDir + "Library" + fs + curLib + fs + "x2c_library.xml"]) then
        X2CLibraryPaths = [X2CLibraryPaths, curLib];
    end
end

mprintf("+ Creation of palette icons\n")
try
    for curLib = X2CLibraryPaths
        scilabDir = [X2CRootDir + "Library" + fs + curLib + fs + "Scilab"];
        if isdir(scilabDir) then
            // only remove files in existing directories
            if  strcmp(curLib, "Basic") then
                // ignore Basic library
                createLibraryIcons(curLib);
            else
                // do nothing for Basic library
            end
        end
    end
    mprintf("- Done\n");
catch
    mprintf("- FAILED\n");
    mprintf("ERROR: %s\n\n", lasterror());
end

endfunction


// Function to create palette icons for each block of specified library
// Parameters:
// libName: library to create icons for
// varargin - (optional) project root directory for external blocks
function [] = createLibraryIcons(libName, varargin)

// import necessary java classes
jimport at.lcm.x2c.utils.LibraryUtils;
jimport at.lcm.x2c.core.structure.Block;

// get current directory
curDir = pwd();

// get file separator
fs = filesep(); 

// get system architecture
arch = getArchitecture();

// get XML file names
if length(varargin) == 0 then
    // internal library
    isIntern = %t;
    xmlPath = jinvoke(LibraryUtils, "getXmlDirectory", libName);
elseif length(varargin) == 1 then
    // external library
    isIntern = %f;
    libRoot = jinvoke(LibraryUtils, "getLibraryRootDirectory", varargin(1))
    libRoot = jinvoke(libRoot, "toString");
    xmlPath = jinvoke(LibraryUtils, "getXmlDirectory", libName, libRoot);
else
    error("Invalid number of input arguments");
end
xmlDir = jinvoke(xmlPath, "toString");
xmlFiles = dir(xmlDir + "*.xml");
xmlFiles = xmlFiles(2)';
xmlList = [];

// go through XML list
for curXML = xmlFiles
    temp = part(curXML, $-3:$)
    convstr(temp,"l")
    if ~strcmp(temp, ".xml") then
        // add file name with *.xml ending
        xmlList = [xmlList, curXML];
    end
end

scilabDir = [xmlDir + ".." + fs + "Scilab"];

if isdir(scilabDir) then
    // only walk through blocks in existing Scilab directories
    
    mprintf("++ Creation of palette icons for library %s\n", libName)
    try
        chdir(scilabDir);
       
        // clean up   
        mdelete("*.xpal");
        
        // walk through blocks
        for curXml = xmlList
            // read block XML file
            x2cBlock = jinvoke(Block, "loadBlockXML", curXml);
            blockType = jinvoke(jinvoke(x2cBlock, "getClass"), "toString");
            blockName = jinvoke(x2cBlock, "getName");
            
            if isIntern then
                createBlockIcon(libName, blockName);
            else
                createBlockIcon(libName, blockName, varargin(1));
            end
        end
    
        chdir(curDir);
        mprintf("-- Done\n");
    catch
        chdir(curDir);      // try to go back to starting directory
        mprintf("-- FAILED\n");
        mprintf("ERROR: %s\n\n", lasterror());
    end
    
else
    // do nothing for non-existing Scilab directories
end

endfunction

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
// Function to create default image for block with block name as text in svg
// format.
// Parameters:
// libName - Library name
// blockName - Block name
// varargin - (optional) project root directory for external blocks

function [] = createDefaultBlockImg(libName, blockName, varargin)
funcprot(0);

// import necessary java classes
jimport("at.lcm.x2c.core.structure.ControlBlock");
jimport("at.lcm.x2c.utils.LibraryUtils");

// get file separator
fs = filesep();

// get XML file name
if length(varargin) == 0 then
    // internal library
    xmlPath = jinvoke(LibraryUtils, "getXmlDirectory", libName);
else
    // external library
    if isVersionLessThan("5.5.0") then
        libRoot = junwrap(jinvoke(LibraryUtils, "getLibraryRootDirectory", varargin(1)));
        libRoot = junwrap(jinvoke(libRoot, "toString"));
    else
        // scilab version 5.5.0 or greater assumed
        libRoot = jinvoke(LibraryUtils, "getLibraryRootDirectory", varargin(1))
        libRoot = jinvoke(libRoot, "toString");
    end
    xmlPath = jinvoke(LibraryUtils, "getXmlDirectory", libName, libRoot);
end

if isVersionLessThan("5.5.0") then
    xmlDir = junwrap(jinvoke(xmlPath, "toString"));
else
    // scilab version 5.5.0 or greater assumed
    xmlDir = jinvoke(xmlPath, "toString");
end

xmlName = [xmlDir + blockName + ".xml"];
if ~isfile(xmlName) then
    disp("Error: could not find file " + xmlName);
    return; // exit script
end

// get/create image directory
imgDir = strsubst(xmlDir, ["XML" + fs], ["Doc" + fs + "Images" + fs]);
if ~isdir(imgDir) then
    mkdir(imgDir)
end


// read block XML file
block = jnewInstance(ControlBlock);
jinvoke(block, "readBlockXml", xmlName);

// get block information from Java block object:
// block mask in-/outports:
mask = jinvoke(block, "getMask");
if isVersionLessThan("5.5.0") then
    maskInportNames = junwrap(jinvoke(mask, "getMaskInportNames"));
    maskOutportNames = junwrap(jinvoke(mask, "getMaskOutportNames"));
else
    maskInportNames = jinvoke(mask, "getMaskInportNames");
    maskOutportNames = jinvoke(mask, "getMaskOutportNames");
end
[dummy, NrOfInports] = size(maskInportNames)
[dummy, NrOfOutports] = size(maskOutportNames)
maxPorts = max(NrOfInports, NrOfOutports);

// calculate dimensions and alignment values for fontsize = 40pt
fontSize = 40;
width = (length(blockName) + 4)*fontSize;  // textwidth = number of characters plus 2 spaces on each side
//height = round(width/5*(2+maxPorts));      // textheight is dependent of maximum number of inports/outports and is scaled to textwidth (scaling ratio is 5/3 for single inport/outport)
height = fontSize * 3;
textCenter = width/2;   // horizontal reference
textBase = height/2 + fontSize/2;    // vertical reference (baseline)

try

    // open/create file
    fileName = imgDir + blockName + ".svg";
    fileID = mopen(fileName, "wt");
    
    // print header
    time = datevec(datenum());
    mfprintf(fileID, "<?xml version='"1.0'" standalone='"yes'"?>\n");
    mfprintf(fileID, "<!DOCTYPE svg PUBLIC '"-//W3C//DTD SVG 1.1//EN'" '"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd'">\n");
    mfprintf(fileID, "<!--\n");
    mfprintf(fileID, "  This file is part of X2C. http://www.mechatronic-simulation.org/\n");
    mfprintf(fileID, "  \n");
    mfprintf(fileID, "  Copyright (c) 2014, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/\n");
    mfprintf(fileID, "  All rights reserved.\n");
    mfprintf(fileID, "  \n");
    mfprintf(fileID, "  This file was generated by %s on %02d-%02d-%04d %02d:%02d\n", "createDefaultBlockImg.sci", time(3), time(2), time(1), time(4), time(5));
    mfprintf(fileID, "  -->\n");
    mfprintf(fileID, "  \n");
    
    // print body
    mfprintf(fileID, "<svg width='"%i'" height='"%i'" version='"1.1'" xmlns='"http://www.w3.org/2000/svg'">\n", width, height);
    mfprintf(fileID, "<text x='"%i'" y='"%i'" style='"text-anchor: middle;'" font-family='"sans-serif'" font-size='"%ipt'">%s</text>\n", textCenter, textBase, fontSize, blockName);
    mfprintf(fileID, "</svg>\n");

    // close file
    mclose(fileID);
    mprintf("Default block image %s successfully created.\n", fileName);
    
catch
    // some error creating the file occured
    disp("Error creating default image for block " + blockName + ": " + lasterror());
end

endfunction


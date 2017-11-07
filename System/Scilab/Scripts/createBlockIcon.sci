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
// Function to create block icon for usage in palette browser.
// Parameters:
// libName - Library name
// blockName - Block name
// varargin - (optional) project root directory for external blocks

function [] = createBlockIcon(libName, blockName, varargin)
funcprot(0);

// import necessary java classes
jimport at.lcm.x2c.core.structure.ControlBlock;
jimport at.lcm.x2c.utils.LibraryUtils;
jimport at.lcm.x2c.scilab.utils.ExportUtils;
jimport org.scilab.modules.xcos.Xcos;
jimport org.scilab.modules.xcos.graph.XcosDiagram;
jimport org.scilab.modules.xcos.io.scicos.ScilabDirectHandler;

// get file separator
fs = filesep();

// get current directory
curDir = pwd();

// get XML file name and Xcos block name
if length(varargin) == 0 then
    // internal library
    xmlPath = jinvoke(LibraryUtils, "getXmlDirectory", libName);
    xcosName = getXcosBlockName(libName, blockName);
else
    // external library
    libRoot = jinvoke(LibraryUtils, "getLibraryRootDirectory", varargin(1))
    libRoot = jinvoke(libRoot, "toString");
    xmlPath = jinvoke(LibraryUtils, "getXmlDirectory", libName, libRoot);
    xcosName = getXcosBlockName(libName, blockName, varargin(1));
end
xmlDir = jinvoke(xmlPath, "toString");

xmlName = [xmlDir + blockName + ".xml"];
if ~isfile(xmlName) then
    disp("Error: could not find file " + xmlName);
    return; // exit script
end

// get/create icon directory
imgDir = strsubst(xmlDir, ["XML" + fs], ["Doc" + fs + "Icons" + fs]);
if ~isdir(imgDir) then
    mkdir(imgDir)
end

try
    // setup diagram structure
    scs_m = scicos_diagram();       // create diagram
    scs_m.props.title = blockName;   // give diagram a name
    execstr("scs_m.objs(1) = "+ xcosName + "('"define'");");    // load block
    sz = scs_m.objs(1).graphics.sz  // get original size of block
    scale = 20;
    scs_m.objs(1).graphics.sz = sz*scale;   // resize block to a suitable size
    
    // create Xcos instance
    sdh = jinvoke(ScilabDirectHandler, "acquire")
    diagram = jnewInstance(XcosDiagram);
    diag = jinvoke(sdh, "readDiagram", diagram, "scs_m")

    // create image
    obj = jnewInstance(ExportUtils);
    jinvoke(obj, "exportDiagram", diag, imgDir, "png");
    
    // release instance
    jinvoke(sdh, "release");

    // resize image if it's too large
    if (sz(1) > 4 | sz(2) > 4) then
        // NOTE: ImageMagick has to be installed!
        //       Block image is resized so it will fit into 96x80 image (aspect-
        //       ratio will be preserved)
        host("convert '"" + imgDir + blockName + ".png'" -resize 96x80 '"" + imgDir + blockName + ".png'"");
    end

    mprintf("Palette icon %s successfully created.\n",[imgDir + blockName + ".png"]);
catch
    mprintf("Error creating Palette icon %s\n", [imgDir + blockName + ".png"]);
    mprintf("ERROR: %s\n", lasterror());
end


endfunction


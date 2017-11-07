// Copyright (c) 2014, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
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
// $LastChangedRevision: 617 $
//
// This file is part of X2C. http://www.mechatronic-simulation.org/
//
// Starter script for Basic library

mprintf("+++ Loading X2C library Basic\n");
funcprot(0);
jimport at.lcm.x2c.utils.Utils;
X2CRootDir = jinvoke(jinvoke(Utils, "getRootDirectory"), "toString");
X2CRootDir = strsubst(X2CRootDir, "\", "/");
err = %f;       // error flag

// load interface functions
exec("x2c_ProjectDocumentation.sci", -1);
exec("x2c_ModelTransformation.sci", -1);
exec("x2c_CommunicatorStart.sci", -1);

// load/create palette for library
if isfile("Basic.xpal")
    // palette already exists -> load saved palette
    xcosPalAdd("Basic.xpal", "X2C");
else
    
    // load blocks and build palette
    pal = xcosPal("Basic");
    
    
    // CommunicatorStart
    mprintf("Loading block x2c_CommunicatorStart...")
    try
        o = x2c_CommunicatorStart("define");
        pal_icon = [];
        style = [];
        style = struct();
        style.image = "file:///" + X2CRootDir + "Library/Basic/Doc/Images/EmptyImage.svg";    // image needed to prevent loading error of library
        pal_icon = "../Doc/Icons/CommunicatorStart.png";
        pal = xcosPalAddBlock(pal, o, pal_icon, style);
        clear("o");
        mprintf("done\n");
    catch
        err = %t;
        mprintf("ERROR: %s\n", lasterror());
    end
    
    // ModelTransformation
    mprintf("Loading block x2c_ModelTransformation...")
    try
        o = x2c_ModelTransformation("define");
        pal_icon = [];
        style = [];
        style = struct();
        style.image = "file:///" + X2CRootDir + "Library/Basic/Doc/Images/EmptyImage.svg";    // image needed to prevent loading error of library
        pal_icon = "../Doc/Icons/ModelTransformation.png";
        pal = xcosPalAddBlock(pal, o, pal_icon, style);
        clear("o");
        mprintf("done\n");
    catch
        err = %t;
        mprintf("ERROR: %s\n", lasterror());
    end
    
    // ProjectDocumentation
    mprintf("Loading block x2c_ProjectDocumentation...")
    try
        o = x2c_ProjectDocumentation("define");
        pal_icon = [];
        style = [];
        style = struct();
        style.image = "file:///" + X2CRootDir + "Library/Basic/Doc/Images/EmptyImage.svg";    // image needed to prevent loading error of library
        pal_icon = "../Doc/Icons/ProjectDocumentation.png";
        pal = xcosPalAddBlock(pal, o, pal_icon, style);
        clear("o");
        mprintf("done\n");
    catch
        err = %t;
        mprintf("ERROR: %s\n", lasterror());
    end
    
    // load palette
    xcosPalAdd(pal, "X2C");
    
    // save palette
    if ~err then
        xcosPalExport(pal, "Basic.xpal");
    end
    
    // cleanup
    clear("pal")
    clear("pal_icon")
    clear("style")
    clear("err")
    
end

mprintf("---\n");

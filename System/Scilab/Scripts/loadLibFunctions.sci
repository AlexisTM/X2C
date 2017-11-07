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
// Several helper functions to get easy access to Scilab Java library functions

funcprot(0)

//mprintf("\n+ Loading X2C Scilab lib\n")
warningmode = warning('query')
warning('off')

function x2c_transformModel_Comm()
	// Transforms model and starts Communicator, 
	jimport("at.lcm.x2c.scilab.xcos.x2cManager.X2cManager");
	x2cMng = jinvoke(X2cManager, "getInstance");
	jinvoke(x2cMng, "setCurrentDiagram");
	jinvoke(x2cMng, "updateModel");
endfunction


function x2c_setCurrentDiagram()
    jimport("at.lcm.x2c.scilab.xcos.x2cManager.X2cManager");
    x2cMng = jinvoke(X2cManager, "getInstance");
	jinvoke(x2cMng, "setCurrentDiagram");
endfunction


function x2c_ModelReset()
    jimport("at.lcm.x2c.scilab.xcos.x2cManager.X2cManager");
    x2cMng = jinvoke(X2cManager, "getInstance");
	jinvoke(x2cMng, "resetModel");
endfunction



function x2c_communicatorConnect()
    jimport("at.lcm.x2c.scilab.xcos.x2cManager.X2cManager");
    x2cMng = jinvoke(X2cManager, "getInstance");
    if isVersionLessThan("5.5.0") then
        success = junwrap(jinvoke(x2cMng, "communicatorConnect"));
    else
        success = jinvoke(x2cMng, "communicatorConnect");
    end
    
	if success then
		mprintf("Successfully connected to Communicator\n")
	else
		error("Connecting to Communicator failed")
	end
endfunction

function x2c_communicatorDisconnect()
    jimport("at.lcm.x2c.scilab.xcos.x2cManager.X2cManager");
    x2cMng = jinvoke(X2cManager, "getInstance");
	jinvoke(x2cMng, "communicatorDisconnect");
endfunction

function x2c_setCurrentWorkingDir()
    jimport("at.lcm.x2c.core.librarymanager.X2cLibraryManager");
    x2cLM = jinvoke(X2cLibraryManager,"getInstance");
	jinvoke(x2cLM, "setWorkingDirectory", pwd());
endfunction

function cwd = x2c_getCurrentWorkingDir()
    jimport("at.lcm.x2c.core.librarymanager.X2cLibraryManager");
    x2cLM = jinvoke(X2cLibraryManager,"getInstance");
    if isVersionLessThan("5.5.0") then
        cwd = junwrap(jinvoke(x2cLM, "getWorkingDirectoryString"));
    else
        cwd = jinvoke(x2cLM, "getWorkingDirectoryString");
    end
endfunction


function [x2cLibs] = x2c_LibManager_addPath(path)
	// Set "x2c_rebuild = %t" to rebuild already compiled libraries.
	//
	// this does not work
	//
	// @author: martin.hochwallner@lcm.at
    currentdir = pwd();
    jimport("at.lcm.x2c.core.librarymanager.X2cLibraryManager");
    x2cLM = jinvoke(X2cLibraryManager,"getInstance");
    
    if isVersionLessThan("5.5.0") then
        x2cLibs = junwrap(jinvoke(x2cLM, "addPath_XcosLibPathStr", path));
    else
        x2cLibs = jinvoke(x2cLM, "addPath_XcosLibPathStr", path);
    end
    
    for l = x2cLibs
        mprintf("\n")
        mprintf("++ %s \n", l )
		chdir(l);
		if exists("x2c_rebuild") then
			mprintf("rebuilding Library\n")
			exec("X2C___builder.sce", -1)
		end		
		warning("This does not work as supposed! Loaded libs are not visible outside this function. FIXME")
		exec("X2C___start.sce", -1)
        mprintf("--\n")
    end
    chdir(currentdir)
	mprintf("libs added:\n")
	disp(x2cLibs')
    mprintf("- done\n")
endfunction


function [x2cLibs] = x2c_LibManager_populate()
	// x2c_LibManager_populateWithDefault()
	// @author: martin.hochwallner@lcm.at
    jimport("at.lcm.x2c.core.librarymanager.X2cLibraryManager");
    x2cLM = jinvoke(X2cLibraryManager,"getInstance");
    
    if isVersionLessThan("5.5.0") then
        x2cLibs = junwrap(jinvoke(x2cLM, "populateWithDefault"));
    else
        x2cLibs = jinvoke(x2cLM, "populateWithDefault");
    end
endfunction


function [x2cLibs] = x2c_LibManager_addPath_woLoad(path)
	// @author: martin.hochwallner@lcm.at
    jimport("at.lcm.x2c.core.librarymanager.X2cLibraryManager");
    x2cLM = jinvoke(X2cLibraryManager,"getInstance");
    
    if isVersionLessThan("5.5.0") then
        x2cLibs = junwrap(jinvoke(x2cLM, "addPath_XcosLibPathStr", path));
    else
        x2cLibs = jinvoke(x2cLM, "addPath_XcosLibPathStr", pat);
    end
endfunction

function x2c_setParameterComm(componentName, blockName, parameter,  value)
	jimport("at.lcm.x2c.scilab.xcos.x2cManager.X2cManager");
	x2cMng = jinvoke(X2cManager, "getInstance");
	jinvoke(x2cMng, "notifyLocalChange2Romete_BlockMaskParameter", componentName, blockName, parameter,  value)	
endfunction



warning(warningmode)
//mprintf("- done\n")  

//eof

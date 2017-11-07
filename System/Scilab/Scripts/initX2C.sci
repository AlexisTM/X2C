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
// X2C setup
// Parameters:
// varargin (optional): If true, X2C will fully rebuild

function [] = initX2C(varargin)
funcprot(0);

// get current directory
curDir = pwd();

// get file separator
fs = filesep();

// get operating system
os = getos();

// default: no setup error
setupError = %f;

// name of startup file
filename = "scilab.ini";

// check for type of installation request
deInstall = %f;
fullInstall = %f
if (length(varargin)>0) then
    if (varargin(1)==%f) then
        deInstall = %t;
    end
    if (varargin(1)==%t) then
        fullInstall = %t;
    end
end

if (deInstall==%f) then
    //--------------------------------------------------------------------------
    // X2C Installation
    //--------------------------------------------------------------------------
    mprintf("\n\nSetting up X2C\n==============\n")
    
    
    // get version info of scilab
    [vers, opt] = getversion();
    arch = opt(2);              // scilab architecture
    
    if vers == "scilab-5.4.1" then
        mprintf("You are using %s, which is not supported by X2C. Please upgrade to scilab-5.5.0 or higher.\n\n", vers);
        exit;
    end
    
    
    // get X2C paths
    // NOTE: it is assumed that setup is called from <X2C_ROOT>\System\Scilab\Scripts
    X2CRootPath = strsubst(curDir, [fs + "System" + fs + "Scilab" + fs + "Scripts"], "");
    X2CJavaPath = [X2CRootPath + fs + "System" + fs + "Java"];
    ScriptPath = curDir;
    
    // load helper file
    exec("getArchitecture.sci", -1);
    
    // set environment variable
    jimport java.io.File;
    coreJar = File.new(X2CJavaPath + fs + "Core.jar");
    javaclasspath(jinvoke(coreJar, "getAbsolutePath"));
    
    jimport at.lcm.x2c.utils.Utils;
    try
        jinvoke(Utils, "setEnvironmentRootVariable", File.new(X2CRootPath));
    catch
        disp(lasterror());
        disp("Please modify environment variables manually");
    end
    
    X2CLibraryPaths = [];
    libs = ls([X2CRootPath + fs + "Library"])';
    for curLib=libs
        if isfile([X2CRootPath + fs + "Library" + fs + curLib + fs + "x2c_library.xml"]) then
            X2CLibraryPaths = [X2CLibraryPaths, curLib];
        end
    end
    
    
    //--------------------------------------------------------------------------
    // Initialize X2C for setup
    //--------------------------------------------------------------------------
    // X2C java class paths
    classPaths = [];
    classPaths = [classPaths, [X2CRootPath + fs + "System" + fs + "Scilab" + fs + "Java" + fs + "dist" + fs + "X2cScilab.jar"]];
    //classPaths = [classPaths, [X2CRootPath + fs + "System" + fs + "Scilab" + fs + "Java" + fs + "conf"]];
    classPaths = [classPaths, [X2CJavaPath + fs + "Core.jar"]];
    classPaths = [classPaths, [X2CJavaPath + fs + "Communicator.jar"]];
    classPaths = [classPaths, [X2CJavaPath + fs + "BlockGenerator.jar"]];
    classPaths = [classPaths, [X2CJavaPath + fs + "lib" + fs + "General" + fs + "general.jar"]];
    classPaths = [classPaths, [X2CJavaPath + fs + "lib" + fs + "apache-log4j-2.0-rc1" + fs + "log4j-api-2.0-rc1.jar"]];
    classPaths = [classPaths, [X2CJavaPath + fs + "lib" + fs + "apache-log4j-2.0-rc1" + fs + "log4j-core-2.0-rc1.jar"]];
    classPaths = [classPaths, [X2CJavaPath + fs + "lib" + fs + "commons-cli-1.2" + fs + "commons-cli-1.2.jar"]];
    classPaths = [classPaths, [X2CJavaPath + fs + "lib" + fs + "commons-lang3-3.1" + fs + "commons-lang3-3.1.jar"]];
    classPaths = [classPaths, [X2CJavaPath + fs + "lib" + fs + "Communication" + fs + "Hardware.jar"]];
    classPaths = [classPaths, [X2CJavaPath + fs + "lib" + fs + "RXTX-create-lab-commons" + fs + "RXTXcomm.jar"]];
    if (os == "Windows") then
        classPaths = [classPaths, [X2CJavaPath + fs + "lib" + fs + "PCAN-Basic" + fs + "PCAN-Basic.jar"]];
        classPaths = [classPaths, [X2CJavaPath + fs + "lib" + fs + "JD2XX" + fs + "jd2xx.jar"]];
    end
    classPaths = [classPaths, [X2CJavaPath + fs + "lib" + fs + "MigLayout" + fs + "miglayout-3.7.4-swing.jar"]];
    classPaths = [classPaths, [X2CJavaPath + fs + "lib" + fs + "Cloning" + fs + "cloning-1.7.4.jar"]];
    classPaths = [classPaths, [X2CJavaPath + fs + "lib" + fs + "Cloning" + fs + "objenesis-1.2.jar"]];
    classPaths = [classPaths, [X2CJavaPath + fs + "lib" + fs + "Commons" + fs + "commons-math3-3.0.jar"]];
    classPaths = [classPaths, [X2CJavaPath + fs + "lib" + fs + "JFreeChart" + fs + "jcommon-1.0.16.jar"]];
    classPaths = [classPaths, [X2CJavaPath + fs + "lib" + fs + "JFreeChart" + fs + "jfreechart_extension.jar"]];
    classPaths = [classPaths, [X2CJavaPath + fs + "lib" + fs + "JFreeChart" + fs + "jfreechart-1.0.13.jar"]];
    classPaths = [classPaths, [X2CJavaPath + fs + "lib" + fs + "Jython" + fs + "jython-standalone-2.5.4-rc1.jar"]];
    
    // X2C java library paths
    libraryPaths = [];
    if (os == "Windows") then
        if arch == "x64" then
            libraryPaths = [libraryPaths, [X2CJavaPath + fs + "lib" + fs + "PCAN-Basic" + fs + "win64"]];
            libraryPaths = [libraryPaths, [X2CJavaPath + fs + "lib" + fs + "RXTX-create-lab-commons" + fs + "win64"]];
            libraryPaths = [libraryPaths, [X2CJavaPath + fs + "lib" + fs + "JD2XX" + fs + "win64"]];
        elseif arch == "x86" then
            libraryPaths = [libraryPaths, [X2CJavaPath + fs + "lib" + fs + "PCAN-Basic" + fs + "win32"]];
            libraryPaths = [libraryPaths, [X2CJavaPath + fs + "lib" + fs + "RXTX-create-lab-commons" + fs + "win32"]];
            libraryPaths = [libraryPaths, [X2CJavaPath + fs + "lib" + fs + "JD2XX" + fs + "win32"]];
        end
    elseif (os == "Linux") then
        if arch == "x64" then
            libraryPaths = [libraryPaths, [X2CJavaPath + fs + "lib" + fs + "RXTX-create-lab-commons" + fs + "linux64"]];
        elseif arch == "x86" then
            libraryPaths = [libraryPaths, [X2CJavaPath + fs + "lib" + fs + "RXTX-create-lab-commons" + fs + "linux32"]];
        end
    elseif (os == "Darwin") then
        if arch == "x64" then
            libraryPaths = [libraryPaths, [X2CJavaPath + fs + "lib" + fs + "RXTX-create-lab-commons" + fs + "mac64"]];
        elseif arch == "x86" then
            libraryPaths = [libraryPaths, [X2CJavaPath + fs + "lib" + fs + "RXTX-create-lab-commons" + fs + "mac32"]];
        end
    else
        // other operating systems are not supported
    end
    
    // X2C library paths
    for curLib=X2CLibraryPaths
        f = [X2CRootPath + fs + "Library" + fs + curLib + fs + "Conversion" + fs + "Java" + fs + curLib + ".jar"];
        if isfile(f) then
            // only add existing jars
            classPaths = [classPaths, f];
        end
    end
    
    //------------------------------------------------------------------------------
    // Full rebuild
    //------------------------------------------------------------------------------
    if (fullInstall==%t) then
        // full rebuild of X2C requested
        mprintf("Setting up workspace for full rebuild...");
        try
            // load java class paths
            for curPath = classPaths
                javaclasspath(curPath);
            end
    
            // load java library paths
            for curPath = libraryPaths
                javalibrarypath(curPath);
            end
    
            // load Xcos libraries
            loadXcosLibs();
    
            // load X2C scripts
            exec([ScriptPath + fs + "loadFunctions.sce"], -1);
        
            mprintf("DONE\n");
            
        catch
            mprintf("FAILED\n");
            mprintf("ERROR: %s\n\n", lasterror());
            setupError = %t;
        end
        
        // fetch architecture info in X2C format
        arch = getArchitecture();
        
        // clean up Scilab directories
        mprintf("+ Deleting files from previous setup...\n");
        try
            for curLib = X2CLibraryPaths
                scilabDir = [X2CRootPath + fs + "Library" + fs + curLib + fs + "Scilab"];
                if isdir(scilabDir) then
                    // only remove files in existing directories
                    if  strcmp(curLib, "Basic") then
                        // ignore Basic library
                        mdelete(scilabDir + fs + "*_" + arch + ".*");
                        mdelete(scilabDir + fs + "*.sci");
                        mdelete(scilabDir + fs + "*.c");
                        mdelete(scilabDir + fs + "Palette_Icons_generated.txt")
                    else
                        // delete files of Basic library
                        mdelete([scilabDir + fs + "libBasic_" + arch + ".*"]);
                        mdelete([scilabDir + fs + "loader_" + arch + ".*"]);
                    end
                    mdelete([scilabDir + fs + "*.xpal"]);
                end
            end
            mprintf("- DONE\n");
        catch
            mprintf("- FAILED\n");
            mprintf("ERROR: %s\n\n", lasterror());
            setupError = %t;
        end
        
        // rebuild libraries
        mprintf("+ Rebuild X2C libraries...\n");
        try
            for curLib = X2CLibraryPaths
                    if strcmp(curLib, "Basic") then
                        // all but Basic
                        createLibrary(curLib);
                    else
                        // Basic
                        scilabDir = [X2CRootPath + fs + "Library" + fs + curLib + fs + "Scilab"];
                        chdir(scilabDir)
                        exec([scilabDir + fs + "builder_" + arch + ".sce"], -1);	// building is sufficient
                        chdir(curDir)
                    end
            end
            mprintf("- DONE\n");
        catch
            mprintf("- FAILED\n");
            mprintf("ERROR: %s\n\n", lasterror());
            setupError = %t;
        end
        
        // populate X2C library manager with existing libraries
        mprintf("+ Populating X2C library manager...\n");
        try
            x2c_LibManager_populate();
            mprintf("- DONE\n");
        catch
            mprintf("- FAILED\n");
            mprintf("ERROR: %s\n\n", lasterror());
            setupError = %t;
        end
        
        // load palettes
        mprintf("+ Loading palettes...\n");
        try
            exec([ScriptPath + fs + "loadPalettes.sce"], -1);
            mprintf("- DONE\n");
        catch
            mprintf("- FAILED\n");
            mprintf("ERROR: %s\n\n", lasterror());
            setupError = %t;
        end
        
        // create palette icons
        mprintf("+ Creating palette icons...\n");
        try
            createAllLibraryIcons();
            mprintf("- DONE\n");
        catch
            mprintf("- FAILED\n");
            mprintf("ERROR: %s\n\n", lasterror());
            setupError = %t;
        end
        
    else
        // normal build -> clean up a little
        // remove palette files
        mprintf("Deleting files from previous setup...");
        try
            for curLib = X2CLibraryPaths
                scilabDir = [X2CRootPath + fs + "Library" + fs + curLib + fs + "Scilab"];
                if isdir(scilabDir) then
                    // only remove files in existing directories
                    mdelete([scilabDir + fs + "*.xpal"]);
                end
            end
            mprintf("DONE\n");
        catch
            mprintf("FAILED\n");
            mprintf("ERROR: %s\n\n", lasterror());
            setupError = %t;
        end
        
    end

    if ~setupError then
        //----------------------------------------------------------------------
        // Write startup file
        //----------------------------------------------------------------------
        mprintf("Opening/creating startup file...");
        try
          
            // create file
            fileID = mopen(SCIHOME + fs + filename, 'wt');   // file will be overwritten if it already exists
            
            mprintf("DONE\n");
            
            // print header
            time = datevec(datenum());
            mfprintf(fileID, "// This file is part of X2C. http://www.mechatronic-simulation.org/\n");
            mfprintf(fileID, "// \n");
            mfprintf(fileID, "// Copyright (c) 2014, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/\n");
            mfprintf(fileID, "// All rights reserved.\n");
            mfprintf(fileID, "// \n");
            mfprintf(fileID, "// This file was generated by %s on %02d-%02d-%04d %02d:%02d\n", "setup.sce", time(3), time(2), time(1), time(4), time(5));
            mfprintf(fileID, "// \n");
            mfprintf(fileID, "  \n");
            
            mprintf("  Writing path entries...");
            try
                mfprintf(fileID, "try\n");
                mfprintf(fileID, "    mprintf('"Start X2C\\n'");\n\n");
                mfprintf(fileID, "    //X2C java class paths:\n");
                for curPath = classPaths
                    mfprintf(fileID, "    javaclasspath('"%s'");\n", curPath);
                end
                mfprintf(fileID, "    \n");
        
                mfprintf(fileID, "    //X2C java library paths:\n");
                for curPath = libraryPaths
                    mfprintf(fileID, "    javalibrarypath('"%s'");\n", curPath);
                end
                mfprintf(fileID, "\n");
                
                mprintf("DONE\n");
            catch
                mprintf("FAILED\n");
                mprintf("ERROR: %s\n\n", lasterror());
            end
            
            mprintf("  Writing function loading entries...");
        
            try
                mfprintf(fileID, "\n");
                        
                mfprintf(fileID, "    loadXcosLibs();\n");
                mfprintf(fileID, "\n");
                
                mfprintf(fileID, "    exec('"%s'", -1);\n", [ScriptPath + fs + "loadFunctions.sce"]);
                mfprintf(fileID, "\n");
                
                mfprintf(fileID, "    mprintf('"+ Populating X2C library manager\\n'");\n");
                mfprintf(fileID, "    x2c_LibManager_populate();\n");
                mfprintf(fileID, "    mprintf('"- Done \\n'");\n");
                mfprintf(fileID, "\n");

                if (os == "Windows") then
                    mfprintf(fileID, "    loadLibs();\n");
                    mfprintf(fileID, "\n");
                else
					// if loadLibs() is executed in Linux a "scicos_free is missing" error will occur. But only when executed within the startup script. After startup, loadLibs() can be manually executed without any problems!
                    // TODO: add support for other OS
                end
                
                mfprintf(fileID, "    exec('"%s'", -1);\n", [ScriptPath + fs + "loadPalettes.sce"]);
                mfprintf(fileID, "\n");
        
                mprintf("DONE\n");
            catch
                mprintf("FAILED\n");
                mprintf("ERROR: %s\n\n", lasterror());
            end
            
            mfprintf(fileID, "catch\n");
            mfprintf(fileID, "    disp(['"ERROR: '" + lasterror()])\n");
            mfprintf(fileID, "end\n\n");
            
            // close file
            mprintf("Closing startup file...");
            try
                mclose(fileID);
                mprintf("DONE\n");
            catch
                mprintf("FAILED\n");
                mprintf("ERROR: %s\n\n", lasterror());
            end
            
        catch
            mclose(fileID); // try to close file
            mprintf("FAILED\n");
            mprintf("ERROR: %s\n\n", lasterror());
        end
    
        mprintf("\n\nFirst part of X2C setup finished, please restart Scilab to complete the setup!\n\n");
    
    else
        // error during setup occured -> do not write startup file
        mprintf("Error during setup -> no startup file created.\n")
    end
    
    // auto exit if full rebuild option enabled
    if (length(varargin)>0 & varargin(1)==%t) then
        mprintf("Scilab will be closed in 5 seconds. Good bye!");
        sleep(5000);
        exit();
    end
    
else
    //--------------------------------------------------------------------------
    // X2C Deinstallation
    //--------------------------------------------------------------------------
    mprintf("\n\nDeinstallation of X2C\n=====================\n")
    mprintf("Deleting startup file...");
    mdelete(SCIHOME + fs + filename);   // delete init script to disable X2C startup
    mprintf("DONE\n");
    
    mprintf("Deinstallation finished. Please restart Scilab.\n")

end



endfunction

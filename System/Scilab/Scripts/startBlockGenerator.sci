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
// Starts Block Generator.

function [] = startBlockGenerator()
  funcprot(0);
  
  // import necessary java classes
  jimport('at.lcm.x2c.utils.Utils');
  
  // get current directory
  curDir = pwd();
  
  // get file separator
  fs = filesep();
  
  // get operating system
  os = getos();
  
  // get version info of scilab
  [vers,opt] = getversion();
  arch = opt(2);// scilab architecture
  
  // get X2C paths
  X2CRootPath = jinvoke(jinvoke(Utils, 'getRootDirectory'), 'toString');
  X2CJavaPath = X2CRootPath + 'System' + fs + 'Java' + fs;
  
  X2CLibraryPaths = [];
  libs = ls(X2CRootPath + fs + 'Library')';
  for curLib = libs,
    if isfile(X2CRootPath + fs + 'Library' + fs + curLib + fs + 'x2c_library.xml') then 
      X2CLibraryPaths = [X2CLibraryPaths,curLib];
    end,
  end,
  
  // get file delimiter
  if os == 'Windows' then 
    fd = ';';
  elseif os == 'Linux' then 
    fd = ':';
  else   // other operating systems
    fd = ';';// fall back to windows delimiter
  end,
  
  //------------------------------------------------------------------------------
  // Gather some X2C information
  //------------------------------------------------------------------------------
  // X2C java class paths
  classPaths = '""' + X2CRootPath + 'System' + fs + 'Scilab' + fs + 'Java' + fs + 'dist' + fs + 'X2cScilab.jar' + '""' + fd;
  classPaths = classPaths + '""' + X2CJavaPath + 'Core.jar' + '""' + fd;
  classPaths = classPaths + '""' + X2CJavaPath + 'Communicator.jar' + '""' + fd;
  classPaths = classPaths + '""' + X2CJavaPath + 'BlockGenerator.jar' + '""' + fd;
  classPaths = classPaths + '""' + X2CJavaPath + 'lib' + fs + 'General' + fs + 'general.jar' + '""' + fd;
  classPaths = classPaths + '""' + X2CJavaPath + 'lib' + fs + 'apache-log4j-2.0-rc1' + fs + 'log4j-api-2.0-rc1.jar' + '""' + fd;
  classPaths = classPaths + '""' + X2CJavaPath + 'lib' + fs + 'apache-log4j-2.0-rc1' + fs + 'log4j-core-2.0-rc1.jar' + '""' + fd;
  classPaths = classPaths + '""' + X2CJavaPath + 'lib' + fs + 'commons-cli-1.2' + fs + 'commons-cli-1.2.jar' + '""' + fd;
  classPaths = classPaths + '""' + X2CJavaPath + 'lib' + fs + 'commons-lang3-3.1' + fs + 'commons-lang3-3.1.jar' + '""' + fd;
  classPaths = classPaths + '""' + X2CJavaPath + 'lib' + fs + 'Communication' + fs + 'Hardware.jar' + '""' + fd;
  classPaths = classPaths + '""' + X2CJavaPath + 'lib' + fs + 'RXTX-create-lab-commons' + fs + 'RXTXcomm.jar' + '""' + fd;
  if os == 'Windows' then 
    classPaths = classPaths + '""' + X2CJavaPath + 'lib' + fs + 'PCAN-Basic' + fs + 'PCAN-Basic.jar' + '""' + fd;
    classPaths = classPaths + '""' + X2CJavaPath + 'lib' + fs + 'JD2XX' + fs + 'jd2xx.jar' + '""' + fd;
  end,
  classPaths = classPaths + '""' + X2CJavaPath + 'lib' + fs + 'MigLayout' + fs + 'miglayout-3.7.4-swing.jar' + '""' + fd;
  classPaths = classPaths + '""' + X2CJavaPath + 'lib' + fs + 'Cloning' + fs + 'cloning-1.7.4.jar' + '""' + fd;
  classPaths = classPaths + '""' + X2CJavaPath + 'lib' + fs + 'Cloning' + fs + 'objenesis-1.2.jar' + '""' + fd;
  classPaths = classPaths + '""' + X2CJavaPath + 'lib' + fs + 'Commons' + fs + 'commons-math3-3.0.jar' + '""' + fd;
  classPaths = classPaths + '""' + X2CJavaPath + 'lib' + fs + 'JFreeChart' + fs + 'jcommon-1.0.16.jar' + '""' + fd;
  classPaths = classPaths + '""' + X2CJavaPath + 'lib' + fs + 'JFreeChart' + fs + 'jfreechart_extension.jar' + '""' + fd;
  classPaths = classPaths + '""' + X2CJavaPath + 'lib' + fs + 'JFreeChart' + fs + 'jfreechart-1.0.13.jar' + '""' + fd;
  
  // X2C java library paths
  libraryPaths = [];
  if os == 'Windows' then 
    if arch == 'x64' then 
      libraryPaths = libraryPaths + '""' + X2CJavaPath + 'lib' + fs + 'PCAN-Basic' + fs + 'win64' + '""' + fd;
      libraryPaths = libraryPaths + '""' + X2CJavaPath + 'lib' + fs + 'RXTX-create-lab-commons' + fs + 'win64' + '""' + fd;
      libraryPaths = libraryPaths + '""' + X2CJavaPath + 'lib' + fs + 'JD2XX' + fs + 'win64' + '""' + fd;
    elseif arch == 'x86' then 
      libraryPaths = libraryPaths + '""' + X2CJavaPath + 'lib' + fs + 'PCAN-Basic' + fs + 'win32' + '""' + fd;
      libraryPaths = libraryPaths + '""' + X2CJavaPath + 'lib' + fs + 'RXTX-create-lab-commons' + fs + 'win32' + '""' + fd;
      libraryPaths = libraryPaths + '""' + X2CJavaPath + 'lib' + fs + 'JD2XX' + fs + 'win32' + '""' + fd;
    end,
  elseif os == 'Linux' then 
    if arch == 'x64' then 
      libraryPaths = libraryPaths + '""' + X2CJavaPath + 'lib' + fs + 'RXTX-create-lab-commons' + fs + 'linux64' + '""' + fd;
    elseif arch == 'x86' then 
      libraryPaths = libraryPaths + '""' + X2CJavaPath + 'lib' + fs + 'RXTX-create-lab-commons' + fs + 'linux32' + '""' + fd;
    end,
  elseif os == 'Darwin' then 
    if arch == 'x64' then 
      libraryPaths = libraryPaths + '""' + X2CJavaPath + 'lib' + fs + 'RXTX-create-lab-commons' + fs + 'mac64' + '""' + fd;
    elseif arch == 'x86' then 
      libraryPaths = libraryPaths + '""' + X2CJavaPath + 'lib' + fs + 'RXTX-create-lab-commons' + fs + 'mac32' + '""' + fd;
    end,
  else 
    // TODO: add support for other operating systems
  end,
  
  // X2C library paths
  for curLib = X2CLibraryPaths,
    f = '""' + X2CRootPath + 'Library' + fs + curLib + fs + 'Conversion' + fs + 'Java' + fs + curLib + '.jar' + '""' + fd;
    if isfile(f) then 
      // only add existing jars
      classPaths = classPaths + f;
    end,
  end,
  
  
  //------------------------------------------------------------------------------
  // Start communicator
  //------------------------------------------------------------------------------
  try
    // in case of Windows OS the Java VM included with Scilab is being used
    if os == 'Windows' then 
      javaPath = SCI + fs + 'java' + fs + 'JRE' + fs + 'bin' + fs;
  
  
      unix('start /B """" ""' + javaPath + 'java.exe"" -Dlog4j.configurationFile=""file:///' + X2CRootPath + 'System' + fs + 'Scilab' + fs + 'Java' + fs + 'conf' + fs + 'log4j2_communicator.xml"" -Djava.library.path=' + libraryPaths + ' -cp ' + classPaths + ' at.lcm.x2c.gui.blockgenerator.BlockGenerator');
    elseif os == 'Linux' then 
  
  
      unix_w('java -Dlog4j.configurationFile=""file://' + X2CRootPath + 'System/Scilab/Java/conf/log4j2_communicator.xml"" -Djava.library.path=' + libraryPaths + ' -cp ' + classPaths + ' at.lcm.x2c.gui.blockgenerator.BlockGenerator &');
    else 
      // TODO: add support for other operating systems
    end,
  catch
    mprintf('Error starting X2C Communicator: %s\n\n', lasterror());
  end,
  
endfunction

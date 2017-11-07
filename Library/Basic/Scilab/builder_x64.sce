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
// This file is part of X2C. http://www.mechatronic-simulation.org/
// $LastChangedRevision: 666 $

mprintf("Building Basic library for x64 system...");

funcprot(0);
msvc = findmsvccompiler();
bOK = configure_msvc();
if ~haveacompiler() then
    mprintf("SKIPPED (no compiler found)\n");
    [compileCompFDone] = return(%f)
end

X2C_ROOT = fullpath(fullfile(getenv("X2C_Root")));
X2C_LIB_PATH = get_absolute_file_path("builder_x64.sce');
X2C_LIB_PATH = dirname(X2C_LIB_PATH);

// delete "is-compiled" marker
mdelete("Library_is_compiled_for_x64.txt');

names = ["x2c_DoNothing_C"];
files = ["x2c_DoNothing_C.c"];
flag = "c";
loadername = "loader_x64.sce";
libname = "Basic_x64";
ldflags = SCI + "\bin\scicos.lib";
cflags = "-I" + SCI + "\modules\scicos_blocks\includes" + " -I" + SCI + "\modules\scicos\includes" + " -I" + X2C_ROOT + "\Controller\Common" + " -I" + X2C_LIB_PATH + "\Controller\src" + " -I" + X2C_LIB_PATH + "\Controller\inc";
ilib_for_link(names, files, [], flag, "", loadername, libname, ldflags, cflags);

// delete temporary files
if isdir("Debug") then
  rmdir("Debug","s");
end
if isdir("Release") then
  rmdir("Release","s");
end
mdelete("cleaner.sce")
mdelete("Makelib.mak")

// create "is-compiled" marker
currentTime=clock();
save("Library_is_compiled_for_x64.txt", "currentTime");

mprintf("DONE\n");

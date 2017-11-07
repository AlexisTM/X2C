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
// $LastChangedRevision: 761 $

function [x,y,typ] = x2c_ModelTransformation(job, arg1, arg2)
    // import necessary java classes
    jimport at.lcm.x2c.utils.Utils;
    
    // get file separator
    fs = filesep();
    
    // get X2C root directory
    X2CRootDir = jinvoke(jinvoke(Utils, "getRootDirectory"), "toString");

    x = [];
    y = [];
    typ = [];

    select job
    case "plot" then
        standard_draw(arg1)

    case "getinputs" then
        [x,y,typ] = standard_inputs(arg1)

    case "getoutputs" then
        [x,y,typ] = standard_outputs(arg1)

    case "getorigin" then
        [x,y] = standard_origin(arg1)

    case "set" then
        x = arg1
        while %t do
            if ~ exists("%scicos_prob") then
                w = createWindow();
                w.axes_size = [300,150];
                w.figure_name = "Model Transformation (%d)";
                w.icon = X2CRootDir + "System" + fs + "Scilab" + fs + "Java" + fs + "src" + fs + "at" + fs + "lcm" + fs + "x2c" + fs + "resource" + fs + "AppIcon.png";
                tf = uicontrol(w, "style", "text", "units", "normalized", "position", [0 0.5 1 0.5], "horizontalalignment", "center", "verticalalignment", "bottom");
                tf.string = "Model transformation in progress...";
                disp(tf.string);
                tf2 = uicontrol(w, "style", "text", "units", "normalized", "position", [0 0 1 0.5], "horizontalalignment", "center","verticalalignment", "top");

                try
                    x2c_transformModel_Comm();
                    tf.string = "Model transformation done!";
                    disp(tf.string);
                    for i = 5:-1:1
                        tf2.string = "(Window will be closed in " + string(i) + " seconds)"
                        sleep(1000);
                    end
                    close(w);
                catch
                    tf.string = "Model transformation failed!";
                    disp(tf.string);
                    tf2.string = "(See console output for more information)";
                    disp(lasterror());
                end

            end
            break
        end

    case "define" then
        // see: help scicos_model
        model = scicos_model()
        model.sim = list("x2c_DoNothing_C", 4);
        model.in = [];
        model.evtin = []
        model.out = [];
        model.state = []   // continuous states
        model.dstate = []  // discrete-time states
        model.ipar = [] //contrParamVals
        model.blocktype = "c"
        model.nmode = 0
        model.nzcross = 0
        model.dep_ut = [%f %f]
        exprs = [""]
        gr_i=[];
        x=standard_define([7 3],model, exprs, gr_i)
        x.graphics.style = "fillColor=#ff8c00;gradientColor=#ff8c00;rounded=%f;noLabel=0;displayedLabel=transform Model and<BR>push to Communicator;align=center" 
    end

endfunction

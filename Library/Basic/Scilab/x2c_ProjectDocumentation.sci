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

function [x,y,typ] = x2c_ProjectDocumentation(job, arg1, arg2)
    
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
                //--------------------------------------------------------------
                // create/open project documentation dialog
                //--------------------------------------------------------------
                // import necessary java classes
                jimport at.lcm.x2c.utils.Utils;

                // get file separator
                fs = filesep();

                // get X2C root directory
                X2CRootDir = jinvoke(jinvoke(Utils, "getRootDirectory"), "toString");

                w = createWindow();

                w.axes_size = [400 150];
                w.figure_name = "Project Documentation (%d)";
                w.infobar_visible = "on";
                w.icon = X2CRootDir + "System" + fs + "Scilab" + fs + "Java" + fs + "src" + fs + "at" + fs + "lcm" + fs + "x2c" + fs + "resource" + fs + "AppIcon.png";

                uicontrol(w, ...
                "style", "text", ...
                "units", "normalized", ...
                "position", [0 0 1 1]);

                uicontrol(w, ...
                "style", "text", ...
                "string", "Optional user documentation file (TeX format):", ...
                "units", "normalized", ...
                "position", [0 0.8 1.0 0.2], ...
                "horizontalalignment", "left");

                e_userDoc = uicontrol(w, ...
                "style", "edit", ...
                "string", "UserDoc.tex", ...
                "units", "normalized", ...
                "position", [0 0.6 0.9 0.2], ...
                "horizontalalignment", "left");

                pb_select = uicontrol(w, ...
                "style", "pushbutton", ...
                "string", "...", ...
                "units", "normalized", ...
                "position", [0.9 0.6 0.1 0.2], ...
                "horizontalalignment", "center", ...
                "TooltipString", "Select user documentation file", ...
                "callback", "selectFile");

                cb_results = uicontrol(w, ...
                "style", "checkbox", ...
                "value", 0, ...
                "string", "Add test report results", ...
                "units", "normalized", ...
                "position", [0 0.4 1.0 0.2], ...
                "callback", "addTestReport");

                pb_create = uicontrol(w, ...
                "style", "pushbutton", ...
                "string", "Create documentation", ...
                "units", "normalized", ...
                "position", [0.3 0.2 0.4 0.2], ...
                "horizontalalignment", "center", ...
                "callback", "createDocu");
                //--------------------------------------------------------------
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
        x=standard_define([5 3],model, exprs, gr_i)
        x.graphics.style = "fillColor=#ff8c00;gradientColor=#ff8c00;rounded=%f;noLabel=0;displayedLabel=create<BR>Documentation;align=center;" 
    end

endfunction


// callback function for test report checkbox
function addTestReport()
    w = gcf();
    if (gcbo.value == 0) then
        w.user_data = "0";
    else
        w.user_data = "1";
    end
endfunction


// callback function for file selection button
function selectFile()
    w = gcf();
    fileName = uigetfile(["*.tex"],pwd(), "Choose a file name", %t);
    w.children(4).string = fileName;    // TODO: find a better way to write into the text field
endfunction


// callback function for create docu button
function createDocu()
    w = gcf();
    w.info_message = "Creating documentation..."
    
    // get user specific docu name
    docuFile = strsubst(w.children(4).string, '\', '/');    // TODO: find a better way to read from the text field
    
    // check if test results should be added
    if w.user_data(1) == "1" then
        addResults = %t;
    else
        addResults = %f;
    end

    // create project documentation
    err = createProjectDocu(addResults, docuFile);
    
    if (err == 0) then
        w.info_message = "Creating documentation...DONE";
    else
        w.info_message = "Creating documentation...FAILED";
    end
endfunction

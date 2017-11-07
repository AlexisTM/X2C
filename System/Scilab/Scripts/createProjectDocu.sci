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
// Analyzes Xcos model and creates documentation.

function err = createProjectDocu(addTestReports, UserDocu)
    
jimport at.lcm.x2c.docu.MaskParameterDocu;
jimport at.lcm.x2c.docu.UsedBlockDocu;
jimport at.lcm.x2c.docu.ProjectDocu;
jimport at.lcm.x2c.utils.Utils;

fs = filesep(); // get file separator
curPath = pwd();
err = 0;

System = getCurrentSystem();    // get name of opened diagram (only one Xcos diagram has to be open, otherwise error will occur)

ProjectPath = [curPath + fs + '..'];
DocuPath = [ProjectPath + fs + Utils.PROJECT_DOC_PATH];

// check for input arguments
if ~exists("addTestReports") then
    addTestReports = %f;
end
if ~exists("UserDocu") then
    UserDocu = "";
end

// create documentation directory if it doesn't exists yet
if ~isdir(DocuPath) then
    mkdir(DocuPath);
end

// create project library documentation
mprintf('Creating project library documentation ');
try
    mprintf('.');
    err = generateProjectLibDocu(ProjectPath);
    if err == 1
        mprintf ('... NO LIBRARY FOUND\n');
    else
        mprintf(' DONE\n');
    end
catch 
    mprintf(' FAILED\n');
    mprintf('   Error: %s\n\n', lasterror()); 
end

mprintf('Creating project documentation ');
try

    // get Xcos stuff ((Sub)System figures, parameter, version)
    mprintf('.');
    createVersionInfo(DocuPath);
    mprintf('.');
    createModelStructure(System, DocuPath);
    mprintf('.');
    createParameterFile(System, DocuPath);

    // get block parameter information
    mprintf('.');
    ParameterDoc = jnewInstance(MaskParameterDocu, ProjectPath, System);
    jinvoke(ParameterDoc, "write");

    // get information of used blocks
    mprintf('.');
    BlockDoc = jnewInstance(UsedBlockDocu, ProjectPath, System);
    jinvoke(BlockDoc, "write");

    // assemble information and create documentation
    mprintf('.');
    ProjectDoc = jnewInstance(ProjectDocu, ProjectPath, System);
    if isfile(".."+ fs + "X2CCode" + fs + UserDocu) then
        // docu is in X2CCode directory
        jinvoke(ProjectDoc, "setUserDocu", ["../X2CCode/" + UserDocu]);
    elseif isfile(UserDocu) then
        // docu is anywhere
        jinvoke(ProjectDoc, "setUserDocu", [UserDocu]);
    end
	jinvoke(ProjectDoc, "createDoxyDoc");
    jinvoke(ProjectDoc, "writeWithHeader", addTestReports);
    mprintf(' DONE\n');
    err = 0;
catch
    mprintf(' FAILED\n');
    mprintf('   Error: %s\n\n', lasterror());
    err = 1;
end

return err;

endfunction



// Create tex-file with Scilab/Xcos parameter values
function createParameterFile(System, DocuPath)
    jimport('at.lcm.x2c.core.structure.Model');
    fs = filesep(); // get file separator
    
    mdl = jnewInstance(Model);
    jinvoke(mdl, "readFromXml", [DocuPath + fs + '..' + fs + Utils.CODEGEN_PATH_NAME + fs + System + '.xml']);
    Ts = jinvoke(mdl, "getSampleTime");
    
    // set filename
    filename = 'ModelParameter.tex';

    try
        fileID = mopen(DocuPath + fs + filename,'wt');   // open/generate file

        mfprintf(fileID, '\\section{Model Parameter}\n\n');

        // sample time
        mfprintf(fileID, '\\subsection{Sample Time}\n');
        mfprintf(fileID, '\\begin{XtoCtabular}{Sample Time}\n');
        mfprintf(fileID, '$T_S$ & $%d\\mu s$ \\tabularnewline\n', round(Ts*1e6));
        mfprintf(fileID, '\\hline\n');
        mfprintf(fileID, '\\end{XtoCtabular}\n\n');
        
        // model parameter
        ScilabFile = 'ModelParameter.sce';
        if isfile(ScilabFile)   // check if file exists
            mfprintf(fileID, '\\subsection{Scilab Parameter}\n');
            mfprintf(fileID, '\\lstinputlisting[caption=%s, captionpos=b, language=Scilab, frame=lines, backgroundcolor=\\color{listingcolor}]{../X2CCode/%s}\n', ScilabFile, ScilabFile);
        end
            
        mclose(fileID);

    catch 
        disp('Couldn''t create ModelParameter.tex!');
        disp('Error: ' + lasterror());
    end
   
endfunction


// Create tex-file with images of Xcos model
function createModelStructure(System, DocuPath)
    fs = filesep(); // get file separator

   // get list of subsystems
   chdir("../X2CCode");
   systemList = ls(System + "_*.png")';
   chdir(curPath);
//   SystemNames = regexprep(SystemList, '/', '_');
//   SystemNames = regexprep(SystemNames, ' ', '_');
//   SystemNames = regexprep(SystemNames, '\n', '_');
//
//    // create images of system and subsystems
//    generateProjectImages(System, DocuPath);

    // set filename
    filename = 'ModelStructure.tex';

    try
        fileID = mopen(DocuPath + fs + filename, 'wt');   // open/generate file

        caption = texString(System);

        
        mfprintf(fileID, '\\section{Model Structure}\n\n');
        mfprintf(fileID, '%%Top System\n');
        mfprintf(fileID, '\\subsection{Xcos Model}\n');
        // TODO: implement automated generation of model images
        if isfile(System + ".png") then
            mfprintf(fileID, '\\begin{figure}[H]\n');
            mfprintf(fileID, '  \\begin{center}\n');
            mfprintf(fileID, '    \\includegraphics[max size={\\textwidth}{0.9\\textheight}]{%s}\n', ["../X2CCode/" + System + ".png"]);
            mfprintf(fileID, '    \\caption{%s}\n', caption);
            mfprintf(fileID, '  \\end{center}\n');
            mfprintf(fileID, '\\end{figure}\n\n');
        else
            mfprintf(fileID, 'NOTE: Automated generation of model images is not implemented yet.\n');
            mfprintf(fileID, 'You can manually include the model image by following these steps:\n');
            mfprintf(fileID, '\\begin{enumerate}\n');
            mfprintf(fileID, '  \\item{Go to Xcos model window}\n');
            mfprintf(fileID, '  \\item{Select \\textit{File->Export all diagrams}}\n');
            mfprintf(fileID, '  \\item{Save image(s) as *.png file(s) in \\textit{X2CCode} directory}\n');
            mfprintf(fileID, '  \\item{Generate project documentation again by double-clicking the block \\textit{create Documentation}}\n');
            mfprintf(fileID, '\\end{enumerate}\n');
        end


        mfprintf(fileID, '%%SubSystems\n');
        mfprintf(fileID, '\\subsection{Subsystems}\n');
        for curSystem = systemList
            // check if there is something to document 
            if isfile("../X2CCode/" + curSystem) then
                caption = texString(curSystem);
                mfprintf(fileID, '\\begin{figure}[H]\n');
                mfprintf(fileID, '  \\begin{center}\n');
                mfprintf(fileID, '    \\includegraphics[max size={\\textwidth}{0.9\\textheight}]{%s}\n', ["../X2CCode/" + curSystem]);
                mfprintf(fileID, '    \\caption{%s}\n', strsubst(caption, ".png", ""));
                mfprintf(fileID, '  \\end{center}\n');
                mfprintf(fileID, '\\end{figure}\n\n');
            end
        end

        mclose(fileID);

    catch
        disp('Couldn''t create ModelStructure.tex!');
        disp('Error: ' + lasterror());
    end

endfunction

// Create Tex-File with version informations
function createVersionInfo(DocuPath)

    //set filename
    filename = 'VersionInfo.tex';

    try
        fileID = mopen(DocuPath + fs + filename, 'wt');   // open/generate file

        // collect version informations
        verInfo = ver();
        verOS = texString(verInfo(2,2));
        verScilab = texString(verInfo(1,2));
        verJava = texString(verInfo(3,2));
        verX2C = getX2CVersion();

        // check type of X2C version
        if isdir([getenv('X2C_Root') + fs + 'System' + fs + 'Matlab'])
            typeX2C = 'full';
        else
            typeX2C = 'open';
        end
     
        //print informations
        mfprintf(fileID, '\\section{Version Information}\n\n');

        mfprintf(fileID, '\\subsection{X2C}\n');
        mfprintf(fileID, '\\begin{itemize}\n');
        mfprintf(fileID, '  \\item{X2C%s:} Version %s\n', typeX2C, verX2C);
        mfprintf(fileID, '\\end{itemize}\n\n');
        
        mfprintf(fileID, '\\subsection{Operating System}\n');
        mfprintf(fileID, '\\begin{itemize}\n');
        mfprintf(fileID, '  \\item{OS:} %s\n', verOS);
        mfprintf(fileID, '\\end{itemize}\n\n');

        mfprintf(fileID, '\\subsection{Scilab}\n');
        mfprintf(fileID, '\\begin{itemize}\n');
        mfprintf(fileID, '  \\item{Scilab:} Version %s\n', verScilab);
        mfprintf(fileID, '  \\item{Java:} Version %s\n', verJava);
        mfprintf(fileID, '\\end{itemize}\n\n');
          
        mclose(fileID);

    catch
        disp('Couldn''t create VersionInfo.tex!');
        disp('Error: ' + lasterror());
    end

endfunction

// Replace special characters with tex commands
function replaced = texString(str)
    tmp = strsubst(str, '\', '\/');
    tmp = strsubst(tmp,'_','\_');
    tmp = strsubst(tmp,'\n',' ');
    
    tmp = strsubst(tmp,'#', '\#');
    tmp = strsubst(tmp,'%', '\%');
    tmp = strsubst(tmp,'$', '\$');
    tmp = strsubst(tmp,'&', '\&');
    tmp = strsubst(tmp,'{', '\{');
    tmp = strsubst(tmp,'}', '\}');
    tmp = strsubst(tmp,'€', '\euro{}');
    tmp = strsubst(tmp,'²', '\textsuperscript{2}');
    tmp = strsubst(tmp,'³', '\textsuperscript{3}');
    tmp = strsubst(tmp,'~', '\textasciitilde{}');
    tmp = strsubst(tmp,'^', '\textasciicircum{}');
    
    replaced = tmp;
    
endfunction

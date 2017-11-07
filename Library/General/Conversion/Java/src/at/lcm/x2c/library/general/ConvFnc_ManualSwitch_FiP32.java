/*
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is licensed according to the BSD 3-clause license as follows:
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the "Linz Center of Mechatronics GmbH" and "LCM" nor
 *       the names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL "Linz Center of Mechatronics GmbH" BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * This file is part of X2C. http://www.mechatronic-simulation.org/
 * $LastChangedRevision: 941 $
 */
// USERCODE-BEGIN:Description                                                                                           
//*     Description:                                                           *
// USERCODE-END:Description                                                                                             

package at.lcm.x2c.library.general;

import at.lcm.x2c.core.structure.*;
import at.lcm.bu21.general.dtypes.*;

// USERCODE-BEGIN:Imports                                                                                               
import at.lcm.x2c.utils.QFormat;

// USERCODE-END:Imports                                                                                                 

@SuppressWarnings("unused")
public class ConvFnc_ManualSwitch_FiP32 extends ConversionFunction {
     private static final long serialVersionUID = 1L;

     public ConvFnc_ManualSwitch_FiP32() throws Exception {
     }

     public void convert() throws Exception {

          MaskDouble ToggleMaskVal = 
               (MaskDouble)this.getMaskParameter("Toggle").getMaskDataType();
          TNumeric ToggleMaskData = 
               (TNumeric)ToggleMaskVal.getData();

          // Controller Parameter Data                                                                                  
          TNumeric ToggleCtrVal = this.getCtrlParamData("Toggle");

// USERCODE-BEGIN:ConvFnc                                                                                               
		ToggleCtrVal.setReal(0, 0, QFormat.getQValue(Double.valueOf(ToggleMaskVal.getValue()), 0, 8, true));
// USERCODE-END:ConvFnc                                                                                                 
          this.setCtrlParamData("Toggle", ToggleCtrVal);
     }

     public void revert() throws Exception {

          MaskDouble ToggleMaskVal = 
               (MaskDouble)this.getMaskParameter("Toggle").getMaskDataType();
          TNumeric ToggleMaskData = 
               (TNumeric)ToggleMaskVal.getData();

          // Controller Parameter Data                                                                                  
          TNumeric ToggleCtrVal = this.getCtrlParamData("Toggle");

// USERCODE-BEGIN:RevFnc                                                                                                
		// get controller parameter
		double Toggle = ToggleCtrVal.getReal(0, 0);

		// calculate mask parameter
		if (Toggle == 0) {
			ToggleMaskData.setReal(0, 0, 0);
		} else {
			ToggleMaskData.setReal(0, 0, 1);
		}
// USERCODE-END:RevFnc                                                                                                  
          this.getMaskParameter("Toggle").setValue(ToggleMaskData.toFullString());
     }
}

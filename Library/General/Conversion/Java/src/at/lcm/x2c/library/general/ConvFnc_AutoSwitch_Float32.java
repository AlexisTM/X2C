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
 * $LastChangedRevision: 457 $
 */
// USERCODE-BEGIN:Description                                                                                           
/* Description: */
// USERCODE-END:Description                                                                                             

package at.lcm.x2c.library.general;

import at.lcm.x2c.core.structure.*;
import at.lcm.bu21.general.dtypes.*;

// USERCODE-BEGIN:Imports                                                                                               
// USERCODE-END:Imports                                                                                                 

@SuppressWarnings("unused")
public class ConvFnc_AutoSwitch_Float32 extends ConversionFunction {
     private static final long serialVersionUID = 1L;

     public ConvFnc_AutoSwitch_Float32() throws Exception {
     }

     public void convert() throws Exception {

          MaskDouble Thresh_upMaskVal = 
               (MaskDouble)this.getMaskParameter("Thresh_up").getMaskDataType();
          TNumeric Thresh_upMaskData = 
               (TNumeric)Thresh_upMaskVal.getData();
          MaskDouble Thresh_downMaskVal = 
               (MaskDouble)this.getMaskParameter("Thresh_down").getMaskDataType();
          TNumeric Thresh_downMaskData = 
               (TNumeric)Thresh_downMaskVal.getData();

          // Controller Parameter Data                                                                                  
          TNumeric Thresh_upCtrVal = this.getCtrlParamData("Thresh_up");
          TNumeric Thresh_downCtrVal = this.getCtrlParamData("Thresh_down");
          TNumeric StatusCtrVal = this.getCtrlParamData("Status");

// USERCODE-BEGIN:ConvFnc                                                                                               
		double Thresh_up, Thresh_down;

		// get mask parameter value
		Thresh_up = Double.valueOf(Thresh_upMaskVal.getValue());
		Thresh_down = Double.valueOf(Thresh_downMaskVal.getValue());

		// validation
		if (Thresh_up < Thresh_down) {
			throw new Exception("Threshold level conflict: up value must not be smaller than down value!");
		}

		// set controller parameter value
		Thresh_upCtrVal.setReal(0, 0, Thresh_up);
		Thresh_downCtrVal.setReal(0, 0, Thresh_down);

// USERCODE-END:ConvFnc                                                                                                 
          this.setCtrlParamData("Thresh_up", Thresh_upCtrVal);
          this.setCtrlParamData("Thresh_down", Thresh_downCtrVal);
          this.setCtrlParamData("Status", StatusCtrVal);
     }

     public void revert() throws Exception {

          MaskDouble Thresh_upMaskVal = 
               (MaskDouble)this.getMaskParameter("Thresh_up").getMaskDataType();
          TNumeric Thresh_upMaskData = 
               (TNumeric)Thresh_upMaskVal.getData();
          MaskDouble Thresh_downMaskVal = 
               (MaskDouble)this.getMaskParameter("Thresh_down").getMaskDataType();
          TNumeric Thresh_downMaskData = 
               (TNumeric)Thresh_downMaskVal.getData();

          // Controller Parameter Data                                                                                  
          TNumeric Thresh_upCtrVal = this.getCtrlParamData("Thresh_up");
          TNumeric Thresh_downCtrVal = this.getCtrlParamData("Thresh_down");
          TNumeric StatusCtrVal = this.getCtrlParamData("Status");

// USERCODE-BEGIN:RevFnc                                                                                                
		double Thresh_up, Thresh_down;

		// get controller parameter value
		Thresh_up = Thresh_upCtrVal.getReal(0, 0);
		Thresh_down = Thresh_downCtrVal.getReal(0, 0);

		// set mask parameter value
		Thresh_upMaskData.setReal(0, 0, Thresh_up);
		Thresh_downMaskData.setReal(0, 0, Thresh_down);

// USERCODE-END:RevFnc                                                                                                  
          this.getMaskParameter("Thresh_up").setValue(Thresh_upMaskData.toFullString());
          this.getMaskParameter("Thresh_down").setValue(Thresh_downMaskData.toFullString());
     }
}

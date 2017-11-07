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
 * $LastChangedRevision: 738 $
 */
// USERCODE-BEGIN:Description                                                                                           
/* Description: */
// USERCODE-END:Description                                                                                             

package at.lcm.x2c.library.control;

import at.lcm.x2c.core.structure.*;
import at.lcm.bu21.general.dtypes.*;

// USERCODE-BEGIN:Imports                                                                                               
// USERCODE-END:Imports                                                                                                 

@SuppressWarnings("unused")
public class ConvFnc_TDSystemO1_Float64 extends ConversionFunction {
     private static final long serialVersionUID = 1L;

     public ConvFnc_TDSystemO1_Float64() throws Exception {
     }

     public void convert() throws Exception {

          MaskDouble AMaskVal = 
               (MaskDouble)this.getMaskParameter("A").getMaskDataType();
          TNumeric AMaskData = 
               (TNumeric)AMaskVal.getData();
          MaskDouble BMaskVal = 
               (MaskDouble)this.getMaskParameter("B").getMaskDataType();
          TNumeric BMaskData = 
               (TNumeric)BMaskVal.getData();
          MaskDouble CMaskVal = 
               (MaskDouble)this.getMaskParameter("C").getMaskDataType();
          TNumeric CMaskData = 
               (TNumeric)CMaskVal.getData();
          MaskDouble DMaskVal = 
               (MaskDouble)this.getMaskParameter("D").getMaskDataType();
          TNumeric DMaskData = 
               (TNumeric)DMaskVal.getData();

          // Controller Parameter Data                                                                                  
          TNumeric a11CtrVal = this.getCtrlParamData("a11");
          TNumeric b11CtrVal = this.getCtrlParamData("b11");
          TNumeric c11CtrVal = this.getCtrlParamData("c11");
          TNumeric d11CtrVal = this.getCtrlParamData("d11");
          TNumeric x1CtrVal = this.getCtrlParamData("x1");

// USERCODE-BEGIN:ConvFnc                                                                                               
		/* get mask values and set controller parameter values */
		a11CtrVal.setReal(0, 0, Double.valueOf(AMaskVal.getValue()));
		b11CtrVal.setReal(0, 0, Double.valueOf(BMaskVal.getValue()));
		c11CtrVal.setReal(0, 0, Double.valueOf(CMaskVal.getValue()));
		d11CtrVal.setReal(0, 0, Double.valueOf(DMaskVal.getValue()));

// USERCODE-END:ConvFnc                                                                                                 
          this.setCtrlParamData("a11", a11CtrVal);
          this.setCtrlParamData("b11", b11CtrVal);
          this.setCtrlParamData("c11", c11CtrVal);
          this.setCtrlParamData("d11", d11CtrVal);
          this.setCtrlParamData("x1", x1CtrVal);
     }

     public void revert() throws Exception {

          MaskDouble AMaskVal = 
               (MaskDouble)this.getMaskParameter("A").getMaskDataType();
          TNumeric AMaskData = 
               (TNumeric)AMaskVal.getData();
          MaskDouble BMaskVal = 
               (MaskDouble)this.getMaskParameter("B").getMaskDataType();
          TNumeric BMaskData = 
               (TNumeric)BMaskVal.getData();
          MaskDouble CMaskVal = 
               (MaskDouble)this.getMaskParameter("C").getMaskDataType();
          TNumeric CMaskData = 
               (TNumeric)CMaskVal.getData();
          MaskDouble DMaskVal = 
               (MaskDouble)this.getMaskParameter("D").getMaskDataType();
          TNumeric DMaskData = 
               (TNumeric)DMaskVal.getData();

          // Controller Parameter Data                                                                                  
          TNumeric a11CtrVal = this.getCtrlParamData("a11");
          TNumeric b11CtrVal = this.getCtrlParamData("b11");
          TNumeric c11CtrVal = this.getCtrlParamData("c11");
          TNumeric d11CtrVal = this.getCtrlParamData("d11");
          TNumeric x1CtrVal = this.getCtrlParamData("x1");

// USERCODE-BEGIN:RevFnc                                                                                                
		/* get controller values and set mask parameter values */
		AMaskData.setReal(0, 0, a11CtrVal.getReal(0, 0));
		BMaskData.setReal(0, 0, b11CtrVal.getReal(0, 0));
		CMaskData.setReal(0, 0, c11CtrVal.getReal(0, 0));
		DMaskData.setReal(0, 0, d11CtrVal.getReal(0, 0));

// USERCODE-END:RevFnc                                                                                                  
          this.getMaskParameter("A").setValue(AMaskData.toFullString());
          this.getMaskParameter("B").setValue(BMaskData.toFullString());
          this.getMaskParameter("C").setValue(CMaskData.toFullString());
          this.getMaskParameter("D").setValue(DMaskData.toFullString());
     }
}

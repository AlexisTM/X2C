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
//*     Description:                                                           *
// USERCODE-END:Description                                                                                             

package at.lcm.x2c.library.control;

import at.lcm.x2c.core.structure.*;
import at.lcm.bu21.general.dtypes.*;

// USERCODE-BEGIN:Imports                                                                                               
import at.lcm.x2c.utils.QFormat;

// USERCODE-END:Imports                                                                                                 

@SuppressWarnings("unused")
public class ConvFnc_TF2_FiP8 extends ConversionFunction {
     private static final long serialVersionUID = 1L;

     public ConvFnc_TF2_FiP8() throws Exception {
     }

     public void convert() throws Exception {

          MaskDouble b2MaskVal = 
               (MaskDouble)this.getMaskParameter("b2").getMaskDataType();
          TNumeric b2MaskData = 
               (TNumeric)b2MaskVal.getData();
          MaskDouble b1MaskVal = 
               (MaskDouble)this.getMaskParameter("b1").getMaskDataType();
          TNumeric b1MaskData = 
               (TNumeric)b1MaskVal.getData();
          MaskDouble b0MaskVal = 
               (MaskDouble)this.getMaskParameter("b0").getMaskDataType();
          TNumeric b0MaskData = 
               (TNumeric)b0MaskVal.getData();
          MaskDouble a1MaskVal = 
               (MaskDouble)this.getMaskParameter("a1").getMaskDataType();
          TNumeric a1MaskData = 
               (TNumeric)a1MaskVal.getData();
          MaskDouble a0MaskVal = 
               (MaskDouble)this.getMaskParameter("a0").getMaskDataType();
          TNumeric a0MaskData = 
               (TNumeric)a0MaskVal.getData();
          MaskDouble ts_factMaskVal = 
               (MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
          TNumeric ts_factMaskData = 
               (TNumeric)ts_factMaskVal.getData();

          // Controller Parameter Data                                                                                  
          TNumeric b0CtrVal = this.getCtrlParamData("b0");
          TNumeric b1CtrVal = this.getCtrlParamData("b1");
          TNumeric b2CtrVal = this.getCtrlParamData("b2");
          TNumeric a0CtrVal = this.getCtrlParamData("a0");
          TNumeric a1CtrVal = this.getCtrlParamData("a1");
          TNumeric sfrbCtrVal = this.getCtrlParamData("sfrb");
          TNumeric sfraCtrVal = this.getCtrlParamData("sfra");
          TNumeric in_oldCtrVal = this.getCtrlParamData("in_old");
          TNumeric in_veryoldCtrVal = this.getCtrlParamData("in_veryold");
          TNumeric out_oldCtrVal = this.getCtrlParamData("out_old");
          TNumeric out_veryoldCtrVal = this.getCtrlParamData("out_veryold");

// USERCODE-BEGIN:ConvFnc                                                                                               
		double b0, b1, b2, a0, a1;
		int sfrb, sfrb0, sfrb1, sfrb2, sfra, sfra0, sfra1;
		final int BITS = 8;

		// get controller parameter values
		b0 = Double.valueOf(b0MaskVal.getValue());
		b1 = Double.valueOf(b1MaskVal.getValue());
		b2 = Double.valueOf(b2MaskVal.getValue());
		a0 = Double.valueOf(a0MaskVal.getValue());
		a1 = Double.valueOf(a1MaskVal.getValue());

		// validate controller parameters

		// calculate shift factor
		sfrb0 = QFormat.getQFormat(b0, BITS, true);
		sfrb1 = QFormat.getQFormat(b1, BITS, true);
		sfrb2 = QFormat.getQFormat(b2, BITS, true);
		sfrb = Math.min(sfrb0, Math.min(sfrb1, sfrb2));

		sfra0 = QFormat.getQFormat(a0, BITS, true);
		sfra1 = QFormat.getQFormat(a1, BITS, true);
		sfra = Math.min(sfra0, sfra1);

		// set shift factors and Q values
		sfrbCtrVal.setReal(0, 0, sfrb);
		sfraCtrVal.setReal(0, 0, sfra);
		b0CtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(b0, (int) (sfrbCtrVal.getReal(0, 0)), BITS, true)));
		b1CtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(b1, (int) (sfrbCtrVal.getReal(0, 0)), BITS, true)));
		b2CtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(b2, (int) (sfrbCtrVal.getReal(0, 0)), BITS, true)));
		a0CtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(a0, (int) (sfraCtrVal.getReal(0, 0)), BITS, true)));
		a1CtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(a1, (int) (sfraCtrVal.getReal(0, 0)), BITS, true)));

// USERCODE-END:ConvFnc                                                                                                 
          this.setCtrlParamData("b0", b0CtrVal);
          this.setCtrlParamData("b1", b1CtrVal);
          this.setCtrlParamData("b2", b2CtrVal);
          this.setCtrlParamData("a0", a0CtrVal);
          this.setCtrlParamData("a1", a1CtrVal);
          this.setCtrlParamData("sfrb", sfrbCtrVal);
          this.setCtrlParamData("sfra", sfraCtrVal);
          this.setCtrlParamData("in_old", in_oldCtrVal);
          this.setCtrlParamData("in_veryold", in_veryoldCtrVal);
          this.setCtrlParamData("out_old", out_oldCtrVal);
          this.setCtrlParamData("out_veryold", out_veryoldCtrVal);
     }

     public void revert() throws Exception {

          MaskDouble b2MaskVal = 
               (MaskDouble)this.getMaskParameter("b2").getMaskDataType();
          TNumeric b2MaskData = 
               (TNumeric)b2MaskVal.getData();
          MaskDouble b1MaskVal = 
               (MaskDouble)this.getMaskParameter("b1").getMaskDataType();
          TNumeric b1MaskData = 
               (TNumeric)b1MaskVal.getData();
          MaskDouble b0MaskVal = 
               (MaskDouble)this.getMaskParameter("b0").getMaskDataType();
          TNumeric b0MaskData = 
               (TNumeric)b0MaskVal.getData();
          MaskDouble a1MaskVal = 
               (MaskDouble)this.getMaskParameter("a1").getMaskDataType();
          TNumeric a1MaskData = 
               (TNumeric)a1MaskVal.getData();
          MaskDouble a0MaskVal = 
               (MaskDouble)this.getMaskParameter("a0").getMaskDataType();
          TNumeric a0MaskData = 
               (TNumeric)a0MaskVal.getData();
          MaskDouble ts_factMaskVal = 
               (MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
          TNumeric ts_factMaskData = 
               (TNumeric)ts_factMaskVal.getData();

          // Controller Parameter Data                                                                                  
          TNumeric b0CtrVal = this.getCtrlParamData("b0");
          TNumeric b1CtrVal = this.getCtrlParamData("b1");
          TNumeric b2CtrVal = this.getCtrlParamData("b2");
          TNumeric a0CtrVal = this.getCtrlParamData("a0");
          TNumeric a1CtrVal = this.getCtrlParamData("a1");
          TNumeric sfrbCtrVal = this.getCtrlParamData("sfrb");
          TNumeric sfraCtrVal = this.getCtrlParamData("sfra");
          TNumeric in_oldCtrVal = this.getCtrlParamData("in_old");
          TNumeric in_veryoldCtrVal = this.getCtrlParamData("in_veryold");
          TNumeric out_oldCtrVal = this.getCtrlParamData("out_old");
          TNumeric out_veryoldCtrVal = this.getCtrlParamData("out_veryold");

// USERCODE-BEGIN:RevFnc                                                                                                
		/* Insert parameter reversion here... */
// USERCODE-END:RevFnc                                                                                                  
          this.getMaskParameter("b2").setValue(b2MaskData.toFullString());
          this.getMaskParameter("b1").setValue(b1MaskData.toFullString());
          this.getMaskParameter("b0").setValue(b0MaskData.toFullString());
          this.getMaskParameter("a1").setValue(a1MaskData.toFullString());
          this.getMaskParameter("a0").setValue(a0MaskData.toFullString());
          this.getMaskParameter("ts_fact").setValue(ts_factMaskData.toFullString());
     }
}

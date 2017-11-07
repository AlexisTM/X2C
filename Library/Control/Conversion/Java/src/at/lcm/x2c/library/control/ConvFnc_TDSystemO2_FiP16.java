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
import at.lcm.x2c.utils.QFormat;
// USERCODE-END:Imports                                                                                                 

@SuppressWarnings("unused")
public class ConvFnc_TDSystemO2_FiP16 extends ConversionFunction {
     private static final long serialVersionUID = 1L;

     public ConvFnc_TDSystemO2_FiP16() throws Exception {
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

          // Controller Parameter Data                                                                                  
          TNumeric a11CtrVal = this.getCtrlParamData("a11");
          TNumeric a12CtrVal = this.getCtrlParamData("a12");
          TNumeric a21CtrVal = this.getCtrlParamData("a21");
          TNumeric a22CtrVal = this.getCtrlParamData("a22");
          TNumeric b11CtrVal = this.getCtrlParamData("b11");
          TNumeric b12CtrVal = this.getCtrlParamData("b12");
          TNumeric b21CtrVal = this.getCtrlParamData("b21");
          TNumeric b22CtrVal = this.getCtrlParamData("b22");
          TNumeric sfra11CtrVal = this.getCtrlParamData("sfra11");
          TNumeric sfra12CtrVal = this.getCtrlParamData("sfra12");
          TNumeric sfra21CtrVal = this.getCtrlParamData("sfra21");
          TNumeric sfra22CtrVal = this.getCtrlParamData("sfra22");
          TNumeric sfrb11CtrVal = this.getCtrlParamData("sfrb11");
          TNumeric sfrb12CtrVal = this.getCtrlParamData("sfrb12");
          TNumeric sfrb21CtrVal = this.getCtrlParamData("sfrb21");
          TNumeric sfrb22CtrVal = this.getCtrlParamData("sfrb22");
          TNumeric x1CtrVal = this.getCtrlParamData("x1");
          TNumeric x2CtrVal = this.getCtrlParamData("x2");

// USERCODE-BEGIN:ConvFnc                                                                                               
		double[] a = new double[4];
		double[] b = new double[4];
		final int BITS = 16;


		// check for correct dimension of matrices
		if (AMaskData.getNumColumns() != 4) {
			throw new Exception("Matrix A size mismatch");
		}
		if (BMaskData.getNumColumns() != 4) {
			throw new Exception("Matrix B size mismatch");
		}

		// get controller parameter values
		for (int i=0;i<4;i++) {
			a[i] = AMaskData.getReal(0, i);
			b[i] = BMaskData.getReal(0, i);
		}


		// set shift factors
		sfra11CtrVal.setReal(0, 0, QFormat.getQFormat(a[0], BITS, true));
		sfra12CtrVal.setReal(0, 0, QFormat.getQFormat(a[1], BITS, true));
		sfra21CtrVal.setReal(0, 0, QFormat.getQFormat(a[2], BITS, true));
		sfra22CtrVal.setReal(0, 0, QFormat.getQFormat(a[3], BITS, true));

		sfrb11CtrVal.setReal(0, 0, QFormat.getQFormat(b[0], BITS, true));
		sfrb12CtrVal.setReal(0, 0, QFormat.getQFormat(b[1], BITS, true));
		sfrb21CtrVal.setReal(0, 0, QFormat.getQFormat(b[2], BITS, true));
		sfrb22CtrVal.setReal(0, 0, QFormat.getQFormat(b[3], BITS, true));

		// set Q values
		a11CtrVal.setReal(0,0, Double.valueOf(QFormat.getQValue(a[0], (int)(sfra11CtrVal.getReal(0,0)), BITS, true)));
		a12CtrVal.setReal(0,0, Double.valueOf(QFormat.getQValue(a[1], (int)(sfra12CtrVal.getReal(0,0)), BITS, true)));
		a21CtrVal.setReal(0,0, Double.valueOf(QFormat.getQValue(a[2], (int)(sfra21CtrVal.getReal(0,0)), BITS, true)));
		a22CtrVal.setReal(0,0, Double.valueOf(QFormat.getQValue(a[3], (int)(sfra22CtrVal.getReal(0,0)), BITS, true)));

		b11CtrVal.setReal(0,0, Double.valueOf(QFormat.getQValue(b[0], (int)(sfrb11CtrVal.getReal(0,0)), BITS, true)));
		b12CtrVal.setReal(0,0, Double.valueOf(QFormat.getQValue(b[1], (int)(sfrb12CtrVal.getReal(0,0)), BITS, true)));
		b21CtrVal.setReal(0,0, Double.valueOf(QFormat.getQValue(b[2], (int)(sfrb21CtrVal.getReal(0,0)), BITS, true)));
		b22CtrVal.setReal(0,0, Double.valueOf(QFormat.getQValue(b[3], (int)(sfrb22CtrVal.getReal(0,0)), BITS, true)));


// USERCODE-END:ConvFnc                                                                                                 
          this.setCtrlParamData("a11", a11CtrVal);
          this.setCtrlParamData("a12", a12CtrVal);
          this.setCtrlParamData("a21", a21CtrVal);
          this.setCtrlParamData("a22", a22CtrVal);
          this.setCtrlParamData("b11", b11CtrVal);
          this.setCtrlParamData("b12", b12CtrVal);
          this.setCtrlParamData("b21", b21CtrVal);
          this.setCtrlParamData("b22", b22CtrVal);
          this.setCtrlParamData("sfra11", sfra11CtrVal);
          this.setCtrlParamData("sfra12", sfra12CtrVal);
          this.setCtrlParamData("sfra21", sfra21CtrVal);
          this.setCtrlParamData("sfra22", sfra22CtrVal);
          this.setCtrlParamData("sfrb11", sfrb11CtrVal);
          this.setCtrlParamData("sfrb12", sfrb12CtrVal);
          this.setCtrlParamData("sfrb21", sfrb21CtrVal);
          this.setCtrlParamData("sfrb22", sfrb22CtrVal);
          this.setCtrlParamData("x1", x1CtrVal);
          this.setCtrlParamData("x2", x2CtrVal);
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

          // Controller Parameter Data                                                                                  
          TNumeric a11CtrVal = this.getCtrlParamData("a11");
          TNumeric a12CtrVal = this.getCtrlParamData("a12");
          TNumeric a21CtrVal = this.getCtrlParamData("a21");
          TNumeric a22CtrVal = this.getCtrlParamData("a22");
          TNumeric b11CtrVal = this.getCtrlParamData("b11");
          TNumeric b12CtrVal = this.getCtrlParamData("b12");
          TNumeric b21CtrVal = this.getCtrlParamData("b21");
          TNumeric b22CtrVal = this.getCtrlParamData("b22");
          TNumeric sfra11CtrVal = this.getCtrlParamData("sfra11");
          TNumeric sfra12CtrVal = this.getCtrlParamData("sfra12");
          TNumeric sfra21CtrVal = this.getCtrlParamData("sfra21");
          TNumeric sfra22CtrVal = this.getCtrlParamData("sfra22");
          TNumeric sfrb11CtrVal = this.getCtrlParamData("sfrb11");
          TNumeric sfrb12CtrVal = this.getCtrlParamData("sfrb12");
          TNumeric sfrb21CtrVal = this.getCtrlParamData("sfrb21");
          TNumeric sfrb22CtrVal = this.getCtrlParamData("sfrb22");
          TNumeric x1CtrVal = this.getCtrlParamData("x1");
          TNumeric x2CtrVal = this.getCtrlParamData("x2");

// USERCODE-BEGIN:RevFnc                                                                                                
		double a[] = new double[4];
		double b[] = new double[4];

		/* get controller parameter values */
		a[0] = a11CtrVal.getReal(0, 0) / Math.pow(2, sfra11CtrVal.getReal(0, 0));
		a[1] = a12CtrVal.getReal(0, 0) / Math.pow(2, sfra12CtrVal.getReal(0, 0));
		a[2] = a21CtrVal.getReal(0, 0) / Math.pow(2, sfra21CtrVal.getReal(0, 0));
		a[3] = a22CtrVal.getReal(0, 0) / Math.pow(2, sfra22CtrVal.getReal(0, 0));

		b[0] = b11CtrVal.getReal(0, 0) / Math.pow(2, sfrb11CtrVal.getReal(0, 0));
		b[1] = b12CtrVal.getReal(0, 0) / Math.pow(2, sfrb12CtrVal.getReal(0, 0));
		b[2] = b21CtrVal.getReal(0, 0) / Math.pow(2, sfrb21CtrVal.getReal(0, 0));
		b[3] = b22CtrVal.getReal(0, 0) / Math.pow(2, sfrb22CtrVal.getReal(0, 0));

		/* set mask parameter values */
		for (int i = 0; i < 4; i++) {
			AMaskData.setReal(0, i, a[i]);
			BMaskData.setReal(0, i, b[i]);
		}

// USERCODE-END:RevFnc                                                                                                  
          this.getMaskParameter("A").setValue(AMaskData.toFullString());
          this.getMaskParameter("B").setValue(BMaskData.toFullString());
     }
}

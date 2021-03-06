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

package at.lcm.x2c.library.general;

import at.lcm.x2c.core.structure.*;
import at.lcm.bu21.general.dtypes.*;

// USERCODE-BEGIN:Imports                                                                                               
import at.lcm.x2c.utils.QFormat;

// USERCODE-END:Imports                                                                                                 

@SuppressWarnings("unused")
public class ConvFnc_LookupTable_FiP32 extends ConversionFunction {
     private static final long serialVersionUID = 1L;

     public ConvFnc_LookupTable_FiP32() throws Exception {
     }

     public void convert() throws Exception {

          MaskDouble LookupMaskVal = 
               (MaskDouble)this.getMaskParameter("Lookup").getMaskDataType();
          TNumeric LookupMaskData = 
               (TNumeric)LookupMaskVal.getData();

          // Controller Parameter Data                                                                                  
          TNumeric TableCtrVal = this.getCtrlParamData("Table");

// USERCODE-BEGIN:ConvFnc                                                                                               
		final int SIZE = 257;
		final int SIZE_ROW = 1;
		final int BITS = 32;

		if ((LookupMaskData.getNumColumns() != SIZE) || (LookupMaskData.getNumRows() != SIZE_ROW)) {
			throw new Exception("Lookup Table Size mismatch in column: expected=(" + SIZE_ROW + ", " + SIZE + ") "
					+ "got=(" + LookupMaskData.getNumRows() + "," + LookupMaskData.getNumColumns() + ")");
		}

		Double[] tmpData = new Double[SIZE];
		for (int i = 0; i < SIZE; i++) {
			tmpData[i] = Double.valueOf(QFormat.getQValue(LookupMaskData.getReal(0, i), BITS - 1, BITS, true));
		}
		TableCtrVal = new TNumeric(tmpData);
// USERCODE-END:ConvFnc                                                                                                 
          this.setCtrlParamData("Table", TableCtrVal);
     }

     public void revert() throws Exception {

          MaskDouble LookupMaskVal = 
               (MaskDouble)this.getMaskParameter("Lookup").getMaskDataType();
          TNumeric LookupMaskData = 
               (TNumeric)LookupMaskVal.getData();

          // Controller Parameter Data                                                                                  
          TNumeric TableCtrVal = this.getCtrlParamData("Table");

// USERCODE-BEGIN:RevFnc                                                                                                
		/* Insert parameter reversion here... */
// USERCODE-END:RevFnc                                                                                                  
          this.getMaskParameter("Lookup").setValue(LookupMaskData.toFullString());
     }
}

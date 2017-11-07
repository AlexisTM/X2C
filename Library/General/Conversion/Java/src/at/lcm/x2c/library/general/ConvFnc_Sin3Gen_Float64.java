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
 * $LastChangedRevision: 578 $
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
public class ConvFnc_Sin3Gen_Float64 extends ConversionFunction {
	private static final long serialVersionUID = 1L;

	public ConvFnc_Sin3Gen_Float64() throws Exception {
	}

	@Override
	public void convert() throws Exception {

		MaskDouble fmaxMaskVal =
				(MaskDouble)this.getMaskParameter("fmax").getMaskDataType();
		TNumeric fmaxMaskData =
				(TNumeric)fmaxMaskVal.getData();
		MaskDouble OffsetMaskVal =
				(MaskDouble)this.getMaskParameter("Offset").getMaskDataType();
		TNumeric OffsetMaskData =
				(TNumeric)OffsetMaskVal.getData();
		MaskDouble ts_factMaskVal =
				(MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
		TNumeric ts_factMaskData =
				(TNumeric)ts_factMaskVal.getData();

		// Controller Parameter Data
		TNumeric delta_phiCtrVal = this.getCtrlParamData("delta_phi");
		TNumeric offsetCtrVal = this.getCtrlParamData("offset");
		TNumeric phiCtrVal = this.getCtrlParamData("phi");

		// USERCODE-BEGIN:ConvFnc
		double Offset;
		int ts_fact;
		double Ts = 0;

		// get controller parameter values
		ts_fact = Double.valueOf(ts_factMaskVal.getValue()).intValue();
		Offset = Double.valueOf(OffsetMaskVal.getValue());

		// validate controller parameters
		if (ts_fact <= 0) {
			ts_fact = 1;
		}

		// sample time
		Ts = ts_fact * this.getDedicatedBlock().getModel().getSampleTime();

		offsetCtrVal.setReal(0, 0, Offset);
		delta_phiCtrVal.setReal(0, 0, 2 * Math.PI * Ts);

		// USERCODE-END:ConvFnc
		this.setCtrlParamData("delta_phi", delta_phiCtrVal);
		this.setCtrlParamData("offset", offsetCtrVal);
		this.setCtrlParamData("phi", phiCtrVal);
	}

	@Override
	public void revert() throws Exception {

		MaskDouble fmaxMaskVal =
				(MaskDouble)this.getMaskParameter("fmax").getMaskDataType();
		TNumeric fmaxMaskData =
				(TNumeric)fmaxMaskVal.getData();
		MaskDouble OffsetMaskVal =
				(MaskDouble)this.getMaskParameter("Offset").getMaskDataType();
		TNumeric OffsetMaskData =
				(TNumeric)OffsetMaskVal.getData();
		MaskDouble ts_factMaskVal =
				(MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
		TNumeric ts_factMaskData =
				(TNumeric)ts_factMaskVal.getData();

		// Controller Parameter Data
		TNumeric delta_phiCtrVal = this.getCtrlParamData("delta_phi");
		TNumeric offsetCtrVal = this.getCtrlParamData("offset");
		TNumeric phiCtrVal = this.getCtrlParamData("phi");

		// USERCODE-BEGIN:RevFnc
		double Offset;

		// get controller parameter
		Offset = offsetCtrVal.getReal(0, 0);

		// set mask parameter
		OffsetMaskData.setReal(0, 0, Offset);

		// USERCODE-END:RevFnc
		this.getMaskParameter("fmax").setValue(fmaxMaskData.toFullString());
		this.getMaskParameter("Offset").setValue(OffsetMaskData.toFullString());
		this.getMaskParameter("ts_fact").setValue(ts_factMaskData.toFullString());
	}
}

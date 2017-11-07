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
import at.lcm.x2c.utils.QFormat;

// USERCODE-END:Imports

@SuppressWarnings("unused")
public class ConvFnc_uRateLimiter_FiP8 extends ConversionFunction {
	private static final long serialVersionUID = 1L;

	public ConvFnc_uRateLimiter_FiP8() throws Exception {
	}

	@Override
	public void convert() throws Exception {

		MaskDouble TrMaskVal =
				(MaskDouble)this.getMaskParameter("Tr").getMaskDataType();
		TNumeric TrMaskData =
				(TNumeric)TrMaskVal.getData();
		MaskDouble TfMaskVal =
				(MaskDouble)this.getMaskParameter("Tf").getMaskDataType();
		TNumeric TfMaskData =
				(TNumeric)TfMaskVal.getData();
		MaskDouble ts_factMaskVal =
				(MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
		TNumeric ts_factMaskData =
				(TNumeric)ts_factMaskVal.getData();

		// Controller Parameter Data
		TNumeric RateUpCtrVal = this.getCtrlParamData("RateUp");
		TNumeric RateDownCtrVal = this.getCtrlParamData("RateDown");
		TNumeric out_oldCtrVal = this.getCtrlParamData("out_old");
		TNumeric enable_oldCtrVal = this.getCtrlParamData("enable_old");

		// USERCODE-BEGIN:ConvFnc
		double Tr, Tf;
		double Ts = 0;
		int ts_fact;
		final int BITS = 16; // Note: slew rate uses high resolution

		// get parameter values
		Tr = Double.valueOf(TrMaskVal.getValue());
		Tf = Double.valueOf(TfMaskVal.getValue());
		ts_fact = Double.valueOf(ts_factMaskVal.getValue()).intValue();

		// validate controller parameters
		if (ts_fact <= 0) {
			ts_fact = 1;
		}

		// calculate sample time
		Ts = ts_fact * this.getDedicatedBlock().getModel().getSampleTime();

		// check range of rising/falling time
		if (Tr < Ts) {
			Tr = Ts;
		}
		if (Tf < Ts) {
			Tf = Ts;
		}

		// calculate Q-values
		RateUpCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(Ts / Tr, BITS - 1, BITS, true)));
		RateDownCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(Ts / Tf, BITS - 1, BITS, true)));

		// USERCODE-END:ConvFnc
		this.setCtrlParamData("RateUp", RateUpCtrVal);
		this.setCtrlParamData("RateDown", RateDownCtrVal);
		this.setCtrlParamData("out_old", out_oldCtrVal);
		this.setCtrlParamData("enable_old", enable_oldCtrVal);
	}

	@Override
	public void revert() throws Exception {

		MaskDouble TrMaskVal =
				(MaskDouble)this.getMaskParameter("Tr").getMaskDataType();
		TNumeric TrMaskData =
				(TNumeric)TrMaskVal.getData();
		MaskDouble TfMaskVal =
				(MaskDouble)this.getMaskParameter("Tf").getMaskDataType();
		TNumeric TfMaskData =
				(TNumeric)TfMaskVal.getData();
		MaskDouble ts_factMaskVal =
				(MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
		TNumeric ts_factMaskData =
				(TNumeric)ts_factMaskVal.getData();

		// Controller Parameter Data
		TNumeric RateUpCtrVal = this.getCtrlParamData("RateUp");
		TNumeric RateDownCtrVal = this.getCtrlParamData("RateDown");
		TNumeric out_oldCtrVal = this.getCtrlParamData("out_old");
		TNumeric enable_oldCtrVal = this.getCtrlParamData("enable_old");

		// USERCODE-BEGIN:RevFnc
		/* Insert parameter reversion here... */
		// USERCODE-END:RevFnc
		this.getMaskParameter("Tr").setValue(TrMaskData.toFullString());
		this.getMaskParameter("Tf").setValue(TfMaskData.toFullString());
		this.getMaskParameter("ts_fact").setValue(ts_factMaskData.toFullString());
	}
}

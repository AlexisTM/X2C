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
public class ConvFnc_AdaptivePT1_Float32 extends ConversionFunction {
	private static final long serialVersionUID = 1L;

	public ConvFnc_AdaptivePT1_Float32() throws Exception {
	}

	@Override
	public void convert() throws Exception {

		MaskDouble VMaskVal =
				(MaskDouble)this.getMaskParameter("V").getMaskDataType();
		TNumeric VMaskData =
				(TNumeric)VMaskVal.getData();
		MaskDouble fmaxMaskVal =
				(MaskDouble)this.getMaskParameter("fmax").getMaskDataType();
		TNumeric fmaxMaskData =
				(TNumeric)fmaxMaskVal.getData();
		MaskDouble ts_factMaskVal =
				(MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
		TNumeric ts_factMaskData =
				(TNumeric)ts_factMaskVal.getData();
		MaskComboBox methodMaskVal =
				(MaskComboBox)this.getMaskParameter("method").getMaskDataType();
		TString methodMaskData =
				(TString)methodMaskVal.getData();

		// Controller Parameter Data
		TNumeric w_scaleCtrVal = this.getCtrlParamData("w_scale");
		TNumeric gainCtrVal = this.getCtrlParamData("gain");
		TNumeric in_oldCtrVal = this.getCtrlParamData("in_old");

		// USERCODE-BEGIN:ConvFnc
		double w_scale;
		double gain, fmax;
		double Ts = 0;
		int ts_fact;

		/* get parameter */
		gain = Double.valueOf(VMaskVal.getValue());
		fmax = 1; /* input fc is in Hz -> no need for scaling */
		ts_fact = Double.valueOf(ts_factMaskVal.getValue()).intValue();

		/* validate parameter */
		fmax = Math.abs(fmax);
		if (ts_fact <= 0) {
			ts_fact = 1;
		}

		/* calculate sample time */
		Ts = ts_fact * this.getDedicatedBlock().getModel().getSampleTime();

		/*
		 * Zero order hold (zoh): G(s) = V/(s/w + 1) -> G(z) = V*(exp(w*T)-1)/(z*exp(w*T)-1)
		 */
		w_scale = -2 * Math.PI * Ts * fmax;

		/* set controller parameter values */
		gainCtrVal.setReal(0, 0, gain);
		w_scaleCtrVal.setReal(0, 0, w_scale);

		// USERCODE-END:ConvFnc
		this.setCtrlParamData("w_scale", w_scaleCtrVal);
		this.setCtrlParamData("gain", gainCtrVal);
		this.setCtrlParamData("in_old", in_oldCtrVal);
	}

	@Override
	public void revert() throws Exception {

		MaskDouble VMaskVal =
				(MaskDouble)this.getMaskParameter("V").getMaskDataType();
		TNumeric VMaskData =
				(TNumeric)VMaskVal.getData();
		MaskDouble fmaxMaskVal =
				(MaskDouble)this.getMaskParameter("fmax").getMaskDataType();
		TNumeric fmaxMaskData =
				(TNumeric)fmaxMaskVal.getData();
		MaskDouble ts_factMaskVal =
				(MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
		TNumeric ts_factMaskData =
				(TNumeric)ts_factMaskVal.getData();
		MaskComboBox methodMaskVal =
				(MaskComboBox)this.getMaskParameter("method").getMaskDataType();
		TString methodMaskData =
				(TString)methodMaskVal.getData();

		// Controller Parameter Data
		TNumeric w_scaleCtrVal = this.getCtrlParamData("w_scale");
		TNumeric gainCtrVal = this.getCtrlParamData("gain");
		TNumeric in_oldCtrVal = this.getCtrlParamData("in_old");

		// USERCODE-BEGIN:RevFnc
		double Ts = 0;
		int ts_fact;
		double gain, w_scale;

		/* get controller parameter */
		w_scale = w_scaleCtrVal.getReal(0, 0);
		gain = gainCtrVal.getReal(0, 0);

		/* get sample time information from model (sample time information can't be obtained from target) */
		ts_fact = Double.valueOf(ts_factMaskVal.getValue()).intValue();
		Ts = ts_fact * this.getDedicatedBlock().getModel().getSampleTime();

		/* set mask parameter */
		VMaskData.setReal(0, 0, gain);
		fmaxMaskData.setReal(0, 0, 1); /* input fc is in Hz -> no need for scaling */
		ts_factMaskData.setReal(0, 0, ts_fact);

		// USERCODE-END:RevFnc
		this.getMaskParameter("V").setValue(VMaskData.toFullString());
		this.getMaskParameter("fmax").setValue(fmaxMaskData.toFullString());
		this.getMaskParameter("ts_fact").setValue(ts_factMaskData.toFullString());
		this.getMaskParameter("method").setValue(methodMaskData.getString());
	}
}

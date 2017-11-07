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
//*     Description:                                                           *
// USERCODE-END:Description

package at.lcm.x2c.library.control;

import at.lcm.x2c.core.structure.*;
import at.lcm.bu21.general.dtypes.*;

// USERCODE-BEGIN:Imports
import at.lcm.x2c.utils.QFormat;

// USERCODE-END:Imports

@SuppressWarnings("unused")
public class ConvFnc_PIDLimit_FiP16 extends ConversionFunction {
	private static final long serialVersionUID = 1L;

	public ConvFnc_PIDLimit_FiP16() throws Exception {
	}

	@Override
	public void convert() throws Exception {

		MaskDouble KpMaskVal =
				(MaskDouble)this.getMaskParameter("Kp").getMaskDataType();
		TNumeric KpMaskData =
				(TNumeric)KpMaskVal.getData();
		MaskDouble KiMaskVal =
				(MaskDouble)this.getMaskParameter("Ki").getMaskDataType();
		TNumeric KiMaskData =
				(TNumeric)KiMaskVal.getData();
		MaskDouble KdMaskVal =
				(MaskDouble)this.getMaskParameter("Kd").getMaskDataType();
		TNumeric KdMaskData =
				(TNumeric)KdMaskVal.getData();
		MaskDouble fcMaskVal =
				(MaskDouble)this.getMaskParameter("fc").getMaskDataType();
		TNumeric fcMaskData =
				(TNumeric)fcMaskVal.getData();
		MaskDouble ts_factMaskVal =
				(MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
		TNumeric ts_factMaskData =
				(TNumeric)ts_factMaskVal.getData();

		// Controller Parameter Data
		TNumeric b0CtrVal = this.getCtrlParamData("b0");
		TNumeric b1CtrVal = this.getCtrlParamData("b1");
		TNumeric b0dCtrVal = this.getCtrlParamData("b0d");
		TNumeric b1dCtrVal = this.getCtrlParamData("b1d");
		TNumeric a0dCtrVal = this.getCtrlParamData("a0d");
		TNumeric sfrb0CtrVal = this.getCtrlParamData("sfrb0");
		TNumeric sfrb1CtrVal = this.getCtrlParamData("sfrb1");
		TNumeric sfrdCtrVal = this.getCtrlParamData("sfrd");
		TNumeric in_oldCtrVal = this.getCtrlParamData("in_old");
		TNumeric i_oldCtrVal = this.getCtrlParamData("i_old");
		TNumeric d_oldCtrVal = this.getCtrlParamData("d_old");
		TNumeric enable_oldCtrVal = this.getCtrlParamData("enable_old");

		// USERCODE-BEGIN:ConvFnc
		double Kp, Ki, Kd;
		double fc, wc;
		double Ts = 0;
		int ts_fact;
		double b0, b1, b0d, b1d, a0d;
		final int BITS = 16;

		// get controller parameter values
		Kp = Double.valueOf(KpMaskVal.getValue());
		Ki = Double.valueOf(KiMaskVal.getValue());
		Kd = Double.valueOf(KdMaskVal.getValue());
		fc = Double.valueOf(fcMaskVal.getValue());
		ts_fact = Double.valueOf(ts_factMaskVal.getValue()).intValue();

		// validate controller parameters
		fc = Math.abs(fc);
		if (ts_fact <= 0) {
			ts_fact = 1;
		}

		// calculate temporary variables
		wc = 2 * Math.PI * fc;
		Ts = ts_fact * this.getDedicatedBlock().getModel().getSampleTime();

		// Zero order hold (zoh):
		// G(s) = Kp + Ki/s + Kd*s/(s/w+1)-> G(z) = Kp + Ki*Ts*z/(z-1) + Kd*w*(z-1)/(z-exp(-w*T))
		b0 = Ki * Ts;
		b1 = Kp;
		b0d = -Kd * wc;
		b1d = Kd * wc;
		a0d = -Math.exp(-wc * Ts);

		sfrb0CtrVal.setReal(0, 0, Double.valueOf(QFormat.getQFormat(b0, BITS, true)));
		sfrb1CtrVal.setReal(0, 0, Double.valueOf(QFormat.getQFormat(b1, BITS, true)));
		sfrdCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQFormat(b0d, BITS, true)));
		b0CtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(b0, (int) (sfrb0CtrVal.getReal(0, 0)), BITS, true)));
		b1CtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(b1, (int) (sfrb1CtrVal.getReal(0, 0)), BITS, true)));
		b0dCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(b0d, (int) (sfrdCtrVal.getReal(0, 0)), BITS, true)));
		b1dCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(b1d, (int) (sfrdCtrVal.getReal(0, 0)), BITS, true)));
		a0dCtrVal.setReal(0, 0, Double.valueOf(QFormat.getQValue(a0d, BITS - 1, BITS, true)));

		// USERCODE-END:ConvFnc
		this.setCtrlParamData("b0", b0CtrVal);
		this.setCtrlParamData("b1", b1CtrVal);
		this.setCtrlParamData("b0d", b0dCtrVal);
		this.setCtrlParamData("b1d", b1dCtrVal);
		this.setCtrlParamData("a0d", a0dCtrVal);
		this.setCtrlParamData("sfrb0", sfrb0CtrVal);
		this.setCtrlParamData("sfrb1", sfrb1CtrVal);
		this.setCtrlParamData("sfrd", sfrdCtrVal);
		this.setCtrlParamData("in_old", in_oldCtrVal);
		this.setCtrlParamData("i_old", i_oldCtrVal);
		this.setCtrlParamData("d_old", d_oldCtrVal);
		this.setCtrlParamData("enable_old", enable_oldCtrVal);
	}

	@Override
	public void revert() throws Exception {

		MaskDouble KpMaskVal =
				(MaskDouble)this.getMaskParameter("Kp").getMaskDataType();
		TNumeric KpMaskData =
				(TNumeric)KpMaskVal.getData();
		MaskDouble KiMaskVal =
				(MaskDouble)this.getMaskParameter("Ki").getMaskDataType();
		TNumeric KiMaskData =
				(TNumeric)KiMaskVal.getData();
		MaskDouble KdMaskVal =
				(MaskDouble)this.getMaskParameter("Kd").getMaskDataType();
		TNumeric KdMaskData =
				(TNumeric)KdMaskVal.getData();
		MaskDouble fcMaskVal =
				(MaskDouble)this.getMaskParameter("fc").getMaskDataType();
		TNumeric fcMaskData =
				(TNumeric)fcMaskVal.getData();
		MaskDouble ts_factMaskVal =
				(MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
		TNumeric ts_factMaskData =
				(TNumeric)ts_factMaskVal.getData();

		// Controller Parameter Data
		TNumeric b0CtrVal = this.getCtrlParamData("b0");
		TNumeric b1CtrVal = this.getCtrlParamData("b1");
		TNumeric b0dCtrVal = this.getCtrlParamData("b0d");
		TNumeric b1dCtrVal = this.getCtrlParamData("b1d");
		TNumeric a0dCtrVal = this.getCtrlParamData("a0d");
		TNumeric sfrb0CtrVal = this.getCtrlParamData("sfrb0");
		TNumeric sfrb1CtrVal = this.getCtrlParamData("sfrb1");
		TNumeric sfrdCtrVal = this.getCtrlParamData("sfrd");
		TNumeric in_oldCtrVal = this.getCtrlParamData("in_old");
		TNumeric i_oldCtrVal = this.getCtrlParamData("i_old");
		TNumeric d_oldCtrVal = this.getCtrlParamData("d_old");
		TNumeric enable_oldCtrVal = this.getCtrlParamData("enable_old");

		// USERCODE-BEGIN:RevFnc
		double Ts = 0;
		int ts_fact;
		double Ki, Kp, Kd, wc, b0, b1, b0d, a0d, sfr0, sfr1, sfrd;
		final int BITS = 16;

		// get controller parameter
		b0 = b0CtrVal.getReal(0, 0);
		b1 = b1CtrVal.getReal(0, 0);
		b0d = b0dCtrVal.getReal(0, 0);
		a0d = a0dCtrVal.getReal(0, 0);
		sfr0 = sfrb0CtrVal.getReal(0, 0);
		sfr1 = sfrb1CtrVal.getReal(0, 0);
		sfrd = sfrdCtrVal.getReal(0, 0);

		// calculate controller coefficients
		b0 = QFormat.getDecValue((long) b0, (int) sfr0, BITS, true);
		b1 = QFormat.getDecValue((long) b1, (int) sfr1, BITS, true);
		b0d = QFormat.getDecValue((long) b0d, (int) sfrd, BITS, true);
		a0d = QFormat.getDecValue((long) a0d, BITS - 1, BITS, true);

		// get sample time information from model (sample time information can't be obtained from target)
		ts_fact = Double.valueOf(ts_factMaskVal.getValue()).intValue();
		Ts = ts_fact * this.getDedicatedBlock().getModel().getSampleTime();

		// Zero order hold (zoh):
		Ki = b0 / Ts;
		Kp = b1;
		wc = -Math.log(-a0d) / Ts;
		Kd = -b0d / wc;

		// set mask parameter
		KpMaskData.setReal(0, 0, Kp);
		KiMaskData.setReal(0, 0, Ki);
		KdMaskData.setReal(0, 0, Kd);
		fcMaskData.setReal(0, 0, wc / (2 * Math.PI));

		// USERCODE-END:RevFnc
		this.getMaskParameter("Kp").setValue(KpMaskData.toFullString());
		this.getMaskParameter("Ki").setValue(KiMaskData.toFullString());
		this.getMaskParameter("Kd").setValue(KdMaskData.toFullString());
		this.getMaskParameter("fc").setValue(fcMaskData.toFullString());
		this.getMaskParameter("ts_fact").setValue(ts_factMaskData.toFullString());
	}
}

/*
 * Copyright (c) 2014, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
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
public class ConvFnc_Sequencer_FiP32 extends ConversionFunction {
	private static final long serialVersionUID = 1L;

	public ConvFnc_Sequencer_FiP32() throws Exception {
	}

	@Override
	public void convert() throws Exception {

		MaskDouble Delay1MaskVal =
				(MaskDouble)this.getMaskParameter("Delay1").getMaskDataType();
		TNumeric Delay1MaskData =
				(TNumeric)Delay1MaskVal.getData();
		MaskDouble Delay2MaskVal =
				(MaskDouble)this.getMaskParameter("Delay2").getMaskDataType();
		TNumeric Delay2MaskData =
				(TNumeric)Delay2MaskVal.getData();
		MaskDouble Delay3MaskVal =
				(MaskDouble)this.getMaskParameter("Delay3").getMaskDataType();
		TNumeric Delay3MaskData =
				(TNumeric)Delay3MaskVal.getData();
		MaskDouble Delay4MaskVal =
				(MaskDouble)this.getMaskParameter("Delay4").getMaskDataType();
		TNumeric Delay4MaskData =
				(TNumeric)Delay4MaskVal.getData();
		MaskDouble ts_factMaskVal =
				(MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
		TNumeric ts_factMaskData =
				(TNumeric)ts_factMaskVal.getData();

		// Controller Parameter Data
		TNumeric delay1CtrVal = this.getCtrlParamData("delay1");
		TNumeric delay2CtrVal = this.getCtrlParamData("delay2");
		TNumeric delay3CtrVal = this.getCtrlParamData("delay3");
		TNumeric delay4CtrVal = this.getCtrlParamData("delay4");
		TNumeric cntCtrVal = this.getCtrlParamData("cnt");
		TNumeric start_oldCtrVal = this.getCtrlParamData("start_old");

		// USERCODE-BEGIN:ConvFnc
		double delay1, delay2, delay3, delay4;
		double Ts = 0;
		int ts_fact;
		final int UINT16_MAX = 65535;

		// get parameter values
		delay1 = Double.valueOf(Delay1MaskVal.getValue());
		delay2 = Double.valueOf(Delay2MaskVal.getValue());
		delay3 = Double.valueOf(Delay3MaskVal.getValue());
		delay4 = Double.valueOf(Delay4MaskVal.getValue());

		// calculate sample time
		ts_fact = Double.valueOf(ts_factMaskVal.getValue()).intValue();
		Ts = ts_fact * this.getDedicatedBlock().getModel().getSampleTime();

		// validate controller parameters
		if (delay1 < 0) {
			delay1 = 0;
		}
		if (delay2 < 0) {
			delay2 = 0;
		}
		if (delay3 < 0) {
			delay3 = 0;
		}
		if (delay4 < 0) {
			delay4 = 0;
		}
		if (ts_fact <= 0) {
			ts_fact = 1;
		}

		// calculate delay values
		delay1 = delay1 / Ts;
		delay2 = delay2 / Ts;
		delay3 = delay3 / Ts;
		delay4 = delay4 / Ts;

		// check delay values
		if (delay1 > UINT16_MAX) {
			throw new Exception("Sequencer-Block: Delay 1 is too high!");
		}
		if (delay2 > UINT16_MAX) {
			throw new Exception("Sequencer-Block: Delay 2 is too high!");
		}
		if (delay3 > UINT16_MAX) {
			throw new Exception("Sequencer-Block: Delay 3 is too high!");
		}
		if (delay4 > UINT16_MAX) {
			throw new Exception("Sequencer-Block: Delay 4 is too high!");
		}

		// set delay values
		delay1CtrVal.setReal(0, 0, delay1);
		delay2CtrVal.setReal(0, 0, delay2);
		delay3CtrVal.setReal(0, 0, delay3);
		delay4CtrVal.setReal(0, 0, delay4);

		// USERCODE-END:ConvFnc
		this.setCtrlParamData("delay1", delay1CtrVal);
		this.setCtrlParamData("delay2", delay2CtrVal);
		this.setCtrlParamData("delay3", delay3CtrVal);
		this.setCtrlParamData("delay4", delay4CtrVal);
		this.setCtrlParamData("cnt", cntCtrVal);
		this.setCtrlParamData("start_old", start_oldCtrVal);
	}

	@Override
	public void revert() throws Exception {

		MaskDouble Delay1MaskVal =
				(MaskDouble)this.getMaskParameter("Delay1").getMaskDataType();
		TNumeric Delay1MaskData =
				(TNumeric)Delay1MaskVal.getData();
		MaskDouble Delay2MaskVal =
				(MaskDouble)this.getMaskParameter("Delay2").getMaskDataType();
		TNumeric Delay2MaskData =
				(TNumeric)Delay2MaskVal.getData();
		MaskDouble Delay3MaskVal =
				(MaskDouble)this.getMaskParameter("Delay3").getMaskDataType();
		TNumeric Delay3MaskData =
				(TNumeric)Delay3MaskVal.getData();
		MaskDouble Delay4MaskVal =
				(MaskDouble)this.getMaskParameter("Delay4").getMaskDataType();
		TNumeric Delay4MaskData =
				(TNumeric)Delay4MaskVal.getData();
		MaskDouble ts_factMaskVal =
				(MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
		TNumeric ts_factMaskData =
				(TNumeric)ts_factMaskVal.getData();

		// Controller Parameter Data
		TNumeric delay1CtrVal = this.getCtrlParamData("delay1");
		TNumeric delay2CtrVal = this.getCtrlParamData("delay2");
		TNumeric delay3CtrVal = this.getCtrlParamData("delay3");
		TNumeric delay4CtrVal = this.getCtrlParamData("delay4");
		TNumeric cntCtrVal = this.getCtrlParamData("cnt");
		TNumeric start_oldCtrVal = this.getCtrlParamData("start_old");

		// USERCODE-BEGIN:RevFnc
		double Ts = 0;
		int ts_fact;
		double delay1, delay2, delay3, delay4;

		// get controller parameter
		delay1 = delay1CtrVal.getReal(0, 0);
		delay2 = delay2CtrVal.getReal(0, 0);
		delay3 = delay3CtrVal.getReal(0, 0);
		delay4 = delay4CtrVal.getReal(0, 0);

		// get sample time information from Simulink block/model (sample time information can't be obtained from target)
		ts_fact = Double.valueOf(ts_factMaskVal.getValue()).intValue();
		Ts = ts_fact * this.getDedicatedBlock().getModel().getSampleTime();

		// set mask parameter
		Delay1MaskData.setReal(0, 0, delay1 * Ts);
		Delay2MaskData.setReal(0, 0, delay2 * Ts);
		Delay3MaskData.setReal(0, 0, delay3 * Ts);
		Delay4MaskData.setReal(0, 0, delay4 * Ts);

		// USERCODE-END:RevFnc
		this.getMaskParameter("Delay1").setValue(Delay1MaskData.toFullString());
		this.getMaskParameter("Delay2").setValue(Delay2MaskData.toFullString());
		this.getMaskParameter("Delay3").setValue(Delay3MaskData.toFullString());
		this.getMaskParameter("Delay4").setValue(Delay4MaskData.toFullString());
		this.getMaskParameter("ts_fact").setValue(ts_factMaskData.toFullString());
	}
}

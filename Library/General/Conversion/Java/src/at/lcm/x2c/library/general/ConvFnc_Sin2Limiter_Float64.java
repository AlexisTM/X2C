/*
 * This file is part of X2C. http://www.mechatronic-simulation.org/
 * $LastChangedRevision: 828 $
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
public class ConvFnc_Sin2Limiter_Float64 extends ConversionFunction {
	private static final long serialVersionUID = 1L;

	public ConvFnc_Sin2Limiter_Float64() throws Exception {
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
		TNumeric Scaled_RateUpCtrVal = this.getCtrlParamData("Scaled_RateUp");
		TNumeric Scaled_RateDownCtrVal = this.getCtrlParamData("Scaled_RateDown");
		TNumeric Out_endCtrVal = this.getCtrlParamData("Out_end");
		TNumeric LevelCtrVal = this.getCtrlParamData("Level");
		TNumeric Step_HeightCtrVal = this.getCtrlParamData("Step_Height");
		TNumeric StateCtrVal = this.getCtrlParamData("State");

		// USERCODE-BEGIN:ConvFnc
		double Tr, Tf;
		double Ts = 0;
		int ts_fact;

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
		RateUpCtrVal.setReal(0, 0, ((Ts / Tr) * Math.PI) / 2); // pi/2 due to sin^2(0) ... sin^2(pi/2)
		RateDownCtrVal.setReal(0, 0, ((Ts / Tf) * Math.PI) / 2); // pi/2 due to sin^2(0) ... sin^2(pi/2)

		// USERCODE-END:ConvFnc
		this.setCtrlParamData("RateUp", RateUpCtrVal);
		this.setCtrlParamData("RateDown", RateDownCtrVal);
		this.setCtrlParamData("Scaled_RateUp", Scaled_RateUpCtrVal);
		this.setCtrlParamData("Scaled_RateDown", Scaled_RateDownCtrVal);
		this.setCtrlParamData("Out_end", Out_endCtrVal);
		this.setCtrlParamData("Level", LevelCtrVal);
		this.setCtrlParamData("Step_Height", Step_HeightCtrVal);
		this.setCtrlParamData("State", StateCtrVal);
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
		TNumeric Scaled_RateUpCtrVal = this.getCtrlParamData("Scaled_RateUp");
		TNumeric Scaled_RateDownCtrVal = this.getCtrlParamData("Scaled_RateDown");
		TNumeric Out_endCtrVal = this.getCtrlParamData("Out_end");
		TNumeric LevelCtrVal = this.getCtrlParamData("Level");
		TNumeric Step_HeightCtrVal = this.getCtrlParamData("Step_Height");
		TNumeric StateCtrVal = this.getCtrlParamData("State");

		// USERCODE-BEGIN:RevFnc
		double Ts = 0;
		int ts_fact;
		double RateUp, RateDown;

		// get controller parameter
		RateUp = RateUpCtrVal.getReal(0, 0);
		RateDown = RateDownCtrVal.getReal(0, 0);

		// get sample time information from model (sample time information can't be obtained from target)
		ts_fact = Double.valueOf(ts_factMaskVal.getValue()).intValue();
		Ts = ts_fact * this.getDedicatedBlock().getModel().getSampleTime();

		// set mask parameter
		TrMaskData.setReal(0, 0, (Ts / RateUp / Math.PI) * 2);
		TfMaskData.setReal(0, 0, (Ts / RateDown / Math.PI) * 2);

		// USERCODE-END:RevFnc
		this.getMaskParameter("Tr").setValue(TrMaskData.toFullString());
		this.getMaskParameter("Tf").setValue(TfMaskData.toFullString());
		this.getMaskParameter("ts_fact").setValue(ts_factMaskData.toFullString());
	}
}

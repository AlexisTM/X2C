/*
 * This file is part of X2C. http://www.mechatronic-simulation.org/
 * $LastChangedRevision: 765 $
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
public class ConvFnc_Sin2Limiter_FiP16 extends ConversionFunction {
     private static final long serialVersionUID = 1L;

     public ConvFnc_Sin2Limiter_FiP16() throws Exception {
     }

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
		final int BITS = 32; /* internal usage of 32 bit variables for higher resolution */

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
          this.setCtrlParamData("Scaled_RateUp", Scaled_RateUpCtrVal);
          this.setCtrlParamData("Scaled_RateDown", Scaled_RateDownCtrVal);
          this.setCtrlParamData("Out_end", Out_endCtrVal);
          this.setCtrlParamData("Level", LevelCtrVal);
          this.setCtrlParamData("Step_Height", Step_HeightCtrVal);
          this.setCtrlParamData("State", StateCtrVal);
     }

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
		final int BITS = 32; /* internal usage of 32 bit variables for higher resolution */

		// get controller parameter
		RateUp = RateUpCtrVal.getReal(0, 0);
		RateDown = RateDownCtrVal.getReal(0, 0);

		// get sample time information from model (sample time information can't be obtained from target)
		ts_fact = Double.valueOf(ts_factMaskVal.getValue()).intValue();
		Ts = ts_fact * this.getDedicatedBlock().getModel().getSampleTime();

		// set mask parameter
		TrMaskData.setReal(0, 0, QFormat.getDecValue((long) (Ts / RateUp), BITS - 1, BITS, true));
		TfMaskData.setReal(0, 0, QFormat.getDecValue((long) (Ts / RateDown), BITS - 1, BITS, true));

// USERCODE-END:RevFnc                                                                                                  
          this.getMaskParameter("Tr").setValue(TrMaskData.toFullString());
          this.getMaskParameter("Tf").setValue(TfMaskData.toFullString());
          this.getMaskParameter("ts_fact").setValue(ts_factMaskData.toFullString());
     }
}

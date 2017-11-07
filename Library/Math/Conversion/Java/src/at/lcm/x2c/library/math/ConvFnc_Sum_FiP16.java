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
/* Description: */
// USERCODE-END:Description                                                                                             

package at.lcm.x2c.library.math;

import at.lcm.x2c.core.structure.*;
import at.lcm.bu21.general.dtypes.*;

// USERCODE-BEGIN:Imports                                                                                               
// USERCODE-END:Imports                                                                                                 

@SuppressWarnings("unused")
public class ConvFnc_Sum_FiP16 extends ConversionFunction {
     private static final long serialVersionUID = 1L;

     public ConvFnc_Sum_FiP16() throws Exception {
     }

     public void convert() throws Exception {

          MaskComboBox In1MaskVal = 
               (MaskComboBox)this.getMaskParameter("In1").getMaskDataType();
          TString In1MaskData = 
               (TString)In1MaskVal.getData();
          MaskComboBox In2MaskVal = 
               (MaskComboBox)this.getMaskParameter("In2").getMaskDataType();
          TString In2MaskData = 
               (TString)In2MaskVal.getData();
          MaskComboBox In3MaskVal = 
               (MaskComboBox)this.getMaskParameter("In3").getMaskDataType();
          TString In3MaskData = 
               (TString)In3MaskVal.getData();
          MaskComboBox In4MaskVal = 
               (MaskComboBox)this.getMaskParameter("In4").getMaskDataType();
          TString In4MaskData = 
               (TString)In4MaskVal.getData();
          MaskComboBox In5MaskVal = 
               (MaskComboBox)this.getMaskParameter("In5").getMaskDataType();
          TString In5MaskData = 
               (TString)In5MaskVal.getData();
          MaskComboBox In6MaskVal = 
               (MaskComboBox)this.getMaskParameter("In6").getMaskDataType();
          TString In6MaskData = 
               (TString)In6MaskVal.getData();
          MaskComboBox In7MaskVal = 
               (MaskComboBox)this.getMaskParameter("In7").getMaskDataType();
          TString In7MaskData = 
               (TString)In7MaskVal.getData();
          MaskComboBox In8MaskVal = 
               (MaskComboBox)this.getMaskParameter("In8").getMaskDataType();
          TString In8MaskData = 
               (TString)In8MaskVal.getData();

          // Controller Parameter Data                                                                                  
          TNumeric signCtrVal = this.getCtrlParamData("sign");

// USERCODE-BEGIN:ConvFnc                                                                                               
          int mask = 0;
          
          if (In1MaskVal.getValue().equals("+")){
        	  mask = 1;
          }else if(In1MaskVal.getValue().equals("-")){
        	  mask = 2;	
          }
          if (In2MaskVal.getValue().equals("+")){
        	  mask += (1<<2);
          }else if(In2MaskVal.getValue().equals("-")){
        	  mask += (2<<2);	
          }  	  
          if (In3MaskVal.getValue().equals("+")){
        	  mask += (1<<4);
          }else if(In3MaskVal.getValue().equals("-")){
        	  mask += (2<<4);	
          }
          if (In4MaskVal.getValue().equals("+")){
        	  mask += (1<<6);
          }else if(In4MaskVal.getValue().equals("-")){
        	  mask += (2<<6);	
          }
          if (In5MaskVal.getValue().equals("+")){
        	  mask += (1<<8);
          }else if(In5MaskVal.getValue().equals("-")){
        	  mask += (2<<8);	
          }
          if (In6MaskVal.getValue().equals("+")){
        	  mask += (1<<10);
          }else if(In6MaskVal.getValue().equals("-")){
        	  mask += (2<<10);	
          }
          if (In7MaskVal.getValue().equals("+")){
        	  mask += (1<<12);
          }else if(In7MaskVal.getValue().equals("-")){
        	  mask += (2<<12);	
          }
          if (In8MaskVal.getValue().equals("+")){
        	  mask += (1<<14);
          }else if(In8MaskVal.getValue().equals("-")){
        	  mask += (2<<14);	
          }       
          
          signCtrVal.setReal(0, 0, mask);
          
// USERCODE-END:ConvFnc                                                                                                 
          this.setCtrlParamData("sign", signCtrVal);
     }

     public void revert() throws Exception {

          MaskComboBox In1MaskVal = 
               (MaskComboBox)this.getMaskParameter("In1").getMaskDataType();
          TString In1MaskData = 
               (TString)In1MaskVal.getData();
          MaskComboBox In2MaskVal = 
               (MaskComboBox)this.getMaskParameter("In2").getMaskDataType();
          TString In2MaskData = 
               (TString)In2MaskVal.getData();
          MaskComboBox In3MaskVal = 
               (MaskComboBox)this.getMaskParameter("In3").getMaskDataType();
          TString In3MaskData = 
               (TString)In3MaskVal.getData();
          MaskComboBox In4MaskVal = 
               (MaskComboBox)this.getMaskParameter("In4").getMaskDataType();
          TString In4MaskData = 
               (TString)In4MaskVal.getData();
          MaskComboBox In5MaskVal = 
               (MaskComboBox)this.getMaskParameter("In5").getMaskDataType();
          TString In5MaskData = 
               (TString)In5MaskVal.getData();
          MaskComboBox In6MaskVal = 
               (MaskComboBox)this.getMaskParameter("In6").getMaskDataType();
          TString In6MaskData = 
               (TString)In6MaskVal.getData();
          MaskComboBox In7MaskVal = 
               (MaskComboBox)this.getMaskParameter("In7").getMaskDataType();
          TString In7MaskData = 
               (TString)In7MaskVal.getData();
          MaskComboBox In8MaskVal = 
               (MaskComboBox)this.getMaskParameter("In8").getMaskDataType();
          TString In8MaskData = 
               (TString)In8MaskVal.getData();

          // Controller Parameter Data                                                                                  
          TNumeric signCtrVal = this.getCtrlParamData("sign");

// USERCODE-BEGIN:RevFnc                                                                                                
          int sign;
          int mask = 0;
          
          /* get controller parameter */
          mask = (int)signCtrVal.getReal(0, 0);
          
          /* calculate mask parameters */
          sign = mask & 0x0003;
          if (sign==1){
        	  In1MaskData = new TString("+");
          }else if (sign == 2){
        	  In1MaskData = new TString("-");
          }else{
        	  In1MaskData = new TString("0");
          }
          
          sign = (mask>>2) & 0x0003;
          if (sign == 1){
        	  In2MaskData = new TString("+");
          }else if (sign == 2){
        	  In2MaskData = new TString("-");
          }else{
        	  In2MaskData = new TString("0");
          } 

          sign = (mask>>4) & 0x0003;
          if (sign == 1){
        	  In3MaskData = new TString("+");
          }else if (sign == 2){
        	  In3MaskData = new TString("-");
          }else{
        	  In3MaskData = new TString("0");
          } 
          
          sign = (mask>>6) & 0x0003;
          if (sign == 1){
        	  In4MaskData = new TString("+");
          }else if (sign == 2){
        	  In4MaskData = new TString("-");
          }else{
        	  In4MaskData = new TString("0");
          }
          
          sign = (mask>>8) & 0x0003;
          if (sign == 1){
        	  In5MaskData = new TString("+");
          }else if (sign == 2){
        	  In5MaskData = new TString("-");
          }else{
        	  In5MaskData = new TString("0");
          } 
          
          sign = (mask>>10) & 0x0003;
          if (sign == 1){
        	  In6MaskData = new TString("+");
          }else if (sign == 2){
        	  In6MaskData = new TString("-");
          }else{
        	  In6MaskData = new TString("0");
          }
          
          sign = (mask>>12) & 0x0003;
          if (sign == 1){
        	  In7MaskData = new TString("+");
          }else if (sign == 2){
        	  In7MaskData = new TString("-");
          }else{
        	  In7MaskData = new TString("0");
          } 
          
          sign = (mask>>14) & 0x0003;
          if (sign == 1){
        	  In8MaskData = new TString("+");
          }else if (sign == 2){
        	  In8MaskData = new TString("-");
          }else{
        	  In8MaskData = new TString("0");
          }
          
// USERCODE-END:RevFnc                                                                                                  
          this.getMaskParameter("In1").setValue(In1MaskData.getString());
          this.getMaskParameter("In2").setValue(In2MaskData.getString());
          this.getMaskParameter("In3").setValue(In3MaskData.getString());
          this.getMaskParameter("In4").setValue(In4MaskData.getString());
          this.getMaskParameter("In5").setValue(In5MaskData.getString());
          this.getMaskParameter("In6").setValue(In6MaskData.getString());
          this.getMaskParameter("In7").setValue(In7MaskData.getString());
          this.getMaskParameter("In8").setValue(In8MaskData.getString());
     }
}

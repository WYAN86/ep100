#ifndef __PID_H
#define __PID_H

#include "stm32f10x.h"
#include "IQmathLib.h"

typedef struct
{
     
     _iq  Ref;   			 
     _iq  Fdb;   			 
     _iq  Err;				
     _iq  Kp;				
     _iq  Up;				
     _iq  Ki;			    
     _iq  Ui;				 
     //u8   Ui_flag;
     _iq  Ud;				 	
     _iq  OutPreSat; 		
     _iq  OutMax;		      
     _iq  OutMin;	    	     
     _iq  Out;   			
     u8   Saturation_flag;
     _iq  SatErr;			
     _iq  Kc;		     	
     _iq  Kd; 		         
     _iq  Up1;		   	      
} pid;

typedef struct 
{         
     _iq  Err;				   // Variable: Error
     _iq  DeltaRef;
     _iq  Kp;				// Parameter: Proportional gain
     _iq  Kaf;				// Variable: Proportional output 
     _iq  OutMax;		    // Parameter: Maximum output 
     _iq  OutMin;	    	// Parameter: Minimum output
     _iq  OutPreSat;
     _iq  Out;   			// Output: PID output
     _iq  Up;
     _iq  Uf;
     _iq  Up1;
     _iq  Ui;
     _iq  Ud;
     _iq  Ki;
     _iq  Kd;
} feed_forward;


// pid
extern pid pid_id;
extern pid pid_iq;
extern pid pid_id_encoder_offset;
extern pid pid_iq_encoder_offset;
extern pid pid_speed;
extern pid pid_pos;
extern feed_forward feed_forward_pos;

void pid_calc(pid *v);
void pi_caculation(pid *v);

#endif
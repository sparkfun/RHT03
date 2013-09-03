//****************************************************************//
//	              Program for AM230x series 
//MCU：  AT89S52 ,   Frequency of crystal oscillator: 11.0592MHz
//Function： Transmit RH & Temp. Data via PC interface ,  Baud rate 9600 
//Connection： P2.0 connected with DHT sensor   
// Company  ： Aosong Electronics   
//****************************************************************//

#include <reg51.h>
#include <intrins.h> 
//
typedef unsigned char  U8;       /* defined for unsigned 8-bits integer variable 	     */
typedef signed   char  S8;       /* defined for signed 8-bits integer variable		   */
typedef unsigned int   U16;      /* defined for unsigned 16-bits integer variable 	     */
typedef signed   int   S16;      /* defined for signed 16-bits integer variable 	     */
typedef unsigned long  U32;      /* defined for unsigned 32-bits integer variable 	  */
typedef signed   long  S32;      /* defined for signed 32-bits integer variable 	      */
typedef float          F32;      /* single precision floating point variable (32bits)    */
typedef double         F64;      /* double precision floating point variable (64bits)    */
//
#define uchar unsigned char
#define uint unsigned int
#define   Data_0_time    4

//----------------------------------------------//
//----------------Definition for IO interface--------------------//
//----------------------------------------------//
sbit  P2_0  = P2^0 ;
sbit  P2_1  = P2^1 ;
sbit  P2_2  = P2^2 ;
sbit  P2_3  = P2^3 ;
//----------------------------------------------//
//----------------Definition zone--------------------//
//----------------------------------------------//
U8  U8FLAG,k;
U8  U8count,U8temp;
U8  U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;
U8  U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;
U8  U8comdata;
U8  outdata[5];  
U8  indata[5];
U8  count, count_r=0;
U8  str[5]={"RS232"};
U16 U16temp1,U16temp2;
SendData(U8 *a)
{
	outdata[0] = a[0]; 
	outdata[1] = a[1];
	outdata[2] = a[2];
	outdata[3] = a[3];
	outdata[4] = a[4];
	count = 1;
	SBUF=outdata[0];
}

       void Delay(U16 j)
    {      U8 i;
	    for(;j>0;j--)
	  { 	
		for(i=0;i<27;i++);

	  }
    }
       void  Delay_10us(void)
      {
        U8 i;
        i--;
        i--;
        i--;
        i--;
        i--;
        i--;
       }
	
        void  COM(void)
      {
     
	        U8 i;
       for(i=0;i<8;i++)	   
	    {
		
	   	    U8FLAG=2;
	
	   	while((!P2_0)&&U8FLAG++);
			Delay_10us();
			Delay_10us();
			Delay_10us();
	  		U8temp=0;
	     if(P2_0)U8temp=1;
		    U8FLAG=2;
		 while((P2_0)&&U8FLAG++);
		 	

	   	 if(U8FLAG==1)break;

	   	 
		   U8comdata<<=1;
	   	   U8comdata|=U8temp;        //0
	     }//rof
	   
	}

    //--------------------------------
	//-----Sub-program for reading %RH ------------
	//--------------------------------
	//----All the variable bellow is global variable--------
	//----Temperature's high 8bit== U8T_data_H------
	//----Temperature's low 8bit== U8T_data_L------
	//----Humidity's high 8bit== U8RH_data_H-----
	//----Humidity's low 8bit== U8RH_data_L-----
	//----Check-sum 8bit == U8checkdata-----
	//--------------------------------

	void RH(void)
	{

     P2_0=0;
	   Delay(5);
	   P2_0=1;
	   Delay_10us();
	   Delay_10us();
	   Delay_10us();
	   Delay_10us();
	   P2_0=1;	  
	   if(!P2_0)		  
	   {
	   U8FLAG=2;
	   while((!P2_0)&&U8FLAG++);
	   U8FLAG=2;
	   while((P2_0)&&U8FLAG++);
	   COM();
	   U8RH_data_H_temp=U8comdata;
	   COM();
	   U8RH_data_L_temp=U8comdata;
	   COM();
	   U8T_data_H_temp=U8comdata;
	   COM();
	   U8T_data_L_temp=U8comdata;
	   COM();
	   U8checkdata_temp=U8comdata;
	   P2_0=1;
	 
	   U8temp=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);
	   if(U8temp==U8checkdata_temp)
	   {
	   	  U8RH_data_H=U8RH_data_H_temp;
	   	  U8RH_data_L=U8RH_data_L_temp;
		  U8T_data_H=U8T_data_H_temp;
	   	  U8T_data_L=U8T_data_L_temp;
	   	  U8checkdata=U8checkdata_temp;
	   }//fi
	   }//fi

	}
	
//----------------------------------------------
//               main()
//----------------------------------------------
void main()
{
	U8  i,j;
	

	TMOD = 0x20;	  
	TH1 = 253;        
	TL1 = 253;
	TR1 = 1;          
	SCON = 0x50;	  
	ES = 1;
	EA = 1;           
	TI = 0;
	RI = 0;
	SendData(str) ;   
	Delay(1);         
	while(1)
	{  

	   //------------------------
	   //调用温湿度读取子程序 
	   RH();
	   //--------------------------

	   str[0]=U8RH_data_H;
	   str[1]=U8RH_data_L;
	   str[2]=U8T_data_H;
	   str[3]=U8T_data_L;
	   str[4]=U8checkdata;
	   SendData(str) ;  
	
	   Delay(20000);
	}//elihw
	
}// main

void RSINTR() interrupt 4 using 2
{
	U8 InPut3;
	if(TI==1) 
	{
		TI=0;
		if(count!=5) 
		{
			SBUF= outdata[count];
			count++;
		}
	}
	
	if(RI==1)	 
	{	
		InPut3=SBUF;
		indata[count_r]=InPut3;
		count_r++;
		RI=0;								 
		if (count_r==5)
		{
			
			count_r=0;
		str[0]=indata[0];
		 str[1]=indata[1];
		   str[2]=indata[2];
			 str[3]=indata[3];
				 str[4]=indata[4];
				 P0=0;
		}
	}
}

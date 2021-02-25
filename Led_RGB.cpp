#include "Led_RGB.h"

//--------------------------------------------------------------------------------------------------------------------------------------
led_RGB::led_RGB(){}

//-------------BEGIN SETUP--------------------------------------------------------------------------------------------------------------
void led_RGB::begin(uint8_t RED_PIN,uint8_t GREEN_PIN,uint8_t BLUE_PIN,bool type)
{
	_bright=100;
	begin(RED_PIN,GREEN_PIN,BLUE_PIN,type,_bright);
}
//--------------------------------------------------------------------------------------------------------------------------------------
void led_RGB::begin(uint8_t RED_PIN,uint8_t GREEN_PIN,uint8_t BLUE_PIN,bool type,uint8_t bright)
{
	_redPin=RED_PIN;
	_greenPin=GREEN_PIN;
	_bluePin=BLUE_PIN;
	_bright=bright;
	pinMode(_redPin,OUTPUT);
	pinMode(_greenPin,OUTPUT);
	pinMode(_bluePin,OUTPUT);
}
//-------------EFFECT------------------------------------------------------------------------------------------------------------------
void led_RGB::turnoff()
{
	digitalWrite(_redPin,LOW);
	digitalWrite(_greenPin,LOW);
	digitalWrite(_bluePin,LOW);
}

//-------------DISPLAY-----------------------------------------------------------------------------------------------------------------
void led_RGB::display(uint8_t color[3])
{
	display(color,_bright);
}
//--------------------------------------------------------------------------------------------------------------------------------------
void led_RGB::display(uint8_t color[3],uint8_t bright)
{ 
	if (type) for (byte i=0;i<=2;i++) color[i]=~(color[i]*bright/100);
		else for(byte i=0;i<=2;i++) color[i]=color[i]*bright/100;
  Serial.print("   Xuat ra : ");
  batbo(color);
  dem++;
	analogWrite(_redPin,color[0]);
	analogWrite(_greenPin,color[1]);
	analogWrite(_bluePin,color[2]);
}
//--------------------------------------------------------------------------------------------------------------------------------------
void led_RGB::display(uint8_t color[3],uint8_t bright,int time)
{
	display(color,bright);
	delay(time);
}
//--------------------------------------------------------------------------------------------------------------------------------------
void led_RGB::display(uint8_t _RED,uint8_t _GREEN,uint8_t _BLUE)
{
  uint8_t color[3];
	color[0]=_RED;
	color[1]=_GREEN;
	color[2]=_BLUE;
	display(color,_bright);
}
//--------------------------------------------------------------------------------------------------------------------------------------
void led_RGB::display(uint8_t _RED,uint8_t _GREEN,uint8_t _BLUE,uint8_t bright)
{
  uint8_t color[3];
	color[0]=_RED;
	color[1]=_GREEN;
	color[2]=_BLUE;
	display(color,bright);
}
//--------------------------------------------------------------------------------------------------------------------------------------
void led_RGB::display(uint8_t _RED,uint8_t _GREEN,uint8_t _BLUE,uint8_t bright,int time)
{
  uint8_t color[3];
	color[0]=_RED;
	color[1]=_GREEN;
	color[2]=_BLUE;
	display(color,bright);
	delay(time);
}


//--------------CHANGE COLOR-----------------------------------------------------------------------------------------------------------
void led_RGB::changeColor(uint8_t _from_color[3], uint8_t _to_color[3],uint8_t level,uint8_t bright,int time)
{	  
	dem=0;  
	byte i;
	for (i=0;i<=2;i++)
	{
    	from_color[i]=_from_color[i];
    	to_color[i]=_to_color[i];
	}
	step=level_exact[level];
	group_start=classify_group(from_color);
	max1_start=max1;
	max2_start=max2;
	min_start=max3;
	group_stop=classify_group(to_color);
	max1_stop=max1;
	max2_stop=max2;
	min_stop=max3;  

	//Chuyen gia tri ve gan step nhat
	for (i=0;i<=2;i++) 
	{
    	from_color[i]=round(float(from_color[i])/float(step))*step;
    	to_color[i]=round(float(to_color[i])/float(step))*step;
	}  
	Serial.println("Lam tron");
	batbo(from_color);
	batbo(to_color);
	Serial.print("group_start=");
	Serial.println(group_start);
	Serial.print("group_stop=");
	Serial.println(group_stop);
//-----------------------------------------------------------------------------------------------------------------------------

	delay_step=calc_time(time);
	// chuyen ve cac gia tri chia het cho step de code-----------------------------------------------------------------------------	
	Serial.println("Giai doan chuyen thanh format");
	//chuyen RGB Start thanh gia tri theo format (1 gia tri =225 va mot gia tri la 0)		  
	while ( (from_color[max1_start]<255)|(from_color[min_start]>0) )
	{	
    display(from_color,bright,delay_step);
		if (from_color[max1_start]<255)
		{
			from_color[max1_start]+=step;
			from_color[max2_start]+=step;
		}
		if (from_color[min_start]>0) from_color[min_start]-=step;	   
	}
	//Giai doan display_per_step-------------------------------------------------------------------------------
	repeat=false;
	Serial.println("Giai doan display per step");
	display_per_step(bright);
	if (repeat==true) display_per_step(bright);
	//Giai doan cung nhom
	from_color[0]=red;
	from_color[1]=green;
	from_color[2]=blue;
	for (i=1;i<=b-1;i++)
	{
		display(from_color,bright,delay_step);
		if (group_stop%2==0) from_color[max2_start]-=step;
			else from_color[max2_start]+=step;
	}
	display(from_color,bright,delay_step);
	//Step change to stop---------------------------------------------------------------------------------------

	Serial.println("Giai doan change to stop");
	while ((from_color[0]!=to_color[0])||(from_color[1]!=to_color[1])||(from_color[2]!=to_color[2]))
	{
	if (from_color[0]>to_color[0]) from_color[0]-=step; 
		else if (from_color[0]<to_color[0])from_color[0]+=step;
	if (from_color[1]>to_color[1]) from_color[1]-=step; 
		else if (from_color[1]<to_color[1]) from_color[1]+=step;
	if (from_color[2]>to_color[2]) from_color[2]-=step;
		else if (from_color[2]< to_color[2]) from_color[2]+=step;
	display(from_color,bright,delay_step);
	}
	Serial.print("Dem la ");
	Serial.println(dem); 
}
//--------------------------------------------------------------------------------------------------------------------------------------
void led_RGB::display_per_step(uint8_t bright)
{
	switch (group_start)
	{
		case 1:
		{	
			red=255;green=from_color[max2_start];blue=0;
			if (group_stop==group_start) {max2_start=1;break;}
			else  
			{
				group_start++;
				for (green;green<=(255-step);green+=step) display(red,green,blue,bright,delay_step);
				from_color[max2_start]=255; 
			}		    
		}	
		
		case 2:
		{
			red=from_color[max2_start];green=255;blue=0;
			if (group_stop==group_start) {max2_start=0;break;}
			else 
			{
				group_start++;
				for (red;red>=step;red-=step) display(red,green,blue,bright,delay_step);
				from_color[max2_start]=0;
			}							
		}
		case 3:
		{
			red=0;green=255;blue=from_color[max2_start];
			if (group_stop==group_start) {max2_start=2;break;}	
			else 
			{
				++group_start;
				for (blue;blue<=(255-step);blue+=step) display(red,green,blue,bright,delay_step);			
				from_color[max2_start]=255;
			}
		}				
		case 4:
		{
			red=0;green=from_color[max2_start];blue=255;
			if (group_stop==group_start) {max2_start=1;break;}
			else
			{
				group_start++;
				for (green;green>=step;green-=step) display(red,green,blue,bright,delay_step);							
				from_color[max2_start]=0;
			}	
		}
		case 5:
		{
			red=from_color[max2_start];green=0;blue=255;
			if (group_stop==group_start) {max2_start=0;break;}	
			else 
			{
				group_start++;
				for (red;red<=(255-step);red+=step) display(red,green,blue,bright,delay_step);			
				from_color[max2_start]=255;
			}		
		}
		case 6:
		{
			red=255;blue=from_color[max2_start];green=0;
			if (group_stop==group_start) {max2_start=2;break;}
			else 
			{				
				group_start=1;
				for (blue;blue>=step;blue-=step) display(red,green,blue,bright,delay_step);
				from_color[max2_start]=0;
				repeat=true;          				
			}	      
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------
uint8_t led_RGB::classify_group(uint8_t array1[3])
{
	max1=0;
	max2=1;
	max3=2; //max 3 la Min cua mang 
	if (array1[max1]<array1[max2]) {max1=1; max2=0;}
	if (array1[max1]<array1[2])	{max2=max1; max1=2;}
	else if (array1[max2]<array1[2]) max2=2;
	for (byte i=0;i<=2;i++) if ((max1!=i) && (max2!=i)) max3=i; 
	byte a=max1*10+max2;
	switch (a)
	{
		case 01:
		{
			if ((array1[max1]-array1[max2])<=22){return(2);break;}
	    	else {return(1);break;}
		}
		case 10: {return(2);break;}
		case 12:
    	{
        	if ((array1[max1]-array1[max2])<=22){return(4);break;}
        	else {return(3);break;}
    	}
		case 21: {return(4);break;}
		case 20: {return(5);break;}
		case 02: {return(6);break;}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------
int led_RGB::calc_time(int time)
{  
  int step_get_format,step_changeto_stop,step_change_group;
	step_get_format=max(((255-from_color[max1_start])/step+1),(from_color[min_start]/step+1));
	step_changeto_stop=max(((255-to_color[max1_stop])/step),(to_color[min_stop]/step))-1;  
  
	if (group_start%2==1) a=(from_color[max1_start]-from_color[max2_start])/step;
		else a=(255-from_color[max1_start]+from_color[max2_start])/step;
	if (group_stop%2==1) b=(255-to_color[max1_stop]+to_color[max2_stop])/step+1;
		else b=(to_color[max1_stop]-to_color[max2_stop])/step+1;
	if (group_start<group_stop) step_change_group=(group_stop-group_start-1)*(255/step)+a+b;
		else if (group_start>group_stop) step_change_group=((5-group_start+group_stop)*(255/step))+a+b;
	  		else //(group_start==group_stop)
			{
				if ((a+b)>(255/step)) step_change_group=a+b-255/step ;
					else if((a+b)<(255/step)) step_change_group=255/step-a-b+2;
						else step_change_group=1;	//from_color=to_color @@
			}
	Serial.print("So buoc la: ");
	Serial.println(step_get_format+step_change_group+step_changeto_stop);  
	return(time/(step_get_format+step_change_group+step_changeto_stop));
}
//--------------------------------------------------------------------------------------------------------------------------------------
void led_RGB::batbo(uint8_t value[3])
{
  //Serial.print("Mang la ");
  for (uint8_t j=0; j<=2;j++) 
  {    
    Serial.print(value[j]);
    Serial.print(" ");
  }
  Serial.println();
//  delay(2000);
}

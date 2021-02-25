#ifndef LED_RGB_H
#define LED_RGB_H
#include <Arduino.h>


#define max(x,y) (((x)>=(y))?(x):(y))
#define COMMON_ANODE true
#define COMMON_CATHODE false
//setting level of exactitude led display

const uint8_t level_exact[7]={85,51,17,15,5,3,1};
const uint8_t RED[3]={255,0,0};
const uint8_t PURPLE[3]={255,0,17};


class led_RGB
{
public:
	led_RGB();
	void begin(uint8_t RED_PIN,uint8_t GREEN_PIN,uint8_t BLUE_PIN,bool type);
	void begin(uint8_t RED_PIN,uint8_t GREEN_PIN,uint8_t BLUE_PIN,bool type,uint8_t bright);
	void turnoff();

	void display(uint8_t color[3]);
	void display(uint8_t color[3],uint8_t bright);
	void display(uint8_t color[3],uint8_t bright,int time);
	void display(uint8_t _RED,uint8_t _GREEN,uint8_t _BLUE);
	void display(uint8_t _RED,uint8_t _GREEN,uint8_t _BLUE,uint8_t bright);
	void display(uint8_t _RED,uint8_t _GREEN,uint8_t _BLUE,uint8_t bright,int time);
  
	void changeColor(uint8_t _from_color[3], uint8_t _to_color[3],uint8_t level,uint8_t bright,int time);
 
private:	
	void display_per_step(uint8_t bright);
	uint8_t classify_group(uint8_t array1[3]);
	int calc_time(int time);
	void batbo(uint8_t value[3]);
	// khai bao cho begin
	uint8_t _redPin,_greenPin,_bluePin;
	uint8_t _bright;
	boolean type,repeat; 
	//Khai bao cho changeColor
	uint8_t from_color[3],to_color[3];
	unsigned int step,delay_step;
	byte group_start,group_stop;
	byte max1,max2,max3;
	uint8_t max1_start,max2_start,min_start,max1_stop,max2_stop,min_stop;
	uint8_t red,green,blue;
	uint8_t a,b;
	unsigned int dem;
};

#endif

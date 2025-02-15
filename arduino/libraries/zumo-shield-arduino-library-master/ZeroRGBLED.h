#ifndef ZERORGBLED_H
#define ZERORGBLED_H

#include <Adafruit_NeoPixel.h>

#define FLASH_DURATION 		200
#define SLOW   						2
#define MIDDLE 						1
#define FAST   						0

#define OFF        				0
#define ON         				1
#define SCALE      				1

#define SWAP              1
#define UNSWAP            0

#define LED_MAX_BRIGHT    255 / SCALE
#define ON_WHITE_MAX   		obj_name.Color(255, 255, 255)
#define ON_WHITE   				obj_name.Color(255 / SCALE, 255 / SCALE, 255 / SCALE)

#define ON_RED_MAX     		obj_name.Color(0 ,  255, 0)
#define ON_GREEN_MAX 	  	obj_name.Color(255, 0 ,  0)
#define ON_BLUE_MAX   		obj_name.Color(0,   0,   255)
#define ON_YELLOW_MAX			obj_name.Color(255, 255, 0)
#define ON_WHITE_MAX			obj_name.Color(255, 255, 255)


#define ON_RED     				obj_name.Color(255 / SCALE, 0,           0)
#define ON_GREEN   				obj_name.Color(0,           255 / SCALE, 0)
#define ON_BLUE    				obj_name.Color(0,           0,           255 / SCALE)
#define ON_YELLOW  				obj_name.Color(255 / SCALE, 255 / SCALE, 0)

#define ON_CYAN    				obj_name.Color(0,           255 / SCALE, 255 / SCALE)
#define ON_YELLOW  				obj_name.Color(255 / SCALE, 255 / SCALE, 0)
#define ON_MAGENTA 				obj_name.Color(255 / SCALE, 0,           255 / SCALE)
#define ON_PURPLE  				obj_name.Color(128 / SCALE, 0,           128 / SCALE)
#define OFF_RGB    				obj_name.Color(0,           0,           0)
class ZeroRGBLED {
	public:
		
			
		ZeroRGBLED(Adafruit_NeoPixel a);
		ZeroRGBLED(void);
		//~ZeroRGBLED();
		
		
		
		
    void begin(void);
    //void show(void);   
    void rainbow_stream(uint8_t wait);
    void theaterChaseRainbow(uint8_t wait);
    
    void FlashOneLED_RGB(int flash_speed, uint8_t pixel, uint32_t c); 
    void FlashOneLED_RGB(int flash_speed, uint8_t pixel, uint32_t c, int swap);
    void policeLightFlash(int pix_num, int flashSpeed, int swap);
    void OneLED_RGB(uint8_t pixel, uint32_t c);
    void policeLightWipe(int pix_num, int *pixel);
    void policeLightRun(int TotalPix, int *pixels);
  private:
    bool firstRun = true;
    double FStartT1 = 0;  
    double FStartT2 = 0;
    long firstPixelHue = 0;
    int outerloop = 0;
    int innerloop = 0;
    
    long WipeStartTime = 0;
    long FlashStartTime = 0;
    long policeLightStart = 0;
    bool oldState = HIGH;
    int showType = 0;
		Adafruit_NeoPixel  obj_name;
  	
};

    
#endif






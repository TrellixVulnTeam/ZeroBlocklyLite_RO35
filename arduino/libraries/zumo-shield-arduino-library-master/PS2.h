/**
 * \par Copyright (C), 206, Zeroworkshop
 * \class   StarterProI2C
 * \brief   Driver for Starter Pro module.
 * @file    StarterProI2C.h
 * @author  Zeroworkshop
 * @version V1.0.0
 * @date    2019/05/8
 * @brief   Header for StarterProI2C.cpp module
 *
 * \par Copyright
 * This software is Copyright (C), 2016-2019, Zeroworkshop. Use is subject to license \n
 * conditions. The main licensing options available are GPL V2 or Commercial: \n
 *
 * \par Open Source Licensing GPL V2
 * This is the appropriate option if you want to share the source code of your \n
 * application with everyone you distribute it to, and you also want to give them \n
 * the right to share who uses it. If you wish to use this software under Open \n
 * Source Licensing, you must contribute all your source code to the open source \n
 * community in accordance with the GPL Version 2 when your application is \n
 * distributed. See http://www.gnu.org/copyleft/gpl.html
 *
*/
#ifndef _PS2_H_
#define _PS2_H_

#include <Arduino.h>
#include <Wire.h>

         
/****************************************************************/
/****************  PS2 REMOTE CONTROL DATA **********************/
/****************  USING SERIAL EVENT ***************************/
/****************************************************************/

/*
#define _ButtonUp        (0x10 & Rx_Buffer[2])  //0b0001 0000   
#define _ButtonRight     (0x20 & Rx_Buffer[2])  //0b0010 0000
#define _ButtonDown      (0x40 & Rx_Buffer[2])  //0b0100 0000
#define _ButtonLeft      (0x80 & Rx_Buffer[2])  //0b1000 0000
#define _ButtonTriangle  (0x10 & Rx_Buffer[3])  //0b0001 0000
#define _ButtonCircle    (0x20 & Rx_Buffer[3])  //0b0010 0000
#define _ButtonCross     (0x40 & Rx_Buffer[3])  //0b0100 0000
#define _ButtonSquare    (0x80 & Rx_Buffer[3])  //0b1000 0000
#define _ButtonL1        (0x4 & Rx_Buffer[3])   //0b0000 0100
#define _ButtonL2        (0x1 & Rx_Buffer[3])   //0b0000 0001
#define _ButtonR1        (0x8 & Rx_Buffer[3])   //0b0000 1000
#define _ButtonR2        (0x2 & Rx_Buffer[3])   //0b0000 0010
#define _ButtonSelect    (0x1 & Rx_Buffer[2])   //0b0000 0001
#define _ButtonStart     (0x8 & Rx_Buffer[2])   //0b0000 1000
   */
 
 
#define _ButtonUp        (!(0x10 ^ Rx_Buffer[2]))  //0b0001 0000   
#define _ButtonRight     (!(0x20 ^ Rx_Buffer[2]))  //0b0010 0000
#define _ButtonDown      (!(0x40 ^ Rx_Buffer[2]))  //0b0100 0000
#define _ButtonLeft      (!(0x80 ^ Rx_Buffer[2]))  //0b1000 0000
#define _ButtonTriangle  (!(0x10 ^ Rx_Buffer[3]))  //0b0001 0000
#define _ButtonCircle    (!(0x20 ^ Rx_Buffer[3]))  //0b0010 0000
#define _ButtonCross     (!(0x40 ^ Rx_Buffer[3]))  //0b0100 0000
#define _ButtonSquare    (!(0x80 ^ Rx_Buffer[3]))  //0b1000 0000
#define _ButtonL1        (!(0x4 ^ Rx_Buffer[3]))   //0b0000 0100
#define _ButtonL2        (!(0x1 ^ Rx_Buffer[3]))   //0b0000 0001
#define _ButtonR1        (!(0x8 ^ Rx_Buffer[3]))   //0b0000 1000
#define _ButtonR2        (!(0x2 ^ Rx_Buffer[3]))   //0b0000 0010
//#define _ButtonSelect    (!(0x1 ^ Rx_Buffer[2]))   //0b0000 0001
#define _ButtonSelect    (0x1 & Rx_Buffer[2])   //0b0000 0001
#define _ButtonStart     (!(0x8 ^ Rx_Buffer[2]))   //0b0000 1000  


#define _ButtonUp_ButtonRight  (!(0x30 ^ Rx_Buffer[2]))   //0b0011 0000
#define _ButtonUp_ButtonLeft   (!(0x90 ^ Rx_Buffer[2]))   //0b1001 0000
#define _ButtonLeft_ButtonDown  (!(0xC0 ^ Rx_Buffer[2]))  //0b1100 0000
#define _ButtonRight_ButtonDown  (!(0x60 ^ Rx_Buffer[2])) //0b0110 0000

#define _ButtonTriangle_ButtonCircle   (!(0x30 ^ Rx_Buffer[3]))
#define _ButtonTriangle_ButtonSquare   (!(0x90 ^ Rx_Buffer[3]))
#define _ButtonSquare_ButtonCross      (!(0xC0 ^ Rx_Buffer[3]))
#define _ButtonCircle_ButtonCross      (!(0x60 ^ Rx_Buffer[3]))

       
#define _ButtonL1_ButtonL2   (!(0x5 ^ Rx_Buffer[3]))
#define _ButtonR1_ButtonR2   (!(0xA ^ Rx_Buffer[3]))
#define _ButtonL1_ButtonR1   (!(0xC ^ Rx_Buffer[3]))
#define _ButtonL1_ButtonR2   (!(0x6 ^ Rx_Buffer[3]))
#define _ButtonL2_ButtonR1   (!(0x9 ^ Rx_Buffer[3]))
#define _ButtonL2_ButtonR2   (!(0x3 ^ Rx_Buffer[3]))



#define _ButtonL1_ButtonUp				 ((!(0x10 ^ Rx_Buffer[2]))  && (!(0x4 ^ Rx_Buffer[3])) )
#define _ButtonL1_ButtonRight       	 ((!(0x20 ^ Rx_Buffer[2]))  && (!(0x4 ^ Rx_Buffer[3])) )
#define _ButtonL1_ButtonDown			 ((!(0x40 ^ Rx_Buffer[2]))  && (!(0x4 ^ Rx_Buffer[3])) )
#define _ButtonL1_ButtonLeft			 ((!(0x80 ^ Rx_Buffer[2]))  && (!(0x4 ^ Rx_Buffer[3])) )


#define _ButtonL1_ButtonTriangle   (!(0x14 ^ Rx_Buffer[3]))
#define _ButtonL1_ButtonCircle     (!(0x24 ^ Rx_Buffer[3]))
#define _ButtonL1_ButtonCross      (!(0x44 ^ Rx_Buffer[3]))
#define _ButtonL1_ButtonSquare     (!(0x84 ^ Rx_Buffer[3]))
#define _ButtonL2_ButtonTriangle   (!(0x11 ^ Rx_Buffer[3]))
#define _ButtonL2_ButtonCircle     (!(0x21 ^ Rx_Buffer[3]))
#define _ButtonL2_ButtonCross      (!(0x41 ^ Rx_Buffer[3]))
#define _ButtonL2_ButtonSquare     (!(0x81 ^ Rx_Buffer[3]))

#define _ButtonR1_ButtonTriangle   (!(0x18 ^ Rx_Buffer[3]))
#define _ButtonR1_ButtonCircle     (!(0x28 ^ Rx_Buffer[3]))
#define _ButtonR1_ButtonCross      (!(0x48 ^ Rx_Buffer[3]))
#define _ButtonR1_ButtonSquare     (!(0x88 ^ Rx_Buffer[3]))
#define _ButtonR2_ButtonTriangle   (!(0x12 ^ Rx_Buffer[3]))
#define _ButtonR2_ButtonCircle     (!(0x22 ^ Rx_Buffer[3]))
#define _ButtonR2_ButtonCross      (!(0x42 ^ Rx_Buffer[3]))
#define _ButtonR2_ButtonSquare     (!(0x82 ^ Rx_Buffer[3]))
   

#define _ButtonSelect_ButtonUp      (!(0x11 ^ Rx_Buffer[2]))  //0b0001 0001  
#define _ButtonSelect_ButtonRight   (!(0x21 ^ Rx_Buffer[2]))  //0b0001 0001  
#define _ButtonSelect_ButtonDown    (!(0x41 ^ Rx_Buffer[2]))  //0b0001 0001  
#define _ButtonSelect_ButtonLeft    (!(0x81 ^ Rx_Buffer[2]))  //0b0001 0001

#define _ButtonStart_ButtonUp      (!(0x18 ^ Rx_Buffer[2]))  //0b0001 1000  
#define _ButtonStart_ButtonRight   (!(0x28 ^ Rx_Buffer[2]))  //0b0010 1000  
#define _ButtonStart_ButtonDown    (!(0x48 ^ Rx_Buffer[2]))  //0b0100 1000  
#define _ButtonStart_ButtonLeft    (!(0x88 ^ Rx_Buffer[2]))  //0b1000 1000  


#define _ButtonSelect_ButtonTriangle   ((!(0x1 ^ Rx_Buffer[2])) && (!(0x10 ^ Rx_Buffer[3])) )
#define _ButtonSelect_ButtonCircle     ((!(0x1 ^ Rx_Buffer[2])) && (!(0x20 ^ Rx_Buffer[3])) )
#define _ButtonSelect_ButtonCross      ((!(0x1 ^ Rx_Buffer[2])) && (!(0x30 ^ Rx_Buffer[3])) )
#define _ButtonSelect_ButtonSquare     ((!(0x1 ^ Rx_Buffer[2])) && (!(0x80 ^ Rx_Buffer[3])) )

#define _ButtonSelect_ButtonL1				 ((!(0x1 ^ Rx_Buffer[2])) && (!(0x4 ^ Rx_Buffer[3])) )
#define _ButtonSelect_ButtonL2			   ((!(0x1 ^ Rx_Buffer[2])) && (!(0x1 ^ Rx_Buffer[3])) )
#define _ButtonSelect_ButtonR1		     ((!(0x1 ^ Rx_Buffer[2])) && (!(0x8 ^ Rx_Buffer[3])) )
#define _ButtonSelect_ButtonR2 		     ((!(0x1 ^ Rx_Buffer[2])) && (!(0x2 ^ Rx_Buffer[3])) )


#define _ButtonStart_ButtonL1   			 ((!(0x8 ^ Rx_Buffer[2])) && (!(0x4 ^ Rx_Buffer[3])) )
#define _ButtonStart_ButtonL2     		 ((!(0x8 ^ Rx_Buffer[2])) && (!(0x1 ^ Rx_Buffer[3])) )
#define _ButtonStart_ButtonR1    		 	 ((!(0x8 ^ Rx_Buffer[2])) && (!(0x8 ^ Rx_Buffer[3])) )
#define _ButtonStart_ButtonR2			     ((!(0x8 ^ Rx_Buffer[2])) && (!(0x2 ^ Rx_Buffer[3])) )



extern int Rx_Buffer[6];  

//void serialEvent();

#endif

 





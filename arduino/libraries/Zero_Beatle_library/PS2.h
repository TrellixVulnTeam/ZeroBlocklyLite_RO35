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
/****************************************************************/
/****************  PS2 REMOTE CONTROL DATA **********************/
/****************  USING SERIAL EVENT ***************************/
/****************************************************************/
#define _ButtonUp        (0x10 & Rx_Buffer[2])
#define _ButtonRight     (0x20 & Rx_Buffer[2])
#define _ButtonDown      (0x40 & Rx_Buffer[2])
#define _ButtonLeft      (0x80 & Rx_Buffer[2])
#define _ButtonTriangle  (0x10 & Rx_Buffer[3])
#define _ButtonCircle    (0x20 & Rx_Buffer[3])
#define _ButtonCross     (0x40 & Rx_Buffer[3])
#define _ButtonSquare    (0x80 & Rx_Buffer[3])
#define _ButtonL1        (0x4 & Rx_Buffer[3])
#define _ButtonL2        (0x1 & Rx_Buffer[3])
#define _ButtonR1        (0x8 & Rx_Buffer[3])
#define _ButtonR2        (0x2 & Rx_Buffer[3])
#define _ButtonSelect    (0x1 & Rx_Buffer[2])
#define _ButtonStart     (0x8 & Rx_Buffer[2])

/****************************************************************/
/****************  PS2 KEY VALUE **********************/
/****************************************************************/
#define PS2_UP        0x10 
#define PS2_RIGHT     0x20 
#define PS2_DOWN      0x40 
#define PS2_LEFT      0x80 
#define PS2_TRIANGLE  0x10 
#define PS2_CIRCLE    0x20 
#define PS2_CROSS     0x40 
#define PS2_SQUARE    0x80 
#define PS2_L1        0x4 
#define PS2_L2        0x1 
#define PS2_R1        0x8 
#define PS2_R2        0x2 
#define PS2_SELECT    0x1 
#define PS2_START     0x8 


   
extern int Rx_Buffer[6];  


#endif

 





/*
 * Ultrasonic.cpp
 * A library for ultrasonic ranger
 *
 * Copyright (c) 2012 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : LG, FrankieChu
 * Create Time: Jan 17,2013
 * Change Log :
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Arduino.h"
#include "Ultrasonic.h"

void Ultrasonic::begin()
{
	_pin = "2";
	_unit = "cm";
}

void Ultrasonic::begin(int pin)
{
	_pin = pin;
	_unit = "cm";
}

void Ultrasonic::begin(int pin,String unit)
{
	_pin = pin;
	_unit = unit;
}

void Ultrasonic::setPin(int pin)
{
	_pin = pin;
}

void Ultrasonic::setUnit(String unit)
{
	_unit = unit;
}

/*The measured distance from the range 0 to 400 Centimeters*/
int Ultrasonic::measDistance(void)
{
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, LOW);
	delayMicroseconds(2);
	digitalWrite(_pin, HIGH);
	delayMicroseconds(10);
	digitalWrite(_pin,LOW);
	pinMode(_pin,INPUT);
	long duration;
	duration = pulseIn(_pin,HIGH);
	int fDistance;
	if(_unit==String("cm"))
	{
		fDistance = duration/29/2;
	}
	else if(_unit==String("Inch"))
	{
		fDistance = duration/74/2;
	}
	else
	{
		fDistance = 999;
	}

	return fDistance;
}

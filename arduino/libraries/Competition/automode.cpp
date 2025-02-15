#include    "automode.h"
#include    "ZeroWorkshop_lib.h"
#include    "LineFollowerArray.h"
#include    "ZeroWorkshop_Macro_Definitions.h"

#define HEAD_SENSORPIN   ZW_A1
#define HAND_BUTTON      ZW_B4
#define CARLEFT_SENSOR   ZW_A2
#define CARRIGHT_SENSOR  1
#define CARBACK_SENSOR   0

#define INIT_STATE       0
#define CATCH_STATE      1
#define DELIVER_STATE    2
#define IDLE_STATE       3

#define HAND_CLOSED       1
#define HAND_OPENED       2
//Servo angles
/*
#define SERVO1_CATCH_POS      135
#define SERVO2_CATCH_POS      145
#define SERVO1_INIT_POS       0
#define SERVO2_INIT_POS       180

#define HANDOPEN_ANG           130
#define HANDCLOSE_ANG          25
#define HEADSENSOR_MIDDLE_POS  90
#define HEADSERVO_RANGE        50
*/ 
double  SERVO1_CATCH_POS;
double  SERVO2_CATCH_POS;
double  SERVO1_INIT_POS;
double  SERVO2_INIT_POS;

double  HANDOPEN_ANG;
double  HANDCLOSE_ANG;
double  HEADSENSOR_MIDDLE_POS;
double  HEADSERVO_RANGE; 

double AUTOGRAB_TIME;

int handStatus;
//IR ranges
#define CAP_RANGE              0.2
#define CATCH_RANGE            50
#define CUBE_SEEN_RANGE        930

#define carSpeed 80

LineFollowerArray  LineFollower(0x09);

int    return_color;

double timerStart = 0;
double AutoModeStartTime;

int    AutoRun_State;
int    headServoField;
bool   cubeMissed;


#define  COLOR_TOLERANCE              5
#define  COLOR_TOLERANCE_MAX          50
#define  COLOR_NUM_MAX                4     //
#define  COLOR_CALIBRATION_TIMES      10
boolean  CALIBRATION_COLOR =          false;

double   tStart = 0;

enum color_type
{
  NOTHING = 0, RED = 1, GREEN = 2, BLUE = 3, INVALID = 8
};

String StrColor[5] = {"NOTHING", "RED", "GREEN", "BLUE", "INVALID"};


typedef struct {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t red_max;
  uint8_t red_min;
  uint8_t green_max;
  uint8_t green_min;
  uint8_t blue_max;
  uint8_t blue_min;
} RGB_type;

RGB_type rgb;

RGB_type RGB_STORE_DATA[COLOR_NUM_MAX];
// Color Sensor-Objekt initialisieren
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);  //changed from TCS34725_GAIN_1X



int num = 0;
int ColorNum = 0;

void sensorMode();



#define  _speed_   150
#define SENSOR_THRESHOLD  200
#define ABOVE_LINE(sensor)   ((sensor) >SENSOR_THRESHOLD)

void carRightTurn() {
  MotorControl(1, BACKWARD, carSpeed);
  MotorControl(2, BACKWARD, carSpeed);
}

void carLeftTurn() {
  MotorControl(1, FORWARD, carSpeed);
  MotorControl(2, FORWARD, carSpeed);
}

void carStop() {
  MotorControl(1, FORWARD, 0);
  MotorControl(2, BACKWARD, 0);
}

void carGoReverse() {
  MotorControl(1, FORWARD, carSpeed);
  MotorControl(2, BACKWARD, carSpeed);
}

void carGoForward() {
  MotorControl(1, BACKWARD, carSpeed);
  MotorControl(2, FORWARD, carSpeed);
}


void carReturn() {
  if (cubeMissed)
    AutoRun_State = INIT_STATE;
  else
    AutoRun_State = DELIVER_STATE;


}

void motor(int leftSpeed, int rightSpeed)
{
  if (leftSpeed > 0)
  {
    MotorControl(1, BACKWARD, leftSpeed);
  }
  else
  {
    MotorControl(1, FORWARD, abs(leftSpeed));
  }

  if (rightSpeed > 0)
  {
    MotorControl(2, FORWARD, rightSpeed);
  }
  else
  {
    MotorControl(2, BACKWARD, abs(rightSpeed));
  }

}


int followLine_firstrun = 1;
void followSegment()
{

  int offset_from_center;
  int power_difference;
  int left_speed, right_speed;
  int newSpeed;

  unsigned int sensors[8];
  int position;
  int white_line = 1;
  int sum = 0;
  double tStart = millis();
  
   if(followLine_firstrun)
   	 {
   	 	//carGoForward();
   	 	//delay(500);
   	 	//carLeftTurn(); 	 	
   	 	MotorControl(1, FORWARD, 0);
      MotorControl(2, FORWARD, 255);
   	 	delay(600);
   	 	MotorControl(2,FORWARD,128);
   	 	delay(500);
   	 	carStop();
   	 	//delay(2000);
   	 	followLine_firstrun = 0;
   	 }
  newSpeed = _speed_;
  while ((millis() - tStart) < 300)   //300
  {
    Serial.println("Line follwing.....................................");
    Serial.println(millis() - tStart);
    position =  LineFollower.readLine(sensors, 1);
 
    offset_from_center = ((int)position) - 3500;
	
    power_difference = offset_from_center / 20;
    if (power_difference >  _speed_)
      power_difference = _speed_;
    if (power_difference < -_speed_)
      power_difference = -_speed_;


    if (power_difference < 0)
    {
      left_speed = _speed_ + power_difference;
      right_speed = _speed_;
    }
    else
    {
      left_speed = _speed_;
      right_speed = _speed_ - power_difference;
    }

    Serial.print(power_difference);
    Serial.print("\t");
    Serial.print(left_speed);
    Serial.print("\t");
    Serial.println(right_speed);

    left_speed = left_speed * 1.5;
    right_speed = right_speed * 1.5;
    motor(left_speed, right_speed);
    //Add for stop
    sum=0;
    for(int i=0;i<8;i++) 
		{
			sum += ABOVE_LINE(sensors[i]);
		//	Serial.print(ABOVE_LINE(sensors[i]));
		//	Serial.print("\t");
		}
		//Serial.println();
		//Serial.print("sum =");
		
		Serial.println(sum);
		if (sum > 5)
		{
			//Serial.println("all on line1");
			
			delay(100);
			 position =  LineFollower.readLine(sensors, 1);
			 sum=0;
			 for(int i=0;i<8;i++) 
			{
				sum += ABOVE_LINE(sensors[i]);
				}
				if (sum > 6)
					{	
						//Serial.println("all on line2");
						
						delay(100);		
			 			position =  LineFollower.readLine(sensors, 1);
			 			sum=0;
			 			for(int i=0;i<8;i++) 
						{
							sum += ABOVE_LINE(sensors[i]);
						}
						if(sum > 6)
							{
								
								delay(350);		
			 			position =  LineFollower.readLine(sensors, 1);
			 			sum=0;
			 			for(int i=0;i<8;i++) 
						{
							sum += ABOVE_LINE(sensors[i]);
						}
						if(sum > 6)
							{
								
								
								//Serial.println("all on line3");
								//Serial.println("STOP");
								sum=0;
								//delay(350);
								motor(-128,128);
								delay(100);
								motor(128,128);
								delay(100);
								motor(0,0);
								delay(30000);
							}
								
								}
					}

  }
}


}


void tcs74725_init()
{


  RGB_STORE_DATA[0].red = 70;
  RGB_STORE_DATA[0].red_max = 83;
  RGB_STORE_DATA[0].red_min = 57;
  RGB_STORE_DATA[0].green = 92;
  RGB_STORE_DATA[0].green_max = 98;
  RGB_STORE_DATA[0].green_min = 85;
  RGB_STORE_DATA[0].blue = 81;
  RGB_STORE_DATA[0].blue_max = 88;
  RGB_STORE_DATA[0].blue_min = 75;

  RGB_STORE_DATA[1].red = 104;
  RGB_STORE_DATA[1].red_max = 160;
  RGB_STORE_DATA[1].red_min = 85;
  RGB_STORE_DATA[1].green = 73;
  RGB_STORE_DATA[1].green_max = 88;
  RGB_STORE_DATA[1].green_min = 30;
  RGB_STORE_DATA[1].blue = 67;
  RGB_STORE_DATA[1].blue_max = 81;
  RGB_STORE_DATA[1].blue_min = 30;

  RGB_STORE_DATA[2].red = 61;
  RGB_STORE_DATA[2].red_max = 68;
  RGB_STORE_DATA[2].red_min = 54;
  RGB_STORE_DATA[2].green = 110;
  RGB_STORE_DATA[2].green_max = 140;
  RGB_STORE_DATA[2].green_min = 99;
  RGB_STORE_DATA[2].blue = 69;
  RGB_STORE_DATA[2].blue_max = 81;
  RGB_STORE_DATA[2].blue_min = 45;

  RGB_STORE_DATA[3].red = 40;
  RGB_STORE_DATA[3].red_max = 52;
  RGB_STORE_DATA[3].red_min = 20;
  RGB_STORE_DATA[3].green = 90;
  RGB_STORE_DATA[3].green_max = 96;
  RGB_STORE_DATA[3].green_min = 84;
  RGB_STORE_DATA[3].blue = 113;
  RGB_STORE_DATA[3].blue_max = 150;
  RGB_STORE_DATA[3].blue_min = 101;

  if (tcs.begin()) {
    // Alles OK
    Serial.println("Sensor founded!");
  } else {
    // Kein Sensor gefunden. Programm an dieser Stelle einfrieren
    Serial.println("TCS34725 is not available, please try check it !");
    while (1); // Halt!
  }

  tcs.setInterrupt(false);

}

void sensorMode() {
  //RGB_type rgb;
  uint16_t clearcol, red, green, blue;
  tcs.getRawData(&red, &green, &blue, &clearcol);
  // Figure out some basic hex code for visualization
  uint32_t sum = clearcol;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;

  rgb.red = (int)r;
  rgb.green = (int)g;
  rgb.blue = (int)b;

  if (rgb.red_max < rgb.red)
    rgb.red_max = rgb.red;
  if (rgb.red_min > rgb.red)
    rgb.red_min = rgb.red;

  if (rgb.green_max < rgb.green)
    rgb.green_max = rgb.green;
  if (rgb.green_min > rgb.green)
    rgb.green_min = rgb.green;

  if (rgb.blue_max < rgb.blue)
    rgb.blue_max = rgb.blue;
  if (rgb.blue_min > rgb.blue)
    rgb.blue_min = rgb.blue;

  num++;

  //Serial.print((int)num, DEC);
  //Serial.print(":\t");


  Serial.print(rgb.red, HEX); Serial.print(rgb.green, HEX); Serial.print(rgb.blue, HEX);

  Serial.println();

  //return rgb;
}

color_type CheckColor(RGB_type rgb_data)
{
  color_type color = INVALID;
  for (int i = 0; i < COLOR_NUM_MAX; i++)
  {
    boolean red_in_limit = false;
    boolean green_in_limit = false;
    boolean blue_in_limit = false;
    if ((rgb_data.red <   RGB_STORE_DATA[i].red_max) &&  (rgb_data.red >   RGB_STORE_DATA[i].red_min))
    {
      red_in_limit = true;
    }
    if ((rgb_data.green <   RGB_STORE_DATA[i].green_max) &&  (rgb_data.green >   RGB_STORE_DATA[i].green_min))
    {
      green_in_limit = true;
    }
    if ((rgb_data.blue <   RGB_STORE_DATA[i].blue_max) &&  (rgb_data.blue >   RGB_STORE_DATA[i].blue_min))
    {
      blue_in_limit = true;
    }

    if (red_in_limit && green_in_limit && blue_in_limit)
    {
      color = i;
    }

  }
  return color;
}



/***************************************************/
/******************   Fucntions  *******************/
/***************************************************/
void lowerArm(Servo servo1, Servo servo2, double *servo1_ang, double *servo2_ang) {
  while (*servo1_ang < SERVO1_CATCH_POS) {
    *servo1_ang += 0.01;
    servo1.write(*servo1_ang);
  }


  while (*servo2_ang > SERVO2_CATCH_POS ) {
    *servo2_ang -= 0.01;
    servo2.write(*servo2_ang);
  }

}

void armUp(Servo servo1, Servo servo2, double *servo1_ang, double *servo2_ang) {
  while (*servo2_ang < SERVO2_INIT_POS) {
    *servo2_ang += 0.05;
    servo2.write(*servo2_ang);
  }
}

void armRestore(Servo servo1, Servo servo2, double *servo1_ang, double *servo2_ang) {
  while (*servo1_ang > SERVO1_INIT_POS ) {
    *servo1_ang -= 0.005;
    servo1.write(*servo1_ang);
  }

  while (*servo2_ang < SERVO2_INIT_POS) {
    *servo2_ang += 0.005;
    servo2.write(*servo2_ang);
  }
}

void closeHand(Servo Hservo) {
  double angle;

  
  angle = HANDOPEN_ANG;
  if (HANDOPEN_ANG > HANDCLOSE_ANG)  {
  	while (angle > HANDCLOSE_ANG) {
       angle -= 0.01;
       Hservo.write(HANDCLOSE_ANG);
    }
  }	
  else {
  	while (angle < HANDCLOSE_ANG) {
       angle += 0.01;
       Hservo.write(HANDCLOSE_ANG);
    }
  }
  	
  
}

void closeHand() {
  timerStart = millis();
  while (digitalRead(HAND_BUTTON) && handStatus == HAND_OPENED) {
    if (millis() - timerStart > 10000)
      return;
    MotorControl(3, BACKWARD, 255);
  }


  MotorControl(3, BACKWARD, 0);
  handStatus = HAND_CLOSED;
}

void openHand(Servo Hservo) {
  Hservo.write(HANDOPEN_ANG);
}
void openHand() {

  if (handStatus == HAND_CLOSED) {     //Open the claw for 1 sec to release the hand close sensor button.
    MotorControl(3, FORWARD, 255);
    if (!digitalRead(HAND_BUTTON))
      delay(1000);
    else
      delay(200);
  }

  timerStart = millis();
  while (digitalRead(HAND_BUTTON) && handStatus == HAND_CLOSED) {
    if (millis() - timerStart > 10000)
      return;
    MotorControl(3, FORWARD, 255);
  }

  MotorControl(3, BACKWARD, 255);
  delay(300);                      //After the claw is totally open, close it for 1 sec to release the sensor button. This is because both the hand close sensor and hand open sensor share the same input pin ZW_A2.
  MotorControl(3, FORWARD, 0);
  handStatus = HAND_OPENED;
}



int readCubeColor() {
  timerStart = millis();
  color_type color;
  char *color_str;


  sensorMode();
  color = CheckColor(rgb);

  if (color == 1) {
    color_str = "RED";
    return_color = 1;
  }
  else if (color  == 2) {
    color_str = "GREEN";
    return_color = 2;

  }
  else if (color == 3) {
    color_str = "BLUE";
    return_color = 3;
  }
  else {
    color_str = "NO_COLOR";
    return_color = 0;
  }


  Serial.print("The cube caught is : ");
  Serial.println(color_str);
  //Serial.println(millis() - timerStart);

  return return_color;


}
void TurnRight90()
{


  int left_val;
  int right_val;

 //pinMode(CARLEFT_SENSOR,INPUT);
 // pinMode(CARRIGHT_SENSOR,INPUT);

  left_val = digitalRead(CARLEFT_SENSOR);
  right_val = digitalRead(CARRIGHT_SENSOR);

 // do {

    do {
      MotorControl(1, BACKWARD, 0);
      MotorControl(2, BACKWARD, 128);
      right_val = digitalRead(CARRIGHT_SENSOR);
      Serial.print("right_val = ");
      Serial.println(right_val);
    } while (right_val == 1);

    MotorControl(1, BACKWARD, 0);
    MotorControl(2, BACKWARD, 0);

    do {
      MotorControl(1, BACKWARD, 128);
      MotorControl(2, BACKWARD, 0);
      left_val = digitalRead(CARLEFT_SENSOR);
      Serial.print("left_val = ");
      Serial.println(left_val);

    } while (left_val == 1);

    MotorControl(1, BACKWARD, 0);
    MotorControl(2, BACKWARD, 0);

   // left_val = digitalRead(CARLEFT_SENSOR);
  //  right_val = digitalRead(CARRIGHT_SENSOR);

 // } while (left_val == 1 || right_val == 1);

}



void TurnRight90_returnToMiddle()
{

  int counter = 0;
  Serial.println("Turnleft90 and return to middle");
  int sum, sumBack;
  unsigned int sensors[8];
  unsigned int sensorsBack[8];

  int positionFront;
  int positionBack;
  int white_line = 1;
  //int counterA = 0;
  int backIsready = 0;
  do
  {
  	//Serial.begin(115200);
    do
    {

      MotorControl(1, FORWARD, 128);
      MotorControl(2, FORWARD, 0);
      delay(1);
      positionFront =  LineFollower.readLine(sensors, 1);


    } while (!ABOVE_LINE(sensors[3]));
    //Serial.end();

    positionBack = digitalRead(CARBACK_SENSOR);
    timerStart = millis();
  
    while (positionBack == 1   && backIsready == 0  && (millis() - timerStart <800) )
    {

      MotorControl(1, FORWARD, 0);
      MotorControl(2, FORWARD, 128);
      positionBack = digitalRead(CARBACK_SENSOR); //use IR sensor
      if(positionBack == 0) backIsready = 1;
      //delay(1);
      //positionBack =  LineFollowerBack.readLine(sensorsBack, 1);

    };// while (positionBack == 1  && backIsready == 0);
    backIsready = 1; 
    positionFront =  LineFollower.readLine(sensors, 1);
    //positionBack =  LineFollowerBack.readLine(sensorsBack, 1);
    //positionBack = digitalRead(CARBACK_SENSOR); //use IR sensor
    counter++;

  } while (((!(ABOVE_LINE(sensors[3])))&& (!(ABOVE_LINE(sensors[4]))) )  || backIsready == 0);
 //while ( ( (!(ABOVE_LINE(sensors[3]) )) && (!(ABOVE_LINE(sensors[4])))  )|| (positionBack == 1));
  MotorControl(1, FORWARD, 0);
  MotorControl(2, FORWARD, 128);
  delay(200);
  MotorControl(1, BACKWARD, 0);
  MotorControl(2, BACKWARD, 0);
  delay(200);
  carGoReverse();
  delay(200);
}

void TurnRight90_returnToMiddleMotorClaw()
{

  int counter = 0;
  Serial.println("Turnleft90 and return to middle");
  int sum, sumBack;
  unsigned int sensors[8];
  unsigned int sensorsBack[8];

  int positionFront;
  int positionBack;
  int white_line = 1;
  //int counterA = 0;
  int backIsready = 0;
  do
  {
  	//Serial.begin(115200);
    do
    {
      if  ((digitalRead(HAND_BUTTON) && handStatus == HAND_CLOSED)) {    //check if hand is totally open, if not open it
        MotorControl(3, FORWARD, 255);
      }
      else
        MotorControl(3, FORWARD, 0);
        
      MotorControl(1, FORWARD, 128);
      MotorControl(2, FORWARD, 0);
      delay(1);
      positionFront =  LineFollower.readLine(sensors, 1);


    } while (!ABOVE_LINE(sensors[3]));
    //Serial.end();

    positionBack = digitalRead(CARBACK_SENSOR);
    timerStart = millis();
  
    while (positionBack == 1   && backIsready == 0  && (millis() - timerStart <800) )
    {
      if  ((digitalRead(HAND_BUTTON) && handStatus == HAND_CLOSED)) {   //check if hand is totally open, if not open it
        MotorControl(3, FORWARD, 255);
      }
      else
        MotorControl(3, FORWARD, 0);
        
      MotorControl(1, FORWARD, 0);
      MotorControl(2, FORWARD, 128);
      positionBack = digitalRead(CARBACK_SENSOR); //use IR sensor
      if(positionBack == 0) backIsready = 1;
      //delay(1);
      //positionBack =  LineFollowerBack.readLine(sensorsBack, 1);

    };// while (positionBack == 1  && backIsready == 0);

    backIsready = 1;
    positionFront =  LineFollower.readLine(sensors, 1);
    //positionBack =  LineFollowerBack.readLine(sensorsBack, 1);
    //positionBack = digitalRead(CARBACK_SENSOR); //use IR sensor
    counter++;

  } while (((!(ABOVE_LINE(sensors[3])))&& (!(ABOVE_LINE(sensors[4]))) )  || backIsready == 0);
 //while ( ( (!(ABOVE_LINE(sensors[3]) )) && (!(ABOVE_LINE(sensors[4])))  )|| (positionBack == 1));
  MotorControl(1, FORWARD, 0);
  MotorControl(2, FORWARD, 128);
  delay(800);
  while  ((digitalRead(HAND_BUTTON) && handStatus == HAND_CLOSED)) {     //If hand is still not totally open, continue to fully open it
    MotorControl(3, FORWARD, 255);
  }
  MotorControl(3, FORWARD, 0);
    
  MotorControl(1, BACKWARD, 0);
  MotorControl(2, BACKWARD, 0);
  MotorControl(3, BACKWARD, 255);  //After the claw is totally open, close it for 600ms to release the sensor button. This is because both the hand close sensor and hand open sensor share the same input pin ZW_A2.
  delay(200);
  carGoReverse();
  delay(400);
  MotorControl(3, BACKWARD, 0);
  handStatus = HAND_OPENED;
}

void TurnLeft90()
{


  int left_val;
  int right_val;
 // pinMode(CARLEFT_SENSOR,INPUT);
 //pinMode(CARRIGHT_SENSOR,INPUT);

  left_val = digitalRead(CARLEFT_SENSOR);
  right_val = digitalRead(CARRIGHT_SENSOR);

 // do {

    do {
      MotorControl(1, FORWARD, 128);
      MotorControl(2, FORWARD, 0);
      left_val = digitalRead(CARLEFT_SENSOR);
      Serial.print("left_val = ");
      Serial.println(left_val);

    } while (left_val == 1);

    MotorControl(1, FORWARD, 0);
    MotorControl(2, FORWARD, 0);

    do {
      MotorControl(1, FORWARD, 0);
      MotorControl(2, FORWARD, 128);
      right_val = digitalRead(CARRIGHT_SENSOR);
      Serial.print("right_val = ");
      Serial.println(right_val);
    } while (right_val == 1);

    MotorControl(1, FORWARD, 0);
    MotorControl(2, FORWARD, 0);

   // left_val = digitalRead(CARLEFT_SENSOR);
  //  right_val = digitalRead(CARRIGHT_SENSOR);

  //} while (left_val == 1 || right_val == 1);

}

void TurnLeft90_returnToMiddleMotorClaw()
{

  int counter = 0;
  Serial.println("Turnleft90 and return to middle");
  int sum, sumBack;
  unsigned int sensors[8];
  unsigned int sensorsBack[8];

  int positionFront;
  int positionBack;
  int white_line = 1;
  //int counterA = 0;
  int backIsready = 0;
  do
  {
  	//Serial.begin(115200);
    do
    {
      if  ((digitalRead(HAND_BUTTON) && handStatus == HAND_CLOSED)) {    //check if hand is totally open, if not open it
        MotorControl(3, FORWARD, 255);
      }
      else
        MotorControl(3, FORWARD, 0);
        
        
      MotorControl(1, BACKWARD, 0);
      MotorControl(2, BACKWARD, 128);
      delay(1);
      positionFront =  LineFollower.readLine(sensors, 1);


    } while (!ABOVE_LINE(sensors[3]));
    //Serial.end();

    positionBack = digitalRead(CARBACK_SENSOR);
    timerStart = millis();
   
    while (positionBack == 1   && backIsready == 0 && (millis() - timerStart <800))
    {
      if  ((digitalRead(HAND_BUTTON) && handStatus == HAND_CLOSED)) {    //check if hand is totally open, if not open it
        MotorControl(3, FORWARD, 255);
      }
      else
        MotorControl(3, FORWARD, 0);
        
        
      MotorControl(1, BACKWARD, 128);
      MotorControl(2, BACKWARD, 0);
      positionBack = digitalRead(CARBACK_SENSOR); //use IR sensor
      if(positionBack == 0) backIsready = 1;
      //delay(1);
      //positionBack =  LineFollowerBack.readLine(sensorsBack, 1);

    };// while (positionBack == 1  && backIsready == 0);

    backIsready =1;
    positionFront =  LineFollower.readLine(sensors, 1);
    //positionBack =  LineFollowerBack.readLine(sensorsBack, 1);
    //positionBack = digitalRead(CARBACK_SENSOR); //use IR sensor
    counter++;

  } while (((!(ABOVE_LINE(sensors[3])))&& (!(ABOVE_LINE(sensors[4]))) )  || backIsready == 0);
 //while ( ( (!(ABOVE_LINE(sensors[3]) )) && (!(ABOVE_LINE(sensors[4])))  )|| (positionBack == 1));
  MotorControl(1, BACKWARD, 128);
  MotorControl(2, BACKWARD, 0);
  delay(800);
  
  while  ((digitalRead(HAND_BUTTON) && handStatus == HAND_CLOSED)) {     //If hand is still not totally open, continue to fully open it
    MotorControl(3, FORWARD, 255);
  }
  MotorControl(3, FORWARD, 0);
  
  MotorControl(1, BACKWARD, 0);
  MotorControl(2, BACKWARD, 0);
  MotorControl(3, BACKWARD, 255);  //After the claw is totally open, close it for 600ms to release the sensor button. This is because both the hand close sensor and hand open sensor share the same input pin ZW_A2.
  delay(200);
  carGoReverse();
  delay(400);
  MotorControl(3, BACKWARD, 0);
  handStatus = HAND_OPENED;
}

void TurnLeft90_returnToMiddle()
{

  int counter = 0;
  Serial.println("Turnleft90 and return to middle");
  int sum, sumBack;
  unsigned int sensors[8];
  unsigned int sensorsBack[8];

  int positionFront;
  int positionBack;
  int white_line = 1;
  //int counterA = 0;
  int backIsready = 0;
  do
  {
  	//Serial.begin(115200);
    do
    {

      MotorControl(1, BACKWARD, 0);
      MotorControl(2, BACKWARD, 128);
      delay(1);
      positionFront =  LineFollower.readLine(sensors, 1);


    } while (!ABOVE_LINE(sensors[3]));
    //Serial.end();

    positionBack = digitalRead(CARBACK_SENSOR);
     timerStart = millis();
   
    while (positionBack == 1   && backIsready == 0 && (millis() - timerStart <800))
    {

      MotorControl(1, BACKWARD, 128);
      MotorControl(2, BACKWARD, 0);
      positionBack = digitalRead(CARBACK_SENSOR); //use IR sensor
      if(positionBack == 0) backIsready = 1;
      //delay(1);
      //positionBack =  LineFollowerBack.readLine(sensorsBack, 1);

    };// while (positionBack == 1  && backIsready == 0);
    
    backIsready =1;
    positionFront =  LineFollower.readLine(sensors, 1);
    //positionBack =  LineFollowerBack.readLine(sensorsBack, 1);
    //positionBack = digitalRead(CARBACK_SENSOR); //use IR sensor
    counter++;

  } while (((!(ABOVE_LINE(sensors[3])))&& (!(ABOVE_LINE(sensors[4]))) )  || backIsready == 0);
 //while ( ( (!(ABOVE_LINE(sensors[3]) )) && (!(ABOVE_LINE(sensors[4])))  )|| (positionBack == 1));
  MotorControl(1, BACKWARD, 128);
  MotorControl(2, BACKWARD, 0);
  delay(200);
  MotorControl(1, BACKWARD, 0);
  MotorControl(2, BACKWARD, 0);
  delay(200);
  carGoReverse();
  delay(200);
}



void deliverStepTwo(Servo servo1, Servo servo2, Servo servohand, double *servo1_ang, double *servo2_ang) {
  openHand(servohand);
  delay(500);
  timerStart = millis();
  while (millis() - timerStart < 500 || (*servo1_ang > SERVO1_INIT_POS) || (*servo2_ang < SERVO2_INIT_POS)) {
    if (millis() - timerStart > 10000)
      return;

    if (*servo1_ang > SERVO1_INIT_POS ) {
      *servo1_ang -= 0.1;
      servo1.write(*servo1_ang);
    }

    if (*servo2_ang < SERVO2_INIT_POS) {
      *servo2_ang += 0.1;
      servo2.write(*servo2_ang);
    }


    while (isHigh(CARBACK_SENSOR))
    {
      carGoReverse();	
    }
  carStop();
  /*
    if (millis() - timerStart < 200) {
      carGoReverse();
    }
    else if (millis() - timerStart >= 200) {
      carStop();
    }*/
  }
  carStop();


}

void deliverStepTwo(Servo servo1, Servo servo2, double *servo1_ang, double *servo2_ang) {
    if (handStatus == HAND_CLOSED) {     //Open the claw for 1 sec to release the hand close sensor button.
    MotorControl(3, FORWARD, 255);
    delay(1500);
    MotorControl(3, FORWARD, 0);
  }
  
  timerStart = millis();
  while (millis() - timerStart < 500 || (*servo1_ang > SERVO1_INIT_POS) || (*servo2_ang < SERVO2_INIT_POS)) {
    if (millis() - timerStart > 10000)
      return;

    if (*servo1_ang > SERVO1_INIT_POS ) {
      *servo1_ang -= 0.1;
      servo1.write(*servo1_ang);
    }

    if (*servo2_ang < SERVO2_INIT_POS) {
      *servo2_ang += 0.1;
      servo2.write(*servo2_ang);
    }


    while (isHigh(CARBACK_SENSOR))
    {
      carGoReverse();	
    }
  carStop();
  /*
    if (millis() - timerStart < 200) {
      carGoReverse();
    }
    else if (millis() - timerStart >= 200) {
      carStop();
    }*/
  }
  carStop();



}
void deliverStepOne(Servo servo1, Servo servo2, double *servo1_ang, double *servo2_ang) {
  timerStart = millis();

  while (millis() - timerStart < 500 || (*servo1_ang < SERVO1_CATCH_POS) || *servo2_ang > SERVO2_CATCH_POS) {

    if (millis() - timerStart < 500) {

      carGoForward();
    }
    else if  (millis() - timerStart >= 500) {
      carStop();
    }
    
    /*
    while(isHigh(CARBACK_SENSOR))
  	{
  		carGoForward();	
  		if(millis() - timerStart > 500 ) break;
  	}
    carStop();
   */
  
    if (*servo1_ang < SERVO1_CATCH_POS) {
      *servo1_ang += 0.005;
      servo1.write(*servo1_ang);
    }

    if (*servo2_ang > SERVO2_CATCH_POS) {
      *servo2_ang -= 0.005;
      servo2.write(*servo2_ang);
    }
  }
  carStop();

}

void grabCube(Servo armServo1, Servo armServo2, Servo servohand, double *armServo1_ang, double *armServo2_ang) {
  double IR_value;
  double IR_temp = 0;


  while (analogRead(HEAD_SENSORPIN) < 950) {
    carGoReverse();
  }
  carStop();
  lowerArm(armServo1, armServo2, armServo1_ang, armServo2_ang);
  IR_value = analogRead(HEAD_SENSORPIN);
  Serial.print("CUBE range is :");
  Serial.println(IR_value);

  timerStart = millis();
  //while (IR_value > CATCH_RANGE && IR_value < CUBE_SEEN_RANGE) { //If the cube is too far from the mechinical arm, adjust the car position
  while (IR_value > CATCH_RANGE) { //If the cube is too far from the mechinical arm, adjust the car position
    if (millis() - timerStart > 500) {
      break;
    }
    else
      carGoForward();
      Serial.println("Going forward!");
      
    for (int i = 0; i < 1; i++) {
      IR_temp += analogRead(HEAD_SENSORPIN);
    }

    IR_value = IR_temp / 1;
    IR_temp = 0;
    //Serial.print("CUBE range is :");
    //Serial.println(IR_value);
  }
  IR_temp = 0;
  timerStart = millis();
  while (IR_value < CATCH_RANGE) {  //If the cube is too close or too far from the mechinical arm, adjust the car position
    if (millis() - timerStart > 500)
      break;
    else
      carGoReverse();

    for (int j = 0; j < 10; j++) {
      IR_temp += analogRead(HEAD_SENSORPIN);
    }
    IR_value = IR_temp / 10;
    IR_temp = 0;

  }
  carStop();

  for (int x = 0; x < 5; x++) {
    MotorControl(1, FORWARD, 200);
    MotorControl(2, FORWARD, 200);
    delay(60);
    MotorControl(1, BACKWARD, 200);
    MotorControl(2, BACKWARD, 200);
    delay(60);
  }
  carStop();

  //  IR_value = analogRead(HEAD_SENSORPIN);
  //  IR_temp = 0;
  timerStart = millis();
  while (IR_value > CATCH_RANGE && IR_value < CUBE_SEEN_RANGE) { //If the cube is too far from the mechinical arm, adjust the car position
    if (millis() - timerStart > 500) {
      break;
    }
    else
      carGoForward();
    for (int i = 0; i < 10; i++) {
      IR_temp += analogRead(HEAD_SENSORPIN);
    }

    IR_value = IR_temp / 10;
    IR_temp = 0;

  }
  carStop();
  closeHand(servohand);

  if (analogRead(HEAD_SENSORPIN) > CATCH_RANGE)
    openHand(servohand);
  
  timerStart = millis();
  while (analogRead(HEAD_SENSORPIN) > CATCH_RANGE) {
  	if (millis() - timerStart > 500) {
      break;
    }
    carGoForward();
  }
  carStop();

  closeHand(servohand);
}

void grabCube(Servo armServo1, Servo armServo2, double *armServo1_ang, double *armServo2_ang) {
  double IR_value;
  double IR_temp = 0;


  while (analogRead(HEAD_SENSORPIN) < 950) {
    carGoReverse();
  }
  carStop();
  lowerArm(armServo1, armServo2, armServo1_ang, armServo2_ang);
  IR_value = analogRead(HEAD_SENSORPIN);
  Serial.print("CUBE range is :");
  Serial.println(IR_value);

  timerStart = millis();
  //while (IR_value > CATCH_RANGE && IR_value < CUBE_SEEN_RANGE) { //If the cube is too far from the mechinical arm, adjust the car position
  while (IR_value > CATCH_RANGE) { //If the cube is too far from the mechinical arm, adjust the car position
    if (millis() - timerStart > 500) {
      break;
    }
    else
      carGoForward();
      Serial.println("Going forward!");
      
    for (int i = 0; i < 1; i++) {
      IR_temp += analogRead(HEAD_SENSORPIN);
    }

    IR_value = IR_temp / 1;
    IR_temp = 0;
    //Serial.print("CUBE range is :");
    //Serial.println(IR_value);
  }
  IR_temp = 0;
  timerStart = millis();
  while (IR_value < CATCH_RANGE) {  //If the cube is too close or too far from the mechinical arm, adjust the car position
    if (millis() - timerStart > 500)
      break;
    else
      carGoReverse();

    for (int j = 0; j < 10; j++) {
      IR_temp += analogRead(HEAD_SENSORPIN);
    }
    IR_value = IR_temp / 10;
    IR_temp = 0;

  }
  carStop();



  //  IR_value = analogRead(HEAD_SENSORPIN);
  //  IR_temp = 0;
  timerStart = millis();
  while (IR_value > CATCH_RANGE && IR_value < CUBE_SEEN_RANGE) { //If the cube is too far from the mechinical arm, adjust the car position
    if (millis() - timerStart > 500) {
      break;
    }
    else
      carGoForward();
    for (int i = 0; i < 10; i++) {
      IR_temp += analogRead(HEAD_SENSORPIN);
    }

    IR_value = IR_temp / 10;
    IR_temp = 0;

  }
  carStop();
  closeHand();

  if (analogRead(HEAD_SENSORPIN) > CATCH_RANGE)
    openHand();

  timerStart = millis();
  while (analogRead(HEAD_SENSORPIN) > CATCH_RANGE) {
  	if (millis() - timerStart > 500) {
      break;
    }
    carGoForward();
  }
  carStop();

  closeHand();
}


void deliverCube(Servo armServo1, Servo armServo2, Servo headServo, Servo handServo, int *headServoDirection, double *armServo1_ang, double *armServo2_ang) {
  Serial.end();
  if (return_color == 1) {
    TurnLeft90();
  }
  else  {  //if (return_color == 2 || return_color == 3) {
    TurnRight90();
  }


  //Serial.begin(115200);

  deliverStepOne(armServo1, armServo2, armServo1_ang, armServo2_ang);

  //Serial.println("1111111111111111111111111111111");
  deliverStepTwo(armServo1, armServo2, handServo, armServo1_ang, armServo2_ang);
  //Serial.println("2222222222222222222222222222222");
  //Serial.end();
   headServo.write(HEADSENSOR_MIDDLE_POS - HEADSERVO_RANGE);
  if (return_color == 1) {
    TurnLeft90_returnToMiddle();
  }
  else { // if (return_color == 2 || return_color == 3) {
    TurnRight90_returnToMiddle();
  }


  AutoRun_State = INIT_STATE;
  *headServoDirection = POSITIVE;
  Serial.begin(115200);
}

void deliverCube(Servo armServo1, Servo armServo2, Servo headServo, int *headServoDirection, double *armServo1_ang, double *armServo2_ang) {
  Serial.end();
  if (return_color == 1) {
    TurnLeft90();
  }
  else  {  //if (return_color == 2 || return_color == 3) {
    TurnRight90();
  }



  deliverStepOne(armServo1, armServo2, armServo1_ang, armServo2_ang);


  deliverStepTwo(armServo1, armServo2, armServo1_ang, armServo2_ang);
  delay(1000);

   headServo.write(HEADSENSOR_MIDDLE_POS - HEADSERVO_RANGE);
  if (return_color == 1) {
    TurnLeft90_returnToMiddleMotorClaw();
  }
  else { // if (return_color == 2 || return_color == 3) {
    TurnRight90_returnToMiddleMotorClaw();
  }


  AutoRun_State = INIT_STATE;
  *headServoDirection = POSITIVE;
  Serial.begin(115200);
}

void cubeSearchingHalfCycle(double *head_pos, int *moving_direction, Servo head_servo, int currentState, double searchingMiddlePos, double searchingRange) {
  Serial.println(*moving_direction);
  carStop();

  bool AllowSearching;
  bool startingEdgeFound;
  bool cubeFound;
  AllowSearching = true;
  bool wholeCycle = false;
  double startingEdge;
  double endEdge;
  int lastIR_value;
  int currentIR_value;
  int IR_diff;
  double searchingStartPos;
  double searchingEndPos;

  startingEdgeFound = false;
  cubeFound = false;



  if (*moving_direction == POSITIVE) {    //initialize the starting edge and end edge as the starting postion of the end position of the half searching cycle
//    Serial.println("Searching POSITIVE");
    searchingStartPos = searchingMiddlePos - searchingRange;
    searchingEndPos   = searchingMiddlePos + searchingRange;
    if (searchingStartPos <= (HEADSENSOR_MIDDLE_POS - HEADSERVO_RANGE)) {
      Serial.println("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
      startingEdge = HEADSENSOR_MIDDLE_POS - HEADSERVO_RANGE;
      searchingStartPos = HEADSENSOR_MIDDLE_POS - HEADSERVO_RANGE;
    }
    else
      startingEdge = searchingMiddlePos - searchingRange;


    if (searchingEndPos >= (HEADSENSOR_MIDDLE_POS + HEADSERVO_RANGE)) {
      endEdge = HEADSENSOR_MIDDLE_POS + HEADSERVO_RANGE;
      searchingEndPos = HEADSENSOR_MIDDLE_POS + HEADSERVO_RANGE;
    }
    else
      endEdge = searchingMiddlePos + searchingRange;     //initialize both starting edge and end edge

  }
  else if ((*moving_direction) == NEGATIVE) {
//    Serial.println("Searching NEGATIVE");
    searchingStartPos = searchingMiddlePos + searchingRange;
    searchingEndPos   = searchingMiddlePos - searchingRange;
    if (searchingStartPos >= (HEADSENSOR_MIDDLE_POS + HEADSERVO_RANGE)) {
      startingEdge = HEADSENSOR_MIDDLE_POS + HEADSERVO_RANGE;
      searchingStartPos = HEADSENSOR_MIDDLE_POS + HEADSERVO_RANGE;
    }
    else
      startingEdge = searchingMiddlePos + searchingMiddlePos;

    if (searchingEndPos <= (HEADSENSOR_MIDDLE_POS - HEADSERVO_RANGE)) {
      endEdge = HEADSENSOR_MIDDLE_POS - HEADSERVO_RANGE;
      searchingEndPos = HEADSENSOR_MIDDLE_POS - HEADSERVO_RANGE;
    }
    else
      endEdge = searchingMiddlePos - searchingRange;     //initialize both starting edge and end edge

  }

  *head_pos = searchingStartPos;

  while (AllowSearching) {

    currentIR_value = analogRead(HEAD_SENSORPIN);
    //    Serial.print("Searching Cube and its current distance is :");
    //    Serial.println(currentIR_value);
    if (currentIR_value <= CUBE_SEEN_RANGE && startingEdgeFound == false) {
      startingEdge = *head_pos;            //record the starting edge
      startingEdgeFound = true;

//      Serial.println("CUBE STARTING SEEN!!!!!!!!!");
    }
    else if (currentIR_value > CUBE_SEEN_RANGE) {
      if (startingEdgeFound) {
        endEdge = *head_pos;

        if (abs(endEdge - startingEdge) > 8) {   // To avoid some sparks during searching. Only when the cube width is greater than 4 degrees, we consider a cube is found
          cubeFound = true;
          AllowSearching = false;

          if (currentState == INIT_STATE)
            AutoRun_State = CATCH_STATE;
//          Serial.println("CUBE END SEEN!!!!!!!!!");

          break;
        }
        else {
          startingEdgeFound = false;
        }
      }
    }

    if ((*moving_direction) == POSITIVE) {
      (*head_pos) += 0.01;//0.5;
      if ((*head_pos) >= searchingEndPos) {    //change from 180 degree to 150 degree
        (*head_pos) = searchingEndPos;
        (*moving_direction) = NEGATIVE;
        AllowSearching = false;   //half cycle completed
      }
    }
    else if ((*moving_direction) == NEGATIVE) {
      (*head_pos) -= 0.01;
      if ((*head_pos) <= searchingEndPos) {  //change from 0 degree to 20 degree
        (*head_pos) = searchingEndPos;
        (*moving_direction) = POSITIVE;
        AllowSearching = false;   //half cycle completed
      }
    }

    head_servo.write((*head_pos));
    //    delay(10);
  }

  if (cubeFound) {
    *head_pos = (startingEdge + endEdge) / 2;   // Locate the head servo to the middle of the cube(middle of two edges found)
    head_servo.write((*head_pos));
    delay(100);
  }
  else if (!cubeFound && currentState == CATCH_STATE) {
    carGoForward();
    delay(100);
    carStop();
  }
}



void catchingCube(int *head_moving_direction, double *headSensor_pos, Servo headServo, Servo armServo1, Servo armServo2, Servo handServo, double *ang_arm1, double *ang_arm2) {
  Serial.println("Catching Start....");
  double cubeStartEdge;
  double cubeEndEdge;
  double currentAngle;
  double cubeDistance;

  int searchingDirection = POSITIVE;
  timerStart = millis();
  while ((*headSensor_pos <= HEADSENSOR_MIDDLE_POS - CAP_RANGE) ||  (*headSensor_pos >= HEADSENSOR_MIDDLE_POS + CAP_RANGE)) {   //Loop run to adjust the car body to make sure the mechinal arm face the cube
    if (millis() - timerStart > 15000) {      //If it takes more than 10 sec to adjust the car, return to the state of line following
      cubeMissed = true;
      carReturn();    //return to the init state
      return;
    }
    cubeDistance = analogRead(HEAD_SENSORPIN);
    if (cubeDistance < CUBE_SEEN_RANGE ) {     //CUBE_SEEN_RANGE = 950
      while (analogRead(HEAD_SENSORPIN) < 100 ) {   //if the sensor is too close to the cube, back off
        carGoReverse();
      }

//      Serial.print("Current distance is: ");
//      Serial.println(cubeDistance);
      if (*headSensor_pos <= HEADSENSOR_MIDDLE_POS - CAP_RANGE) {
        Serial.println("Turning Left......");
        carLeftTurn();
        headServoField = 1;
      }
      else if (*headSensor_pos >= HEADSENSOR_MIDDLE_POS + CAP_RANGE) {
        Serial.println("Turning Right......");
        carRightTurn();
        headServoField = -1;
      }
      *headSensor_pos += 0.05 * headServoField;  //Since the car is turning towards the cube, if the servo keep still, it will miss the cube. So the servo should turn in the opposite direction of the car body.
      headServo.write(*headSensor_pos);
    }
    else { //If the car turns too much, the servo sensor may miss the cube. In this case, the car stops turning and the servo turns to find the cube again.
      Serial.println("CUBE MISSED..............");
      carStop();
      currentAngle = *headSensor_pos;
      Serial.println(currentAngle);
      *headSensor_pos = currentAngle;   //If the cube is lost, start to search it again from 20 degree the left of where it is lost.

      cubeSearchingHalfCycle(headSensor_pos, head_moving_direction, headServo, CATCH_STATE, currentAngle, 10);
    }

  }

  /*
  cubeSearchingHalfCycle(headSensor_pos, head_moving_direction, headServo, CATCH_STATE, HEADSENSOR_MIDDLE_POS, 20);  //Adjust to fine tune the car to make the sensor face the middle of the cube
  while ((*headSensor_pos <= HEADSENSOR_MIDDLE_POS - CAP_RANGE) ||  (*headSensor_pos >= HEADSENSOR_MIDDLE_POS + CAP_RANGE)) {
    if (*headSensor_pos <= HEADSENSOR_MIDDLE_POS - CAP_RANGE) {
      Serial.println("Turning Left......");
      carLeftTurn();
      headServoField = 1;
    }
    else if (*headSensor_pos >= HEADSENSOR_MIDDLE_POS + CAP_RANGE) {
      Serial.println("Turning Right......");
      carRightTurn();
      headServoField = -1;
    }
    *headSensor_pos += 0.05 * headServoField;  //Since the car is turning towards the cube, if the servo keep still, it will miss the cube. So the servo should turn in the opposite direction of the car body.
    headServo.write(*headSensor_pos);

    if (analogRead(HEAD_SENSORPIN) > CUBE_SEEN_RANGE)
      cubeSearchingHalfCycle(headSensor_pos, head_moving_direction, headServo, CATCH_STATE, HEADSENSOR_MIDDLE_POS, 20);
  }
  */
  
  //carGoForward();
  //delay(50);
  timerStart = millis();
  do {
  	carLeftTurn();
  	Serial.print("Tuning left......");
  	cubeDistance = analogRead(HEAD_SENSORPIN);
  	Serial.println(cubeDistance);
  	delay(10);
  } while (cubeDistance <= CUBE_SEEN_RANGE+20);
  carStop();
  do {
  	carRightTurn();
  	Serial.print("Tuning right back......");
  	cubeDistance = analogRead(HEAD_SENSORPIN);
  	Serial.println(cubeDistance);
  	delay(10);
  }while (cubeDistance > CUBE_SEEN_RANGE);
  
  
  timerStart = millis();
  do {
  	carRightTurn();
  	Serial.print("Tuning right......");
  	cubeDistance = analogRead(HEAD_SENSORPIN);
  	Serial.println(cubeDistance);
  	delay(10);
  }while (cubeDistance <= CUBE_SEEN_RANGE);
  
  double timeDelay = millis() - timerStart;
  
  carLeftTurn();
  delay(timeDelay/3);
              
  carStop();



  if ((*headSensor_pos > HEADSENSOR_MIDDLE_POS - CAP_RANGE) &&  (*headSensor_pos < HEADSENSOR_MIDDLE_POS + CAP_RANGE)) {   //Check whether the mechanical arm is facing the cube or not
    carStop();
    grabCube(armServo1, armServo2, handServo, ang_arm1, ang_arm2);
    readCubeColor();
    armUp(armServo1, armServo2, ang_arm1, ang_arm2);
    AutoRun_State = DELIVER_STATE;
  }
}


void catchingCube(int *head_moving_direction, double *headSensor_pos, Servo headServo, Servo armServo1, Servo armServo2, double *ang_arm1, double *ang_arm2) {
  Serial.println("Catching Start....");
  double cubeStartEdge;
  double cubeEndEdge;
  double currentAngle;
  double cubeDistance;

  int searchingDirection = POSITIVE;
  timerStart = millis();
  while ((*headSensor_pos <= HEADSENSOR_MIDDLE_POS - CAP_RANGE) ||  (*headSensor_pos >= HEADSENSOR_MIDDLE_POS + CAP_RANGE)) {   //Loop run to adjust the car body to make sure the mechinal arm face the cube
    if (millis() - timerStart > 15000) {      //If it takes more than 10 sec to adjust the car, return to the state of line following
      cubeMissed = true;
      carReturn();    //return to the init state
      return;
    }
    cubeDistance = analogRead(HEAD_SENSORPIN);
    if (cubeDistance < CUBE_SEEN_RANGE ) {     //CUBE_SEEN_RANGE = 950
      while (analogRead(HEAD_SENSORPIN) < 100 ) {   //if the sensor is too close to the cube, back off
        carGoReverse();
      }

//      Serial.print("Current distance is: ");
//      Serial.println(cubeDistance);
      if (*headSensor_pos <= HEADSENSOR_MIDDLE_POS - CAP_RANGE) {
        Serial.println("Turning Left......");
        carLeftTurn();
        headServoField = 1;
      }
      else if (*headSensor_pos >= HEADSENSOR_MIDDLE_POS + CAP_RANGE) {
        Serial.println("Turning Right......");
        carRightTurn();
        headServoField = -1;
      }
      *headSensor_pos += 0.05 * headServoField;  //Since the car is turning towards the cube, if the servo keep still, it will miss the cube. So the servo should turn in the opposite direction of the car body.
      headServo.write(*headSensor_pos);
    }
    else { //If the car turns too much, the servo sensor may miss the cube. In this case, the car stops turning and the servo turns to find the cube again.
      Serial.println("CUBE MISSED..............");
      carStop();
      currentAngle = *headSensor_pos;
      Serial.println(currentAngle);
      *headSensor_pos = currentAngle;   //If the cube is lost, start to search it again from 20 degree the left of where it is lost.

      cubeSearchingHalfCycle(headSensor_pos, head_moving_direction, headServo, CATCH_STATE, currentAngle, 10);
    }

  }
  /*
  cubeSearchingHalfCycle(headSensor_pos, head_moving_direction, headServo, CATCH_STATE, HEADSENSOR_MIDDLE_POS, 20);  //Adjust to fine tune the car to make the sensor face the middle of the cube
  while ((*headSensor_pos <= HEADSENSOR_MIDDLE_POS - CAP_RANGE) ||  (*headSensor_pos >= HEADSENSOR_MIDDLE_POS + CAP_RANGE)) {
    if (*headSensor_pos <= HEADSENSOR_MIDDLE_POS - CAP_RANGE) {
      Serial.println("Turning Left......");
      carLeftTurn();
      headServoField = 1;
    }
    else if (*headSensor_pos >= HEADSENSOR_MIDDLE_POS + CAP_RANGE) {
      Serial.println("Turning Right......");
      carRightTurn();
      headServoField = -1;
    }
    *headSensor_pos += 0.05 * headServoField;  //Since the car is turning towards the cube, if the servo keep still, it will miss the cube. So the servo should turn in the opposite direction of the car body.
    headServo.write(*headSensor_pos);

    if (analogRead(HEAD_SENSORPIN) > CUBE_SEEN_RANGE)
      cubeSearchingHalfCycle(headSensor_pos, head_moving_direction, headServo, CATCH_STATE, HEADSENSOR_MIDDLE_POS, 20);
  }
  */

  timerStart = millis();
  do {
  	carLeftTurn();
  	Serial.print("Tuning left......");
  	cubeDistance = analogRead(HEAD_SENSORPIN);
  	Serial.println(cubeDistance);
  	delay(10);
  } while (cubeDistance <= CUBE_SEEN_RANGE+20);
  carStop();
  do {
  	carRightTurn();
  	Serial.print("Tuning right back......");
  	cubeDistance = analogRead(HEAD_SENSORPIN);
  	Serial.println(cubeDistance);
  	delay(10);
  }while (cubeDistance > CUBE_SEEN_RANGE);
  
  
  timerStart = millis();
  do {
  	carRightTurn();
  	Serial.print("Tuning right......");
  	cubeDistance = analogRead(HEAD_SENSORPIN);
  	Serial.println(cubeDistance);
  	delay(10);
  }while (cubeDistance <= CUBE_SEEN_RANGE);
  
  double timeDelay = millis() - timerStart;
  
  carLeftTurn();
  delay(timeDelay/3);
              
  carStop();



  if ((*headSensor_pos > HEADSENSOR_MIDDLE_POS - CAP_RANGE) &&  (*headSensor_pos < HEADSENSOR_MIDDLE_POS + CAP_RANGE)) {   //Check whether the mechanical arm is facing the cube or not
    carStop();
    grabCube(armServo1, armServo2, ang_arm1, ang_arm2);
    readCubeColor();
    armUp(armServo1, armServo2, ang_arm1, ang_arm2);
    AutoRun_State = DELIVER_STATE;
  }
}


void AutoModeSetup(Servo headServo, Servo armServo1, Servo armServo2, Servo handServo, double *headServoPos, double *armServo1_ang, double *armServo2_ang, int *headServoDirection)
{
  pinAsOutput(MOTOR1P);
  pinAsOutput(MOTOR1M);
  pinAsOutput(MOTOR2P);
  pinAsOutput(MOTOR2M);
  pinAsOutput(MOTOR3P);
  pinAsOutput(MOTOR3M);
  pinAsOutput(MOTOR4P);
  pinAsOutput(MOTOR4M);

  *armServo1_ang = SERVO1_INIT_POS;
  *armServo2_ang = SERVO2_INIT_POS;
  armServo1.write(*armServo1_ang);
  armServo2.write(*armServo2_ang);

  pinAsInput(HEAD_SENSORPIN);
  pinAsInput(ZW_A2);
  AutoRun_State = INIT_STATE;
  *headServoPos = HEADSENSOR_MIDDLE_POS - HEADSERVO_RANGE;
  //*headServoPos = HEADSENSOR_MIDDLE_POS;
  *headServoDirection = POSITIVE;
  //  headServo.attach(ZW_B1);
  headServo.write(*headServoPos);   //Searching from most left

  tcs74725_init();
  LineFollower._CAL_MAX_[0] = 2000;//,2000,2000,2000,2000,2000,2000,2000};
  LineFollower._CAL_MIN_[0] = 324;//,324,296,332,372,544,496,620};
  LineFollower._CAL_MAX_[1] = 2000;//,2000,2000,2000,2000,2000,2000,2000};
  LineFollower._CAL_MIN_[1] = 324;//,324,296,332,372,544,496,620};
  LineFollower._CAL_MAX_[2] = 2000;//,2000,2000,2000,2000,2000,2000,2000};
  LineFollower._CAL_MIN_[2] = 296;//,324,296,332,372,544,496,620};
  LineFollower._CAL_MAX_[3] = 2000;//,2000,2000,2000,2000,2000,2000,2000};
  LineFollower._CAL_MIN_[3] = 332;//,324,296,332,372,544,496,620};
  LineFollower._CAL_MAX_[4] = 2000;//,2000,2000,2000,2000,2000,2000,2000};
  LineFollower._CAL_MIN_[4] = 372;//,324,296,332,372,544,496,620};
  LineFollower._CAL_MAX_[5] = 2000;//,2000,2000,2000,2000,2000,2000,2000};
  LineFollower._CAL_MIN_[5] = 544;//,324,296,332,372,544,496,620};
  LineFollower._CAL_MAX_[6] = 2000;//,2000,2000,2000,2000,2000,2000,2000};
  LineFollower._CAL_MIN_[6] = 496;//,324,296,332,372,544,496,620};
  LineFollower._CAL_MAX_[7] = 2000;//,2000,2000,2000,2000,2000,2000,2000};
  LineFollower._CAL_MIN_[7] = 620;//,324,296,332,372,544,496,620};
  LineFollower.begin();

  handServo.write(HANDOPEN_ANG);


}

void AutoModeSetup(Servo headServo, Servo armServo1, Servo armServo2, double *headServoPos, double *armServo1_ang, double *armServo2_ang, int *headServoDirection)
{
  pinAsOutput(MOTOR1P);
  pinAsOutput(MOTOR1M);
  pinAsOutput(MOTOR2P);
  pinAsOutput(MOTOR2M);
  pinAsOutput(MOTOR3P);
  pinAsOutput(MOTOR3M);
  pinAsOutput(MOTOR4P);
  pinAsOutput(MOTOR4M);
  
  
  *armServo1_ang = SERVO1_INIT_POS;
  *armServo2_ang = SERVO2_INIT_POS;
  armServo1.write(*armServo1_ang);
  armServo2.write(*armServo2_ang);

  pinAsInput(HEAD_SENSORPIN);
  pinAsInput(ZW_A2);
  pinAsInput(ZW_B4);
  AutoRun_State = INIT_STATE;
  *headServoPos = HEADSENSOR_MIDDLE_POS - HEADSERVO_RANGE;
  *headServoDirection = POSITIVE;
 
  headServo.write(*headServoPos);   //Searching from most left

  handStatus = HAND_CLOSED;
  openHand();
  
  tcs74725_init();
  LineFollower._CAL_MAX_[0] = 2000;//,2000,2000,2000,2000,2000,2000,2000};
  LineFollower._CAL_MIN_[0] = 324;//,324,296,332,372,544,496,620};
  LineFollower._CAL_MAX_[1] = 2000;//,2000,2000,2000,2000,2000,2000,2000};
  LineFollower._CAL_MIN_[1] = 324;//,324,296,332,372,544,496,620};
  LineFollower._CAL_MAX_[2] = 2000;//,2000,2000,2000,2000,2000,2000,2000};
  LineFollower._CAL_MIN_[2] = 296;//,324,296,332,372,544,496,620};
  LineFollower._CAL_MAX_[3] = 2000;//,2000,2000,2000,2000,2000,2000,2000};
  LineFollower._CAL_MIN_[3] = 332;//,324,296,332,372,544,496,620};
  LineFollower._CAL_MAX_[4] = 2000;//,2000,2000,2000,2000,2000,2000,2000};
  LineFollower._CAL_MIN_[4] = 372;//,324,296,332,372,544,496,620};
  LineFollower._CAL_MAX_[5] = 2000;//,2000,2000,2000,2000,2000,2000,2000};
  LineFollower._CAL_MIN_[5] = 544;//,324,296,332,372,544,496,620};
  LineFollower._CAL_MAX_[6] = 2000;//,2000,2000,2000,2000,2000,2000,2000};
  LineFollower._CAL_MIN_[6] = 496;//,324,296,332,372,544,496,620};
  LineFollower._CAL_MAX_[7] = 2000;//,2000,2000,2000,2000,2000,2000,2000};
  LineFollower._CAL_MIN_[7] = 620;//,324,296,332,372,544,496,620};
  LineFollower.begin();





}


void autoModeRun(Servo headServo, Servo armServo1, Servo armServo2, Servo handServo, double *headServoPos, double *armServo1_ang, double *armServo2_ang, int *headServoDirection)
{

  switch (AutoRun_State) {
    case INIT_STATE:

      followSegment();
      
      if (millis() - AutoModeStartTime < AUTOGRAB_TIME * 1000) 
        cubeSearchingHalfCycle(headServoPos, headServoDirection, headServo, INIT_STATE, HEADSENSOR_MIDDLE_POS, HEADSERVO_RANGE);

      break;

    case CATCH_STATE:
      Serial.println("CATCH STATE.................");
      catchingCube(headServoDirection, headServoPos, headServo, armServo1, armServo2, handServo, armServo1_ang, armServo2_ang);
      break;

    case DELIVER_STATE:
      deliverCube(armServo1, armServo2, headServo, handServo,headServoDirection, armServo1_ang, armServo2_ang);
      break;

    case IDLE_STATE:
      break;
  }
}

void autoModeRun(Servo headServo, Servo armServo1, Servo armServo2, double *headServoPos, double *armServo1_ang, double *armServo2_ang, int *headServoDirection)
{

  switch (AutoRun_State) {
    case INIT_STATE:

      followSegment();

      if (millis() - AutoModeStartTime < AUTOGRAB_TIME * 1000)
        cubeSearchingHalfCycle(headServoPos, headServoDirection, headServo, INIT_STATE, HEADSENSOR_MIDDLE_POS, HEADSERVO_RANGE);

      break;

    case CATCH_STATE:
      Serial.println("CATCH STATE.................");
      catchingCube(headServoDirection, headServoPos, headServo, armServo1, armServo2, armServo1_ang, armServo2_ang);
      break;

    case DELIVER_STATE:
      deliverCube(armServo1, armServo2, headServo, headServoDirection, armServo1_ang, armServo2_ang);
      break;

    case IDLE_STATE:
      break;
  }
}

void parameterDefinition(double armLowerServo_initPos,  double armLowerServo_catchPos, 
                         double armHigherServo_initPos, double armHigherServo_catchPos, 
                         double handServo_openPos,      double handServo_closePos, 
                         double headServo_midPos,       double headServo_Range,
                         double userDefined_grabTime) {
 /*                        	
  arm1_init_pos = armLowerServo_initPos;
  arm2_init_pos = armHigherServo_initPos;     
  arm1_catch_pos = armLowerServo_catchPos;
  arm2_catch_pos = armHigherServo_catchPos;      
  hand_open_pos = handServo_openPos;
  hand_close_pos = handServo_closePos;
  head_mid_pos = headServo_midPos;
  head_range =   headServo_Range;
*/
  SERVO1_CATCH_POS = armLowerServo_catchPos;
  SERVO2_CATCH_POS = armHigherServo_catchPos;
  SERVO1_INIT_POS  = armLowerServo_initPos;
  SERVO2_INIT_POS  = armHigherServo_initPos;

  HANDOPEN_ANG     = handServo_openPos;
  HANDCLOSE_ANG    = handServo_closePos;
  HEADSENSOR_MIDDLE_POS = headServo_midPos;
  HEADSERVO_RANGE       = headServo_Range;
  
  AUTOGRAB_TIME = userDefined_grabTime; 
                         	
  Serial.print("SERVO1_CATCH_POS = ");
  Serial.println(SERVO1_CATCH_POS);  
                      	
} 

void parameterDefinition(double armLowerServo_initPos,  double armLowerServo_catchPos, 
                         double armHigherServo_initPos, double armHigherServo_catchPos, 
                         double headServo_midPos,       double headServo_Range,
                         double userDefined_grabTime) {
 /*                        	
  arm1_init_pos = armLowerServo_initPos;
  arm2_init_pos = armHigherServo_initPos;     
  arm1_catch_pos = armLowerServo_catchPos;
  arm2_catch_pos = armHigherServo_catchPos;      
  hand_open_pos = handServo_openPos;
  hand_close_pos = handServo_closePos;
  head_mid_pos = headServo_midPos;
  head_range =   headServo_Range;
*/
  SERVO1_CATCH_POS = armLowerServo_catchPos;
  SERVO2_CATCH_POS = armHigherServo_catchPos;
  SERVO1_INIT_POS  = armLowerServo_initPos;
  SERVO2_INIT_POS  = armHigherServo_initPos;

  HEADSENSOR_MIDDLE_POS = headServo_midPos;
  HEADSERVO_RANGE       = headServo_Range;
                         	
  AUTOGRAB_TIME = userDefined_grabTime;                     	
} 


void T3_colorSetup() {
Serial.begin(115200);
         pinMode(ZW_A1,INPUT);
         pinMode(ZW_B1,OUTPUT);

            rgb.red = 0;
            rgb.red_min = 255;
            rgb.red_max = 0;
            rgb.green = 0;
            rgb.green_min = 255;
            rgb.green_max = 0;
            rgb.blue = 0;
            rgb.blue_min = 255;
            rgb.blue_max = 0;
         if (tcs.begin()) {
           Serial.println("Sensor founded!");
         } else {
           Serial.println("TCS34725 is not available, please try check it !");
           while (1);
         }

         tcs.setInterrupt(false);
         digitalWrite(ZW_B1,HIGH);

     if(CALIBRATION_COLOR)
     {
          Serial.println("=======================================================================");
          Serial.println("Please follow bellow steps to calibration those colors.");
          Serial.println("Step 1: Read the color of surronding.");
          Serial.println("	  Please keep nothing and try to adjust the position of the sensor, then press button A1.");
          Serial.print  ("	  Please do the same steps and try "); Serial.print(COLOR_CALIBRATION_TIMES); Serial.println(" times at least.");
          Serial.println("	  Please press button A2 when finished. it will save the surrounding color data to EEPROM.");
     }
     else
     {
           for(int i = 0; i< COLOR_NUM_MAX; i++)
           {
           int COLOR_START_POS;
           COLOR_START_POS  =COLOR1_START_POS +  i * COLOR_LENGTH;
           EEPROM.get(COLOR_START_POS,RGB_STORE_DATA[i]);
           Serial.print("Read Color "); Serial.print(i);Serial.print(" data from EEPROM ");Serial.print(COLOR_START_POS); Serial.print(":	");
           Serial.print(" red:"); Serial.print(RGB_STORE_DATA[i].red, DEC); Serial.print(":");Serial.print(RGB_STORE_DATA[i].red_max, DEC); Serial.print(":");Serial.print(RGB_STORE_DATA[i].red_min, DEC);
           Serial.print(" green:");Serial.print(RGB_STORE_DATA[i].green, DEC);Serial.print(":"); Serial.print(RGB_STORE_DATA[i].green_max, DEC); Serial.print(":");Serial.print(RGB_STORE_DATA[i].green_min, DEC);
           Serial.print(" blue:"); Serial.print(RGB_STORE_DATA[i].blue, DEC);Serial.print(":");Serial.print(RGB_STORE_DATA[i].blue_max, DEC); Serial.print(":");Serial.print(RGB_STORE_DATA[i].blue_min, DEC);
           Serial.println("");
     }
     }


}
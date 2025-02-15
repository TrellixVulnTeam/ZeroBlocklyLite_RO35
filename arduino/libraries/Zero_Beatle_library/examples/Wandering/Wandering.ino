#include <Beatle.h>

Beatle beatle;


void setup() {
  // put your setup code here, to run once:
	Serial.begin(115200);
  pinMode(DSL,INPUT);
  pinMode(DSR,INPUT);
  beatle.motors.flipLeftMotor(true);
  beatle.LineSensors.init();
  randomSeed((unsigned int) millis());
	
  beatle.StartProgram();
 
}

void loop() {
  // put your main code here, to run repeatedly:
		int idx;
		int move_time;
		int speed;
		int left_value,right_value;
		int border_detect = 0;
		int obstacle_detect = 0;

    unsigned int sensor_values[7];

    //Generate random direction , moving time  and speed		
		idx = random(1,9);
		move_time = random(400,2000);
		speed = random(80,255);
		Serial.print("idx = ");Serial.println(idx);
		Serial.print("speed = ");Serial.println(speed);
		Serial.print("move_time = ");Serial.println(move_time);
	
		unsigned long time_startA;
		time_startA = millis();
		while(millis() - time_startA < move_time)
		{	
			left_value = digitalRead(DSL);
			right_value = digitalRead(DSR);
			
			beatle.LineSensors.read(sensor_values);
			Serial.print(left_value); Serial.print("\t");Serial.print(right_value);Serial.print("\t");
			for(int i = 0; i<7; i++)
			{
				Serial.print(sensor_values[i]); Serial.print("\t");
				
			}
			
			Serial.print("idx = "); Serial.println(idx);
			if(left_value ==0 && right_value == 0)
			{
					idx = BACKWARD;
			}
			else if(left_value == 0)
			{
					idx = LEFT_BACK;
			}		
			else if (right_value == 0 )
			{
					idx = RIGHT_BACK;
			}
			
			if(sensor_values[0]>1500 && sensor_values[6]>1500)
			{
					idx = BACKWARD;
			}
			else if(sensor_values[0]>1500)
			{
					idx = LEFT_BACK;
			}		
			else if (sensor_values[6]>1500 )
			{
					idx = RIGHT_BACK;
			}
				
				Serial.print("idx = "); Serial.println(idx);
			
			switch(idx)
			{	
				case FORWARD:
					beatle.motors.setSpeeds(speed,speed);
					break;		
				case FORWARD_LEFT:
					beatle.motors.setSpeeds(0,speed);
					break;
				case LEFT:
					beatle.motors.setSpeeds(-speed,speed);
					break;
				case FORWARD_RIGHT:
					beatle.motors.setSpeeds(speed,0);
					break;
				case RIGHT:
					beatle.motors.setSpeeds(speed,-speed);
					break;
				case LEFT_BACK:
					beatle.motors.setSpeeds(-speed,0);
					break;
				case BACKWARD:
					beatle.motors.setSpeeds(-speed,-speed);
					break;
				case RIGHT_BACK:
					beatle.motors.setSpeeds(0,-speed);
					break;
				case STOP:
					beatle.motors.setSpeeds(0,0);
					break;				
			}	
		
		}
}

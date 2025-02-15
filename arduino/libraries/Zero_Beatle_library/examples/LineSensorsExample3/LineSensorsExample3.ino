#include <Beatle.h>
Beatle beatle;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  beatle.motors.flipLeftMotor(true);
  beatle.StartProgram();
  beatle.setDebugLevel(1);
  beatle.led.colorAll(beatle.led.strip.Color(0,0,255));
  delay(500);
  beatle.LineSensorCalibration(true,128,20);
 
  beatle.button.waitForButton();
  // Play music and wait for it to finish before we start driving.
  beatle.buzzer.play("L16 cdegreg4");
  while(beatle.buzzer.isPlaying());  
}

void loop() {
  // put your main code here, to run repeatedly:
 	unsigned int sensors[7];
 	//unsigned int *sensors;
 	//sensors = readCalibrated.LineSensors.read();
 	beatle.LineSensors.readCalibrated(sensors);
	if(beatle.DEBUG>0)
	{
 		for(int i = 0; i<7;i++)
 		{
  	//Serial.print(*(sensors+i));
  	Serial.print(sensors[i]);
  	Serial.print("\t");
  	}
  	Serial.println();
	}
}

#include <Beatle.h>
Beatle beatle;
//Set the maxvalue and minvalue of the LineSensors.
unsigned int max_value[] = {2000,2001,2002,2003,2004,2005,2006};
unsigned int min_value[] = {200,201,202,203,204,205,206};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  beatle.StartProgram();
  beatle.setDebugLevel(1);
  beatle.led.colorAll(beatle.led.strip.Color(0,0,255));
  delay(500);
  beatle.writeCalibrationData(max_value,min_value);
  delay(500);
  beatle.buzzer.play(">g32>>c32");
  beatle.readCalibrationData();
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
 for(int i = 0; i<7;i++)
 {
  //Serial.print(*(sensors+i));
  Serial.print(sensors[i]);
  Serial.print("\t");
  }
  Serial.println();
}
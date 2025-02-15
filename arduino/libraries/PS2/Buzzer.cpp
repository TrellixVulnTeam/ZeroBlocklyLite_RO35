#include "StarterPro.h"
#include <Arduino.h>                                                
#include <EEPROM.h>
//#ifdef _INCLUDE_BUZZER_  

int eeAddr_LEVEL1_DEFAULT_PROG = 0;

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};

struct ProgNumInEPROM {
  int lastProgSelected;
};
int ButtonState;                    // variable to store button state

int lastButtonState;                // variable to store last button state

//int ProgramSelector;

bool KeepOnReadButton;

bool ReadButtonState;

long ButtonInterval = 2000;

long startTime ;                    // start time for stop watch

long elapsedTime ;                  // elapsed time for stop watch


#define NumberOfProgram 5   //define the number of programs that stored in the CPU

/****************************************************************/
/**********************  DEFINITIONS FOR SOUND*******************/
/****************************************************************/

#define a0   28
#define as0  29
#define b0   31
#define c1   33
#define cs1  35
#define d1   37
#define ds1  39
#define e1   41
#define f1   44
#define fs1  46
#define g1   49
#define gs1  52
#define a1   55
#define as1  58
#define b1   62
#define c2   65
#define cs2  69
#define d2   73
#define ds2  78
#define e2   82
#define f2   87
#define fs2  93
#define g2   98
#define gs2  104
#define a2   110
#define as2  117
#define b2   123
#define c3   131
#define cs3  139
#define d3   147
#define ds3  156
#define e3   165
#define f3   175
#define fs3  185
#define g3   196
#define gs3  208
#define a3   220
#define as3  233
#define b3   247
#define c4   262
#define cs4  277
#define d4   294
#define ds4  311
#define e4   330
#define f4   349
#define fs4  370
#define g4   392
#define gs4  415
#define a4   440
#define as4  466
#define b4   494
#define c5   523
#define cs5  554
#define d5   587
#define ds5  622
#define e5   659
#define f5   698
#define fs5  740
#define g5   784
#define gs5  831
#define a5   880
#define as5  932
#define b5   988
#define c6   1047
#define cs6  1109
#define d6   1175
#define ds6  1245
#define e6   1319
#define f6   1397
#define fs6  1480
#define g6   1568
#define gs6  1661
#define a6   1760
#define as6  1865
#define b6   1976
#define c7   2093
#define cs7  2217
#define d7   2349
#define ds7  2489
#define e7   2637
#define f7   2794
#define fs7  2960
#define g7   3136
#define gs7  3322
#define a7   3520
#define as7  3729
#define b7   3951
#define c8   4186
#define cs8  4435
#define d8   4699
#define ds8  4978

#define NOTE_A0  a0
#define NOTE_AS0 as0
#define NOTE_B0  b0
#define NOTE_C1  c1
#define NOTE_CS1 cs1
#define NOTE_D1  d1
#define NOTE_DS1 ds1
#define NOTE_E1  e1
#define NOTE_F1  f1
#define NOTE_FS1 fs1
#define NOTE_G1  g1
#define NOTE_GS1 gs1
#define NOTE_A1  a1
#define NOTE_AS1 as1
#define NOTE_B1  b1
#define NOTE_C2  c2
#define NOTE_CS2 cs2
#define NOTE_D2  d2
#define NOTE_DS2 ds2
#define NOTE_E2  e2
#define NOTE_F2  f2
#define NOTE_FS2 fs2
#define NOTE_G2  g2
#define NOTE_GS2 gs2
#define NOTE_A2  a2
#define NOTE_AS2 as2
#define NOTE_B2  b2
#define NOTE_C3  c3
#define NOTE_CS3 cs3
#define NOTE_D3  d3
#define NOTE_DS3 ds3
#define NOTE_E3  e3
#define NOTE_F3  f3
#define NOTE_FS3 fs3
#define NOTE_G3  g3
#define NOTE_GS3 gs3
#define NOTE_A3  a3
#define NOTE_AS3 as3
#define NOTE_B3  b3
#define NOTE_C4  c4
#define NOTE_CS4 cs4
#define NOTE_D4  d4
#define NOTE_DS4 ds4
#define NOTE_E4  e4
#define NOTE_F4  f4
#define NOTE_FS4 fs4
#define NOTE_G4  g4
#define NOTE_GS4 gs4
#define NOTE_A4  a4
#define NOTE_AS4 as4
#define NOTE_B4  b4
#define NOTE_C5  c5
#define NOTE_CS5 cs5
#define NOTE_D5  d5
#define NOTE_DS5 ds5
#define NOTE_E5  e5
#define NOTE_F5  f5
#define NOTE_FS5 fs5
#define NOTE_G5  g5
#define NOTE_GS5 gs5
#define NOTE_A5  a5
#define NOTE_AS5 as5
#define NOTE_B5  b5
#define NOTE_C6  c6
#define NOTE_CS6 cs6
#define NOTE_D6  d6
#define NOTE_DS6 ds6
#define NOTE_E6  e6
#define NOTE_F6  f6
#define NOTE_FS6 fs6
#define NOTE_G6  g6
#define NOTE_GS6 gs6
#define NOTE_A6  a6
#define NOTE_AS6 as6
#define NOTE_B6  b6
#define NOTE_C7  c7
#define NOTE_CS7 cs7
#define NOTE_D7  d7
#define NOTE_DS7 ds7
#define NOTE_E7  e7
#define NOTE_F7  f7
#define NOTE_FS7 fs7
#define NOTE_G7  g7
#define NOTE_GS7 gs7
#define NOTE_A7  a7
#define NOTE_AS7 as7
#define NOTE_B7  b7
#define NOTE_C8  c8
#define NOTE_CS8 cs8
#define NOTE_D8  d8
#define NOTE_DS8 ds8


#define wholeNote       4000*0.5
#define halfNote        2000*0.5
#define quaterNote      1000*0.5
#define eighthNote      500*0.5
#define sixteenthNote   250*0.5

#define meters_x1       1
#define meters_x2       2
#define meters_x3       3
#define meters_x4       4

#define SONG_1          1
#define SONG_2          2
#define SONG_3          3
#define SONG_4          4
#define SONG_5          5
/****************************************************************/
/***************** ** END OF  NOTE PERIOD ***********************/
/****************************************************************/




int NOTE[] = {
  c5, c4, d4, e4, f4, g4, a4, b4, c5, d5, e5, f5
};




void playNote(int Note, int Meter, int Length) {
  tone(BEEP, Note, Meter * Length);
  //  delay(Meter * 1.3 * Length);
  long duration_time = millis();
  for (int i = 0; i < Meter * 1.3 * Length * 200; i++) {
    //    Serial.println(i);
    if (millis() - duration_time > Meter * 1.3 * Length) break;
    //digitalRead(ZW_A1);
  }
  //  noTone(BuzzerPin);
}

void playNoteShort(int Note, int Meter, int Length) {
  tone(BEEP, Note, Meter * Length);
  //  delay(Meter * 1.3 * Length);
  long duration_time = millis();
  for (int i = 0; i < Meter * 1.3 * Length * 200; i++) {
    //    Serial.println(i);
    if (millis() - duration_time > Meter * 1.0 * Length) break;
    //digitalRead(ZW_A1);
  }
  //  noTone(BuzzerPin);
}


void playStart()
{
  playNoteShort(e7, sixteenthNote * 0.25, meters_x1);
  playNoteShort(g7, sixteenthNote * 0.25, meters_x1);
  playNoteShort(f7, sixteenthNote * 0.25, meters_x1);
  playNoteShort(g7, sixteenthNote * 0.25, meters_x1);
  delay(100);

  playNoteShort(e7, sixteenthNote * 0.25, meters_x1);
  playNoteShort(g7, sixteenthNote * 0.25, meters_x1);
  playNoteShort(f7, sixteenthNote * 0.25, meters_x1);
  playNoteShort(g7, sixteenthNote * 0.25, meters_x1);
}


void playPowerOn()
{
	playNote(c4, eighthNote, meters_x1);
  playNote(e4, eighthNote, meters_x1);
  playNote(g4, eighthNote, meters_x1);
  playNote(c5, quaterNote, meters_x1);
}
void playSong(int songSelected) {
  switch (songSelected) {
  case 1:
    playNote(e4, eighthNote, meters_x1);
    playNote(e4, eighthNote, meters_x1);
    playNote(f4, eighthNote, meters_x1);
    playNote(g4, eighthNote, meters_x1);

    playNote(g4, eighthNote, meters_x1);
    playNote(f4, eighthNote, meters_x1);
    playNote(e4, eighthNote, meters_x1);
    playNote(d4, eighthNote, meters_x1);

    playNote(c4, eighthNote, meters_x1);
    playNote(c4, eighthNote, meters_x1);
    playNote(d4, eighthNote, meters_x1);
    playNote(e4, eighthNote, meters_x1);

    playNote(e4, sixteenthNote, meters_x3);
    playNote(d4, sixteenthNote, meters_x1);
    playNote(d4, eighthNote, meters_x2);



    playNote(e4, eighthNote, meters_x1);
    playNote(e4, eighthNote, meters_x1);
    playNote(f4, eighthNote, meters_x1);
    playNote(g4, eighthNote, meters_x1);

    playNote(g4, eighthNote, meters_x1);
    playNote(f4, eighthNote, meters_x1);
    playNote(e4, eighthNote, meters_x1);
    playNote(d4, eighthNote, meters_x1);

    playNote(c4, eighthNote, meters_x1);
    playNote(c4, eighthNote, meters_x1);
    playNote(d4, eighthNote, meters_x1);
    playNote(e4, eighthNote, meters_x1);

    playNote(d4, sixteenthNote, meters_x3);
    playNote(c4, sixteenthNote, meters_x1);
    playNote(c4, eighthNote, meters_x2);


    for (int i = 0; i < 2; i++) {
      playNote(d4, eighthNote, meters_x1);
      playNote(d4, eighthNote, meters_x1);
      playNote(e4, eighthNote, meters_x1);
      playNote(c4, eighthNote, meters_x1);

      playNote(d4, eighthNote, meters_x1);
      playNote(e4, sixteenthNote, meters_x1);
      playNote(f4, sixteenthNote, meters_x1);
      playNote(e4, eighthNote, meters_x1);
      playNote(c4, eighthNote, meters_x1);

      playNote(d4, eighthNote, meters_x1);
      playNote(e4, sixteenthNote, meters_x1);
      playNote(f4, sixteenthNote, meters_x1);
      playNote(e4, eighthNote, meters_x1);
      playNote(d4, eighthNote, meters_x1);

      playNote(c4, eighthNote, meters_x1);
      playNote(d4, eighthNote, meters_x1);
      playNote(g3, eighthNote, meters_x1);
      playNote(e4, eighthNote, meters_x2);

      //playNote(e4,eighthNote,meters_x1);
      playNote(e4, eighthNote, meters_x1);
      playNote(f4, eighthNote, meters_x1);
      playNote(g4, eighthNote, meters_x1);

      playNote(g4, eighthNote, meters_x1);
      playNote(f4, eighthNote, meters_x1);
      playNote(e4, eighthNote, meters_x1);
      playNote(d4, eighthNote, meters_x1);

      playNote(c4, eighthNote, meters_x1);
      playNote(c4, eighthNote, meters_x1);
      playNote(d4, eighthNote, meters_x1);
      playNote(e4, eighthNote, meters_x1);

      playNote(d4, sixteenthNote, meters_x3);
      playNote(c4, sixteenthNote, meters_x1);
      playNote(c4, eighthNote, meters_x2);
    }
    break;

  case 2:
    playNote(c4, sixteenthNote, meters_x3);
    playNote(e4, sixteenthNote, meters_x1);
    playNote(g4, eighthNote, meters_x1);
    playNote(g4, eighthNote, meters_x1);

    playNote(a4, quaterNote, meters_x1);
    playNote(g4, quaterNote, meters_x1);

    playNote(e4, sixteenthNote, meters_x3);
    playNote(c4, sixteenthNote, meters_x1);
    playNote(g4, quaterNote / 3, meters_x1);
    playNote(g4, quaterNote / 3, meters_x1);
    playNote(g4, quaterNote / 3, meters_x1);

    playNote(e4, quaterNote, meters_x1);
    playNote(c4, quaterNote, meters_x1);

    playNote(g3, quaterNote / 3, meters_x1);
    playNote(g3, quaterNote / 3, meters_x1);
    playNote(g3, quaterNote / 3, meters_x1);
    playNote(g3, quaterNote / 3, meters_x1);
    playNote(g3, quaterNote / 3, meters_x1);
    playNote(g3, quaterNote / 3, meters_x1);

    playNote(c4, quaterNote, meters_x1);
    delay(eighthNote * 1.3 * meters_x1);
    playNote(g3, eighthNote, meters_x1);

    playNote(c4, eighthNote, meters_x3);
    playNote(c4, eighthNote, meters_x1);

    playNote(c4, sixteenthNote, meters_x3);
    playNote(c4, sixteenthNote, meters_x1);
    playNote(g3, eighthNote, meters_x1);
    playNote(a3, sixteenthNote, meters_x1);
    playNote(b3, sixteenthNote, meters_x1);

    playNote(c4, quaterNote, meters_x1);
    playNote(c4, quaterNote, meters_x1);
    delay(eighthNote * 1.3 * meters_x1);

    playNote(e4, eighthNote, meters_x1);
    playNote(c4, eighthNote, meters_x1);
    playNote(d4, sixteenthNote, meters_x1);
    playNote(e4, sixteenthNote, meters_x1);

    playNote(g4, quaterNote, meters_x1);
    playNote(g4, quaterNote, meters_x1);

    playNote(e4, sixteenthNote, meters_x3);
    playNote(e4, sixteenthNote, meters_x1);
    playNote(c4, sixteenthNote, meters_x3);
    playNote(e4, sixteenthNote, meters_x1);

    playNote(g4, sixteenthNote, meters_x3);
    playNote(e4, sixteenthNote, meters_x1);
    playNote(d4, quaterNote, meters_x1);

    playNote(d4, quaterNote, meters_x2);

    playNote(a4, quaterNote, meters_x1);
    playNote(g4, quaterNote, meters_x1);

    playNote(d4, quaterNote, meters_x1);
    playNote(e4, quaterNote, meters_x1);

    playNote(g4, eighthNote, meters_x1);
    playNote(e4, eighthNote, meters_x1);
    delay(eighthNote * 1.3 * meters_x1);
    playNote(g4, eighthNote, meters_x1);

    playNote(e4, eighthNote, meters_x1);
    playNote(d4, sixteenthNote, meters_x1);
    playNote(e4, sixteenthNote, meters_x1);
    playNote(c4, quaterNote, meters_x1);

    playNote(e4, quaterNote, meters_x1);
    delay(quaterNote * 1.3 * meters_x1);

    playNote(g3, sixteenthNote, meters_x3);
    playNote(a3, sixteenthNote, meters_x1);
    playNote(c4, eighthNote, meters_x1);
    playNote(c4, eighthNote, meters_x1);

    playNote(e4, sixteenthNote, meters_x3);
    playNote(e4, sixteenthNote, meters_x1);
    playNote(g4, eighthNote, meters_x1);
    playNote(g4, eighthNote, meters_x1);

    playNote(d4, eighthNote, meters_x1);
    playNote(d4, sixteenthNote, meters_x1);
    playNote(d4, sixteenthNote, meters_x1);
    playNote(a3, quaterNote, meters_x1);

    playNote(d4, eighthNote, meters_x3);
    playNote(g3, eighthNote, meters_x1);

    playNote(c4, eighthNote, meters_x3);
    playNote(c4, eighthNote, meters_x1);

    playNote(e4, eighthNote, meters_x3);
    playNote(e4, eighthNote, meters_x1);

    playNote(g4, quaterNote, meters_x2);

    playNote(c4, sixteenthNote, meters_x3);
    playNote(e4, sixteenthNote, meters_x1);
    playNote(g4, eighthNote, meters_x1);
    playNote(g4, eighthNote, meters_x1);

    playNote(a4, quaterNote, meters_x1);
    playNote(g4, quaterNote, meters_x1);

    playNote(e4, sixteenthNote, meters_x3);
    playNote(c4, sixteenthNote, meters_x1);
    playNote(g4, quaterNote / 3, meters_x1);
    playNote(g4, quaterNote / 3, meters_x1);
    playNote(g4, quaterNote / 3, meters_x1);

    playNote(e4, eighthNote, meters_x1);
    delay(eighthNote * 1.3 * meters_x1);
    playNote(c4, eighthNote, meters_x1);
    delay(eighthNote * 1.3 * meters_x1);

    playNote(g3, quaterNote, meters_x1);
    playNote(c4, quaterNote, meters_x1);

    playNote(e4, sixteenthNote, meters_x3);
    playNote(c4, sixteenthNote, meters_x1);
    playNote(g4, quaterNote / 3, meters_x1);
    playNote(g4, quaterNote / 3, meters_x1);
    playNote(g4, quaterNote / 3, meters_x1);

    playNote(e4, eighthNote, meters_x1);
    delay(eighthNote * 1.3 * meters_x1);
    playNote(c4, eighthNote, meters_x1);
    delay(eighthNote * 1.3 * meters_x1);

    playNote(g3, quaterNote, meters_x1);
    playNote(c4, quaterNote, meters_x1);

    playNote(g3, quaterNote, meters_x1);
    playNote(c4, quaterNote, meters_x1);

    playNote(g3, quaterNote, meters_x1);
    playNote(c4, quaterNote, meters_x1);

    playNote(c4, quaterNote, meters_x1);
    delay(quaterNote * 1.3 * meters_x1);
    break;

  case 3:
    break;
  case 4:
    break;

  case 5:
    break;

  default:
    break;
  }

}



void StartProgram(int *ProgramSelector)
{
  ProgNumInEPROM ProgToBeSelected;
  ProgNumInEPROM lastRunProg;

  int eepromAddr = eeAddr_LEVEL1_DEFAULT_PROG;

  EEPROM.get(eepromAddr, lastRunProg);
  if (lastRunProg.lastProgSelected == 0) {
    ProgToBeSelected.lastProgSelected = 1;
    EEPROM.put(eepromAddr, ProgToBeSelected);
  }


  //Serial.begin(115200);

  pinMode(BEEP, OUTPUT);
  pinMode(START_BUTTON, INPUT);
  digitalWrite(START_BUTTON, HIGH);


  //int bullet_left = bulletNumber;
  int noteDuration = 1000 / noteDurations[0];
  int pauseBetweenNotes = noteDuration * 1.30;

  playNote(c4, eighthNote, meters_x1);
  playNote(e4, eighthNote, meters_x1);
  playNote(g4, eighthNote, meters_x1);
  playNote(c5, quaterNote, meters_x1);

  (*ProgramSelector) = -1;
  KeepOnReadButton = true;

  while (KeepOnReadButton) {


    ReadButtonState = true;
    while (ReadButtonState) {
      //TuningLoader(bulletLoader_servo, bulletTrigger_servo, &bullet_left) ;
      lastButtonState = ButtonState;
      delay(10);                                           //make a 10ms interval between successive reading. This is to make sure the button state is stable enough
      ButtonState = digitalRead(START_BUTTON);

      if ((*ProgramSelector) == -1 && ButtonState == HIGH) {    //if no program is selected, keep on read the button state
        //      if (ButtonState == HIGH) {    //if no program is selected, keep on read the button state
        ReadButtonState = true;
      }
      else if ((*ProgramSelector) >= 0 && ButtonState == HIGH && lastButtonState == HIGH) {     //if one program is selected and the next program is not selected in ButtonInterval(initially 2 seconds) time, the program selected will  run
        elapsedTime =   millis() - startTime;   // store elapsed time

        if (elapsedTime > ButtonInterval) {
          ReadButtonState = false;
          KeepOnReadButton = false;
        }
        else {
          ReadButtonState = true;
          KeepOnReadButton = true;
        }
      }
      else if (ButtonState == LOW && lastButtonState == LOW) {      //if the button is kept on being pressed, keep on reading the the state until the button is released.
        ReadButtonState = true;

      }
      else if (ButtonState == HIGH && lastButtonState == LOW) {      //if a low to high transition is found, it means the user just release the button. Reset the timer and wait button to be pressed for ButtonInterval(intially 2 seconds).
        startTime = millis();                                   // reset the start time
        ReadButtonState = true;

      }
      else if (ButtonState == LOW && lastButtonState == HIGH) {        //if a high to low transition is found, it means the user can select program. Stop reading the button, the corresponding tone will be played.
        ReadButtonState = false;
        (*ProgramSelector)++;
        break;
      }
    }

    if ((*ProgramSelector) > NumberOfProgram) {          //If times of StartButton pressed more than the number of program, program selector goes to the first program
      (*ProgramSelector) = 1;
    }


    if (ButtonState == LOW && lastButtonState == HIGH) {

      startTime = millis();                                   // store the start time

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      noteDuration = 1000 / noteDurations[(*ProgramSelector)];
      tone(BEEP, NOTE[(*ProgramSelector)], noteDuration);

      // the note's duration + 30% seems to work well:
      pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      noTone(BEEP);

      //      int eepromAddr = eeAddr_LEVEL1_DEFAULT_PROG;
      //      EEPROM.get(eepromAddr, lastRunProg);
      //      if (lastRunProg.lastProgSelected == 0) {
      //        ProgToBeSelected.lastProgSelected = 1;
      //        EEPROM.put(eepromAddr, ProgToBeSelected);
      //      }

      //      ProgToBeSelected.lastProgSelected = (*ProgramSelector);
      //      Serial.print("###########Program To be saved in EEPROM = ");
      //      Serial.println((*ProgramSelector));
      //      if (ProgToBeSelected.lastProgSelected != 0) {
      //
      //        Serial.print("Program To be saved in EEPROM = ");
      //        Serial.println(ProgToBeSelected.lastProgSelected);
      //
      //        EEPROM.put(eepromAddr, ProgToBeSelected);
      //      }
    }
  }
  ProgToBeSelected.lastProgSelected = (*ProgramSelector);

  if (ProgToBeSelected.lastProgSelected != 0) {

    Serial.print("Program To be saved in EEPROM = ");
    Serial.println(ProgToBeSelected.lastProgSelected);

    EEPROM.put(eepromAddr, ProgToBeSelected);
  }
  else {
    EEPROM.get(eepromAddr, lastRunProg);

    (*ProgramSelector) = lastRunProg.lastProgSelected;
  }

  playNoteShort(e7, sixteenthNote * 0.25, meters_x1);
  playNoteShort(g7, sixteenthNote * 0.25, meters_x1);
  playNoteShort(f7, sixteenthNote * 0.25, meters_x1);
  playNoteShort(g7, sixteenthNote * 0.25, meters_x1);
  delay(100);

  playNoteShort(e7, sixteenthNote * 0.25, meters_x1);
  playNoteShort(g7, sixteenthNote * 0.25, meters_x1);
  playNoteShort(f7, sixteenthNote * 0.25, meters_x1);
  playNoteShort(g7, sixteenthNote * 0.25, meters_x1);
//  delay(100);
//
//  playNoteShort(e7, sixteenthNote * 0.25, meters_x1);
//  playNoteShort(g7, sixteenthNote * 0.25, meters_x1);
//  playNoteShort(f7, sixteenthNote * 0.25, meters_x1);
//  playNoteShort(g7, sixteenthNote * 0.25, meters_x1);
}
//#endif




void throwTheBall(Servo B1_mian_servo, Servo B2_throw_servo)
{
  B1_mian_servo.write(180);
  delay(500);
  B2_throw_servo.write(180);
  delay(500);
  B1_mian_servo.write(90);
  B2_throw_servo.write(90);
  
}

void filterTheBall(Servo B1_mian_servo, Servo B2_throw_servo)
{
  B1_mian_servo.write(0);
  delay(500);
  B1_mian_servo.write(90);
  B2_throw_servo.write(90);
  
}
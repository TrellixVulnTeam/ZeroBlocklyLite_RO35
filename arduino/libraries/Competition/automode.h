#include    "ZeroWorkshop_lib.h"
#include    "LineFollowerArray.h"
#include    "ZeroWorkshop_Macro_Definitions.h"




void motor(int leftSpeed, int rightSpeed);

void followSegment();

void tcs74725_init();

void sensorMode();

//color_type CheckColor(RGB_type rgb_data);

void cubeSearching(double *head_pos, int *moving_direction, Servo head_servo);

void cubeSearchingHalfCycle(double *head_pos, int *moving_direction, Servo head_servo, int currentState, double searchingMiddlePos, double searchingRange);

void catchingCube(int *head_moving_direction, double *headSensor_pos, Servo headServo, Servo armServo1, Servo armServo2, Servo handServo, double *ang_arm1, double *ang_arm2);
void catchingCube(int *head_moving_direction, double *headSensor_pos, Servo headServo, Servo armServo1, Servo armServo2, double *ang_arm1, double *ang_arm2);
void catchingCube(int *head_moving_direction, double *headSensor_pos, Servo headServo, Servo handServo);

void carRightTurn();

void carLeftTurn();

void carStop();

void carGoReverse();

void carGoForward();

void grabCube(Servo armServo1, Servo armServo2, Servo servohand, double *armServo1_ang, double *armServo2_ang);
void grabCube(Servo armServo1, Servo armServo2, double *armServo1_ang, double *armServo2_ang);
void grabCube(Servo servohand);

void lowerArm(Servo servo1, Servo servo2, double *servo1_ang, double *servo2_ang);
void lowerArm();

void armUp(Servo servo1, Servo servo2, double *servo1_ang, double *servo2_ang);

void armRestore(Servo servo1, Servo servo2, double *servo1_ang, double *servo2_ang);

void closeHand(Servo Hservo);
void closeHand();

void openHand(Servo Hservo);
void openHand();

int readCubeColor();

void carReturn();

void deliverCube(Servo armServo1, Servo armServo2, Servo headServo, Servo handServo, int *headServoDirection, double *armServo1_ang, double *armServo2_ang);
void deliverCube(Servo armServo1, Servo armServo2, Servo headServo, int *headServoDirection, double *armServo1_ang, double *armServo2_ang);

void TurnRight90();

void TurnRight90_returnToMiddle();
void TurnRight90_returnToMiddleMotorClaw();

void TurnLeft90();

void TurnLeft90_returnToMiddle();
void TurnLeft90_returnToMiddleMotorClaw();

void deliverStepTwo(Servo servo1, Servo servo2, Servo servohand, double *servo1_ang, double *servo2_ang);
void deliverStepTwo(Servo servo1, Servo servo2, double *servo1_ang, double *servo2_ang);

void deliverStepOne(Servo servo1, Servo servo2, double *servo1_ang, double *servo2_ang);
void deliverStepOne();

void AutoModeSetup(Servo headServo, Servo armServo1, Servo armServo2, Servo handServo, double *headServoPos, double *armServo1_ang, double *armServo2_ang, int *headServoDirection);
void AutoModeSetup(Servo headServo, Servo armServo1, Servo armServo2,                  double *headServoPos, double *armServo1_ang, double *armServo2_ang, int *headServoDirection);
void AutoModeSetup(Servo headServo, Servo handServo, double *headServoPos, int *headServoDirection);

void autoModeRun(Servo headServo, Servo armServo1, Servo armServo2, Servo handServo, double *headServoPos, double *armServo1_ang, double *armServo2_ang, int *headServoDirection);
void autoModeRun(Servo headServo, Servo armServo1, Servo armServo2,                  double *headServoPos, double *armServo1_ang, double *armServo2_ang, int *headServoDirection);
void autoModeRun(Servo headServo, Servo handServo, double *headServoPos,                                               int *headServoDirection);

void parameterDefinition(double armLowerServo_initPos,  double armLowerServo_catchPos, 
                         double armHigherServo_initPos, double armHigherServo_catchPos, 
                         double handServo_openPos,      double handServo_closePos, 
                         double headServo_midPos,       double headServo_Range,
                         double userDefined_grabTime);
                         
void parameterDefinition(double armLowerServo_initPos,  double armLowerServo_catchPos, 
                         double armHigherServo_initPos, double armHigherServo_catchPos, 
                         double headServo_midPos,       double headServo_Range,
                         double userDefined_grabTime);
                         
void T3_colorSetup() ;
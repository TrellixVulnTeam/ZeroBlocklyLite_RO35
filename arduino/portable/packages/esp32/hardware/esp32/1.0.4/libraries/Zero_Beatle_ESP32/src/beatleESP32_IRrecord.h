//------------------------------------------------------------------------------
// Include the IRremote library header
//
#include <IRremote.h>
#include "NextionAll.h"
//------------------------------------------------------------------------------
// Tell IRremote which Arduino pin is connected to the IR Receiver (TSOP4838)
//

int IR_RECEIVE_PIN = 15;

IRrecv irrecv(IR_RECEIVE_PIN);

NexText     tEncoding = NexText(0, 5, "t2");
NexText     tCode = NexText(0, 7, "t4");
NexText     tRaw = NexText(0, 9, "t6");

char buf[2000];


NexTouch *nex_listen_list[] = 
{
    &tEncoding,
    &tCode,
    &tRaw,
    NULL
};


//+=============================================================================
// Configure the Arduino
//
void IRrecordsetup() {
   // pinMode(LED_BUILTIN, OUTPUT);

    nexInit();

    //Serial.begin(115200);   // Status message will be sent to PC at 9600 baud
#if defined(__AVR_ATmega32U4__)
    while (!Serial); //delay for Leonardo, but this loops forever for Maple Serial
#endif
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__));

    irrecv.enableIRIn();  // Start the receiver

    Serial.print(F("Ready to receive IR signals at pin "));
    Serial.println(IR_RECEIVE_PIN);

    sprintf(buf, "Ready to receive IR \\r signals at pin %d:", IR_RECEIVE_PIN);
   //t1.setText(buf);
}

//+=============================================================================
// Display IR code
//
void ircode(decode_results *results) {
    // Panasonic has an Address
    if (results->decode_type == PANASONIC) {
        Serial.print(results->address, HEX);
        char buf[100];
       
        Serial.print(":");
    }

    // Print Code
    Serial.print(results->value, HEX);
    sprintf(buf,"0x%08X",results->value);
    tCode.setText(buf);
}

//+=============================================================================
// Display encoding type
//
void encoding(decode_results *results) {
    switch (results->decode_type) {
    default:
    case UNKNOWN:
        Serial.print("UNKNOWN");
        tEncoding.setText("UNKNOW");
        break;
    case NEC:
        Serial.print("NEC");
        tEncoding.setText("NEC");
        break;
    case SONY:
        Serial.print("SONY");
        tEncoding.setText("SONY");
        break;
    case RC5:
        Serial.print("RC5");
        tEncoding.setText("RC5");
        break;
    case RC6:
        Serial.print("RC6");
        tEncoding.setText("RC6");
        break;
    case DISH:
        Serial.print("DISH");
        tEncoding.setText("DISH");
        break;
    case SHARP:
        Serial.print("SHARP");
        tEncoding.setText("SHARP");
        break;
    case SHARP_ALT:
        Serial.print("SHARP_ALT");
        tEncoding.setText("SHARP_ALT");
        break;
    case JVC:
        Serial.print("JVC");
        tEncoding.setText("JVC");
        break;
    case SANYO:
        Serial.print("SANYO");
        tEncoding.setText("SANYO");
        break;
    case MITSUBISHI:
        Serial.print("MITSUBISHI");
        tEncoding.setText("MITSUBISHI");
        break;
    case SAMSUNG:
        Serial.print("SAMSUNG");
        tEncoding.setText("SAMSUNG");
        break;
    case LG:
        Serial.print("LG");
        tEncoding.setText("LG");
        break;
    case WHYNTER:
        Serial.print("WHYNTER");
        tEncoding.setText("WHYNTER");
        break;
    case AIWA_RC_T501:
        Serial.print("AIWA_RC_T501");
        tEncoding.setText("AIWA_RC_T501");
        break;
    case PANASONIC:
        Serial.print("PANASONIC");
        tEncoding.setText("PANASONIC");
        break;
    case DENON:
        Serial.print("Denon");
        tEncoding.setText("Denon");
        break;
    case BOSEWAVE:
        Serial.print("BOSEWAVE");
        tEncoding.setText("BOSEWAVE");
        break;
    }
}

//+=============================================================================
// Dump out the decode_results structure.
//
void dumpInfo(decode_results *results) {
    // Check if the buffer overflowed
    if (results->overflow) {
        Serial.println("IR code too long. Edit IRremoteInt.h and increase RAW_BUFFER_LENGTH");
        return;
    }

    // Show Encoding standard
    Serial.print("Encoding  : ");
    encoding(results);
    Serial.println("");
    

    // Show Code & length
    Serial.print("Code      : 0x");
    ircode(results);
    Serial.print(" (");
    Serial.print(results->bits, DEC);
    Serial.println(" bits)");
}

//+=============================================================================
// Dump out the decode_results structure.
//
void dumpRaw(decode_results *results) {
    // Print Raw data
    Serial.print("Timing[");
    Serial.print(results->rawlen - 1, DEC);
    Serial.println("]: ");

    for (unsigned int i = 1; i < results->rawlen; i++) {
        unsigned long x = results->rawbuf[i] * MICROS_PER_TICK;
        if (!(i & 1)) {  // even
            Serial.print("-");
            if (x < 1000)
                Serial.print(" ");
            if (x < 100)
                Serial.print(" ");
            Serial.print(x, DEC);
        } else {  // odd
            Serial.print("     ");
            Serial.print("+");
            if (x < 1000)
                Serial.print(" ");
            if (x < 100)
                Serial.print(" ");
            Serial.print(x, DEC);
            if (i < results->rawlen - 1)
                Serial.print(", "); //',' not needed for last one
        }
        if (!(i % 8))
            Serial.println("");
    }
    Serial.println("");                    // Newline
}

//+=============================================================================
// Dump out the decode_results structure.
//
void dumpCode(decode_results *results) {
    // Start declaration
    String rawinfo;
    char buf[100];

    rawinfo = "unsigned int  ";
    
    

    rawinfo +="rawData[";
    rawinfo += String(results->rawlen - 1);
    rawinfo +="] = {";
  //  Serial.print("unsigned int  ");          // variable type
  //  Serial.print("rawData[");                // array name
  //  Serial.print(results->rawlen - 1, DEC);  // array size
  //  Serial.print("] = {");                   // Start declaration

    // Dump data
    for (unsigned int i = 1; i < results->rawlen; i++) {
       // Serial.print(results->rawbuf[i] * MICROS_PER_TICK, DEC);
        //rawinfo  +="0x"; 
        rawinfo += String(results->rawbuf[i] * MICROS_PER_TICK,DEC);
        if (i < results->rawlen - 1)
        {
           // Serial.print(","); // ',' not needed on last one
           rawinfo +=",";
        }
        if (!(i & 1))
        {
            //Serial.print(" ");
            rawinfo +=" ";
        }
    }

    // End declaration
   // Serial.print("};");  //
    rawinfo +="}";
    
    Serial.print(rawinfo);
   
    tRaw.setText(rawinfo.c_str());
    // Comment
    Serial.print("  // ");
    encoding(results);
    Serial.print(" ");
    ircode(results);

    // Newline
    Serial.println("");

    // Now dump "known" codes
    if (results->decode_type != UNKNOWN) {

        // Some protocols have an address
        if (results->decode_type == PANASONIC) {
            Serial.print("unsigned int  addr = 0x");
            Serial.print(results->address, HEX);
            Serial.println(";");
        }

        // All protocols have data
        Serial.print("unsigned int  data = 0x");
        Serial.print(results->value, HEX);
        Serial.println(";");
    }
}

//+=============================================================================
// The repeating section of the code
//
void IRrecordloop() {
    decode_results results;        // Somewhere to store the results

    if (irrecv.decode(&results)) {  // Grab an IR code
        dumpInfo(&results);           // Output the results
        //dumpRaw(&results);            // Output the results in RAW format
        dumpCode(&results);           // Output the results as source code
        Serial.println("");           // Blank line between entries
        irrecv.resume();              // Prepare for the next value
    }
}
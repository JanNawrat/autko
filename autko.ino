#include <IRremote.hpp>
#include "conifg.h"
#include "Wheels.h"

Wheels w;
unsigned long timeOfLastSignal;
int maxTimeBetweenSignals = 100;

void setup() {
    /*
    * setting up driving system
    */
    w.attach(
        RIGHT_WHEEL_FORWARD_PIN,
        RIGHT_WHEEL_BACKWARD_PIN,
        RIGHT_WHEEL_SPEED_PIN,
        LEFT_WHEEL_FORWARD_PIN,
        LEFT_WHEEL_BACKWARD_PIN,
        LEFT_WHEEL_SPEED_PIN
    );
    w.setSpeed(200);


    // led feedback is received to enable "beeping" instead
    if(RECEIVE_NEC || RECEIVE_PULSE_DISTANCE) {
        IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK); // Start the receiver
    }

    pinMode(BEEPER, OUTPUT);
    Timer1.initialize();

    Serial.begin(9600);
    if(RECEIVE_SERIAL) {
        Serial.println("Forward: WAD");
        Serial.println("Back: ZXC");
        Serial.println("Stop: S");
    }
}

void loop() {
    /*
    * receiving commands from remote
    */
    while((RECEIVE_NEC || RECEIVE_PULSE_DISTANCE) && IrReciver.decode()) {
        Serial.println("IR input recived:");
        IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
        
        /*
        * NEC protocol
        */
        if(RECEIVE_NEC && IrReceiver.decodedIRData.protocol == NEC) {
            int command = IrReceiver.decodedIRData.command;
            switch(command) {
                case IR_REMOTE_1: {
                    Serial.println("Received: 1");
                    w.setSpeed(100);
                    Serial.println("Wheel speed set to 100");
                    break;
                }
                case IR_REMOTE_2: {
                    Serial.println("Received: 2");
                    w.setSpeed(150);
                    Serial.println("Wheel speed set to 150");
                    break;
                }
                case IR_REMOTE_3: {
                    Serial.println("Received: 3");
                    w.setSpeed(200);
                    Serial.println("Wheel speed set to 200");
                    break;
                }
                case IR_REMOTE_UP: {
                    Serial.println("Received: UP");
                    w.setForward();
                    Serial.println("Moving forward");
                    // TODO: holding code
                    break;
                }
                case IR_REMOTE_DOWN: {
                    Serial.println("Received: DOWN");
                    w.setBack();
                    Serial.println("Moving backward");
                    // TODO: holding code
                    break;
                }
                case IR_REMOTE_RIGHT: {
                    Serial.println("Received: RIGHT");
                    // TODO: turn
                    Serial.println("Turning right");
                    // TODO: holding code
                    break;
                }
                case IR_REMOTE_LEFT: {
                    Serial.println("Received: LEFT");
                    // TODO: turn
                    Serial.println("Turning left");
                    // TODO: holding code
                    break;
                }
                case IR_REMOTE_OK: {
                    Serial.println("Received: OK");
                    w.stop();
                    Serial.println("Emergency stopping");
                    break;
                }
                default: {
                    Serial.print("Received: UNMAPPED");
                    Serial.println(command);
                    break;
                }
            }
        }

        /*
        * PULSE DISTANCE protocol
        */
        if(RECEIVE_PULSE_DISTANCE && IrReceiver.decodedIRData.protocol == NEC) {
            unsigned long cmd = IrReceiver.decodedIRData.decodedRawData;
            switch(command) {
                case PD_REMOTE_1: {
                    Serial.println("Received: 1");
                    w.setSpeed(100);
                    Serial.println("Wheel speed set to 100");
                    break;
                }
                case PD_REMOTE_2: {
                    Serial.println("Received: 2");
                    w.setSpeed(150);
                    Serial.println("Wheel speed set to 150");
                    break;
                }
                case PD_REMOTE_3: {
                    Serial.println("Received: 3");
                    w.setSpeed(200);
                    Serial.println("Wheel speed set to 200");
                    break;
                }
                case PD_REMOTE_UP: {
                    Serial.println("Received: UP");
                    w.setForward();
                    Serial.println("Moving forward");
                    // TODO: holding code
                    break;
                }
                case PD_REMOTE_DOWN: {
                    Serial.println("Received: DOWN");
                    w.setBack();
                    Serial.println("Moving backward");
                    // TODO: holding code
                    break;
                }
                case PD_REMOTE_RIGHT: {
                    Serial.println("Received: RIGHT");
                    // TODO: turn
                    Serial.println("Turning right");
                    // TODO: holding code
                    break;
                }
                case PD_REMOTE_LEFT: {
                    Serial.println("Received: LEFT");
                    // TODO: turn
                    Serial.println("Turning left");
                    // TODO: holding code
                    break;
                }
                case PD_REMOTE_OK: {
                    Serial.println("Received: OK");
                    w.stop();
                    Serial.println("Emergency stopping");
                    break;
                }
                default: {
                    Serial.print("Received: UNMAPPED");
                    Serial.println(command);
                    break;
                }
            }
        }
        // pulse distance seems to be using UNKNOWN for holding down
        if(RECEIVE_PULSE_DISTANCE && IrReceiver.decodedIRData.protocol == UNKNOWN) {
            // TODO: holding down
        }

        /*
        * resuming receiver
        */
        IrReceiver.resume();
        Serial.println("IR resumed");
    }

    /*
    * checking for releasing buttons
    */
    // TODO
  
    /*
    * receiveing commands from serial
    */
    while(RECEIVE_SERIAL && Serial.available()) {
        Serial.println("Serial received");
        char cmd = Serial.read();
        switch(cmd) {
            case 'w': w.forward(); break;
            case 'x': w.back(); break;
            case 'a': w.forwardLeft(); break;
            case 'd': w.forwardRight(); break;
            case 'z': w.backLeft(); break;
            case 'c': w.backRight(); break;
            case 's': w.stop(); break;
            case '1': w.setSpeedLeft(75); break;
            case '2': w.setSpeedLeft(200); break;
            case '9': w.setSpeedRight(75); break;
            case '0': w.setSpeedRight(200); break;
            case '5': w.setSpeed(100); break;
            case 'g' : w.goForward(10); break;
            case 'b' : w.goBack(10); break;
        }
    } 
}

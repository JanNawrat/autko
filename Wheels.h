/* 
 * prosta implementacja klasy obsługującej 
 * silniki pojazdu za pośrednictwem modułu L298
 *
 * Sterowanie odbywa się przez:
 * 1)  powiązanie odpowiednich pinów I/O Arduino metodą attach() 
 * 2)  ustalenie prędkości setSpeed*()
 * 3)  wywołanie funkcji ruchu
 */


#include <Arduino.h>
/*
 * version used: https://github.com/johnrickman/LiquidCrystal_I2C
 */
#include <LiquidCrystal_I2C.h>
#include "TimerOne.h"
#include "conifg.h"


#ifndef Wheels_h
#define Wheels_h



class Wheels {
    public: 
        Wheels();
        /*
         *  pinForward - wejście "naprzód" L298
         *  pinBack    - wejście "wstecz" L298
         *  pinSpeed   - wejście "enable/PWM" L298
         */
        void attach(int pinRightForward, int pinRightBack, int pinRightSpeed,
                    int pinLeftForward, int pinLeftBack, int pinLeftSpeed);

        /*
         *  LCD functions using LiquidCrystal_I2C
         */
        void initLCD();
        void printSpeedLeft();
        void printSpeedRight();

        /*
         *  movement functions
         */
        void forward();
        void forwardLeft();
        void forwardRight();
        void back();
        void backLeft();
        void backRight();
        void stop();
        void stopLeft();
        void stopRight();
        /*
         *  ustawienie prędkości obrotowej (przez PWM)
         *   - minimalna efektywna wartość 60
         *      może zależeć od stanu naładowania baterii
         */
        void setSpeed(uint8_t);
        void setSpeedRight(uint8_t);
        void setSpeedLeft(uint8_t);
        
        void goForward(int cm);
        void goBack(int cm);

    private:
        bool pinsAttached = false;
        int pinsRight[3];
        int pinsLeft[3];
        uint8_t speedLeft = 0;
        uint8_t speedRight = 0;
        /*
         *  0 = not moving, 1 = moving forward, 2 = moving backward
         */
        int dirLeft = 0;
        int dirRight = 0;
        void updateBeeper();
};

void doBeep();

#endif

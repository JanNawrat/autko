#include "Wheels.h"

byte LCDAddress = 0x27;

LiquidCrystal_I2C lcd(LCDAddress, 16, 2);

#define SET_MOVEMENT(side,f,b) digitalWrite( side[0], f);\
                               digitalWrite( side[1], b)

Wheels::Wheels() {}

void Wheels::attach(int pinRightForward, int pinRightBack, int pinRightSpeed, int pinLeftForward, int pinLeftBack, int pinLeftSpeed) {
    // right side
    pinMode(pinRightForward, OUTPUT);
    pinMode(pinRightBack, OUTPUT);
    pinMode(pinRightSpeed, OUTPUT);
    this->pinsRight[0] = pinRightForward;
    this->pinsRight[1] = pinRightBack;
    this->pinsRight[2] = pinRightSpeed;
    // left side
    pinMode(pinLeftForward, OUTPUT);
    pinMode(pinLeftBack, OUTPUT);
    pinMode(pinLeftSpeed, OUTPUT);
    this->pinsLeft[0] = pinLeftForward;
    this->pinsLeft[1] = pinLeftBack;
    this->pinsLeft[2] = pinLeftSpeed;

    this->pinsAttached = true;
}

void Wheels::initLCD() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  printSpeedLeft();
  printSpeedRight();
}

void Wheels::printSpeedLeft() {
    this->updateBeeper();  
    lcd.setCursor(0, 1);
    
    if (this->speedLeft == 0 || this-> dirLeft == 0) {
      lcd.print("0000");
      return;
    }

    if (this->dirLeft == 1) {
      lcd.print(0);
    } else {
      lcd.print('-');
    }

    if (this->speedLeft < 100) {
      lcd.print(0);
    }

    if (this->speedLeft < 10) {
      lcd.print(0);
    }

    lcd.print(this->speedLeft);
}

void Wheels::printSpeedRight() {
    this->updateBeeper();
    lcd.setCursor(12, 1);
    
    if (this->speedRight == 0 || this-> dirRight == 0) {
      lcd.print("0000");
      return;
    }

    if (this->dirRight == 1) {
      lcd.print(0);
    } else {
      lcd.print('-');
    }

    if (this->speedRight < 100) {
      lcd.print(0);
    }

    if (this->speedRight < 10) {
      lcd.print(0);
    }

    lcd.print(this->speedRight);
}

void Wheels::setSpeedRight(uint8_t s) {
    if(this->pinsAttached) {
        analogWrite(this->pinsRight[2], s);
        this->speedRight = s;
        printSpeedRight();
    }
}

void Wheels::setSpeedLeft(uint8_t s) {
    if(this->pinsAttached) {
        analogWrite(this->pinsLeft[2], s);
        this->speedLeft = s;
        printSpeedLeft();
    }
}

void Wheels::setSpeed(uint8_t s) {
    setSpeedLeft(s);
    setSpeedRight(s);
}

void Wheels::forwardLeft() {
    if(this->pinsAttached) {
        SET_MOVEMENT(pinsLeft, HIGH, LOW);
        this->dirLeft = 1;
        printSpeedLeft();
    }
}

void Wheels::forwardRight() {
    if(this->pinsAttached) {
        SET_MOVEMENT(pinsRight, HIGH, LOW);
        this->dirRight = 1;
        printSpeedRight();
    }
}

void Wheels::backLeft() {
    if(this->pinsAttached) {
        SET_MOVEMENT(pinsLeft, LOW, HIGH);
        this->dirLeft = -1;
        printSpeedLeft();
    }
}

void Wheels::backRight() {
    if(this->pinsAttached) {
        SET_MOVEMENT(pinsRight, LOW, HIGH);
        this->dirRight = -1;
        printSpeedRight();
    }
}

void Wheels::forward() {
    this->forwardLeft();
    this->forwardRight();
}

void Wheels::back() {
    this->backLeft();
    this->backRight();
}

void Wheels::stopLeft() {
    if(this->pinsAttached) {
        SET_MOVEMENT(pinsLeft, LOW, LOW);
        this->dirLeft = 0;
        printSpeedLeft();
    }
}

void Wheels::stopRight() {
    if(this->pinsAttached) {
        SET_MOVEMENT(pinsRight, LOW, LOW);
        this->dirRight = 0;
        printSpeedRight();
    }
}

void Wheels::stop() {
    this->stopLeft();
    this->stopRight();
}

void Wheels::goForward(int cm) {
    this->setSpeed(200);
    this->forward();
    delay(cm*100);
    this->stop();
}

void Wheels::goBack(int cm) {
    this->setSpeed(200);
    this->back();
    delay(cm*100);
    this->stop();
}

void Wheels::updateBeeper() {
    if((this->dirLeft == -1 && this->speedLeft > 0) || (this->dirRight == -1 && this->speedRight > 0)) {
        Timer1.detachInterrupt();
        if(this->dirLeft == -1 && this->dirRight == -1) {
            Timer1.attachInterrupt(doBeep, 100000000 / (this->speedLeft + this->speedRight));
        } else if(this->dirLeft == -1) {
            Timer1.attachInterrupt(doBeep, 100000000 / this->speedLeft);
        } else { // if(this->dirRight == -1)
            Timer1.attachInterrupt(doBeep, 100000000 / this->speedRight);
        }
    } else {
        Timer1.detachInterrupt();
        digitalWrite(BEEPER, LOW);
    }
}

void doBeep() {
  digitalWrite(BEEPER, digitalRead(BEEPER) ^ 1);
}


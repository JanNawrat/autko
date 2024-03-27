#include "Wheels.h"

byte LCDAddress = 0x27;

LiquidCrystal_I2C lcd(LCDAddress, 16, 2);

#define SET_MOVEMENT(side,f,b) digitalWrite( side[0], f);\
                               digitalWrite( side[1], b)

Wheels::Wheels() {}

void Wheels::attachRight(int pF, int pB, int pS) {
    pinMode(pF, OUTPUT);
    pinMode(pB, OUTPUT);
    pinMode(pS, OUTPUT);
    this->pinsRight[0] = pF;
    this->pinsRight[1] = pB;
    this->pinsRight[2] = pS;
}


void Wheels::attachLeft(int pF, int pB, int pS) {
    pinMode(pF, OUTPUT);
    pinMode(pB, OUTPUT);
    pinMode(pS, OUTPUT);
    this->pinsLeft[0] = pF;
    this->pinsLeft[1] = pB;
    this->pinsLeft[2] = pS;
}

void Wheels::initLCD() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  printSpeedLeft();
  printSpeedRight();
}

void Wheels::printSpeedLeft() {   
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
    analogWrite(this->pinsRight[2], s);
    this->speedRight = s;
    printSpeedRight();
}

void Wheels::setSpeedLeft(uint8_t s) {
    analogWrite(this->pinsLeft[2], s);
    this->speedLeft = s;
    printSpeedLeft();
}

void Wheels::setSpeed(uint8_t s) {
    setSpeedLeft(s);
    setSpeedRight(s);
}

void Wheels::attach(int pRF, int pRB, int pRS, int pLF, int pLB, int pLS) {
    this->attachRight(pRF, pRB, pRS);
    this->attachLeft(pLF, pLB, pLS);
}

void Wheels::forwardLeft() {
    SET_MOVEMENT(pinsLeft, HIGH, LOW);
    this->dirLeft = 1;
    printSpeedLeft();
}

void Wheels::forwardRight() {
    SET_MOVEMENT(pinsRight, HIGH, LOW);
    this->dirRight = 1;
    printSpeedRight();
}

void Wheels::backLeft() {
    SET_MOVEMENT(pinsLeft, LOW, HIGH);
    this->dirLeft = -1;
    printSpeedLeft();
}

void Wheels::backRight() {
    SET_MOVEMENT(pinsRight, LOW, HIGH);
    this->dirRight = -1;
    printSpeedRight();
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
    SET_MOVEMENT(pinsLeft, LOW, LOW);
    this->dirLeft = 0;
    printSpeedLeft();
}

void Wheels::stopRight() {
    SET_MOVEMENT(pinsRight, LOW, LOW);
    this->dirRight = 0;
    printSpeedRight();
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

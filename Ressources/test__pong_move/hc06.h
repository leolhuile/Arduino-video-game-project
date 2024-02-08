#ifndef __HC_06__
  #define _hc06_ALIM 8

  void hc06_setup() {
    Serial.begin(38400);
    Serial1.begin(38400);
    //DEBUG :: To be sure everything is working :
    Serial.println("Enter AT Commands:");

    // Powering HC-06 (bcs the 5V pin is already taken) : 
    pinMode(_hc06_ALIM, OUTPUT);
    digitalWrite(_hc06_ALIM, HIGH);
  }

  #define __HC_06__
#endif
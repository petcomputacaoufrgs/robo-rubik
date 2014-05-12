class Robot
{
 private:
 uint8_t _ledPin;
 long _turnOffTime;

public:
 AMLed(uint8_t pin);
 void setOn();
 void setOff();

 // Turn the led on for a given amount of time (relies on a call to check() in the main loop())
 void setOnForTime(int millis);
 void check();
};

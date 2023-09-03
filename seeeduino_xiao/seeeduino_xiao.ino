#include <Mouse.h>

void setup() {
  Serial.begin( 115200 );
  Mouse.begin();
}

void loop() {
  if (Serial.available() > 1) { 
    byte x = Serial.read();
    byte y = Serial.read();
    Mouse.move(x, y, 0);
  }
}

#include <FourSegDisplay.h>

FourSegDisplay seg_display;
// Temperature measurement variables 
float power_voltage = 4.7;
float fixed_reading = 0;
int temp_pin = A0;

// Button & control variables 
int btn_pin = A5;
int prev_state = LOW;
int current_state;
int display_state = HIGH;
long push_time = 0;

void setup() {
  // Set pins for 4-digit 7-segment display
  seg_display.setPinC1(2);
  seg_display.setPinC2(3);
  seg_display.setPinC3(4);
  seg_display.setPinC4(5);
  seg_display.setPinA(6);
  seg_display.setPinB(7);
  seg_display.setPinC(8);
  seg_display.setPinD(9);
  seg_display.setPinE(10);
  seg_display.setPinF(11);
  seg_display.setPinG(12);
  seg_display.setPinDot(13);

  // Button Pins
  pinMode(btn_pin, INPUT);
}

void loop() {
  // Get and store temperature value
  float temp = temp_reading();

  // change fixed_reading only when there are temperature changes
  // that differ by more than 0.5 degrees celsius (avoid constant flickering)
  if(abs(temp - fixed_reading) > 0.5) {
    fixed_reading = temp;
  }

  // Button controls to turn on and off the 4 segment display
  current_state = digitalRead(btn_pin);

  // Toggle button state when pushed
  if (current_state == HIGH && prev_state == LOW && millis() - push_time > 200) {
    if (display_state == HIGH) {
      display_state = LOW;
    } else {
      display_state = HIGH;
    }
    push_time = millis();
  }
  
  prev_state = current_state;

  // Turn on or off display depending on button state
  if (display_state == HIGH) {
    String str_temp = String(fixed_reading, 2);
    seg_display.printNum(str_temp);
  } else {
    seg_display.clearDisplay();
  }
}


// Method to calculate temperature value in degrees celsius
float temp_reading(){
  float sensorValue = analogRead(temp_pin);
  // Convert voltage reading to degrees celsius
  return (sensorValue/1024)*power_voltage*100;
}

#define low_level 0
#define high_level 4
#define motor 12

// variables
// int tank_level = 0; // 0 to 1023
int tank_level_percentage = 0; // 0 to 100 %
unsigned long start_millis; // initial time
unsigned long current_millis; // current time
const unsigned long period = 1000; // number of milliseconds

void setup() {
  pinMode(low_level, INPUT); // low level - flash btn
  pinMode(high_level, INPUT); // high level - push btn
  pinMode(motor, OUTPUT); // motor running - green led

  Serial.begin(9600);
  start_millis = millis();
}

void loop() {
  current_millis = millis();
  // tank_level = analogRead(A0); // read LDR sensor - simulate tank level
  tank_level_percentage = map(analogRead(A0), 0, 1023, 100, 0);
  // Serial.println(tank_level_percentage);

  if (digitalRead(low_level) == false && digitalRead(high_level) == false) {
    digitalWrite(motor, false); // turn off motor
  } else if (digitalRead(low_level) == true && digitalRead(high_level) == true) {
    digitalWrite(motor, true); // turn on motor
  } else if (digitalRead(low_level) == false && digitalRead(high_level) == true) {
    // keep the same motor state - do nothing
  } else if (digitalRead(low_level) == true && digitalRead(high_level) == false) {
    Serial.print("FAULT - High level sensor malfuntion.");
    digitalWrite(motor, 0);
    delay(10000);
  } // if statement

  if (current_millis - start_millis >= period) {
    // print sensor values
    Serial.print(!digitalRead(low_level));
    Serial.print(", ");
    Serial.print(!digitalRead(high_level));
    Serial.print(", ");
    Serial.print(digitalRead(motor));
    Serial.print(", ");
    Serial.print(tank_level_percentage);
    Serial.print("\n");
    /*byte sensor_values[] = {low_level, high_level, tank_level_percentage};
      Serial.write(sensor_values, 3);*/

    start_millis = current_millis;
  } // if statement

} // void loop

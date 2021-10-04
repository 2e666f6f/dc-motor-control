#define SENSOR_PIN A0

void setup() {
    Serial.begin(115200);
}

void loop() {
    // Continuously read values from the IR sensor and print them to the
    // serial monitor
    if Serial.available() {
        reading = analogRead(SENSOR_PIN);
        Serial.println(reading);
        delay(1000);
    }
}

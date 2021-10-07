double reading0;
double reading1;

void setup() {
    Serial.begin(115200);
}

void loop() {
    // Continuously read values from the IR sensor and print them to the
    // serial monitor
    if (Serial.available()) {
        reading0 = analogRead(A0);
        reading1 = analogRead(A1);
        Serial.print("A0:");
        Serial.println(reading0);
        Serial.print("A1:");
        Serial.println(reading1);
        delay(1000);
    }
}

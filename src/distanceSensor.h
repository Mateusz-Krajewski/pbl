#include <Arduino.h>
#include <Ultrasonic.h>

class UltraSonic {
    private:
        Ultrasonic ultrasonic;
    public:
        void setup() {
            ultrasonic = Ultrasonic(12,13);
        }

        int read() {
            int distance = ultrasonic.read();
            Serial.print("Distance in CM: ");
            Serial.println(distance);
            return distance;
        }
};
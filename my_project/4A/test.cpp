#include <iostream>
#include <string>

/* =========================
   ENUM: finite set of states
   ========================= */
enum class SensorStatus {
    OK,
    WARNING,
    ERROR
};

/* =========================
   STRUCT: plain data bundle
   ========================= */
struct SensorReading {
    double value;        // measured value
    std::string unit;    // e.g. "C"
};

/* =========================
   CLASS: behaviour + rules
   ========================= */
class Sensor {
    SensorStatus status;
    SensorReading reading;

public:
    Sensor(double v, const std::string& u)
        : status(SensorStatus::OK), reading{v, u} {}

    void update(double new_value) {
        reading.value = new_value;

        // enforce rules
        if (new_value < 0)
            status = SensorStatus::ERROR;
        else if (new_value > 80)
            status = SensorStatus::WARNING;
        else
            status = SensorStatus::OK;
    }

    void print() const {
        std::cout << "Value: " << reading.value << reading.unit << " | Status: ";

        switch (status) {
            case SensorStatus::OK:      std::cout << "OK"; break;
            case SensorStatus::WARNING: std::cout << "WARNING"; break;
            case SensorStatus::ERROR:   std::cout << "ERROR"; break;
        }

        std::cout << "\n";
    }
};

int main() {
    Sensor s(25.0, "C");

    s.print();

    s.update(90.0);
    s.print();

    s.update(-5.0);
    s.print();
}
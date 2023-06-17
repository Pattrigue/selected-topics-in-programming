#include "Car.h"

class Car::Impl {
public:
    Impl(int maxSpeed, int fuel) : maxSpeed(maxSpeed), currentSpeed(0), fuel(fuel) {}

    void Accelerate(int amount) {
        currentSpeed += amount;
        if (currentSpeed > maxSpeed) {
            currentSpeed = maxSpeed;
        }
        fuel--;
    }

    void Brake(int amount) {
        currentSpeed -= amount;
        if (currentSpeed < 0) {
            currentSpeed = 0;
        }
    }

    void Refuel(int amount) {
        fuel += amount;
    }

    int GetSpeed() const {
        return currentSpeed;
    }

    int GetFuel() const {
        return fuel;
    }

private:
    int maxSpeed;
    int currentSpeed;
    int fuel;
};

Car::Car(int maxSpeed, int fuel) : pimpl(std::make_unique<Impl>(maxSpeed, fuel)) {}

Car::~Car() = default; // unique_ptr will automatically delete the Impl object

void Car::Accelerate(int amount) { pimpl->Accelerate(amount); }

void Car::Brake(int amount) { pimpl->Brake(amount); }

void Car::Refuel(int amount) { pimpl->Refuel(amount); }

int Car::GetSpeed() const { return pimpl->GetSpeed(); }

int Car::GetFuel() const { return pimpl->GetFuel(); }

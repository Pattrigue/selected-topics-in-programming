#ifndef PIMPL_CAR_H
#define PIMPL_CAR_H

#include <memory>

class Car {
public:
    Car(int maxSpeed, int fuel);
    ~Car();

    void Accelerate(int amount);
    void Brake(int amount);
    void Refuel(int amount);
    int  GetSpeed() const;
    int  GetFuel() const;

private:
    class Impl; // forward declaration
    std::unique_ptr<Impl> pimpl;
};


#endif

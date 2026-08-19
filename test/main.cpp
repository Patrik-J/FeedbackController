#include "pid.hpp"

#include <iostream>

int main() {
    PIDParams params;
    params.gains.proportional = 5.0;
    params.gains.integral = 1.0;
    params.gains.derivative = 0.01;
    params.setpoint = 1.0;

    PIDController pid = PIDController(params);    

    std::cout << pid << std::endl;

};
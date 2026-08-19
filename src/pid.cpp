#include "pid.hpp"

PIDController::PIDController() : stored_vals(5) {};

PIDController::PIDController(PIDParams params) : stored_vals(params.stored_vals) {
    this->setpoint = params.setpoint;
    this->gains = params.gains;
    this->time_integral_cap = params.time_integral_cap;
    this->derivative_cap = params.derivative_cap;

    this->init();
};

PIDController::PIDController(PIDGains gains, double setpoint, unsigned int stored_vals = 5) : stored_vals(stored_vals) {
    this->setpoint = setpoint;
    this->gains = gains;

    this->init();
};

PIDController::~PIDController() {
    delete[] this->last_vals;
    delete[] this->last_times;
};

void PIDController::init() {
    this->last_vals = zeroArray(this->stored_vals);
    this->last_times = zeroArray(this->stored_vals);
    this->last_input_index = 0;

    this->timer = Timer();
    this->timer.start();
};

double PIDController::loop(double input) {
    // determine difference 
    double diff = this->setpoint - input;

    // store new difference
    unsigned int lii = (this->last_input_index + 1) % this->stored_vals;
    this->last_vals[lii] = diff;
    this->last_times[lii] = this->timer.currentMicros();
    this->last_input_index = lii;

    // total
    double sum = 0.0;

    // proportional part
    sum += this->gains.proportional * diff;

    // integral part;
    this->integrate();
    sum += this->gains.integral * this->time_integral;

    // derivative part
    this->differentiate();
    sum += this->gains.derivative * this->derivative;

    // return sum
    return sum;
};

void PIDController::setCaps(double time_integral, double derivative) {
    this->time_integral_cap = time_integral;
    this->derivative_cap = derivative;
}; 

PIDParams PIDController::getParams() {
    PIDParams params = {
        this->gains,
        this->stored_vals,
        this->setpoint,
        this->time_integral_cap,
        this->derivative_cap
    };
    return params;
};

void PIDController::integrate() {
    unsigned int lii = this->last_input_index;

    double dt = this->last_times[lii] - this->last_times[(lii - 1) % this->stored_vals];
    double I = this->last_vals[lii] - this->last_vals[(lii - 1) % this->stored_vals];

    // add new integral
    this->time_integral += dt*I;

    // check if the time integral is too large
    this->time_integral = (abs(this->time_integral) > this->time_integral_cap) ? sign(this->time_integral) * this->time_integral_cap : this->time_integral;
};

void PIDController::differentiate() {
    // three-point central difference formula
    
    double deriv = 0.0;

    unsigned int lii = this->last_input_index;

    double h = this->last_times[lii] - this->last_times[(lii - 1) % this->stored_vals];

    double f1 = this->last_vals[lii];
    double f2 = this->last_vals[(lii - 2) % this->stored_vals];

    deriv = (f1 - f2)/(2*h);

    this->derivative = (deriv > this->derivative_cap) ? sign(deriv) * this->derivative_cap : deriv;
};

double* zeroArray(unsigned int length) {
    double* d = new double[length];
    for (unsigned int i = 0; i < length; i++) {
        d[i] = 0.0;
    } 
    return d;
};

double sign(double input) {
    if (input >= 0.0) 
        return 1.0;
    else
        return -1.0;  
};
#ifndef PID_HPP
#define PID_HPP

#include "feedbackcontroller.hpp"
#include "timer.hpp"

struct PIDGains {
    double proportional;
    double integral;
    double derivative;
};

struct PIDParams {
    PIDGains gains;
    unsigned int stored_vals = 5;
    double setpoint;
    double time_integral_cap = 1e3;
    double derivative_cap = 1.0;
};

class PIDController : public FeedbackController {
    public:
        PIDController();
        PIDController(PIDParams params);
        PIDController(PIDGains gains, double setpoint, unsigned int stored_vals = 5);
        ~PIDController();

        void setCaps(double time_integral, double derivative);
        PIDParams getParams();

        double loop(double input) override;
        void init() override;

    private:
        // stored values
        double* last_vals;
        double* last_times;
        unsigned int last_input_index;

        // integration and derivation
        void integrate();
        void differentiate();

        // PID params
        PIDGains gains;
        const unsigned int stored_vals;
        double setpoint;

        // time integral
        double time_integral = 0.0;
        double time_integral_cap = 1e3;

        // derivative
        double derivative = 0.0;
        double derivative_cap = 1.0;

        // timer
        Timer timer;
};

double* zeroArray(unsigned int length);
double sign(double input);

#endif 
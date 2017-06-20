#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	PID::Kp = Kp;
	PID::Ki = Ki;
	PID::Kd = Kd;
	PID::p_error = 0;
	PID::d_error = 0;
	PID::i_error = 0;
	PID::past_cte = 0;

}

void PID::UpdateError(double cte) {
	d_error = cte-past_cte;
	past_cte = cte;
	i_error += cte;
	p_error = cte;
}

double PID::TotalError() {
	double error = -(p_error*Kp + i_error*Ki + d_error*Kp);
	if (error<-1){
		return -1;
	}
	if (error>1){
		return 1;
	}
	return error;
}


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
	if (PID::twiddle_tunning){
		EvalSteady(steady_steps);

	}
	if (error<-1){
		return -1;
	}
	if (error>1){
		return 1;
	}
	return error;
}

void PID::Twiddle(double cte){
   if (!PID::twiddle_initialized){
   	Init(0, 0, 0);
   	PID::delta_p = 1; 
   	PID::delta_i = 1;
   	PID::delta_d = .5;
   	PID::steady_steps = 0;
   	PID::twiddle_initialized = true;
   	PID::cumulative_error= 0;
   }

   //PID::best_error = EvalSteady(steady_steps);

}

void PID::EvalSteady(int total_steps){
	past_cte = 0;
	if(PID::steady_steps >= total_steps){
		PID::best_error = PID::cumulative_error / total_steps;
	}

}

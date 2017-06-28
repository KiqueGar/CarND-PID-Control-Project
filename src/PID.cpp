#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/
//bool fast_correct = false;
double cte_debug;
PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd, bool tune) {
	PID::Kp = Kp;
	PID::Ki = Ki;
	PID::Kd = Kd;
	PID::p_error = 0;
	PID::d_error = 0;
	PID::i_error = 0;
	PID::past_cte = 0;

	PID::twiddle_tunning = tune;
	dp= {0.1*Kp, 0.1*Ki, 0.1*Kd};
	current_step =1;
	fast_steps =1;
	//Start tunning on Kd
	param_index=1;
	steady_steps = 300;
	eval_steps = 2200;
	cumulative_error=0;
	best_error = 999999999;
	adding = false;
	substracting = false;
}

void PID::UpdateError(double cte) {
	d_error = cte-past_cte;
	past_cte = cte;
	i_error += cte;
	p_error = cte;
	cte_debug = cte;

	//Update cumulative error after a steady cicle
	if (fast_steps % (steady_steps+ eval_steps) > steady_steps){
		cumulative_error += cte*cte;
		if(cumulative_error > best_error && twiddle_tunning){
			cout << "Worsening! Next iteration" << endl;
			fast_steps = 0;
		}
		if(best_error<1.2*(eval_steps+steady_steps) && twiddle_tunning){
			twiddle_tunning = false;
			cout << "Finished Tunning!!"<< endl;
			cout << "Best coeficients:	" << Kp << "	" << Ki << "	" << Kd << endl << endl;
		}
	}

	//Update k's
	if(twiddle_tunning && fast_steps % (steady_steps + eval_steps) == 0){
		cout << "Step: " << current_step << endl;
		cout << "Cumulative Error: " << cumulative_error << endl;
		cout << "Best Error: " << best_error << endl << endl;
//		cout << "PID coeficients:	" << Kp << "	" << Ki << "	" << Kd << endl;
		if (cumulative_error< best_error){
			cout << "Best coeficients:	" << Kp << "	" << Ki << "	" << Kd << endl << endl;
			best_error = cumulative_error;
			if(current_step != steady_steps + eval_steps){
				dp[param_index] *=1.1;
			}
			//next parameter
			param_index = (param_index+1)%3;
			adding = substracting = false;
		}
		if(!adding && !substracting){
			//Add dp[index] to param[i]
			TuneParameter(param_index, dp[param_index]);
			adding = true;
		}
		else if (adding && !substracting){
			//Substract dp[index] from param[i]
			TuneParameter(param_index, -2*dp[param_index]);
			substracting = true;
		}
		else{
			// Reduce dp and try again later
			TuneParameter(param_index, dp[param_index]);
			dp[param_index]*=0.9;
			param_index = (param_index + 1)%3;
			if(dp[param_index]==0){
				param_index = (param_index + 1)%3;
			}
			adding = substracting = false;
		}
		cumulative_error = 0;

	}
	current_step++;
	fast_steps++;
}

double PID::TotalError() {
	double error = -(p_error*Kp + i_error*Ki + d_error*Kp);
	//cout << "Pecentage of contribution in cte: " << cte_debug << endl;
	//cout << p_error*Kp/error <<"   "<< i_error*Ki/error <<"   " << d_error*Kp/error << endl;
	if (error<-1){
		return -1;
	}
	if (error>1){
		return 1;
	}
	return error;
}

void PID::TuneParameter(int index, double value){
	if (index == 0){
		Kp += value;
	}
	else if (index == 1){
		Ki += value;
	}
	else if (index == 2){
		Kd += value;
	}
	else{ cout << "TuneParameter: index out of bounds: " << index << endl;}
}
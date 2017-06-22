#ifndef PID_H
#define PID_H
#include <vector>
#include <iostream>

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;
  double past_cte;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;

  /*
  * Twiddle vars
  */
  bool twiddle_tunning;
  bool adding, substracting;
  bool twiddle_initialized =false;    //???
  std::vector<double> dp;
  int param_index;
  int steady_steps;
  int current_step;
  int eval_steps;
  float best_error;
  float cumulative_error;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd, bool tune);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  /*
  * Tune parameter
  */
  void TuneParameter(int index, double value);

};

#endif /* PID_H */

#ifndef PID_H
#define PID_H

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
  bool twiddle_tunning = false;
  bool twiddle_initialized =false;
  double delta_p;
  double delta_i;
  double delta_d;
  int steady_steps;
  int current_step;
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
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  /*
  * Twiddle
  */
  void Twiddle(double cte);

  void EvalSteady(int total_steps);

};

#endif /* PID_H */

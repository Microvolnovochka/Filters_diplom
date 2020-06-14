#ifndef KALMANFILTER_H
#define KALMANFILTER_H
#include "matrix.h"

class  KalmanFilter
{
public:
    KalmanFilter(int state_dimension,
                 int observation_dimension);
    void alloc_filter(double _x,double _y,double dt,double _vX,double _vY,double R, double _aX = 0, double _aY = 0);

    void free_filter();

    void update();

    /* Just the prediction phase of update. */
    void predict();
    /* Just the estimation phase of update. */
    void estimate();

    void setObservation(double _x,double _y);

    double getX();

    double getY();
private:
  /* This group of matrices must be specified by the user. */
  /* F_k */
  Matrix state_transition;
  /* H_k */
  Matrix observation_model;
  /* Q_k */
  Matrix process_noise_covariance;
  /* R_k */
  Matrix observation_noise_covariance;
  /*B_k*/
  Matrix B;
  /*u_k*/
  Matrix u;


  /* The observation is modified by the user before every time step. */
  /* z_k */
  Matrix observation;

  /* This group of matrices are updated every time step by the filter. */
  /* x-hat_k|k-1 */
  Matrix predicted_state;
  /* P_k|k-1 */
  Matrix predicted_estimate_covariance;
  /* y-tilde_k */
  Matrix innovation;
  /* S_k */
  Matrix innovation_covariance;
  /* S_k^-1 */
  Matrix inverse_innovation_covariance;
  /* K_k */
  Matrix optimal_gain;
  /* x-hat_k|k */
  Matrix state_estimate;
  /* P_k|k */
  Matrix estimate_covariance;

  /* This group is used for intermediate calculations */
  Matrix vertical_scratch;
  Matrix small_square_scratch;
  Matrix B_u;
  Matrix big_square_scratch;

};
#endif // KALMANFILTER_H

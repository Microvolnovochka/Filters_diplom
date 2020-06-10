#include "kalmanfilter.h"

#include <QDebug>

KalmanFilter::KalmanFilter(int state_dimension,
              int observation_dimension)
{
  state_transition = alloc_matrix(state_dimension,
                    state_dimension);
  observation_model = alloc_matrix(observation_dimension,
                     state_dimension);
  process_noise_covariance = alloc_matrix(state_dimension,
                        state_dimension);
  observation_noise_covariance = alloc_matrix(observation_dimension,
                        observation_dimension);

  observation = alloc_matrix(observation_dimension, 1);

  predicted_state = alloc_matrix(state_dimension, 1);
  predicted_estimate_covariance = alloc_matrix(state_dimension,
                         state_dimension);
  innovation = alloc_matrix(observation_dimension, 1);
  innovation_covariance = alloc_matrix(observation_dimension,
                     observation_dimension);
  inverse_innovation_covariance = alloc_matrix(observation_dimension,
                         observation_dimension);
  optimal_gain = alloc_matrix(state_dimension,
                observation_dimension);
  state_estimate = alloc_matrix(state_dimension, 1);
  estimate_covariance = alloc_matrix(state_dimension,
                       state_dimension);

  vertical_scratch = alloc_matrix(state_dimension,
                    observation_dimension);
  small_square_scratch = alloc_matrix(observation_dimension,
                    observation_dimension);
  big_square_scratch = alloc_matrix(state_dimension,
                      state_dimension);
}

void KalmanFilter::alloc_filter(double _x,double _y,double dt,double _vX,double _vY,double R)
{
    set_identity_matrix(state_transition);
    state_transition.data[0][1] = dt;
    state_transition.data[2][3] = dt;
    observation_model.data[0][0] = 1;
    observation_model.data[1][2] = 1;
    observation_noise_covariance.data[0][0] = pow(R,1/2);
    observation_noise_covariance.data[1][1] = pow(R,1/2);
    set_identity_matrix(estimate_covariance);
    state_estimate.data[0][0] = _x;
    state_estimate.data[1][0] = _vX;
    state_estimate.data[2][0] = _y;
    state_estimate.data[3][0] = _vY;
}

void KalmanFilter::setObservation(double _x, double _y)
{
    observation.data[0][0] = _x;
    observation.data[1][0] = _y;
}

double KalmanFilter::getX()
{
    return state_estimate.data[0][0];
}

double KalmanFilter::getY()
{
    return state_estimate.data[2][0];
}

void KalmanFilter::free_filter()
{
  free_matrix(state_transition);
  free_matrix(observation_model);
  free_matrix(process_noise_covariance);
  free_matrix(observation_noise_covariance);

  free_matrix(observation);

  free_matrix(predicted_state);
  free_matrix(predicted_estimate_covariance);
  free_matrix(innovation);
  free_matrix(innovation_covariance);
  free_matrix(inverse_innovation_covariance);
  free_matrix(optimal_gain);
  free_matrix(state_estimate);
  free_matrix(estimate_covariance);

  free_matrix(vertical_scratch);
  free_matrix(small_square_scratch);
  free_matrix(big_square_scratch);
}

void KalmanFilter::update()
{
  this->predict();
  this->estimate();
}

void KalmanFilter::predict()
{

  multiply_matrix(state_transition, state_estimate,
         predicted_state);

  multiply_matrix(state_transition, estimate_covariance,
          big_square_scratch);
  multiply_by_transpose_matrix(big_square_scratch, state_transition,
                   predicted_estimate_covariance);
  add_matrix(predicted_estimate_covariance, process_noise_covariance,
         predicted_estimate_covariance);
}

void KalmanFilter::estimate() {
  multiply_matrix(observation_model, predicted_state,
          innovation);
  subtract_matrix(observation, innovation,
          innovation);

  multiply_by_transpose_matrix(predicted_estimate_covariance,
                   observation_model,
                   vertical_scratch);
  multiply_matrix(observation_model, vertical_scratch,
          innovation_covariance);
  add_matrix(innovation_covariance, observation_noise_covariance,
         innovation_covariance);

  destructive_invert_matrix(innovation_covariance,
                inverse_innovation_covariance);

  multiply_matrix(vertical_scratch, inverse_innovation_covariance,
          optimal_gain);

  multiply_matrix(optimal_gain, innovation,
          state_estimate);
  add_matrix(state_estimate, predicted_state,
         state_estimate);

  multiply_matrix(optimal_gain, observation_model,
          big_square_scratch);
  subtract_from_identity_matrix(big_square_scratch);
  multiply_matrix(big_square_scratch, predicted_estimate_covariance,
          estimate_covariance);
}

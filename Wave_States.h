#pragma once
#ifndef WAVE_STATES_H
#define WAVE_STATES_H
#endif // !1

#include "Eigen/Dense"

struct Wave_State
{
	Eigen::VectorXd Energy_Vector;
	Eigen::MatrixXd Orthonormal_Transformation;
};

Wave_State Hexagon5(double Scale_Distance, int Num_Layers);

Wave_State Hexagon5(double Scale_Distance);

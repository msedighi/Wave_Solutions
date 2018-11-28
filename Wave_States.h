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

Wave_State HexagonX(int Num_Layers, bool noise_flag = false);

Wave_State HexagonX(int Num_Layers, double Scale_Distance, bool noise_flag = false);

Wave_State Hexagon5(double Scale_Distance, bool noise_flag = false);

Wave_State Hexagon5(bool noise_flag = false);

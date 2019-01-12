#pragma once
#define _USE_MATH_DEFINES
#ifndef TRIANGLETILE_H
#define TRIANGLETILE_H
#endif // !1
#include "Eigen/Dense"
#include "time.h"

struct Wave_State
{
	Eigen::VectorXd Energy_Vector;
	Eigen::MatrixXd Orthonormal_Transformation;
};

class TriangleTile
{
private:
	double* base_1;
	double* base_2;
	int i_hub;

public:
	const int dimension = 2;
	double** positions;
	int Num_Points;
	int Num_Layers;

	Wave_State Hexagon_Wave();
	Wave_State Hexagon_Wave(double Scale_Distance);

	TriangleTile(int num_layers, double noise, bool noise_flag = true);
	TriangleTile(int num_layers, bool noise_flag = false);
	TriangleTile(bool noise_flag = false);
	~TriangleTile();
};


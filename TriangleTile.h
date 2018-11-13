#pragma once
#define _USE_MATH_DEFINES
#ifndef TRIANGLETILE_H
#define TRIANGLETILE_H
#endif // !1
#include "Eigen/Dense"

class TriangleTile
{
private:
	const int dimension = 2;
	double* base_1;
	double* base_2;
	int i_hub;

public:
	double** positions;
	int Num_Points;
	int Num_Layers;
	TriangleTile(int num_layers);
	TriangleTile();
	~TriangleTile();
};


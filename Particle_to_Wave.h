#pragma once
#ifndef PARTICLE_TO_WAVE_H
#define PARTICLE_TO_WAVE_H
#endif // !1

#include "Eigen/Dense"
#include "TriangleTile.h"

class WaveParticle_Interface
{	
public:
	TriangleTile* Tile;

	Eigen::VectorXd Run(Eigen::VectorXd global_points_state, int num_points);
	Eigen::VectorXd Run(Eigen::VectorXd points_state, Eigen::MatrixXd orthogonal_transformation, int num_points);
	Eigen::VectorXd Run(double* points_state, int num_points, Eigen::MatrixXd orthogonal_transformation);

	WaveParticle_Interface(int Num_Layers);
	~WaveParticle_Interface();
private:
	Wave_State Hexagon_Waves;

	Eigen::VectorXd acting_global_points_state;
	int num_points;
};
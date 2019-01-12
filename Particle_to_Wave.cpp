#include "stdafx.h"
#include "Particle_to_Wave.h"

//Temp!!!
#include <iostream>

using namespace Eigen;

VectorXd WaveParticle_Interface::Run(VectorXd global_points_state, int num_points)
{

	// Making sure the number of states are the same
	
	if (num_points >= Tile->Num_Points)
		acting_global_points_state = global_points_state.head(Tile->Num_Points);
	else
		acting_global_points_state.head(num_points) = global_points_state;
	//

	VectorXd Out_Wave = Hexagon_Waves.Orthonormal_Transformation.transpose() * acting_global_points_state;

	if (true)
	{
		std::cout << "Hexagon Energies: " << std::endl;
		std::cout << Hexagon_Waves.Energy_Vector << std::endl;
		std::cout << std::endl;
		std::cout << "Hexagon Waves: " << std::endl;
		std::cout << Hexagon_Waves.Orthonormal_Transformation << std::endl;
		std::cout << std::endl;
		std::cout << "Global State: " << std::endl;
		std::cout << global_points_state << std::endl;
		std::cout << std::endl;
		std::cout << "Acting Global State: " << std::endl;
		std::cout << acting_global_points_state << std::endl;
		std::cout << std::endl;
		std::cout << "Tile Wave: " << std::endl;
		std::cout << Out_Wave << std::endl;
		std::cout << std::endl;
	}

	return Out_Wave;
}

VectorXd WaveParticle_Interface::Run(VectorXd points_state, MatrixXd orthogonal_transformation, int num_points)
{
	VectorXd Global_State = orthogonal_transformation * points_state;

	return WaveParticle_Interface::Run(Global_State, num_points);
}

VectorXd WaveParticle_Interface::Run(double* points_state, int num_points, MatrixXd orthogonal_transformation)
{
	VectorXd points_state_vector = VectorXd::Constant(num_points, 0);
	for (int i = 0; i < num_points; i++)
		points_state_vector[i] = points_state[i];

	return WaveParticle_Interface::Run(points_state_vector, orthogonal_transformation, num_points);
}

WaveParticle_Interface::WaveParticle_Interface(int Num_Layers)
{
	//Hexagon_Waves = HexagonX(4, Scale_Distance, noise, false);
	Tile = new TriangleTile(Num_Layers, false);
	Hexagon_Waves = Tile->Hexagon_Wave();	
	acting_global_points_state = VectorXd::Constant(Tile->Num_Points, 0);
}

WaveParticle_Interface::~WaveParticle_Interface()
{
	delete Tile;
}

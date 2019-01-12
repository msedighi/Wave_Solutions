#define _USE_MATH_DEFINES
#include <cmath>  
#include "stdafx.h"
#include "TriangleTile.h"
#include "Eigen/Dense"
#include "iostream"
#include "Data_Structures.h"
#include "Clusters.h"

using namespace Eigen;

Wave_State TriangleTile::Hexagon_Wave()
{
	// Finding "Wave" solutions to a Triangulation of a X (Num_Layers) layer Hexagon
	Wave_State out;

	Distance_Struct Hub_Distances = Distance_Matrix(Euclidean_Distance, positions, Num_Points, dimension);

	Clusters Hierarchical_Clusters = Clusters(Hub_Distances);
	// TEMP!!!
	if (false)
	{
		std::cout << "Min & Max Scale : " << std::endl;
		std::cout << Hierarchical_Clusters.Max_Vacuum_Scale << " , " << Hierarchical_Clusters.Min_Saturation_Scale << std::endl;
		std::cout << std::endl;
	}
	//
	double Scale_Distance = (Hierarchical_Clusters.Max_Vacuum_Scale + Hierarchical_Clusters.Min_Saturation_Scale) / 2.0;

	VectorXd Vac_Hexagon = VectorXd::Constant(Num_Points, 1);
	MatrixXd Correlation_Operator_HexagonX = (Hub_Distances.Operator.array() <= Scale_Distance).cast<double>();
	MatrixXd Mass_Operator_HexagonX = (Correlation_Operator_HexagonX * Vac_Hexagon).asDiagonal();
	MatrixXd Laplacian_HexagonX = Mass_Operator_HexagonX - Correlation_Operator_HexagonX;

	SelfAdjointEigenSolver<MatrixXd> Laplacian_Eigenstructure;
	Laplacian_Eigenstructure.compute(Laplacian_HexagonX);

	out.Energy_Vector = Laplacian_Eigenstructure.eigenvalues().cwiseAbs();
	out.Orthonormal_Transformation = Laplacian_Eigenstructure.eigenvectors().transpose();

	return out;
}

Wave_State TriangleTile::Hexagon_Wave(double Scale_Distance)
{
	// Finding "Wave" solutions to a Triangulation of a X (Num_Layers) layer Hexagon
	Wave_State out;

	Distance_Struct Hub_Distances = Distance_Matrix(Euclidean_Distance, positions, Num_Points, dimension);
	MatrixXd Noise_Operator;
	//if (noise_flag)
	//{
	//	TriangleTile HexagonX_0 = TriangleTile(Num_Layers, false);
	//	Distance_Struct Hub_Distances_0 = Distance_Matrix(Euclidean_Distance, HexagonX_0.positions, HexagonX_0.Num_Points, Dome_Dimension);
	//	Noise_Operator = Hub_Distances.Operator - Hub_Distances_0.Operator;
	//}

	VectorXd Vac_Hexagon = VectorXd::Constant(Num_Points, 1);
	MatrixXd Correlation_Operator_HexagonX;
	//if (noise_flag)
	//	Correlation_Operator_HexagonX = (Hub_Distances.Operator.array() <= Scale_Distance).cast<double>() + Noise_Operator.array();
	//else
	Correlation_Operator_HexagonX = (Hub_Distances.Operator.array() <= Scale_Distance).cast<double>();

	MatrixXd Mass_Operator_HexagonX = (Correlation_Operator_HexagonX * Vac_Hexagon).asDiagonal();
	MatrixXd Laplacian_HexagonX = Mass_Operator_HexagonX - Correlation_Operator_HexagonX;

	SelfAdjointEigenSolver<MatrixXd> Laplacian_Eigenstructure;
	Laplacian_Eigenstructure.compute(Laplacian_HexagonX);

	out.Energy_Vector = Laplacian_Eigenstructure.eigenvalues().cwiseAbs();
	out.Orthonormal_Transformation = Laplacian_Eigenstructure.eigenvectors().transpose();

	return out;
}

TriangleTile::TriangleTile(int num_layers, double noise, bool noise_flag)
{
	Num_Layers = num_layers;
	Num_Points = 1 + 3 * Num_Layers*(Num_Layers - 1);

	base_1 = new double[dimension];
	base_2 = new double[dimension];
	base_1[0] = 1;
	base_1[1] = 0;
	base_2[0] = -cos(M_PI / 3);
	base_2[1] = sin(M_PI / 3);

	positions = new double*[Num_Points];

	i_hub = 0;
	for (int i_1 = 0; i_1 < Num_Layers; i_1++)
	{
		for (int i_2 = 0; i_2 < Num_Layers; i_2++)
		{
			i_hub++;
			positions[i_hub - 1] = new double[dimension];
			for (int j = 0; j < dimension; j++)
			{
				positions[i_hub - 1][j] = i_1 * base_1[j] + i_2 * base_2[j];
			}
			if ((i_1 > 0) || (i_2 > 0))
			{
				i_hub++;
				positions[i_hub - 1] = new double[dimension];
				for (int j = 0; j < dimension; j++)
				{
					positions[i_hub - 1][j] = -i_1 * base_1[j] - i_2 * base_2[j];
				}
			}
		}
	}
	for (int i_1 = 1; i_1 < Num_Layers; i_1++)
	{
		for (int i_2 = 1; i_2 < (Num_Layers - i_1); i_2++)
		{
			i_hub++;
			positions[i_hub - 1] = new double[dimension];
			for (int j = 0; j < dimension; j++)
			{
				positions[i_hub - 1][j] = i_1 * base_1[j] - i_2 * base_2[j];
			}
			i_hub++;
			positions[i_hub - 1] = new double[dimension];
			for (int j = 0; j < dimension; j++)
			{
				positions[i_hub - 1][j] = -i_1 * base_1[j] + i_2 * base_2[j];
			}
		}
	}

	if (noise_flag)
	{
		srand(time(NULL));

		for (int i = 1; i < Num_Points; i++)
		{
			for (int j = 0; j < dimension; j++)
			{
				double noise_value = 2 * noise * static_cast <double> (rand()) / static_cast <double> (RAND_MAX) - noise;
				//double noise = 0.01 * static_cast <double> (rand()) / static_cast <double> (RAND_MAX) - 0.005;
				positions[i][j] += noise_value;
			}
		}
	}

}

TriangleTile::TriangleTile(int num_layers, bool noise_flag):TriangleTile::TriangleTile(num_layers, 0.005, noise_flag) {}

TriangleTile::TriangleTile(bool noise_flag):TriangleTile::TriangleTile(5, noise_flag) {}

TriangleTile::~TriangleTile()
{
	delete[] base_1;
	delete[] base_2;
	for (int i = 0; i < Num_Points; i++)
		delete[] positions[i];
	delete[] positions;
}

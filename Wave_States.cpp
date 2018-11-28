
#include "stdafx.h"
#include "Wave_States.h"
#include "TriangleTile.h"
#include "Data_Structures.h"
#include "Clusters.h"
// TEMP!
#include <iostream>
//
using namespace Eigen;

Wave_State HexagonX(int Num_Layers, bool noise_flag)
{
	// Finding "Wave" solutions to a Triangulation of a X (Num_Layers) layer Hexagon
	Wave_State out;
	int Dome_Dimension = 2;

	TriangleTile HexagonX = TriangleTile(Num_Layers, noise_flag);
	Distance_Struct Hub_Distances = Distance_Matrix(Euclidean_Distance, HexagonX.positions, HexagonX.Num_Points, Dome_Dimension);

	Clusters Hierarchical_Clusters = Clusters(Hub_Distances);
	// TEMP!!!
	std::cout << "Min & Max Scale : " << std::endl;
	std::cout << Hierarchical_Clusters.Max_Vacuum_Scale << " , " << Hierarchical_Clusters.Min_Saturation_Scale << std::endl;
	std::cout << std::endl;
	//
	double Scale_Distance = (Hierarchical_Clusters.Max_Vacuum_Scale + Hierarchical_Clusters.Min_Saturation_Scale) / 2.0;

	VectorXd Vac_Hexagon = VectorXd::Constant(HexagonX.Num_Points, 1);
	MatrixXd Correlation_Operator_HexagonX = (Hub_Distances.Operator.array() <= Scale_Distance).cast<double>();
	MatrixXd Mass_Operator_HexagonX = (Correlation_Operator_HexagonX * Vac_Hexagon).asDiagonal();
	MatrixXd Laplacian_HexagonX = Mass_Operator_HexagonX - Correlation_Operator_HexagonX;

	SelfAdjointEigenSolver<MatrixXd> Laplacian_Eigenstructure;
	Laplacian_Eigenstructure.compute(Laplacian_HexagonX);

	out.Energy_Vector = Laplacian_Eigenstructure.eigenvalues().cwiseAbs();
	out.Orthonormal_Transformation = Laplacian_Eigenstructure.eigenvectors().transpose();

	return out;
}

Wave_State HexagonX(int Num_Layers, double Scale_Distance, bool noise_flag)
{
	// Finding "Wave" solutions to a Triangulation of a X (Num_Layers) layer Hexagon
	Wave_State out;
	int Dome_Dimension = 2;

	TriangleTile HexagonX = TriangleTile(Num_Layers, noise_flag);
	Distance_Struct Hub_Distances = Distance_Matrix(Euclidean_Distance, HexagonX.positions, HexagonX.Num_Points, Dome_Dimension);
	MatrixXd Noise_Operator;
	//if (noise_flag)
	//{
	//	TriangleTile HexagonX_0 = TriangleTile(Num_Layers, false);
	//	Distance_Struct Hub_Distances_0 = Distance_Matrix(Euclidean_Distance, HexagonX_0.positions, HexagonX_0.Num_Points, Dome_Dimension);
	//	Noise_Operator = Hub_Distances.Operator - Hub_Distances_0.Operator;
	//}


	VectorXd Vac_Hexagon = VectorXd::Constant(HexagonX.Num_Points, 1);
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

Wave_State Hexagon5(double Scale_Distance, bool noise_flag)
{
	// Finding "Wave" solutions to a Triangulation of a 5 layer Hexagon
	return HexagonX(Scale_Distance, 5, noise_flag);
}

Wave_State Hexagon5(bool noise_flag)
{
	// Finding "Wave" solutions to a Triangulation of a 5 layer Hexagon
	return HexagonX(5, noise_flag);
}

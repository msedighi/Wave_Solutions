
#include "stdafx.h"
#include "Wave_States.h"
#include "TriangleTile.h"
#include "Data_Structures.h"

using namespace Eigen;

Wave_State Hexagon5(double Scale_Distance, int Num_Layers)
{
	// Finding "Wave" solutions to a Triangulation of a 5 layer Hexagon
	Wave_State out;
	int Dome_Dimension = 2;

	TriangleTile Hexagon5 = TriangleTile(Num_Layers);
	Distance_Struct Hub_Distances = Distance_Matrix(Euclidean_Distance, Hexagon5.positions, Hexagon5.Num_Points, Dome_Dimension);

	VectorXd Vac_Hexagon = VectorXd::Constant(Hexagon5.Num_Points, 1);
	MatrixXd Correlation_Operator_Hexagon5 = (Hub_Distances.Operator.array() < Scale_Distance).cast<double>();
	MatrixXd Mass_Operator_Hexagon5 = (Correlation_Operator_Hexagon5 * Vac_Hexagon).asDiagonal();
	MatrixXd Laplacian_Hexagon5 = Mass_Operator_Hexagon5 - Correlation_Operator_Hexagon5;

	SelfAdjointEigenSolver<MatrixXd> Laplacian_Eigenstructure;
	Laplacian_Eigenstructure.compute(Laplacian_Hexagon5);

	out.Energy_Vector = Laplacian_Eigenstructure.eigenvalues().cwiseAbs();
	out.Orthonormal_Transformation = Laplacian_Eigenstructure.eigenvectors().transpose();

	return out;
}

Wave_State Hexagon5(double Scale_Distance)
{
	// Finding "Wave" solutions to a Triangulation of a 5 layer Hexagon
	Wave_State out;
	int Dome_Dimension = 2;

	TriangleTile Hexagon5 = TriangleTile();
	Distance_Struct Hub_Distances = Distance_Matrix(Euclidean_Distance, Hexagon5.positions, Hexagon5.Num_Points, Dome_Dimension);

	VectorXd Vac_Hexagon = VectorXd::Constant(Hexagon5.Num_Points, 1);
	MatrixXd Correlation_Operator_Hexagon5 = (Hub_Distances.Operator.array() < Scale_Distance).cast<double>();
	MatrixXd Mass_Operator_Hexagon5 = (Correlation_Operator_Hexagon5 * Vac_Hexagon).asDiagonal();
	MatrixXd Laplacian_Hexagon5 = Mass_Operator_Hexagon5 - Correlation_Operator_Hexagon5;

	SelfAdjointEigenSolver<MatrixXd> Laplacian_Eigenstructure;
	Laplacian_Eigenstructure.compute(Laplacian_Hexagon5);

	out.Energy_Vector = Laplacian_Eigenstructure.eigenvalues().cwiseAbs();
	out.Orthonormal_Transformation = Laplacian_Eigenstructure.eigenvectors().transpose();

	return out;
}

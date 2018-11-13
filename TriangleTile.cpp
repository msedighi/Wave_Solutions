#define _USE_MATH_DEFINES
#include <cmath>  
#include "stdafx.h"
#include "TriangleTile.h"
#include "Eigen/Dense"
#include "iostream"

using namespace Eigen;


TriangleTile::TriangleTile(int num_layers)
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
}

TriangleTile::TriangleTile()
{
	//TriangleTile::TriangleTile(5);
	Num_Layers = 5;
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
}

TriangleTile::~TriangleTile()
{
	delete[] base_1;
	delete[] base_2;
	for (int i = 0; i < Num_Points; i++)
		delete[] positions[i];
	delete[] positions;
}

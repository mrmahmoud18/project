#include "Grid.h"

Grid::Grid(int r_x ,int r_y){
	Xsize=r_x ;
	Ysize=r_y ;
	Nodes.resize( Xsize ,std::vector<Node>(Ysize) ) ;
	GridInitializion() ;
}

void Grid::AddGate(std::pair<int, int> r_GateCenter)
{
	for (int i = -2; i <= 2 ; i++)
	{
		for (int j = -3; j <=3 ; j++)
		{
			Nodes[i+r_GateCenter.second][j+r_GateCenter.first].m_Stat = Node::GATE;
		}
	}
	Nodes[r_GateCenter.second][r_GateCenter.first + 4].m_Stat=Node::PINPOINT;
	Nodes[r_GateCenter.second][r_GateCenter.first - 4].m_Stat = Node::PINPOINT;
	Nodes[r_GateCenter.second + 1][r_GateCenter.first - 4].m_Stat = Node::PINPOINT;
	Nodes[r_GateCenter.second - 1][r_GateCenter.first - 4].m_Stat = Node::PINPOINT;
	for (int i = -6; i <= 6; i++)
	{
		for (int j = -6; j <=6 ; j++)
		{
			if (Nodes[i+r_GateCenter.second][j+r_GateCenter.first].m_Stat == Node::NOTHING)
			{
				Nodes[i + r_GateCenter.second][j + r_GateCenter.first].m_Stat = Node::NOCONNECTION;
			}
		}
	}
}

void Grid::DeleteGate(std::pair<int, int> r_GateCenter)
{
	for (int i = -6; i <= 6; i++)
	{
		for (int j = -6; j <= 6; j++)
		{
			if (Nodes[i + r_GateCenter.second][j + r_GateCenter.first].m_Stat == Node::GATE || Nodes[i + r_GateCenter.second][j + r_GateCenter.first].m_Stat ==Node::NOCONNECTION || Nodes[i + r_GateCenter.second][j + r_GateCenter.first].m_Stat ==Node::NOCONNECTION || Nodes[i + r_GateCenter.second][j + r_GateCenter.first].m_Stat==Node::PINPOINT)
			{
				Nodes[i + r_GateCenter.second][j + r_GateCenter.first].m_Stat = Node::NOTHING;
			}
			
		}

	}
}

bool Grid::IsValidGateCenter(std::pair<int, int> r_GateCenter)
{
	for (int i = -6; i <= 6; i++)
	{
		for (int j = -6; j <= 6; j++)
		{
			if (Nodes[i+r_GateCenter.second][j+r_GateCenter.first].m_Stat!=Node::NOTHING)
			{
				return false;
			}

		}
	}
	return true;
}

void Grid::TestGrid()
{
	std::ofstream out;
	out.open("Grid.txt");
	for (int i = 0; i < Ysize; i++)
	{
		for (int j = 0; j < Xsize; j++)
		{
			switch (Nodes[i][j].m_Stat)
			{
			case Node::NOTHING:
				out << " - ";
				break;
			case Node::NOCONNECTION:
				out << " c ";
				break;
			case Node::GATE:
				out << " g ";
				break;
			case Node::PINPOINT:
				out << " * "; 
				break;
			default:
				out << " x ";
				break;
			}
		}
		out << std::endl;
	}
}



void Grid::GridInitializion(){
	for (int i = 0; i < Ysize; i++)
	{
		for (int j = 0; j < Xsize; j++)
		{
			Nodes[i][j].m_Stat= Node::NOTHING ;
			Nodes[i][j].m_X = j;
			Nodes[i][j].m_Y = i;
		}
	}
}
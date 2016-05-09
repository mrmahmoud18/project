#pragma once

#include<vector>
#include<fstream>

class Component;

class Grid
{
public:
    Grid(int r_x, int r_y);
    void AddGate(std::pair<int,int> r_GateCenter);
    void DeleteGate(std::pair<int,int> r_GateCenter);
    bool IsValidGateCenter(std::pair<int,int> r_GateCenter);
	Component* GetComponent(std::pair<int, int> r_Point);
	void TestGrid();
private:
	struct Node;
	std::vector< std::vector<Node> > Nodes;
	int Xsize, Ysize;
	friend class Connection;
	void GridInitializion();
    struct Node
    {
        int m_X, m_Y , m_XParent ,m_Yparent;
        enum {NOCONNECTION, CONNECTIONFULL, VERTICAL ,HORIZONTAL ,GATE ,PINPOINT ,NOTHING} m_Stat;
		Component* pComp;
		int m_NumberOfConnections;
    };
};

/*

-------------
-CCCCCCCCCCC-
-CCCCCCCCCCC-
-CCCCCCCCCCC-
-CCGGGGGGGCC-
-C*GGGGGGGCC-
-C*GGGGGGG*C-
-C*GGGGGGGCC-
-CCGGGGGGGCC-
-CCCCCCCCCCC-
-CCCCCCCCCCC-
-CCCCCCCCCCC-
-------------

*/

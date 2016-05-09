#pragma once

#include"Grid.h"
#include"..\Components\Component.h"
#include"..\GUI\Interface.h"

#include<queue>
#include<vector>

class Connection : public Component
{
public:
	Connection(std::pair <int, int> r_Point1, std::pair<int, int>r_Point2, Grid& r_GridObject);
	void AddNewConnection(std::pair<int,int> r_Point1 ,std::pair<int,int>r_Point2 );
	void CreateThePath(std::pair<int, int> r_point1, std::pair<int, int>r_point2);
	virtual void Operate();
	virtual void Draw(Interface* pInterface);
	~Connection(void);
private:
	std::vector< std::vector < std::pair<int, int> > >m_ConnectionList;
	Grid m_GridObject;
	std::vector< std::pair <int, int > >m_Path;

	bool IsValidPoint(int Tempx, int TempY, std::vector < std::vector<bool> >Visited);
	bool ISValidState(int r_Tempx, int r_TempY, std::queue< Grid::Node>r_TempQueue);
	void ClearQueue(std::queue < Grid::Node >& r_TempQueue);
	void ClearParent();
};


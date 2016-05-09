#include "Connection.h"



Connection::Connection(std::pair<int, int> r_Point1, std::pair<int, int> r_Point2 ,Grid &r_GridObject)
	:m_GridObject(r_GridObject)
{
	AddNewConnection(r_Point1, r_Point2);
}

void Connection::AddNewConnection(std::pair<int, int> r_Point1, std::pair<int, int> r_Point2)
{
	std::queue< Grid::Node> TempQueue;
	std::vector< std::vector<bool> >Visited(m_GridObject.Ysize, std::vector <bool>(m_GridObject.Xsize, false));
	bool IsPathFounded = false;
	int TempArrayX[4] = { 0,0,1,-1 }, TempArrayY[4] = {1,-1,0,0 };
	int TempX, TempY, CurrentX  , CurrentY  ;
	TempQueue.push(m_GridObject.Nodes[r_Point1.second][r_Point1.first]);
	Visited[r_Point1.second][r_Point1.first] = true;
	while (!TempQueue.empty() && !IsPathFounded)
	{
		CurrentX = TempQueue.front().m_X;
		CurrentY = TempQueue.front().m_Y;
		for (int z = 0; z < 4; z++)
		{
			TempX = TempArrayX[z] + CurrentX;
			TempY = TempArrayY[z] + CurrentY;
			if (IsValidPoint(TempX, TempY, Visited))
			{
				if (m_GridObject.Nodes[TempY][TempX].m_Stat == Grid::Node::PINPOINT )
				{
					if (TempX == r_Point2.first && TempY == r_Point2.second)
					{
						IsPathFounded = true;
						m_GridObject.Nodes[TempY][TempX].m_XParent = CurrentX;
						m_GridObject.Nodes[TempY][TempX].m_Yparent = CurrentY;
						ClearQueue(TempQueue);
						break;
					}
					continue;
				}
				if ( ISValidState(TempX ,TempY,TempQueue) )
				{
					m_GridObject.Nodes[TempY][TempX].m_XParent = CurrentX;
					m_GridObject.Nodes[TempY][TempX].m_Yparent = CurrentY;
					Visited[TempY][TempX] = true;
					TempQueue.push(m_GridObject.Nodes[TempY][TempX]);
				}
			}
		}
		if (!TempQueue .empty())
		{
			TempQueue.pop();
		}
	}
	if (IsPathFounded)
	{
		// TODO
		CreateThePath(r_Point1, r_Point2);
	}
	else
	{
		exit(1);
	}
}

void Connection::CreateThePath(std::pair<int, int> r_point1, std::pair<int, int> r_point2)
{
	std::vector<std::pair<int, int> >Path;
	Path.push_back(std::make_pair(r_point2.first, r_point2.second));
	int CurrentX= r_point2.first, CurrentY= r_point2.second, TempX, TempY;
	TempX = CurrentX;
	TempY = CurrentY;
	CurrentX = m_GridObject.Nodes[TempY][TempX].m_XParent;
	CurrentY = m_GridObject.Nodes[TempY][TempX].m_Yparent;
	do
	{
		while ( (TempX != r_point1.first || TempY != r_point1.second ) && TempX==CurrentX)
		{
			if (m_GridObject.Nodes[TempY][TempX].m_Stat == Grid::Node::NOTHING || m_GridObject.Nodes[TempY][TempX].m_Stat == Grid::Node::NOCONNECTION)
			{
				m_GridObject.Nodes[TempY][TempX].m_Stat = Grid::Node::VERTICAL;
			}
			if (m_GridObject.Nodes[TempY][TempX].m_Stat == Grid::Node::HORIZONTAL)
			{
				m_GridObject.Nodes[TempY][TempX].m_Stat = Grid::Node::CONNECTIONFULL;
			}
			TempX = CurrentX;
			TempY = CurrentY;
			CurrentX = m_GridObject.Nodes[TempY][TempX].m_XParent;
			CurrentY = m_GridObject.Nodes[TempY][TempX].m_Yparent;
			if (TempX != CurrentX)
			{
				Path.push_back(std::make_pair(TempX, TempY));
			}
		}
		while ( (TempX != r_point1.first || TempY != r_point1.second ) && TempX != CurrentX)
		{
			if (m_GridObject.Nodes[TempY][TempX].m_Stat == Grid::Node::NOTHING || m_GridObject.Nodes[TempY][TempX].m_Stat == Grid::Node::NOCONNECTION)
			{
				m_GridObject.Nodes[TempY][TempX].m_Stat = Grid::Node::HORIZONTAL;
			}
			if (m_GridObject.Nodes[TempY][TempX].m_Stat == Grid::Node::VERTICAL)
			{
				m_GridObject.Nodes[TempY][TempX].m_Stat = Grid::Node::CONNECTIONFULL;
			}
			TempX = CurrentX;
			TempY = CurrentY;
			CurrentX = m_GridObject.Nodes[TempY][TempX].m_XParent;
			CurrentY = m_GridObject.Nodes[TempY][TempX].m_Yparent;
			if (TempX == CurrentX)
			{
				Path.push_back(std::make_pair(TempX, TempY));
			}
		}

	} while (TempX!=r_point1.first || TempY!=r_point1.second);
	if (  !(r_point1.first==Path.back().first && r_point1.second==Path.back().second) )
	{
		Path.push_back(std::make_pair(r_point1.first, r_point1.second));
	}
	m_Path = Path;
	ClearParent();
}

void Connection::Draw(Interface * pInterface)
{
	pInterface->DrawConnection(m_Path);
	// TODO print pin
}

Connection::~Connection(void)
{
}


bool Connection::IsValidPoint(int r_TempX, int r_TempY, std::vector<std::vector<bool>> r_Visited)
{
	return (r_TempX < m_GridObject.Xsize && r_TempX>0 && r_TempY < m_GridObject.Ysize  && r_TempY>0 && !r_Visited[r_TempY][r_TempX]
		&& m_GridObject.Nodes[r_TempY][r_TempX].m_Stat != Grid::Node::GATE && m_GridObject.Nodes[r_TempY][r_TempX].m_Stat != Grid::Node::CONNECTIONFULL);
}

bool Connection::ISValidState(int r_TempX, int r_TempY, std::queue<Grid::Node> r_TempQueue)
{
	return ((r_TempY == r_TempQueue.front().m_Y && m_GridObject.Nodes[r_TempY][r_TempX].m_Stat != Grid::Node::HORIZONTAL)
		|| (r_TempX == r_TempQueue.front().m_X && m_GridObject.Nodes[r_TempY][r_TempX].m_Stat != Grid::Node::VERTICAL)) ;
}

void Connection::ClearQueue(std::queue<Grid::Node>& r_TempQueue)
{
	while (! r_TempQueue.empty())
	{
		r_TempQueue.pop();
	}
}

void Connection::ClearParent()
{
	for (int i = 0; i < m_GridObject.Ysize; i++)
	{
		for (int j = 0; j < m_GridObject.Xsize; j++)
		{
			m_GridObject.Nodes[i][j].m_XParent = 0;
			m_GridObject.Nodes[i][j].m_Yparent = 0;
		}
	}
}

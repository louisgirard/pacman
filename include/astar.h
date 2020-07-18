#ifndef ASTAR
#define ASTAR

#include <vector>
#include <list>
#include <cmath>
#include <queue>
#include <algorithm>
#include <iostream>
#include <limits>

struct Node
{
	int value = 0;
	int x = 0;
	int y = 0;
	int g = std::numeric_limits<int>::max();
	int h = 0;
	struct Node *father = NULL;
};

struct CompareNodes
{
    bool operator()(Node* node1, Node* node2)
    {
		int f1 = node1->g + node1->h;
		int f2 = node2->g + node2->h;
		if(f1 < f2){
			return 1;
		}else if(f1 == f2){
			return 0;
		}else{
			return -1;
		}
    }
};

#ifndef DIRECTION
#define DIRECTION
enum Direction{Left,Right,Up,Down,Null};
#endif

class Astar
{
public:
	std::list<Direction> shortestPath(std::vector<std::vector<Node>> &graph, int start_x, int start_y, int goal_x, int goal_y);
	void printPath(std::list<Direction> path);

private:
	std::list<Direction> reconstructPath(Node *start, Node *current);
	void treatNeighbor(Node *neighbor, Node *current, Node* goal, std::priority_queue<Node*, std::vector<Node*>, CompareNodes> &openList, std::vector<Node*> &closedList);
	int heuristic(Node *start, Node *goal);
	bool equalNodes(Node *node1, Node *node2);
	Direction nodeDirection(Node *node);
	
};

#endif
#include "astar.h"

std::list<Direction> Astar::shortestPath(std::vector<std::vector<Node>> &graph, int start_x, int start_y, int goal_x, int goal_y){
	std::priority_queue<Node*, std::vector<Node*>, CompareNodes> openList;
	std::vector<Node*> closedList;
	std::list<Direction> path;

	Node *start = &(graph.at(start_y).at(start_x));
	Node *goal = &(graph.at(goal_y).at(goal_x));

	start->g = 0;
	heuristic(start, goal);

	openList.push(start);
	Node *current;

	while(!openList.empty()){
		current = openList.top();
		openList.pop();

		if(equalNodes(current, goal)){
			path = reconstructPath(start, current);
			//reset graph
			for(size_t i = 0; i < graph.size(); i++){
				for(size_t j = 0; j < graph.at(0).size(); j++){
					graph.at(i).at(j).g = std::numeric_limits<int>::max();
					graph.at(i).at(j).h = 0;
					graph.at(i).at(j).father = NULL;
				}
			}
			return path;
		}

		Node* neighbor;
		//find neighbors
		if((current->y - 1) >= 0){
			neighbor = &(graph.at(current->y - 1).at(current->x));
			treatNeighbor(neighbor, current, goal, openList, closedList);
		}
		if((current->y + 1) < graph.size()){
			neighbor = &(graph.at(current->y + 1).at(current->x));
			treatNeighbor(neighbor, current, goal, openList, closedList);
		}
		if((current->x - 1) >= 0){
			neighbor = &(graph.at(current->y).at(current->x - 1));
			treatNeighbor(neighbor, current, goal, openList, closedList);
		}
		if((current->x + 1) < graph.at(0).size()){
			neighbor = &(graph.at(current->y).at(current->x + 1));
			treatNeighbor(neighbor, current, goal, openList, closedList);
		}
		closedList.push_back(current);
	}

	return {};
}

void Astar::treatNeighbor(Node *neighbor, Node *current, Node* goal, std::priority_queue<Node*, std::vector<Node*>, CompareNodes> &openList, std::vector<Node*> &closedList){
	if(neighbor->value == 0){
		if(!(std::find(closedList.begin(), closedList.end(), neighbor) != closedList.end())){
			if(current->g + 1 < neighbor->g){
				neighbor->g = current->g + 1;
				neighbor->h = heuristic(neighbor, goal);
				neighbor->father = current;
				openList.push(neighbor);
			}
		}
	}	
}

std::list<Direction> Astar::reconstructPath(Node *start, Node *current){
	std::list<Direction> path;
	Direction direction;
	while(true){
		direction = nodeDirection(current);
		if(direction == Null){
			break;
		}
		path.push_front(nodeDirection(current));
		current = current->father;
	}
	return path;
}

int Astar::heuristic(Node *start, Node *goal){
	//Manhattan distance
	return std::abs(start->x - goal->x) + std::abs(start->y - goal->y);
}

bool Astar::equalNodes(Node *node1, Node *node2){
	return (node1->x == node2->x && node1->y == node2->y);
}

void Astar::printPath(std::list<Direction> path){
	std::cout << "Path" << std::endl;
	for (std::list<Direction>::iterator it = path.begin(); it != path.end(); ++it){
		if(*it == Left){
			std::cout << "Left" << std::endl;
		}else if(*it == Right){
			std::cout << "Right" << std::endl;
		}else if(*it == Up){
			std::cout << "Up" << std::endl;
		}else if(*it == Down){
			std::cout << "Down" << std::endl;
		}else{
			std::cout << "Null" << std::endl;
		}
	}
}

Direction Astar::nodeDirection(Node *node){
	Node *father = node->father;
	if(father == NULL){
		return Null;
	}
	if(node->x < father->x){
		return Left;
	}
	if(node->x > father->x){
		return Right;
	}
	if(node->y < father->y){
		return Up;
	}
	if(node->y > father->y){
		return Down;
	}
	return Null;
}
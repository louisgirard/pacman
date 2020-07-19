#include "astar.h"

std::vector<Direction> Astar::shortestPath(std::vector<std::vector<Node>> &graph, int start_x, int start_y, int goal_x, int goal_y){
	std::priority_queue<Node*, std::vector<Node*>, CompareNodes> openList;
	std::vector<Node*> closedList;
	std::vector<Direction> path;

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
			treatNeighbor(graph, neighbor, current, goal, openList, closedList);
		}
		if((current->y + 1) < graph.size()){
			neighbor = &(graph.at(current->y + 1).at(current->x));
			treatNeighbor(graph, neighbor, current, goal, openList, closedList);
		}
		if((current->x - 1) >= 0){
			neighbor = &(graph.at(current->y).at(current->x - 1));
			treatNeighbor(graph, neighbor, current, goal, openList, closedList);
		}
		if((current->x + 1) < graph.at(0).size()){
			neighbor = &(graph.at(current->y).at(current->x + 1));
			treatNeighbor(graph, neighbor, current, goal, openList, closedList);
		}
		closedList.push_back(current);
	}
	std::cout << "End ASTAR, ERROR" << std::endl;
	return {};
}

void Astar::treatNeighbor(std::vector<std::vector<Node>> &graph, Node *neighbor, Node *current, Node* goal, std::priority_queue<Node*, std::vector<Node*>, CompareNodes> &openList, std::vector<Node*> &closedList){
	if(nodeValue(graph, neighbor) == 0){
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

std::vector<Direction> Astar::reconstructPath(Node *start, Node *current){
	std::vector<Direction> path;
	Direction direction;
	while(true){
		direction = nodeDirection(current);
		if(direction == Null){
			break;
		}
		path.insert(path.begin(),nodeDirection(current));
		current = current->father;
	}
	return path;
}

Direction Astar::shortestPathDirection(std::vector<std::vector<Node>> &graph, int start_x, int start_y, int goal_x, int goal_y){
	return shortestPath(graph, start_x, start_y, goal_x, goal_y).front();
}

int Astar::heuristic(Node *start, Node *goal){
	//Manhattan distance
	return std::abs(start->x - goal->x) + std::abs(start->y - goal->y);
}

bool Astar::equalNodes(Node *node1, Node *node2){
	if(node1->x == node2->x && node1->y == node2->y){
		return true;
	}else if(node1->x+1 == node2->x && node1->y == node2->y){
		return true;
	}else if(node1->x == node2->x+1 && node1->y == node2->y){
		return true;
	}else if(node1->x == node2->x && node1->y+1 == node2->y){
		return true;
	}else if(node1->x == node2->x && node1->y == node2->y+1){
		return true;
	}else if(node1->x+1 == node2->x && node1->y+1 == node2->y){
		return true;
	}else if(node1->x == node2->x+1 && node1->y == node2->y+1){
		return true;
	}else{
		return false;
	}
}

void Astar::printPath(std::vector<Direction> path){
	std::cout << "------------Path------------" << std::endl;
	for (std::vector<Direction>::iterator it = path.begin(); it != path.end(); ++it){
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

int Astar::nodeValue(std::vector<std::vector<Node>> &graph, Node *node){
	int value1, value2, value3, value4;
	value1 = node->value;
	if(node->y+1 >= graph.size()){
		return -1;
	}else{
		value2 = graph.at(node->y+1).at(node->x).value;
	}
	if(node->x+1 >= graph.at(0).size()){
		return -1;
	}else{
		value3 = graph.at(node->y).at(node->x+1).value;
	}
	value4 = graph.at(node->y+1).at(node->x+1).value;
	if(value1 == 0 && value2 == 0 && value3 == 0 && value4 == 0){
		return 0;
	}else{
		return 1;
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
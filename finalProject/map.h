#pragma once

#include <unordered_map>
#include <set>
#include <stack>
#include <queue>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <climits>
#include <algorithm>

//#include "interactiveIterator.h"

using crossroadName = std::string;
using distance = uint;

using path = std::pair < std::vector < crossroadName >, distance >;

#define infinity UINT_MAX

class map{
private:

	std::unordered_map<crossroadName, std::unordered_map<crossroadName, distance>> adjacencyList;

	void connect(const crossroadName &currCR, const crossroadName &destCR, distance dist){
		adjacencyList[currCR][destCR] = dist;
		if (adjacencyList.find(destCR) == adjacencyList.end())
			adjacencyList.insert({destCR, std::unordered_map<crossroadName, distance>()});
	}

	void readLine(const std::string &line){
		std::istringstream stream(line);
		std::string current, from, dest;
		uint distance;

		stream >> from;
		while (stream >> current){
			dest = current;
			stream >> current;
			distance = std::stoi(current);
			connect(from, dest, distance);
		}
	}

	distance getDist(const crossroadName &cr1, const crossroadName &cr2) const{
		if(adjacencyList.find(cr1) == adjacencyList.end() || adjacencyList.at(cr1).find(cr2) == adjacencyList.at(cr1).end())
			return infinity;
		return adjacencyList.at(cr1).at(cr2);
	}

/*
	bool path(const crossroadName &currCR, const crossroadName &cr2, std::set<crossroadName> &visited) const{
		if (currCR == cr2)
			return true;
		visited.insert(currCR);
		for(auto it : adjacencyList.at(currCR)){
			if (visited.find(it.first) == visited.end()){
				if (path(it.first, cr2, visited))
					return true;
			}
		}
		return false;
	}
	bool trip(const	crossroadName &currCR, std::set<crossroadName> &visited) const{
		if (visited.find(currCR) != visited.end())
			return true;
		visited.insert(currCR);
		for(auto it : adjacencyList.at(currCR)){
			if (visited.find(it.first) == visited.end()){
				if (trip(it.first, visited))
					return true;
			}
		}
		return false;
	}
	*/
	/*
	void deadEnd(std::set<crossroadName> &visited, const crossroadName &currCR, std::set<crossroadName>& result) const{
		visited.insert(currCR);
		for(auto it : adjacencyList.at(currCR)){
			if(adjacencyList.at(currCR).empty()){
				result.insert(currCR);
			}
			else{
				if (visited.find(it.first) == visited.end()){
					deadEnd(visited, it.first, result);
				}
			}
		}
	}*/

public:

	map() {}

	void load(const std::string &file){
		std::fstream loadFile(file);
		std::string line;
		if (loadFile.is_open()){
			while (std::getline(loadFile, line)){
				readLine(line);
			}
			loadFile.close();
		}
		else{
			std::cout << "Couldn't open file!\n";
		}
	}
	/*
	bool path(const crossroadName &cr1, const crossroadName &cr2) const{
		if (adjacencyList.find(cr1) == adjacencyList.end() || adjacencyList.find(cr2) == adjacencyList.end())
			return false;
		std::set<crossroadName> visited;
		return path(cr1, cr2, visited);
	}*/

	bool hasPath(const crossroadName &cr1, const crossroadName &cr2) const{
		if (adjacencyList.find(cr1) == adjacencyList.end() || adjacencyList.find(cr2) == adjacencyList.end())
			return false;
		std::stack<crossroadName> dfsStack;
		std::set<crossroadName> visited;
		crossroadName currCR;
		dfsStack.push(cr1);
		while(!dfsStack.empty()){
			currCR = dfsStack.top(); dfsStack.pop();
			if(currCR == cr2)
				return true;
			if(visited.find(currCR) == visited.end()){
				visited.insert(currCR);
				for(auto it : adjacencyList.at(currCR)){
					dfsStack.push(it.first);
				}
			}
		}
		return false;
	}
/*
	bool trip(const crossroadName &currCR) const{
		if (adjacencyList.find(currCR) == adjacencyList.end())
			return false;
		std::set<crossroadName> visited;
		return trip(currCR, visited);
	}
*/
	bool trip(const crossroadName &initCR) const{
		std::stack<crossroadName> dfsStack;
		std::set<crossroadName> visited;
		crossroadName currCR;
		dfsStack.push(initCR);
		while(!dfsStack.empty()){
			currCR = dfsStack.top(); dfsStack.pop();
			if(visited.find(currCR) != visited.end())
				return true;
			else{
				visited.insert(currCR);
				for(auto it : adjacencyList.at(currCR)){
					dfsStack.push(it.first);
				}
			}
		}
		return false;
	}
	/*
	std::set<crossroadName> deadEnd() const{
		std::set<crossroadName> result, visited;
		//std::cout << adjacencyList.begin()->first << std::endl;
		deadEnd(visited, adjacencyList.begin()->first, result);
		return result;
	}*/

	std::set<crossroadName> deadEnd() const{
		std::stack<crossroadName> dfsStack;
		std::set<crossroadName> visited, result;
		crossroadName currCR;
		dfsStack.push(adjacencyList.begin()->first);
		while(!dfsStack.empty()){
			currCR = dfsStack.top(); dfsStack.pop();
			if(adjacencyList.at(currCR).empty())
				result.insert(currCR);
			if(visited.find(currCR) == visited.end()){
				visited.insert(currCR);
				for(auto it : adjacencyList.at(currCR)){
					dfsStack.push(it.first);
				}
			}
			if(dfsStack.empty() && visited.size() < adjacencyList.size()){
				auto it = adjacencyList.begin();
				while(visited.find(it->first) != visited.end())
					++it;
				dfsStack.push(it->first);
			}
		}
		return result;
	}

	bool reachAll(const crossroadName &initCR){
		std::stack<crossroadName> dfsStack;
		std::set<crossroadName> visited;
		crossroadName currCR;
		dfsStack.push(initCR);
		while(!dfsStack.empty()){
			currCR = dfsStack.top(); dfsStack.pop();
			if(visited.find(currCR) == visited.end()){
				visited.insert(currCR);
				for(auto it : adjacencyList.at(currCR)){
					dfsStack.push(it.first);
				}			
			}
		}
		return visited.size() == adjacencyList.size();
	}

	bool isNotInPath(const crossroadName &cr, path &cp) const{
		for(auto it : cp.first)
			if(it == cr)
				return false;
		return true;
	}

	std::vector<path> allPaths(const crossroadName &initCR, const crossroadName &dest, const std::set<crossroadName> &closed = std::set<crossroadName>()) const {
		std::queue<path> bfsQueue;
		std::vector<path> result;
		path currPath;
		currPath.first.push_back(initCR);
		currPath.second = 0;
		bfsQueue.push(currPath);
		while(!bfsQueue.empty()){
			currPath = bfsQueue.front(); bfsQueue.pop();
			crossroadName prev = currPath.first[currPath.first.size() - 1];
			if(prev == dest)
				result.push_back(currPath);
			for(auto it : adjacencyList.at(prev)){
				if(isNotInPath(it.first, currPath) && closed.find(it.first) == closed.end()){
					path newPath = currPath;
					newPath.first.push_back(it.first);
					newPath.second += getDist(prev, it.first);
					bfsQueue.push(newPath);
				}
			}
		}
		return result;
	}

	struct compare{
		bool operator()(const path &p1, const path &p2){
			return p1.second < p2.second;
		}
	};

	std::vector<path> KshortestPaths(const crossroadName &initCR, const crossroadName &dest,const std::set<crossroadName> &closed = std::set<crossroadName>(), uint k = 3) const{
		std::vector<path> result = allPaths(initCR, dest, closed);
		std::sort(result.begin(), result.end(), compare());
		if(result.size() >= 3)
			return std::vector<path>(result.begin(), result.begin() + 3);
		else
			return result;
	}

	std::vector<crossroadName> neighbors(const crossroadName &currCR) const{
		std::vector<crossroadName> result;
		for(auto it : adjacencyList.at(currCR))
			result.push_back(it.first);
		return result;
	}

	//friend class interactiveIterator;

/*
	struct compare{
		bool operator()(const path &lhs, const path &rhs) const{
			return lhs.second > rhs.second;
		}
	};

	bool vecFind(const std::vector<crossroadName> &v, const crossroadName& e) const{
		for(auto it : v)
			if(it == e)
				return true;
		return false;
	}

	std::set<path> KshortestPaths(const crossroadName &s, const crossroadName &t, uint k = 3) const{	
		path Pu;
		std::priority_queue<path, std::vector<path>, compare> B;
		std::set<path> P;
		std::unordered_map< crossroadName, distance> countU;
		for(auto it : adjacencyList)
			countU[it.first] = 0;
		Pu.first.push_back(s);
		Pu.second = 0;
		B.push(Pu);
		crossroadName u = s;
		while(!B.empty() && countU[u] < k){
			Pu = B.top(); B.pop();
			countU[u] = countU[u] + 1;
			if(u == t)
				P.insert(Pu);
			if(countU[u] < k){
				for(auto v : adjacencyList.at(u)){
					if(!vecFind(Pu.first, v.first)){
						path Pv;
						Pv.first = Pu.first;
						Pv.first.push_back(v.first);
						Pv.second = Pu.second + getDist(u, v.first);
						B.push(Pv);
					}
				}
			}
		}
		return P;
	}
*/
	// test methods

	void printMapNodes(){
		for(auto it : adjacencyList){
			std::cout << it.first << std::endl;
		}
	}

	// iterator utility methods

	bool find(const crossroadName &CR) const{
		return adjacencyList.find(CR) != adjacencyList.end();
	}

	//std::unordered_map<crossroadName, distance> neighbors(const crossroadName &CR) const{
	//	return adjacencyList.at(CR);
	//}

};

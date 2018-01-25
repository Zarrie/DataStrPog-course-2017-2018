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

	void inOutDegrees(std::unordered_map<crossroadName, std::pair<uint, uint>> &in_outDegree) const{
		for(auto nodeListPair : adjacencyList)
			in_outDegree[nodeListPair.first] = std::make_pair(0, nodeListPair.second.size());
		for(auto nodeListPair : adjacencyList)
			for(auto nodeEdgePair : nodeListPair.second)
				in_outDegree.at(nodeEdgePair.first).first++;
	}

	crossroadName hasInitNode(const std::vector<crossroadName> &differentInOutDegreesNodes, const std::unordered_map<crossroadName, std::pair<uint, uint>> &in_outDegree) const{
		if(abs(in_outDegree.at(differentInOutDegreesNodes[0]).first - in_outDegree.at(differentInOutDegreesNodes[0]).second) == 1 &&
		   abs(in_outDegree.at(differentInOutDegreesNodes[1]).first - in_outDegree.at(differentInOutDegreesNodes[1]).second) == 1){
			if(in_outDegree.at(differentInOutDegreesNodes[0]).first < in_outDegree.at(differentInOutDegreesNodes[0]).second)
				return differentInOutDegreesNodes[0];
			else
				return differentInOutDegreesNodes[1];
		}
		else
			return std::string();
	}

	crossroadName getInitNode(const std::unordered_map<crossroadName, std::pair<uint, uint>> &in_outDegree) const{
		const uint maxDifferentDegreesAllowingEulerianPath = 2;
		std::vector<crossroadName> differentInOutDegreesNodes;
		for(auto it : in_outDegree)
			if(it.second.first != it.second.second)
				differentInOutDegreesNodes.push_back(it.first);
		if(differentInOutDegreesNodes.size() > maxDifferentDegreesAllowingEulerianPath)	// No eulerian path/circle exists
			return std::string();
		else if(differentInOutDegreesNodes.size() == maxDifferentDegreesAllowingEulerianPath){ // No eulerian circle exists but possibly a path does
			return hasInitNode(differentInOutDegreesNodes, in_outDegree);
		}
		else{
			return in_outDegree.begin()->first;
		}
	}

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
	}*/

	std::set<crossroadName> deadEnd() const{
		std::set<crossroadName> result;
		for(auto it : adjacencyList){
			if(it.second.empty())
				result.insert(it.first);
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

	std::vector<crossroadName> fullTrip() const{
		std::unordered_map<crossroadName, std::pair<uint, uint>> in_outDegree;
		inOutDegrees(in_outDegree);
		crossroadName initCR = getInitNode(in_outDegree);
		if(initCR.empty())
			return std::vector<crossroadName>(); // No eulerian path or circle exists
		std::stack<crossroadName> st;
		std::vector<crossroadName> resultPath;
		std::unordered_map<crossroadName, std::unordered_map<crossroadName, distance>> adjacencyListCopy = adjacencyList;
		st.push(initCR);
		while(!st.empty()){
			crossroadName currCR = st.top();
			if(!adjacencyListCopy.at(currCR).empty()){
				st.push(adjacencyListCopy.at(currCR).begin()->first);
				adjacencyListCopy.at(currCR).erase(adjacencyListCopy.at(currCR).begin());
			}
			else{
				resultPath.push_back(currCR);
				st.pop();
			}
		}
		std::reverse(resultPath.begin(), resultPath.end());
		return resultPath;
	}

	void printMapNodes(){
		for(auto it : adjacencyList){
			std::cout << it.first << std::endl;
		}
	}

	bool find(const crossroadName &CR) const{
		return adjacencyList.find(CR) != adjacencyList.end();
	}
};

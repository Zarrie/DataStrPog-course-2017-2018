#pragma once

#include "map.h"

using crossroadName = std::string;
using distance = uint;

using path = std::pair < std::vector < crossroadName >, distance >;

class interactiveIterator{
private:
	crossroadName currLocation;
	std::set<crossroadName> closedCrossroads;
	map currMap;

public:
	interactiveIterator(const std::string &fileName){
		currMap.load(fileName);
	}

	void location() const{
		if(currLocation.empty())
			std::cout << "!> Your current location is unknown" << std::endl;
		else
			std::cout << "> Your current location is " << currLocation << std::endl;
	}

	void change(const crossroadName &newLocation){
		if(currMap.find(newLocation)){
			currLocation = newLocation;
			std::cout << "> Your new location is " << newLocation << std::endl;
		}
		else{
			std::cout << "!> New location not recognized!" << std::endl;
		}
	}

	void neighbors(const crossroadName &currCR) const{
		std::cout << "> Neighbors of crossroad " << currCR << " are " << std::endl;
		for(auto it : currMap.neighbors(currCR))
			std::cout << it << " ";
		std::cout << std::endl;
	}

	void move(const crossroadName &destCR){
		if(currLocation == destCR){
			std::cout << "> You are already at " << destCR << std::endl;
			return;
		}
		std::vector<path> foundPaths = currMap.allPaths(currLocation, destCR, closedCrossroads);
		if(foundPaths.empty()){
			std::cout << "!> There is no road connecting " << currLocation << " and " << destCR << std::endl;
			return;
		}
		std::cout << "> Moving to " << destCR << " passing through ";
		for(auto it : foundPaths[0].first)
			std::cout << it << " ";
		std::cout << std::endl;
		currLocation = destCR;
	}

	void close(const crossroadName &closeCR){
		if(currMap.find(closeCR)){
			closedCrossroads.insert(closeCR);
			std::cout << "> Closing " << closeCR << " crossroad!" << std::endl;
		}
		else{
			std::cout << "!> Crossroad not recognized" << std::endl;
		}
	}

	void open(const crossroadName &openCR){
		if(closedCrossroads.find(openCR) != closedCrossroads.end()){
			closedCrossroads.erase(closedCrossroads.find(openCR));
			std::cout << "> Opening " << openCR << " crossroad!" << std::endl;
		}
		else{
			std::cout << "!> Crossroad not recognized" << std::endl;
		}
	}

	void closed()const {
		if(closedCrossroads.empty()){
			std::cout << "> There are no currently closed crossroads!" << std::endl;
		}
		else{
			std::cout << "> Currently closed crossroads are ";
			for(auto it : closedCrossroads)
				std::cout << it << " ";
			std::cout << std::endl;				
		}
	}

	void tour()const {
		std::vector<crossroadName> tourPath = currMap.fullTrip();
		if(tourPath.empty()){
			std::cout << "> There is no way to make full tour of the town!" << std::endl;
		}
		else{
			std::cout << "> The route for the full trip is ";
			for(auto it : tourPath)
				std::cout << it << " ";
			std::cout << std::endl;
		}
	}
};
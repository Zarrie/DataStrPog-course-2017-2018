#include "map.h"
#include "interactiveIterator.h"


void mapLOADtest(){
	map m;
	m.load("map.pt");
	m.printMapNodes();
	std::cout << std::endl;
}

void mapPATHtest(){
	map m;
	m.load("map.pt");
	//m.printMapNodes();
	std::cout << std::endl;
	std::cout << m.hasPath("Попа", "НДК") << " Expected 1" << std::endl;
	std::cout << m.hasPath("НДК", "Попа") << " Expected 1" << std::endl;
	std::cout << m.hasPath("НДК", "Алабин") << " Expected 1" << std::endl;
	std::cout << m.hasPath("НДК", "Графа") << " Expected 1" << std::endl;
	std::cout << m.hasPath("Алабин", "БСФС") << " Expected 0" << std::endl;
	std::cout << m.hasPath("Графа", "Попа") << " Expected 0" << std::endl;
	std::cout << m.hasPath("Графа", "БСФС") << " Expected 0" << std::endl;
	std::cout << m.hasPath("Графа", "Попа") << " Expected 0" << std::endl;
	std::cout << m.hasPath("Алабин", "НДК") << " Expected 0" << std::endl;
}

void mapTRIPtest(){
	map m;
	m.load("map.pt");

	std::cout << m.trip("Попа") << " Expected 1" << std::endl;
	std::cout << m.trip("Център") << " Expected 0" << std::endl;
	std::cout << m.trip("НДК") << " Expected 1" << std::endl;
	std::cout << m.trip("Графа") << " Expected 1" << std::endl;
}

void mapDEADENDtest(){
	map m;
	m.load("map.pt");
	//m.printMapNodes();
	for(auto it : m.deadEnd())
		std::cout << it << " ";
	std::cout << std::endl;
}

void mapREACHALLtest(){
	map m;
	m.load("map.pt");
	std::cout << m.reachAll("Попа") << " Expected 1" << std::endl;
	std::cout << m.reachAll("НДК") << " Expected 1" << std::endl;
	std::cout << m.reachAll("Алабин") << " Expected 0" << std::endl;
	std::cout << m.reachAll("Графа") << " Expected 0" << std::endl;
	std::cout << m.reachAll("Център") << " Expected 0" << std::endl;
	std::cout << m.reachAll("БСФС") << " Expected 1" << std::endl;
}

void map3PATHSFINDtest(){
	map m;
	m.load("map.pt");
	std::set<std::string> closed = {"Гурко"};
	for(auto it : m.KshortestPaths("Графа", "Алабин", closed)){
		for(auto it2 : it.first){
			std::cout << it2 << " ";
		}
		std::cout << std::endl;		
	}
}

int main(int argc, char ** argv){
	//mapLOADtest();
	//mapPATHtest();
	//mapTRIPtest();
	//mapDEADENDtest();
	//mapREACHALLtest();
	//map3PATHSFINDtest();
	if(argc == 2){
		map m;
		m.load(argv[1]);
	}
	else{
		interactiveIterator it(argv[2]);
		std::string command;
		std::cin >> command;
		while(command != "exit"){
			if(command == "location")
				it.location();
			else if(command == "change"){
				std::string newLocation;
				std::cin >> newLocation >> newLocation;
				it.change(newLocation);
			}
			else if(command == "neighbors"){
				std::string currCR;
				std::cin >> currCR;
				it.neighbors(currCR);
			}
			else if(command == "move"){
				std::string newLocation;
				std::cin >> newLocation >> newLocation;
				it.move(newLocation);
			}
			else if(command == "close"){
				std::string closeCR;
				std::cin >> closeCR >> closeCR;
				it.close(closeCR);
			}
			else if(command == "open"){
				std::string openCR;
				std::cin >> openCR >> openCR;
				it.open(openCR);
			}
			else if(command == "closed")
				it.closed();
			else if(command == "tour"){

			}
			else
				std::cout << "!> Command not recognized!" << std::endl;
			std::cin >> command;
		}
		std::cout << "> Exiting..." << std::endl;
	}


	return 0;
}
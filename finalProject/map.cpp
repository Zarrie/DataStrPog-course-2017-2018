#include "map.h"
#include "interactiveIterator.h"


int main(int argc, char ** argv){	
	if(argc == 2){
		map m;
		if(m.load(argv[1]))
			std::cout << "> Map loaded!" << std::endl;
		else
			std::cout << "!> Couldn't open file!\n";
	}
	else{
		std::cout << "> Interactive mode ON!" << std::endl;
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
				it.neighbors();
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
				it.tour();
			}
			else
				std::cout << "!> Command not recognized!" << std::endl;
			std::cin >> command;
		}
		std::cout << "> Exiting..." << std::endl;
	}

	return 0;
}
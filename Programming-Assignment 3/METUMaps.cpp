#include "METUMaps.h"
#include "GraphExceptions.h"

#include <iostream>

void METUMaps::PrintNotInJourney() const
{
    std::cout << "Device is not in a journey!" << std::endl;
}

void METUMaps::PrintUnableToChangeDestination() const
{
    std::cout << "Cannot change Destination during journey!" << std::endl;
}

void METUMaps::PrintUnableToChangeStartingLoc() const
{
    std::cout << "Cannot change Starting Location during journey!" << std::endl;
}

void METUMaps::PrintAlreadyInJourney() const
{
    std::cout << "Device is already in a journey!" << std::endl;
}

void METUMaps::PrintJourneyIsAlreadFinished() const
{
    std::cout << "Journey is already finished!" << std::endl;
}

void METUMaps::PrintLocationNotFound() const
{
    std::cout << "One (or both) of the locations are not found in the maps!" << std::endl;
}

void METUMaps::PrintJourneyCompleted() const
{
    std::cout << "Journey Completed!" << std::endl;
}

void METUMaps::PrintCachedLocationFound(const std::string& location0,
                                        const std::string& location1) const
{
    std::cout << "Route between \""
              << location0 << "\" and \""
              << location1 << "\" is in cache, using that..."
              << std::endl;
}

void METUMaps::PrintCalculatingRoutes(const std::string& location0,
                                      const std::string& location1) const
{
    std::cout << "Calculating Route(s) between \""
              << location0 << "\" and \""
              << location1 << "\"..."
              << std::endl;
}

std::string METUMaps::GenerateKey(const std::string& location0,
                                  const std::string& location1)
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    return location0 + "/" + location1;
}

METUMaps::METUMaps(int potentialPathCount,
                   const std::string& mapFilePath)
{
	map = Graph(mapFilePath);
    this -> potentialPathCount = potentialPathCount;
    inJourney = false;
    cachedPaths = KeyedHashTable(map.TotalVertexCount() * this -> potentialPathCount);
}

void METUMaps::SetDestination(const std::string& name)
{
    if (inJourney){
    	PrintUnableToChangeDestination();
	}
	
	else destination = name;
}

void METUMaps::SetStartingLocation(const std::string& name)
{
    if (inJourney){
    	PrintUnableToChangeStartingLoc();
	}
	
	else startingLoc = name;
}

void METUMaps::StartJourney()
{
    if (inJourney){
    	PrintAlreadyInJourney();
	}
	
	else{
		PrintCalculatingRoutes(startingLoc, destination);
		std::vector<std::vector<int> > foundPaths;
		
		try {
			map.MultipleShortPaths(foundPaths, startingLoc, destination, potentialPathCount);
		}
		
		catch(VertexNotFoundException excpt) {
			PrintLocationNotFound();
			return;
		}
		
		inJourney = true;
		for (int i = 0; i < foundPaths.size(); i++){
			for (int j = 0; j < foundPaths[i].size() - 1; j++){
				
				std::string initname = map.VertexName(foundPaths[i][j]);
				std::string hashkey = GenerateKey(initname, destination);
				std::vector<int> subpath;
				
				for (int k = j; k < foundPaths[i].size(); k++){
					subpath.push_back(foundPaths[i][k]);
				}
				
				cachedPaths.Insert(hashkey, subpath);
			}
		}
		
		currentLoc = startingLoc;
		currentRoute = foundPaths[0];
	}
}

void METUMaps::EndJourney()
{
    if (!inJourney){
    	PrintJourneyIsAlreadFinished();
	}
	
	else{
		inJourney = false;
		destination = "";
		startingLoc = "";
		currentLoc = "";
		currentRoute.clear();
		cachedPaths.ClearTable();
	}
}

void METUMaps::UpdateLocation(const std::string& name)
{
    if (!inJourney){
    	PrintNotInJourney();
	}
	
	// The user updates his/her location to destination, journey is finished.
	else if (name == destination){
	    PrintJourneyCompleted();
	    currentLoc = name;
	}
	
	else{
		
		std::vector<int> cachedP;
		std::string hashkey = GenerateKey(name, destination);
		
		//There is a path from name to destination in cache.
		if (cachedPaths.Find(cachedP, hashkey) == true){
			
			PrintCachedLocationFound(name, destination);
			currentRoute = cachedP;
			currentLoc = name;
			
		}
		
		//There is no path from name to destination in cache.
		else{
			PrintCalculatingRoutes(name, destination);
			std::vector<std::vector<int> > foundPaths;
			
			try {
				map.MultipleShortPaths(foundPaths, name, destination, potentialPathCount);
			}
			
			//Given name is not on the map.
			catch(VertexNotFoundException excpt) {
				PrintLocationNotFound();
				return;
			}
			
			for (int i = 0; i < foundPaths.size(); i++){
				for (int j = 0; j < foundPaths[i].size() - 1; j++){
					
					std::string initname = map.VertexName(foundPaths[i][j]);
					std::string hashkey = GenerateKey(initname, destination);
					std::vector<int> subpath;
					
					for (int k = j; k < foundPaths[i].size(); k++){
						subpath.push_back(foundPaths[i][k]);
					}
					
					cachedPaths.Insert(hashkey, subpath);
				}
			}
			
			currentLoc = name;
			currentRoute = foundPaths[0];
		}
	}
}

void METUMaps::Display()
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    if(!inJourney)
    {
        // We are not in journey, this function
        // shouldn't be called
        PrintNotInJourney();
        return;
    }

    int timeLeft = map.TotalWeightInBetween(currentRoute);

    // Print last known location
    std::cout << "Journey         : " << startingLoc << "->"
              << destination << "\n";
    std::cout << "Current Location: " << currentLoc << "\n";
    std::cout << "Time Left       : " << timeLeft << " minutes\n";
    std::cout << "Current Route   : ";
    map.PrintPath(currentRoute, true);

    std::cout.flush();
}

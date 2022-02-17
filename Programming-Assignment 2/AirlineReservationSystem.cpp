#include "AirlineReservationSystem.h"

void AirlineReservationSystem::addPassenger(const std::string &firstname, const std::string &lastname) {
    
	Passenger new_passenger(firstname, lastname);

    if (passengers.search(new_passenger) == NULL){
    	
		passengers.insert(new_passenger);
	} 
}

Passenger *AirlineReservationSystem::searchPassenger(const std::string &firstname, const std::string &lastname) {
    
	Passenger searched_psg(firstname, lastname);
	BSTNode<Passenger> *searched_node = passengers.search(searched_psg);
	
	if (searched_node != NULL) return &(searched_node -> data);
	else return NULL; 
}

void AirlineReservationSystem::addFlight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity) {
    
	Flight new_flight(flightCode, departureTime, arrivalTime, departureCity, arrivalCity, economyCapacity, businessCapacity);
    
    if (flights.search(new_flight) == NULL){
    	
    	flights.insert(new_flight);
	}
}

std::vector<Flight *> AirlineReservationSystem::searchFlight(const std::string &departureCity, const std::string &arrivalCity) {
    
    std::vector<Flight *> flights_vector;
    BSTNode<Flight> *flights_root = flights.getRoot();
    
    if (flights_root){
        
    	if ((flights_root -> data).getDepartureCity() == departureCity && (flights_root -> data).getArrivalCity() == arrivalCity){
    		flights_vector.push_back(&(flights_root -> data));
		}
		
		while (flights.getSuccessor(flights_root, preorder) != NULL){
    		
			flights_root = flights.getSuccessor(flights_root, preorder);
    		
			if ((flights_root -> data).getDepartureCity() == departureCity && (flights_root -> data).getArrivalCity() == arrivalCity){
    			flights_vector.push_back(&(flights_root -> data));
			}
		}	
	}
	return flights_vector;
}

void AirlineReservationSystem::issueTicket(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    
	Passenger searched_psg(firstname, lastname), *searched_psg_ptr;
	Flight searched_flight(flightCode, "", "", "", "", -1, -1), *searched_flight_ptr;
	
	BSTNode<Passenger> *psgnode = passengers.search(searched_psg);
	BSTNode<Flight> *flgnode = flights.search(searched_flight);
	
	if (psgnode && flgnode){
		
		searched_psg_ptr = &(psgnode -> data);
		searched_flight_ptr = &(flgnode -> data);
		
		Ticket new_ticket(searched_psg_ptr, searched_flight_ptr, ticketType);
		searched_flight_ptr -> addTicket(new_ticket);
	}
}

void AirlineReservationSystem::saveFreeTicketRequest(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    
	Passenger searched_psg(firstname, lastname), *searched_psg_ptr;
    Flight searched_flight(flightCode, "", "", "", "", -1, -1), *searched_flight_ptr;
    
    BSTNode<Passenger> *psgnode = passengers.search(searched_psg);
    BSTNode<Flight> *flgnode = flights.search(searched_flight);
    
    if (psgnode && flgnode){
    	
		searched_psg_ptr = &(psgnode -> data);
		searched_flight_ptr = &(flgnode -> data);
		
		Ticket free_ticket(searched_psg_ptr, searched_flight_ptr, ticketType);
		freeTicketRequests.enqueue(free_ticket);
	}
}

void AirlineReservationSystem::executeTheFlight(const std::string &flightCode) {
    
    Flight searched_flight(flightCode, "", "", "", "", -1, -1), *searched_flight_ptr;
    BSTNode<Flight> *flgnode = flights.search(searched_flight);
    
    if (flgnode){
    	
    	int i = 0;
		searched_flight_ptr = &(flgnode -> data);
    	
    	while (i < freeTicketRequests.size()){
    		
    		if (freeTicketRequests.peek().getFlight() == searched_flight_ptr){
    			
				if (searched_flight_ptr -> addTicket(freeTicketRequests.peek())){
    				freeTicketRequests.dequeue();
    				i++;
				}
			
				else{
					freeTicketRequests.enqueue(freeTicketRequests.dequeue());
					i++;
				}
			}
			
			else{
				freeTicketRequests.enqueue(freeTicketRequests.dequeue());
				i++;
			}
		}
    	
    	searched_flight_ptr -> setCompleted(true);
	}
}

void AirlineReservationSystem::print() const {
    std::cout << "# Printing the airline reservation system ..." << std::endl;

    std::cout << "# Passengers:" << std::endl;
    passengers.print(inorder);

    std::cout << "# Flights:" << std::endl;
    flights.print(inorder);

    std::cout << "# Free ticket requests:" << std::endl;
    freeTicketRequests.print();

    std::cout << "# Printing is done." << std::endl;
}

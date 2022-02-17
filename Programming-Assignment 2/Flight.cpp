#include "Flight.h"

Flight::Flight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity) {
    this->flightCode = flightCode;
    this->departureTime = departureTime;
    this->arrivalTime = arrivalTime;
    this->departureCity = departureCity;
    this->arrivalCity = arrivalCity;
    this->economyCapacity = economyCapacity;
    this->businessCapacity = businessCapacity;
    this->completed = false;
}

const std::string &Flight::getFlightCode() const {
    return flightCode;
}

const std::string &Flight::getDepartureTime() const {
    return departureTime;
}

const std::string &Flight::getArrivalTime() const {
    return arrivalTime;
}

const std::string &Flight::getDepartureCity() const {
    return departureCity;
}

const std::string &Flight::getArrivalCity() const {
    return arrivalCity;
}

int Flight::getEconomyCapacity() const {
    return economyCapacity;
}

int Flight::getBusinessCapacity() const {
    return businessCapacity;
}

bool Flight::isCompleted() const {
    return completed;
}

void Flight::setCompleted(bool completed) {
    this->completed = completed;
}

bool Flight::addTicket(const Ticket &ticket) {
    
	if (ticket.getTicketType() == economy){
    	
		int econticketcount = 0, i = 0, tickets_size = tickets.size();
		
		while (i < tickets_size){
			if ((tickets[i]).getTicketType() == economy){
				econticketcount++;
			}
			i++;
		}
		
		if (economyCapacity > econticketcount){
    		tickets.push_back(ticket);
    		return true;
		}
		else return false;
	}
	
	else{
		
		int businessticketcount = 0, i = 0, tickets_size = tickets.size();
		
		while (i < tickets_size){
			if ((tickets[i]).getTicketType() == business){
				businessticketcount++;
			}
			i++;
		}
		
		if (businessCapacity > businessticketcount){
			tickets.push_back(ticket);
			return true;
		}
		else return false;
	}
}

bool Flight::operator<(const Flight &rhs) const {
    std::string flightcode1 = getFlightCode(), flightcode2 = rhs.getFlightCode();
    int i = 0;
    
    while (flightcode1[i] != '\0' && flightcode2[i] !=  '\0'){
    	if (flightcode1[i] < flightcode2[i]) return true;
    	else if (flightcode1[i] > flightcode2[i]) return false;
    	i++;
	}
	
	if (flightcode1[i] != '\0' && flightcode2[i] == '\0' ) return false;
	else if (flightcode1[i] == '\0' && flightcode2[i] != '\0') return true;
}

bool Flight::operator>(const Flight &rhs) const {
    return rhs < *this;
}

bool Flight::operator==(const Flight &rhs) const {
    return flightCode == rhs.flightCode;
}

bool Flight::operator!=(const Flight &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Flight &flight) {
    os << "Flight(flightCode: " << flight.flightCode;
    os << ", departureTime: " << flight.departureTime;
    os << ", arrivalTime: " << flight.arrivalTime;
    os << ", departureCity: " << flight.departureCity;
    os << ", arrivalCity: " << flight.arrivalCity;
    os << ", economyCapacity: " << flight.economyCapacity;
    os << ", businessCapacity: " << flight.businessCapacity;
    os << ", completed: " << (flight.completed ? "yes" : "no");
    os << ", tickets: [";
    for (int i = 0 ; i < flight.tickets.size() ; ++i) {
        os << flight.tickets[i];
        if (i != (flight.tickets.size() - 1)) os << ", ";
    }
    os << "])";
    return os;
}

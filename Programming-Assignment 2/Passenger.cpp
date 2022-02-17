#include "Passenger.h"

Passenger::Passenger(std::string firstname, std::string lastname) {
    this->firstname = firstname;
    this->lastname = lastname;
}

const std::string &Passenger::getFirstname() const {
    return firstname;
}

const std::string &Passenger::getLastname() const {
    return lastname;
}

bool Passenger::operator<(const Passenger &rhs) const {
    std::string psg1last = getLastname(), psg2last = rhs.getLastname();
    std::string psg1first = getFirstname(), psg2first = rhs.getFirstname();
    int i = 0;
    
    while (psg1last[i] != '\0' && psg2last[i] != '\0'){
    	if (psg1last[i] < psg2last[i]){
    		return true;
		}
		else if (psg1last[i] > psg2last[i]){
			return false;
		}
		i++;
	}
	
	if (psg2last[i] == '\0' && psg1last[i] != '\0') return false;
	
	else if (psg2last[i] != '\0' && psg1last[i] == '\0') return true;
	
	else{
		i = 0;
		while (psg1first[i] != '\0' && psg2first[i] != '\0'){
    		if (psg1first[i] < psg2first[i]){
    			return true;
			}
			else if (psg1first[i] > psg2first[i]){
				return false;
			}
			i++;
		}
		
		if (psg2first[i] == '\0' && psg1first[i] != '\0') return false;
		else return true;
	}
}

bool Passenger::operator>(const Passenger &rhs) const {
    return rhs < *this;
}

bool Passenger::operator==(const Passenger &rhs) const {
    return firstname == rhs.firstname && lastname == rhs.lastname;
}

bool Passenger::operator!=(const Passenger &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Passenger &passenger) {
    os << "Passenger(firstname: " << passenger.firstname;
    os << ", lastname: " << passenger.lastname << ")";
    return os;
}

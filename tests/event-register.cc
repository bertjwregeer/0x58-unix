#include <iostream>
#include <map>
#include <0x58-unix/Event.h>

using namespace x58unix::eventImplementation;

std::ostream& x58unix::eventImplementation::operator<< (std::ostream& o, const EventRegistry& registry) {
        
        std::cout << "Vector size: " << (registry._roll).size() << std::endl;
        
        for (std::vector<EventRegistry::event_t>::const_iterator a = (registry._roll).begin(), b = (registry._roll).end(); a!=b; a++) {
                std::cout << "Name: " << (*a).name << " weight: " << (*a).weight << " address: " << ((*a).fptr) << std::endl;
        }
	return o;
}

int main() {
        EventRegistry& registry(EventRegistry::retrieve());
        std::cout << registry << std::endl;
        
        x58unix::Event* (*func)(void) = registry.search("kqueue");
        x58unix::Event* _ptr = func();
        
        _ptr->dispatch();
}
#pragma warning (disable:4786)
#pragma warning (disable:4503)

#include "RailSystem.h"

void RailSystem::reset(void) {
    // TODO: reset the data objects of the 
    // City objects' contained in cities
	for (map<string, City*>::iterator cur = cities.begin(); cur != cities.end(); cur++) {
		(*cur).second->from_city = "";
		(*cur).second->visited = false;
		(*cur).second->total_fee = (*cur).second->total_distance = 0;
	}
}

RailSystem::RailSystem(string const &filename) {
    
    load_services(filename);
}

void RailSystem::load_services(string const &filename) {

	ifstream inf(filename.c_str());
	string from, to;
	int fee, distance;

	while ( inf.good() ) {

		// Read in the from city, to city, the fee, and distance.
		inf >> from >> to >> fee >> distance;

		if ( inf.good() ) {
		
			// TODO: Add entries in the cities container and
			// and services in the rail system for the new 
            // cities we read in.	
			City *f, *t;
			// initialize from city
			if (cities[from] == NULL) {
				cities[from] = new City(from);
			}
			f = cities[from];
			// initialize to city
			if (cities[to] == NULL) {
				cities[to] = new City(to);
			}
			t = cities[to];
			// initialize services
			if (outgoing_services.find(from) == outgoing_services.end()) {
				list<Service*> list;
				outgoing_services[from] = list;
				outgoing_services[from].push_back(new Service(to, fee, distance));
			} else {
				outgoing_services.find(from)->second.push_back(new Service(to, fee, distance));
			}
		}
	}

	inf.close();
}

RailSystem::~RailSystem(void) {

    // TODO: release all the City* and Service*
    // from cities and outgoing_services

	// cleaning of outgoing_services
	list<Service*>::iterator cur2;
	//for (map<string, list<Service*>>::iterator cur = outgoing_services.begin(); cur != outgoing_services.end(); cur++) {
for (map<string, list<Service*>>::iterator cur = outgoing_services.begin(); cur != outgoing_services.end(); cur++) {
		
	cur2 = (*cur).second.begin(); 
		while(cur2 != (*cur).second.end()) {
			delete *cur2;
			cur2++;
		}
	}
	// cleaning of cities
	for (map<string, City*>::iterator cur = cities.begin(); cur != cities.end(); cur++) {
		delete (*cur).second;
	}
}

void RailSystem::output_cheapest_route(const string& from,
                const string& to, ostream& out) {

	reset();
	pair<int, int> totals = calc_route(from, to);

	if (totals.first == INT_MAX) {
		out << "There is no route from " << from << " to " << to << "\n";
	} else {
		out << "The cheapest route from " << from << " to " << to << "\n";
		out << "costs " << totals.first << " euros and spans " << totals.second
			<< " kilometers\n";
        cout << recover_route(to) << "\n\n";
	}
}

bool RailSystem::is_valid_city(const string& name) {

	return cities.count(name) == 1;
}

pair<int, int> RailSystem::calc_route(string from, string to) {
    // You can use another container
	priority_queue<City*, vector<City*>, Cheapest> candidates;

    // TODO: Implement Dijkstra's shortest path algorithm to
    // find the cheapest route between the cities
    // clear previous calculations
	reset();

	// start initialize all routes to maximum values
	for (map<string, City*>::iterator cur = cities.begin(); cur != cities.end(); cur++) {
		(*cur).second->total_fee = INT_MAX;
		candidates.push((*cur).second);
	}
	// initialize start and end cities
	City *start, *end;
	start = cities[from];
	end = cities[to];
	// set start data
	start->from_city = start->name;
	start->total_fee = 0;
	start->visited = true;
	end->total_fee = INT_MAX;
	//Dijkstra
	for (std::make_heap(const_cast<City**> (&candidates.top()), const_cast<City**> (&candidates.top()) + candidates.size(), Cheapest());
			candidates.size() && candidates.top()->visited && candidates.top() != end; 
				std::make_heap(const_cast<City**> (&candidates.top()), const_cast<City**> (&candidates.top()) + candidates.size(), Cheapest())) {
		
		start = candidates.top();
		candidates.pop();

		list<Service*>::iterator cur = outgoing_services[start->name].begin(); 
		while(cur != outgoing_services[start->name].end()) {

			if (cities[(*cur)->destination]->total_fee > (start->total_fee + (*cur)->fee)) {
				cities[(*cur)->destination]->visited = true;
				cities[(*cur)->destination]->from_city = start->name;
				cities[(*cur)->destination]->total_fee = start->total_fee + (*cur)->fee;
				cities[(*cur)->destination]->total_distance = start->total_distance + (*cur)->distance;
			}
			cur++;
		}
	}

    // Return the total fee and total distance.
    // Return (INT_MAX, INT_MAX) if not path is found.
    if (cities[to]->visited) {
            return pair<int,int>(cities[to]->total_fee, cities[to]->total_distance);
    } else {
            return pair<int,int>(INT_MAX, INT_MAX);
    }

}

string RailSystem::recover_route(const string& city) {
	
    // TODO: walk backwards through the cities
    // container to recover the route we found
	if (city == cities[city]->from_city) {
		return cities[city]->from_city;
	} else {
		return recover_route(cities[city]->from_city) + " to " + city;
	}
}

/*
Route RailSystem::getCheapestRoute(const string& from, const string& to){
    assert(is_valid_city(from));
    assert(is_valid_city(to));
    reset();
    pair<int, int> p =  calc_route(from,to);
    return Route(from,to,p.first,p.second);
}
 */
#pragma warning (disable:4786)
#pragma warning (disable:4503)

#include "RailSystem.h"

void RailSystem::reset(void) {

    // TODO: reset the data objects of the 
    // City objects' contained in cities
    for(auto p:  cities)
    {
         p.second->visited = false;
         p.second->total_distance = INT_MAX;
         p.second->total_fee = INT_MAX;
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
            if (cities.find(from) == cities.end()){
                cities[from] = new City();
            }
           outgoing_services[from].push_back(new Service(to,fee,distance)); 
		}
	}

	inf.close();
}

RailSystem::~RailSystem(void) {

    // TODO: release all the City* and Service*
    // from cities and outgoing_services
    for(auto p: outgoing_services)
    {
        for (Service* service: p.second)
        {
            delete service;
        }
    }
    
    for(auto p:  cities)
    {
        delete p.second;
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

    
    City* current = cities[from]; 
    current->total_distance = 0;
    current->total_fee = 0;
    //current->visited = true;
    candidates.push(current);
    do
    {
        current = candidates.top();
        for (Service* service: outgoing_services[current->name]){
            if (! cities[service->destination]->visited )
            {
                City * city =  cities[service->destination];
                city->total_distance =  current->total_distance + service->distance;
                city->total_fee =  current->total_distance + service->fee;
                candidates.push(city);
                // rebild
            }
        }
        
        current->visited = true;
        candidates.pop();
    }  while(candidates.size() > 0);
    
    // TODO: Implement Dijkstra's shortest path algorithm to
    // find the cheapest route between the cities
    
    
    
    

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

    return "";
}


Route RailSystem::getCheapestRoute(const string& from, const string& to){
    assert(is_valid_city(from));
    assert(is_valid_city(to));
    reset();
    pair<int, int> p =  calc_route(from,to);
    return Route(from,to,p.first,p.second);
}
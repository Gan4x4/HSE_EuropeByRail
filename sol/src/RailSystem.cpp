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
            if (! is_valid_city(from)){
                cities[from] = new City(from);
            }
            
            if ( ! is_valid_city(to))
            {
                cities[to] = new City(to);
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
    
    // Validate city's names
    if (! is_valid_city(from) || ! is_valid_city(to))
    {
        throw invalid_argument("City name are bad");
    }
        
    // You can use another container
    vector<City*> data;
	priority_queue<City*, vector<City*>, Cheapest> candidates(data.begin(),data.end());
    
    // Dijkstra's shortest path algorithm 
    City* current = cities[from]; 
    current->total_distance = 0;
    current->total_fee = 0;
    candidates.push(current);
    do
    {
        current = candidates.top();
        for (Service* service: outgoing_services[current->name])
        {
            City *city =  cities[service->destination];
            int newFee = current->total_fee + service->fee;
            if (! city->visited  && newFee < city->total_fee )
            {
                // Update fee and distance
                city->total_distance =  current->total_distance + service->distance;
                city->total_fee =  newFee;
                city->from_city =  current->name;
                if (std::find(data.begin(),data.end(),city) == data.end())
                {
                    // Put new element
                    candidates.push(city);
                }
                else
                {
                    // If city already in queue we need to rebuild heap,
                    // because place on this element can changed
                    make_heap(data.begin(),data.end(),Cheapest());     
                }
            }
        }
        // all path from this city are checked
        current->visited = true; 
        candidates.pop();
    }  while(candidates.size() > 0);

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
    City* current = cities[city];
    string output;
    while (current->total_fee)
    {
        output =  " to " +current->name + output ; 
        current = cities[current->from_city];
    }
    output = current->name + output; 
    return output;
}


Route RailSystem::getCheapestRoute(const string& from, const string& to){
    assert(is_valid_city(from));
    assert(is_valid_city(to));
    reset();
    pair<int, int> p =  calc_route(from,to);
    return Route(from,to,p.first,p.second);
}
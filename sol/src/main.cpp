#pragma warning (disable:4786)
#pragma warning (disable:4503)

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <queue>


#include "City.h"
#include "Service.h"
#include "RailSystem.h"

using namespace std;


bool check(Route & expected,RailSystem &rs){
    Route actual = rs.getCheapestRoute(expected.from,expected.to);
    return actual == expected;
}



int main(int argc, char* argv[]) {


          
        Route w1{"Warsaw","Paris",105,4900};
        Route w2{"Lisbon","Athens",200,4450};
        
	vector<Route> test;
	test.push_back(w1);
	test.push_back(w2);

    try {

        RailSystem rs("services.txt");
        for(Route w: test ){
            if (! check(w,rs)){
                    cout << "Test not pass: " << w.from << " to " << w.to <<"\n";
            };
        }
        
		
        while (true) {

            cerr << "\n\nEnter a start and destination city:  ('quit' to exit)\n";

            string from, to;
			from ="Lisbon";
			to ="Madrid";
			
            cin >> from;
            if (from == "quit") break;
            cin >> to;

            if (rs.is_valid_city(from) && rs.is_valid_city(to)) {
                rs.output_cheapest_route (from, to, cout); // TO DO function must return value
            }
            else {
                cout << "Please enter valid cities\n\n";
            }
			

        }

        return EXIT_SUCCESS;

    }
    catch (exception& e) {
        cerr << e.what() << endl;
    }
    catch (...) {
        cerr << "Unknown exception caught\n";
    }

    return EXIT_FAILURE;
}

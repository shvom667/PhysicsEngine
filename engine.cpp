#include <bits/stdc++.h>
#include <cstdlib>
#include <unistd.h>
using namespace std;


#define f80 int

// Only 1 point
// Only 1 dimension

struct Point {
	f80 mass;
	f80 x;
	f80 initial_velocity;
	f80 current_velocity;
	f80 current_x;
	f80 acceleration;
	Point () {

	}
	Point (f80 mass, f80 x, f80 initial_velocity, f80 acceleration) {
		this->mass = mass;
		this->x = x;
		this->current_x = x;
		this->initial_velocity = initial_velocity;
		this->current_velocity = current_velocity;
		this->acceleration = acceleration;
	}


};

// Engine Tells us the state of the point after time T

struct Engine {
	Point p;
	Engine (Point p) {
		this->p = p;
	}

	auto Compute_New_State_Of_Point(f80 T) {
		Point current_p = p;
		current_p.current_velocity = current_p.initial_velocity  + current_p.acceleration * T;

		current_p.current_x += current_p.initial_velocity * T + (current_p.acceleration * T * T) / 2;
		return current_p;
	}

};




int main() {

	Point p{
		1,
		0,
		1,
		2,
	};


	Engine E(p);


	vector<char> axis(10000	, '_');

	while (true) {
		for (int time = 0; time <= 100; time++) {
			Point now_point = E.Compute_New_State_Of_Point(time);

			auto current_axis = axis;

			current_axis[now_point.current_x] = '0';

			for (int i = 0; i < 10000; i++) {
				cout << current_axis[i] << " ";
			}	cout << endl;
			usleep(100000);
			system("clear");
		}
	}

		
	cout << '\n';
	
	return 0;
}

#include <bits/stdc++.h>
#include <cstdlib>
#include <unistd.h>
using namespace std;


#define f80 long double

// Only 1 point
// Only 1 dimension

/*
	2 points
*/

#ifndef ONLINE_JUDGE
#include "./debug.cpp"
#include "./random_gen.cpp"
#else
#define dbg(...) 42
#define rnd(...) 42
#endif

const f80 eps = 1e-6;

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
		this->current_velocity = initial_velocity;
		this->acceleration = acceleration;
	}
};

auto __print(Point pts) {
	cerr<<pts.current_x;
}

// 1d
// Engine updates state after each duration of T = 1 second
// n pts
// inital constant force + graviatational force


struct Engine {
	vector<Point> pts;
	vector<f80> forces;

	Engine (vector<Point> pts) {
		this->pts = pts;
		forces = vector<f80> ((int)pts.size());
		for (int i = 0; i < (int)pts.size(); i++) { // if there is some initial acceleration
			forces[i] = pts[i].acceleration * pts[i].mass;
		}
	}

	auto Compute_New_State_Of_Point(Point p, f80 force, f80 T) {
		p.acceleration = force / p.mass;
		Point current_p = p;
		current_p.current_velocity += current_p.acceleration * T;
		current_p.current_x += current_p.initial_velocity * T + (current_p.acceleration * T * T) / (2.0);
		return current_p;
	}

	auto gravitational_force(f80 m1, f80 m2, f80  r) { // ignoring the constant G
		long double res =  (m1 * m2) / (r * r);
		return res;
	}
	
	auto Compute_Forces_On_Points() {  // time complexity O(pts**2)
		vector<f80> gravity_force((int)pts.size(), 0);
		vector<f80> total_force((int)pts.size(), 0);

		for (int i = 0; i < (int)pts.size(); i++) {
			for (int j = 0; j < (int)pts.size(); j++) {
				if (i == j) continue;
				if (pts[i].current_x - pts[j].current_x < eps) {
					gravity_force[i] += gravitational_force(pts[i].mass, pts[j].mass, abs(pts[i].current_x - pts[j].current_x));
				} else {
					gravity_force[i] -= gravitational_force(pts[i].mass, pts[j].mass, abs(pts[i].current_x - pts[j].current_x));
				}
			}
			total_force[i] = forces[i] + gravity_force[i];
		}

		return total_force;
	}

	auto Compute_New_State_Of_System(f80 duration) {
		vector<f80> total_force = Compute_Forces_On_Points();
		for (int i = 0; i < (int)pts.size(); i++) {
			pts[i] = Compute_New_State_Of_Point(pts[i], total_force[i], duration);
		}
		return pts;
	}

};




int main() {

	Point p1{
		1000,
		0,
		0,
		0,
	};



	Point p2{
		1000,
		80,
		0,
		0,
	};


	Point p3{
		1000,
		200,
		0,
		0,
	};


	vector<Point> pts = {p1, p2, p3};


	Engine E(pts);


	vector<char> axis(1000	, '_');


	cout << pts[0].current_x << " " << pts[1].current_x << '\n';


	for (int j = 0; j < 100; j++) {
		auto res = E.Compute_New_State_Of_System(1);
		dbg(res[0], res[1], res[2]);
	}
	
	return 0;
}

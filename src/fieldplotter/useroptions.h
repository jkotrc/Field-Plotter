#pragma once

#include <string>
#include <vector>


/*
PointCharge(Point(0.0f, 0.0f, 0.5f), 0.1f),
PointCharge(Point(0.0f, 0.0f, -0.5f), -0.1f),
PointCharge(Point(0.0f, 0.5f, 0.0f), 0.1f)
*/

struct UserOptions {
	float camera_sensitivity;
	float visible_step;
	float computational_step;
	float maxrange;
	int arrow_count;
	int line_density;
	float arrow_spatial_separation;
	std::vector<std::string> charges;
	UserOptions() : camera_sensitivity(0.0f), 
					visible_step(0.05f), 
					computational_step(0.5f), 
					arrow_count(20),
					arrow_spatial_separation(0.2f),
					maxrange(4.0f),
					line_density(4)
	{
		charges.push_back("(0,0,0.5);0.1");
		charges.push_back("(0,0,-0.5);-0.1");
		charges.push_back("(0,0.5,0);0.1");
	}
};
#pragma once

#include <string>


/*
PointCharge(Point(0.0f, 0.0f, 0.5f), 0.1f),
PointCharge(Point(0.0f, 0.0f, -0.5f), -0.1f),
PointCharge(Point(0.0f, 0.5f, 0.0f), 0.1f)
*/

struct UserOptions {
	float camera_sensitivity=0.0f;
	float visible_step=0.05f;
	float computational_step=0.5f;
	float maxrange=4.0f;
	int arrow_count=20;
	int line_density=4;
	float arrow_spatial_separation=0.2f;
	float ball_radius=0.1f;
	std::string charges[4] = { "(0,0,0.5);0.1", "(0,0,-0.5);-0.1",  "(0,0.5,0);0.1" , "" };
};
#include <vector>
#pragma once


class Dividers{
	int num_dividers_;
	float separation_width_;
	float divider_width_;
	float start_pos_, end_pos_;
	float length_;

public:
	Dividers();
	Dividers(int num_dividers_);
	Dividers(float separation_width_);


};


// std::vector<float> generateBuckets(float length, int divisions);

// std::vector<float> generateDivisionsBySeparation(float length, float separation_width)

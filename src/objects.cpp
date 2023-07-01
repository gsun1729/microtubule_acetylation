#include "objects.hpp"
#include "config.hpp"
#include "probability.hpp"
#include "config.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>


int Particle::next_id = 0; 

const Config config;

Particle::Particle(){
	id_ = next_id++;
	position_ = 0;
	diff_coeff_ = config.diffusion_coefficient;
	p_reaction_ = config.p_reaction;
	

}


Particle::Particle(double pos, double diff_coeff, double p_reaction){
	id_ = next_id++;
	position_ = pos;
	diff_coeff_ = diff_coeff;
	p_reaction_ = p_reaction;
}


void Particle::Move(double dt){
	double mean_sq_displacement = sqrt(2 * diff_coeff_ * dt);
	mean_sq_displacement *= randomGaussianVariable(1,0.1);
	bool direction = randomBool();
	if (direction){
		mean_sq_displacement *= -1;
	}
	position_ += mean_sq_displacement;
}

bool Particle::HasReacted(){
	return isRandomSampleGreaterThanValue(p_reaction_);
}



double Particle::getPosition() const{
	return position_;
}


void Particle::PrintSelf(){
	std::cout << std::setprecision(5)<< std::fixed;
	std::cout << "position: " << position_ << "\t";
	std::cout << "D: "<< diff_coeff_ << "\t";
	std::cout << "pRx: "<< p_reaction_ << std::endl;
}

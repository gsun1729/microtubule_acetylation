#include "objects.hpp"
#include "config.hpp"
#include "probability.hpp"
#include "config.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>


int Particle::next_id_ = 0; 

const Config config;

Particle::Particle(){
	id_ = next_id_++;
	position_ = 0;
	diff_coeff_ = config.diffusion_coefficient;
	p_reaction_ = config.p_reaction;
	

}


Particle::Particle(float pos, float diff_coeff, float p_reaction){
	id_ = next_id_++;
	position_ = pos;
	diff_coeff_ = diff_coeff;
	p_reaction_ = p_reaction;
}


void Particle::Move(float dt){
	float mean_sq_displacement = sqrt(2 * diff_coeff_ * dt);
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



float Particle::getPosition() const{
	return position_;
}

float Particle::getDiffusionCoeff() const{
	return diff_coeff_;
}

float Particle::getRxnProbability() const{
	return p_reaction_;
}

void Particle::PrintSelf(){
	std::cout << std::setprecision(5)<< std::fixed;
	std::cout << "position: " << position_ << "\t";
	std::cout << "D: "<< diff_coeff_ << "\t";
	std::cout << "pRx: "<< p_reaction_ << std::endl;
}

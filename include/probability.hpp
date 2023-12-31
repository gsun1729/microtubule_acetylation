#include <cmath>
#include <iostream>
#include <random> 
#include <iterator>
#include <cassert>
#include <algorithm>
#include <chrono>

#pragma once
/*
Samples from a uniform distribution between a range of 0-1, 
Returns TRUE if random value is larger than cutoff provided, 
FALSE if otherwise
*/
bool isRandomSampleGreaterThanValue(float cutoff);

/*
Samples from a uniform distribution between a range of 0-1, 
Returns the value generated.
*/
float sampleUniformDistribution();

/*
Generates randomly true or false with equal probability
*/
bool randomBool();

/*
Generates a random gaussian variable sammpled from a distribution
with a defined mean and standard deviation*/
float randomGaussianVariable(float mean, float stdev);

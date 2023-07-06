#include "probability.hpp"

bool isRandomSampleGreaterThanValue(float cutoff){
  /**Function generates a number from range of 0-1;
  If random value is greater than cutoff, return false, else
  return true.
  **/
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);
  float sample = dis(gen);
  return sample < cutoff;
}

float sampleUniformDistribution(){
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);
  return(dis(gen));
}

bool randomBool() {
    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::bernoulli_distribution distribution(0.5); 
    return distribution(generator); 
}

float randomGaussianVariable(float mean, float stdev){
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator (seed);
  std::normal_distribution<double> distribution(mean,stdev);
  return distribution(generator);
}

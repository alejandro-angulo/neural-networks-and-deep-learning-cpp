#include "network.h"

// Helper Functions
double dRand (double min, double max) {
  double d = (double)rand() / RAND_MAX;
  return min + d*(max - min);
}

/*
 * PRIVATE
 */

void network::random_weights () {
  for (unsigned int i = 0; i < (num_layers - 1); ++i) {
    weights.push_back( std::vector< std::vector<double> > () );
    for (unsigned int j = 0; j < sizes[i + 1]; ++j) {
      weights[i].push_back( std::vector<double> () );
      for (unsigned int k = 0; k < sizes[i]; ++k) {
        weights[i][j].push_back( dRand(-1, 1) );
      }
    }
  }
}

void network::random_biases () {

}

/*
 * PUBLIC
 */

// Constructor
network::network (std::vector<unsigned int> sizes) {
  this->sizes = sizes;
  num_layers = sizes.size();

  // Generate weights and biases
  random_weights();
  std::cout << weights.size() << std::endl;
  std::cout << weights[0].size() << std::endl;
  std::cout << weights[0][0].size() << std::endl;
  // for (auto outer = weights.begin(); outer != weights.end(); ++outer) {
  int l = 1;
    for (auto mid = weights[l].begin(); mid != weights[l].end(); ++mid) {
      for (auto inner = (*mid).begin(); inner != (*mid).end(); ++inner) {
        std::cout << std::setfill(' ') << std::setw(10) << *inner << ' ';
      }
      std::cout << std::endl;
    }
}

#ifndef NETWORK
#define NETWORK

#include <cstdlib>
#include <vector>
#include "mnist_loader.h"

class network {
  unsigned int num_layers;
  std::vector<unsigned int> sizes;
  std::vector< std::vector< std::vector<double> > > weights;
  std::vector<double> biases;

  // Generate weights and biases
  void random_weights ();
  void random_biases  ();

  public:
    // Constructor
    network(std::vector<unsigned int>);
    // Destructor
    ~network();
};

#endif

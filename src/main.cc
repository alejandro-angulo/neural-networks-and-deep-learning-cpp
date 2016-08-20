#include <iostream>
#include <fstream>
#include <linux/limits.h> // For PATH_MAX
#include <vector>
#include <string>
#include "mnist_loader.h"
using namespace std;

int main () {
  char images[PATH_MAX];
  char labels[PATH_MAX];
  realpath("../data/train-images-idx3-ubyte", images);
  realpath("../data/train-labels-idx1-ubyte", labels);

  // read_mnist_images(abs_path, num_images);
  mnist_loader test(labels, images);
  cout << "Image Filename: " << test.get_imageFileName() << endl;
  cout << "Label Filename: " << test.get_labelFileName() << endl;
  test.load_labels();
  test.load_images();

  return 0;
}

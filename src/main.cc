#include <iostream>
#include <fstream>
#include <linux/limits.h> // For PATH_MAX
#include <vector>
#include <string>
#include "mnist_loader.h"
using namespace std;

int reverseInt (int i) {
    unsigned char c1, c2, c3, c4;

    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;

    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

void read_mnist_images (string full_path, int num_images) {
  ifstream file(full_path);
  if ( file.is_open() ) {
    int magic_number = 0, total_num_images = 0, n_rows = 0, n_cols = 0;
    unsigned char* buffer = new unsigned char[2];
    // cout << sizeof(buffer) << endl;

    // Check if file is gzip compressed
    file.read( (char*)buffer, 2 );
    if (buffer[0] == 0x1f && buffer[1] == 0x8b) {
      cout << "what" << endl;
      throw runtime_error("File needs to be decompressed.");
    }
    delete[] buffer;
    file.seekg(0, ios::beg);

    file.read( (char*)&magic_number, sizeof(magic_number) );
    magic_number = reverseInt(magic_number);

    if (magic_number != 2051) throw runtime_error("Invalid MNIST image file!");

    file.read( (char *)&total_num_images, sizeof(total_num_images) );
    total_num_images = reverseInt(total_num_images);
    file.read( (char *)&n_rows, sizeof(n_rows) );
    n_rows = reverseInt(n_rows);
    file.read( (char *)&n_cols, sizeof(n_cols) );
    n_cols = reverseInt(n_cols);

    if (num_images > total_num_images) {
      throw runtime_error("There are only " + to_string(total_num_images) +
        " images available. Cannot retrieve " + to_string(num_images) + " images.");
    }

    cout << total_num_images << ' ' << num_images << ' ' << n_rows << ' ' << n_cols << endl;
    for (int i = 0; i < num_images; ++i) {
      for (int r = 0; r < n_rows; ++r) {
        for (int c = 0; c < n_cols; ++c) {
          unsigned char temp = 0;
          file.read( (char*)&temp, sizeof(temp) );
        }
      }
    }
  }
  else {
    // include the full directory in the message
    throw runtime_error("Cannot open file `" + full_path + "`!");
  }
}

int main () {
  int num_images = 500;
  // int img_sz     = 500;
  char images[PATH_MAX];
  char labels[PATH_MAX];
  realpath("../data/train-images-idx3-ubyte", images);
  realpath("../data/train-labels-idx1-ubyte", labels);

  // read_mnist_images(abs_path, num_images);
  mnist_loader test(labels, images);
  cout << "Image Filename: " << test.get_imageFileName() << endl;
  cout << "Label Filename: " << test.get_labelFileName() << endl;
  test.load_labels();

  return 0;
}

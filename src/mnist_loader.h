#ifndef MNIST_LOADER
#define MNIST_LOADER

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <linux/limits.h> // for PATH_MAX
#include <string>
#include <vector>

class mnist_loader {
  std::string labelFileName;
  std::string imageFileName;

  std::vector<unsigned char> labels;
  unsigned char*** images;

  int num_images;
  int num_labels;

  // Constants taken from MNIST site.
  // All *_OFFSET and *_SIZE vars are in bytes.
  const static int MAGIC_OFFSET = 0;
  const static int OFFSET_SIZE = 4;

  const static int LABEL_MAGIC = 2049;
  const static int IMAGE_MAGIC = 2051;

  const static int NUMBER_ITEMS_OFFSET = 4;
  const static int NUMBER_ITEMS_SIZE = 4;

  const static int LABEL_OFFSET = 8;
  const static int LABEL_SIZE = 1;

  const static int ROWS_OFFSET = 8;
  const static int ROWS_SIZE = 4;

  const static int COLS_OFFSET = 12;
  const static int COLS_SIZE = 4;

  const static int ROWS = 28;
  const static int COLS = 28;

  const static int IMAGE_OFFSET = 16;
  const static int IMAGE_SIZE = ROWS * COLS;

  void handle_file (std::string, std::ifstream&);

  public:
    // Constructor
    mnist_loader (std::string, std::string);
    // Destructor
    ~mnist_loader ();

    // Getters
    std::string get_labelFileName ();
    std::string get_imageFileName ();
    unsigned char** get_image  (int);
    unsigned char   get_label  (int);

    // Load Files
    void load_labels ();
    void load_images ();

    // Misc.
    void print_image (int);
};

#endif

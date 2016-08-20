#include "mnist_loader.h"

// Helper Functions
bool is_gzipped (std::ifstream &file) {
  bool is_zipped = false;
  unsigned char buffer[2];

  file.read( (char*)buffer, 2 );
  if (buffer[0] == 0x1f && buffer[1] == 0x8b) {
    is_zipped = true;
  }
  file.seekg(0, std::ios::beg);

  return is_zipped;
}

int reverseInt (int i) {
    unsigned char c1, c2, c3, c4;

    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;

    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

void shuffle (unsigned char **array, size_t n) {
  if (n > 1) {
    for (size_t i = 0; i < (n - 1); ++i) {
      size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
      unsigned char *k = array[j];
      array[j] = array[i];
      array[i] = k;
    }
  }
}

/*
 * PRIVATE
 */

void mnist_loader::handle_file (std::string abs_path, std::ifstream& file) {
  if ( file.is_open() ) {
    // MNIST data is gzip-compressed, but we need uncompressed files.
    if ( is_gzipped(file) ) {
      throw std::runtime_error(abs_path + " needs to be decompressed.");
    }
  } else throw std::runtime_error(abs_path + " could not be opened.");
}

/*
* PUBLIC
*/

// Constructor
mnist_loader::mnist_loader (std::string labelFileName, std::string imageFileName) :
  labelFileName(labelFileName), imageFileName(imageFileName) {}

// Destructor
mnist_loader::~mnist_loader () {
  for (int i = 0; i < num_images; ++i) {
    delete[] images[i];
  }
  delete[] images;
}


// Getters
std::string mnist_loader::get_labelFileName () { return labelFileName; }
std::string mnist_loader::get_imageFileName () { return imageFileName; }

// Load Files
void mnist_loader::load_labels () {
  std::ifstream file(labelFileName);
  handle_file(labelFileName, file);
  int magic_number = 0;

  file.seekg(this->MAGIC_OFFSET);
  file.read( (char*)&magic_number, this->OFFSET_SIZE );
  magic_number = reverseInt(magic_number);

  if (magic_number != this->LABEL_MAGIC) {
    throw std::runtime_error("Invalid MNIST label file!");
  } else {
    std::cout << "Magic number is correct." << std::endl;
  }

  file.seekg(this->NUMBER_ITEMS_OFFSET);
  file.read( (char *)&num_labels, this->NUMBER_ITEMS_SIZE );
  num_labels = reverseInt(num_labels);
  std::cout << "There are " << num_labels << " labels." << std::endl;

  file.seekg(this->LABEL_OFFSET);
  std::cout << "Reading labels..." << std::endl;
  for (int i = 0; i < num_labels; ++i) {
    unsigned char temp;
    file.read( (char *)&temp, this->LABEL_SIZE );
    this->labels.push_back(temp);
  }

  std::cout << "Shuffling labels..." << std::endl;
  std::random_shuffle( labels.begin(), labels.end() );
}

void mnist_loader::load_images () {
  std::ifstream file(imageFileName);
  handle_file(imageFileName, file);

  int magic_number = 0;

  file.seekg(this->MAGIC_OFFSET);
  file.read( (char *)&magic_number, this->OFFSET_SIZE );
  magic_number = reverseInt(magic_number);

  if (magic_number != this->IMAGE_MAGIC) {
    throw std::runtime_error("Invalid MNIST image file!");
  } else {
    std::cout << "Magic number is correct." << std::endl;
  }

  file.seekg(this->NUMBER_ITEMS_OFFSET);
  file.read( (char *)&num_images, this->NUMBER_ITEMS_SIZE );
  num_images = reverseInt(num_images);
  std::cout << "There are " << num_images << " images." << std::endl;

  images = new unsigned char* [num_images];

  file.seekg(this->IMAGE_OFFSET);
  std::cout << "Reading images..." << std::endl;
  for (int i = 0; i < num_images; ++i) {
    images[i] =  new unsigned char [this->IMAGE_SIZE];
    for (int j = 0; j < this->IMAGE_SIZE; ++j) {
      unsigned char temp;
      file.read( (char *)&temp, 1 );
      images[i][j] = temp;
    }
  }

  srand( (unsigned) time(NULL) );
  std::cout << "Shuffling images..." << std::endl;
  shuffle(images, num_images);
}

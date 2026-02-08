#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct Pixel {
  unsigned char red, green, blue;
};

struct Image {
  int width;
  int height;
  std::vector<Pixel> pixels;

  Pixel get_pixel(int x, int y) { return pixels[y * width + x]; }
};

Image load_jpg_image(std::string filename) {
  int width, height, channels;
  unsigned char *img_data =
      stbi_load(filename.c_str(), &width, &height, &channels, 3);
  if (img_data == NULL) {
    return Image{0, 0, {}};
  }
  Image loaded_image;
  loaded_image.width = width;
  loaded_image.height = height;
  loaded_image.pixels.resize(width * height);

  for (int i = 0, j = 0; i < width * height * 3; i += 3) {
    Pixel pixel{
        img_data[i],     // R
        img_data[i + 1], // G
        img_data[i + 2]  // B
    };
    loaded_image.pixels[j] = pixel;
    j++;
  }
  stbi_image_free(img_data);
  return loaded_image;
}

int main(void) {
  std::string file_name = "test.jpg";
  Image image = load_jpg_image(file_name);
  for (Pixel &pixel : image.pixels) {
    std::cout << (int)pixel.red << (int)pixel.green << (int)pixel.blue
              << std::endl;
  }

  return 0;
}
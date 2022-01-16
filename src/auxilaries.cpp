#include <iostream>
#include <fstream>
#include <limits>

void ignore_line(std::istream &is)
{
  is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


void output_base_image()
{
  const int width{256};
  const int height{256};

  std::ofstream outImageFile;

  outImageFile.open("outImage.PPM");
  
  outImageFile << "P3\n" << width << ' ' << height << "\n255\n";

  for (auto row{height}; row>0; --row)
  {
    std::cout << "\rScanlines remaining: " << row << '\n' << std::flush;
    for (auto col{0}; col<width; ++col)
    {
      auto r = static_cast<double>(row)/width;
      auto g = static_cast<double>(col)/height;
      auto b = 0.25;
      outImageFile << static_cast<int> (r*255.999) << ' ';
      outImageFile << static_cast<int> (g*255.999) << ' ';
      outImageFile << static_cast<int> (b*255.999) << ' ';
      
    }
    outImageFile << '\n';
  }
  std::cout << "done";
  outImageFile.close();
}
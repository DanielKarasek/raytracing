#ifndef AUXILARIES_1213_H
#define AUXILARIES_1213_H

#include <iostream>

void ignore_line(std::istream &is);

template <typename T>
T get_integral_value(std::string_view text, bool (*condition)(T))
{
  T val;
  while (true)
  {
    std::cout << text;
    std::cin >> val;
    if (std::cin.fail())
    {
      std::cout << "Input failed due to invalid value\n";
      std::cin.clear();
      ignore_line(std::cin);
    }
    else if (!condition(val))
    {
      std::cout << "Input failed due to value not passing condition\n";
      ignore_line(std::cin);
    }
    else
    {
      ignore_line(std::cin);
      return val;
    }
  }
}

void output_base_image();

#endif
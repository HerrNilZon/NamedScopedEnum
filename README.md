# NamedScopedEnum
Scoped C++ enumeration with string descriptors

[![Build Status](https://travis-ci.org/HerrNilZon/NamedScopedEnum.svg?branch=master)](https://travis-ci.org/HerrNilZon/NamedScopedEnum)
[![Version](https://img.shields.io/badge/c%2B%2B-11-blue.svg)](http://en.cppreference.com/w/cpp)
[![License](https://img.shields.io/badge/license-MIT-lightgrey.svg)](https://en.wikipedia.org/wiki/MIT_License)

--

# Usage

An enumeration created using the `NAMED_SCOPED_ENUM` macro behaves like strongly typed (scoped) C++11 enumeration.
Additionally the size of the enumeration is available at compile time, and the `std::string` representation of the
current enumeration value as well as a vector of `std::string`s of all names can be retrieved by special member functions.  

```cpp
#include "NamedScopedEnum.hpp"

NAMED_SCOPED_ENUM( Colors, GREEN, YELLOW, RED );

class TrafficLight
{
public:
  TrafficLight( Colors color ) :
          color_( color )
  {
    std::cout << "Initialized signal with: " << color_.name( ) << std::endl;
  }

  void set_color( Colors color )
  {
    color_ = color;
    std::cout << "Set signal to: " << color_.name( ) << std::endl;
  }

  Colors get_color( ) const
  {
    return color_;
  }

private:
  Colors color_;
};

int main( int argc,
          char **argv )
{
  TrafficLight signal( Colors::RED );

  signal.set_color( Colors::YELLOW );

  signal.set_color( Colors::GREEN );

  std::string current_color = signal.get_color( );

  std::cout << "current_color: " << current_color << std::endl;

  std::cout << "Available colors are:";

  for ( const auto & color : Colors::names( ) )
  {
    std::cout << " " << color;
  }

  std::cout << std::endl;
}
```

```
Initialized signal with: RED
Set signal to: YELLOW
Set signal to: GREEN
current_color: GREEN
Available colors are: GREEN YELLOW RED
```

## Create a static map using a std::array

To create a map with a fixed number of keys and __real__ contant time look up (no hard feelings `std::map`)
just combine `std::array` with a `NamedScopedEnum`. 

```cpp
#include "NamedScopedEnum.hpp"

#include <array>

int main( int argc,
          char **argv )
{
  NAMED_SCOPED_ENUM( FRUIT, APPLE, ORANGE, BANANA, PLUM ); // Something healthy

  std::array<int, FRUIT::size( )> fruitMap;                // size() is constexpr

  fruitMap[FRUIT::APPLE] = 4;
  fruitMap[FRUIT::ORANGE] = 1;
  fruitMap[FRUIT::BANANA] = 3;
  fruitMap[FRUIT::PLUM] = 2;

  std::cout << "How much fruit is in the basket?" << std::endl;

  for ( size_t i = 0; i < FRUIT::size( ); ++i )
  {
    auto names = FRUIT::names( );                          // names() is static
    std::cout << names[i] << " : " << fruitMap[i] << std::endl;
  } // end of i -loop
}
```

```
How much fruit is in the basket?
APPLE : 4
ORANGE : 1
BANANA : 3
PLUM : 2
```
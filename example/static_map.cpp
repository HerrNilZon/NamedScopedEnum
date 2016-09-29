// The MIT License (MIT)
//
// Copyright (c) 2016 Nils Zander, Tino Bog
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "NamedScopedEnum.hpp"

#include <array>

int main( int argc,
          char **argv )
{
  NAMED_SCOPED_ENUM( FRUIT, APPLE, ORANGE, BANANA, PLUM );
  // Something healthy

  std::array<int, FRUIT::size( )> fruitMap; // size() is constexpr

  fruitMap[FRUIT::APPLE] = 4;
  fruitMap[FRUIT::ORANGE] = 1;
  fruitMap[FRUIT::BANANA] = 3;
  fruitMap[FRUIT::PLUM] = 2;

  std::cout << "How much fruit is in the basket?" << std::endl;

  for ( size_t i = 0; i < FRUIT::size( ); ++i )
  {
    auto names = FRUIT::names( ); // names() is static
    std::cout << names[i] << " : " << fruitMap[i] << std::endl;
  } // end of i -loop
}


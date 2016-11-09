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

#ifndef _NAMED_SCOPED_ENUM_HPP_
#define _NAMED_SCOPED_ENUM_HPP_

#include <string>
#include <iostream>
#include <regex> // uses gcc compiler >= 4.9

namespace detail 
{


typedef std::vector<std::string> StringVector;

inline StringVector tokenize( const std::string& parameters )
{
  const std::regex re( "\\s*,\\s*" );
  std::sregex_token_iterator begin( parameters.begin( ), parameters.end( ), re, -1 );
  std::sregex_token_iterator end;
  StringVector tokens( begin, end );
  return tokens;
}

constexpr bool noCustomEnumerators( char const * str )
{
  return *str != '=' && ( *str == '\0' || noCustomEnumerators( str + 1 ) );
}

} // namespace utilities

#define NAMED_SCOPED_ENUM(ENUM_NAME, ...)\
\
static_assert( detail::noCustomEnumerators(#__VA_ARGS__),"Custom values for the enumerators are not supported!" );\
\
class ENUM_NAME{\
public:\
  enum ENUMERATORS {__VA_ARGS__};\
  \
  ENUM_NAME( ENUMERATORS default_enumerator ):\
    _name(names()[default_enumerator]),\
    _enumerator(default_enumerator)\
  {\
  }\
  \
  static constexpr size_t size()\
  {\
    return std::tuple_size<decltype(std::make_tuple(__VA_ARGS__))>::value;\
  }\
  \
  std::string name() const\
  {\
    return _name;\
  }\
  \
  ENUMERATORS enumerator() const\
  {\
    return _enumerator;\
  }\
  \
  void set_enumerator( ENUMERATORS enumerator)\
  {\
    _enumerator = enumerator;\
    _name = names()[enumerator];\
  }\
  \
  operator ENUMERATORS() const\
  {\
    return _enumerator;\
  }\
  \
  operator std::string() const\
  {\
    return _name;\
  }\
  \
  static detail::StringVector names()\
  {\
    return detail::tokenize(#__VA_ARGS__);\
  }\
  \
private:\
  std::string _name;\
  ENUMERATORS _enumerator;\
}

#endif // _NAMED_SCOPED_ENUM_HPP_

/** @file      string.hpp
 *
 *  @mainpage  string.hpp
 *
 *  @brief     build your own string like std::string from scratch
 *
 *  @author    Gapry
 *
 *  @date      2020
 *
 *  @copyright MIT License
 */

#ifndef __STRING_HPP__
#define __STRING_HPP__

#include <cstddef>

class beta::string : public beta::noncopyable {
  using size_type = std::size_t;

public:
  /**
   * @brief constructs a string
   */
  string(const char* = "");

  /**
   * @brief copy constructor
   */
  string(const string&);

  /**
   * @brief assigns values to the string
   */
  string& operator=(const string&);

  /**
   * @brief assigns values to the string
   */
  string& operator=(const char*);

  /**
   * @brief destroys the string, deallocating internal storage if used
   */
  ~string();

  /**
   * @brief returns a non-modifiable standard C character array version of the string
   */
  operator const char*() const;

  /**
   * @brief concatenates two strings
   */
  string& operator+=(const string&);

  /**
   * @brief concatenates a string and a char
   */
  string& operator+=(const char*);

  /**
   * @brief returns the number of characters
   */
  size_type length() const;

  /**
   * @brief returns the number of characters that can be held in currently allocated storage
   */
  size_type capacity() const;

  /**
   * @brief checks whether the string is empty
   */
  bool empty();
};

#endif

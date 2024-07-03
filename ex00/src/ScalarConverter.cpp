/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 09:15:43 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/03 14:38:02 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include "colors.hpp"
#include <iomanip>
#include <iostream>

int ScalarConverter::_errFlags = OK;
ScalarConverter::t_ScalarType ScalarConverter::_type = DEFAULT;
char ScalarConverter::_char = DEFAULT;
int ScalarConverter::_int = DEFAULT;
float ScalarConverter::_float = DEFAULT;
double ScalarConverter::_double = DEFAULT;

char const *ScalarConverter::TypeNotFound::what(void) const throw() {
  return ("Please enter a valid type (char, int, float, double).");
}

char const *ScalarConverter::OverflowLiteral::what(void) const throw() {
  return ("Overflow in the literal value. Please enter a value with the "
          "correct range from the type.");
}

static void setErrFlags(void) {
  switch (ScalarConverter::_type) {
  case ScalarConverter::INT:
    if (ScalarConverter::_int > std::numeric_limits<char>::max() ||
        ScalarConverter::_int < std::numeric_limits<char>::lowest())
      ScalarConverter::_errFlags |= ScalarConverter::CHAR_OVERFLOW;
    break;
  case ScalarConverter::FLOAT:
    if (ScalarConverter::_float > std::numeric_limits<char>::max() ||
        ScalarConverter::_float < std::numeric_limits<char>::lowest())
      ScalarConverter::_errFlags |= ScalarConverter::CHAR_OVERFLOW;
    if (ScalarConverter::_float > std::numeric_limits<int>::max() ||
        ScalarConverter::_float < std::numeric_limits<int>::lowest()) {
      ScalarConverter::_errFlags |= ScalarConverter::INT_OVERFLOW;
    }
    break;
  case ScalarConverter::DOUBLE:
    if (ScalarConverter::_double > std::numeric_limits<char>::max() ||
        ScalarConverter::_double < std::numeric_limits<char>::lowest())
      ScalarConverter::_errFlags |= ScalarConverter::CHAR_OVERFLOW;
    if (ScalarConverter::_double > std::numeric_limits<int>::max() ||
        ScalarConverter::_double < std::numeric_limits<int>::lowest())
      ScalarConverter::_errFlags |= ScalarConverter::INT_OVERFLOW;
    if (ScalarConverter::_double > std::numeric_limits<float>::max() ||
        ScalarConverter::_double < std::numeric_limits<float>::lowest())
      ScalarConverter::_errFlags |= ScalarConverter::FL_OVERFLOW;
    break;
  default:
    return;
  }
}

static bool isCharOk(void) {
  if (ScalarConverter::_errFlags & ScalarConverter::CHAR_OVERFLOW ||
      ScalarConverter::_errFlags & ScalarConverter::CHAR_UNPRINTABLE)
    return (false);
  return (true);
}

static std::string charErrMsg(void) {
  if (ScalarConverter::_errFlags & ScalarConverter::CHAR_OVERFLOW)
    return ("impossible");
  if (ScalarConverter::_errFlags & ScalarConverter::CHAR_UNPRINTABLE)
    return ("Non displayable");
  return ("error");
}

static bool isIntOk(void) {
  if (ScalarConverter::_errFlags & ScalarConverter::INT_OVERFLOW)
    return (false);
  return (true);
}

static std::string intErrMsg(void) {
  if (ScalarConverter::_errFlags & ScalarConverter::INT_OVERFLOW)
    return ("impossible");
  return ("error");
}

static bool isFlOk(void) {
  if (ScalarConverter::_errFlags & ScalarConverter::FL_OVERFLOW)
    return (false);
  return (true);
}

static std::string flErrMsg(void) {
  if (ScalarConverter::_errFlags & ScalarConverter::FL_OVERFLOW)
    return ("impossible");
  return ("error");
}

static bool isDlOk(void) {
  if (ScalarConverter::_errFlags & ScalarConverter::DL_OVERFLOW)
    return (false);
  return (true);
}

static std::string dlErrMsg(void) {
  if (ScalarConverter::_errFlags & ScalarConverter::DL_OVERFLOW)
    return ("impossible");
  return ("error");
}

void ScalarConverter::displayConversion() {
  std::cout << RESET << "char:\t" << YELLOW;
  if (isCharOk())
    std::cout << "'" << ScalarConverter::_char << "'\n";
  else
    std::cout << charErrMsg() << "\n";
  std::cout << RESET << "int:\t" << YELLOW;
  if (isIntOk())
    std::cout << ScalarConverter::_int << "\n";
  else
    std::cout << intErrMsg() << "\n";
  std::cout << RESET << "float:\t" << YELLOW;
  if (isFlOk()) {
    if (std::fabs(ScalarConverter::_float - ScalarConverter::_int) < 0.000001f)
      std::cout << std::fixed << std::setprecision(1) << ScalarConverter::_float
                << "f\n";
    else
      std::cout << std::fixed << ScalarConverter::_float << "f\n";
  } else
    std::cout << flErrMsg() << "\n";
  std::cout << RESET << "double:\t" << YELLOW;
  if (isDlOk()) {
    if (std::fabs(ScalarConverter::_double - ScalarConverter::_int) < 0.000001)
      std::cout << std::fixed << std::setprecision(1)
                << ScalarConverter::_double;
    else
      std::cout << std::fixed << ScalarConverter::_double;
  } else
    std::cout << dlErrMsg();
  std::cout << RESET << std::endl;
}

void ScalarConverter::convert(std::string const &literal) {
  ScalarConverter::_errFlags = OK;
  try {
    setType(literal);
    setErrFlags();
    castScalar();
    ScalarConverter::displayConversion();
  } catch (std::exception &e) {
    std::cerr << RED << "Error: Input could not be converted:\n\t" << RESET
              << e.what() << std::endl;
  }
}

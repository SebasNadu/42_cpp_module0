/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setType.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 21:09:05 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/02 09:07:36 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <limits>

static bool setInt(std::string const &literal) {
  char *endptr;
  long nb = std::strtol(literal.c_str(), &endptr, 10);

  if (*endptr != '\0' || endptr == literal.c_str())
    return (false);
  if (nb > std::numeric_limits<int>::max() ||
      nb < std::numeric_limits<int>::lowest()) {
    ScalarConverter::_errFlags |= ScalarConverter::INT_OVERFLOW;
    throw ScalarConverter::OverflowLiteral();
  }
  ScalarConverter::_int = static_cast<int>(nb);
  return (true);
}

static bool setFloat(std::string const &literal) {
  char *endptr;
  double nb = std::strtod(literal.c_str(), &endptr);

  if (*endptr != 'f' || endptr == literal.c_str())
    return (false);
  if (*endptr == 'f' && (endptr + 1 && *(endptr + 1) != '\0'))
    return (false);
  if (nb > std::numeric_limits<float>::max() ||
      nb < std::numeric_limits<float>::lowest()) {
    ScalarConverter::_errFlags |= ScalarConverter::FL_OVERFLOW;
    throw ScalarConverter::OverflowLiteral();
  }
  ScalarConverter::_float = static_cast<float>(nb);
  return (true);
}

static bool setDouble(std::string const &literal) {
  char *endptr;

  size_t pos = literal.find('.');
  if (pos == std::string::npos)
    return (false);
  long double nb = std::strtold(literal.c_str(), &endptr);
  if (*endptr != '\0' || endptr == literal.c_str())
    return (false);
  if (nb > std::numeric_limits<double>::max() ||
      nb < std::numeric_limits<double>::lowest()) {
    ScalarConverter::_errFlags |= ScalarConverter::DL_OVERFLOW;
    throw ScalarConverter::OverflowLiteral();
  }
  ScalarConverter::_double = static_cast<double>(nb);
  return (true);
}

static bool setChar(std::string const &literal) {
  if (literal.length() == 1) {
    ScalarConverter::_char = literal[0];
    if (!std::isprint(ScalarConverter::_char))
      ScalarConverter::_errFlags |= ScalarConverter::CHAR_UNPRINTABLE;
    return (true);
  }
  return (false);
}

static bool setPseudoLiteral(std::string const &literal) {
  if (literal == "inf" || literal == "+inf" || literal == "inff" ||
      literal == "+inff") {
    ScalarConverter::_errFlags |= ScalarConverter::CHAR_OVERFLOW;
    ScalarConverter::_errFlags |= ScalarConverter::INT_OVERFLOW;
    ScalarConverter::_float = std::numeric_limits<float>::infinity();
    ScalarConverter::_double = std::numeric_limits<double>::infinity();
    return (true);
  }
  if (literal == "-inf" || literal == "-inff") {
    ScalarConverter::_errFlags |= ScalarConverter::CHAR_OVERFLOW;
    ScalarConverter::_errFlags |= ScalarConverter::INT_OVERFLOW;
    ScalarConverter::_float = -std::numeric_limits<float>::infinity();
    ScalarConverter::_double = -std::numeric_limits<double>::infinity();
    return (true);
  }
  if (literal == "nan" || literal == "nanf") {
    ScalarConverter::_errFlags |= ScalarConverter::CHAR_OVERFLOW;
    ScalarConverter::_errFlags |= ScalarConverter::INT_OVERFLOW;
    ScalarConverter::_float = std::numeric_limits<float>::quiet_NaN();
    ScalarConverter::_double = std::numeric_limits<double>::quiet_NaN();
    return (true);
  }
  return (false);
}

void setType(std::string const &literal) {
  if (setPseudoLiteral(literal))
    ScalarConverter::_type = ScalarConverter::PSEUDO_LITERAL;
  else if (setInt(literal))
    ScalarConverter::_type = ScalarConverter::INT;
  else if (setFloat(literal))
    ScalarConverter::_type = ScalarConverter::FLOAT;
  else if (setDouble(literal))
    ScalarConverter::_type = ScalarConverter::DOUBLE;
  else if (setChar(literal))
    ScalarConverter::_type = ScalarConverter::CHAR;
  else
    throw ScalarConverter::TypeNotFound();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   castScalar.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 21:11:25 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/01 23:32:42 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

static void castFromChar(void) {
  ScalarConverter::_int = static_cast<int>(ScalarConverter::_char);
  ScalarConverter::_float = static_cast<float>(ScalarConverter::_char);
  ScalarConverter::_double = static_cast<double>(ScalarConverter::_char);
}

static void castFromInt(void) {
  ScalarConverter::_char = static_cast<char>(ScalarConverter::_int);
  ScalarConverter::_float = static_cast<float>(ScalarConverter::_int);
  ScalarConverter::_double = static_cast<double>(ScalarConverter::_int);
  if (!std::isprint(ScalarConverter::_char))
    ScalarConverter::_errFlags |= ScalarConverter::CHAR_UNPRINTABLE;
}

static void castFromFloat(void) {
  ScalarConverter::_char = static_cast<char>(ScalarConverter::_float);
  ScalarConverter::_int = static_cast<int>(ScalarConverter::_float);
  ScalarConverter::_double = static_cast<double>(ScalarConverter::_float);
  if (!std::isprint(ScalarConverter::_char))
    ScalarConverter::_errFlags |= ScalarConverter::CHAR_UNPRINTABLE;
}

static void castFromDouble(void) {
  ScalarConverter::_char = static_cast<char>(ScalarConverter::_double);
  ScalarConverter::_int = static_cast<int>(ScalarConverter::_double);
  ScalarConverter::_float = static_cast<float>(ScalarConverter::_double);
  if (!std::isprint(ScalarConverter::_char))
    ScalarConverter::_errFlags |= ScalarConverter::CHAR_UNPRINTABLE;
}

void castScalar(void) {
  switch (ScalarConverter::_type) {
  case ScalarConverter::CHAR:
    castFromChar();
    break;
  case ScalarConverter::INT:
    castFromInt();
    break;
  case ScalarConverter::FLOAT:
    castFromFloat();
    break;
  case ScalarConverter::DOUBLE:
    castFromDouble();
    break;
  case ScalarConverter::PSEUDO_LITERAL:
    break;
  default:
    throw ScalarConverter::TypeNotFound();
  }
}

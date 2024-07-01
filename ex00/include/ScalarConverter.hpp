/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 23:21:21 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/01 23:39:14 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

class ScalarConverter {
public:
  static void convert(std::string const &literal);
  static void displayConversion(void);

  typedef enum e_ScalarType {
    DEFAULT,
    CHAR,
    INT,
    FLOAT,
    DOUBLE,
    PSEUDO_LITERAL,
  } t_ScalarType;

  typedef enum e_ScalarFlags {
    OK = 0x00,
    CHAR_UNPRINTABLE = 0x01,
    CHAR_OVERFLOW = 0x02,
    INT_OVERFLOW = 0x04,
    FL_OVERFLOW = 0x08,
    DL_OVERFLOW = 0x10,
  } t_ScalarFlags;

  static t_ScalarType _type;
  static char _char;
  static int _int;
  static float _float;
  static double _double;
  static int _errFlags;

  class TypeNotFound : public std::exception {
  public:
    virtual char const *what(void) const throw();
  };

  class OverflowLiteral : public std::exception {
  public:
    virtual char const *what(void) const throw();
  };
};

void setType(std::string const &literal);
void castScalar(void);

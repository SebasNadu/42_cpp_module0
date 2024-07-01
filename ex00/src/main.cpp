/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 20:40:49 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/01 21:07:42 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Colors.hpp"
#include "ScalarConverter.hpp"
#include <iostream>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << RED << "Error: \n\t" << RESET
              << "Usage: ./convert [scalar_value]\n"
                 "\tscalar_value: int, float, double or char."
              << std::endl;
    return (1);
  }
  try {
    ScalarConverter::convert(argv[1]);
  } catch (...) {
    std::cerr << RED << "Error: Fatal\n" << RESET << std::endl;
    return (1);
  }
  return (0);
}

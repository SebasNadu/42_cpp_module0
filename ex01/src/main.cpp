/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:05:59 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/03 14:35:48 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include "colors.hpp"
#include <iostream>

int main() {
  Data jack;
  Data bob;

  jack.name = "Jack White";
  jack.age = 49;
  jack.next = &bob;
  bob.name = "Bob Marley";
  bob.age = 79;
  bob.next = NULL;

  std::cout << YELLOW << "\n----- Data 1 -----\n\n" << RESET;
  std::cout << "address: " << &jack << '\n';
  std::cout << "name   : " << jack.name << '\n';
  std::cout << "age    : " << jack.age << '\n';
  std::cout << "next   : " << jack.next << '\n';
  std::cout << YELLOW << "\n----- Data 2 -----\n\n" << RESET;
  std::cout << "address: " << &bob << '\n';
  std::cout << "name   : " << bob.name << '\n';
  std::cout << "age    : " << bob.age << '\n';
  std::cout << "next   : " << bob.next << std::endl;

  uintptr_t serializedJack = Serializer::serialize(&jack);

  std::cout << YELLOW << "\n----- Check Data 1 -----\n\n" << RESET;
  std::cout << "Original address  : " << PURPLE << &jack << '\n' << RESET;
  std::cout << "serialized address: " << CYAN << serializedJack << "\n\n"
            << RESET;

  std::cout << "Original name    : " << PURPLE << jack.name << '\n' << RESET;
  std::cout << "Deserialized name: " << CYAN
            << Serializer::deserialize(serializedJack)->name << "\n\n"
            << RESET;

  std::cout << "Original age    : " << PURPLE << jack.age << '\n' << RESET;
  std::cout << "Deserialized age: " << CYAN
            << Serializer::deserialize(serializedJack)->age << "\n\n"
            << RESET;

  std::cout << "Original next   : " << PURPLE << jack.next << '\n' << RESET;
  std::cout << "Deserialize next: " << CYAN
            << Serializer::deserialize(serializedJack)->next << '\n'
            << RESET;

  std::cout << "\nIs the same data?: ";
  if (Serializer::deserialize(serializedJack) == &jack &&
      Serializer::deserialize(serializedJack)->name == jack.name &&
      Serializer::deserialize(serializedJack)->age == jack.age &&
      Serializer::deserialize(serializedJack)->next == jack.next)
    std::cout << GREEN << "Yes" << RESET << std::endl;
  else
    std::cout << RED << "No" << RESET << std::endl;

  uintptr_t serializedBob = Serializer::serialize(&bob);

  std::cout << YELLOW << "\n----- Check Data 2 -----\n\n" << RESET;
  std::cout << "Original address  : " << PURPLE << &bob << '\n' << RESET;
  std::cout << "serialized address: " << CYAN << serializedBob << "\n\n"
            << RESET;

  std::cout << "Original name    : " << PURPLE << bob.name << '\n' << RESET;
  std::cout << "Deserialized name: " << CYAN
            << Serializer::deserialize(serializedBob)->name << "\n\n"
            << RESET;

  std::cout << "Original age    : " << PURPLE << bob.age << '\n' << RESET;
  std::cout << "Deserialized age: " << CYAN
            << Serializer::deserialize(serializedBob)->age << "\n\n"
            << RESET;

  std::cout << "Original next   : " << PURPLE << bob.next << '\n' << RESET;
  std::cout << "Deserialize next: " << CYAN
            << Serializer::deserialize(serializedBob)->next << '\n'
            << RESET;

  std::cout << "\nIs the same data?: ";
  if (Serializer::deserialize(serializedBob) == &bob &&
      Serializer::deserialize(serializedBob)->name == bob.name &&
      Serializer::deserialize(serializedBob)->age == bob.age &&
      Serializer::deserialize(serializedBob)->next == bob.next)
    std::cout << GREEN << "Yes" << RESET << std::endl;
  else
    std::cout << RED << "No" << RESET << std::endl;
}

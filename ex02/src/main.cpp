/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:50:40 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/08/07 18:43:12 by johnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "A.hpp"
#include "B.hpp"
#include "Base.hpp"
#include "C.hpp"
#include "colors.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <unistd.h>

static void tic_tac(int usleep_time, int duration) {
  std::cout << std::unitbuf;
  for (int i = 0; i < duration; i++) {
    std::cout << ".";
    usleep(usleep_time);
  }
  std::cout << std::nounitbuf;
  std::cout << std::endl;
}

Base *generate(void) {
  int random = std::rand() % 100;

  if (random <= 33) {
    std::cout << "A instance created" << std::endl;
    return (new A());
  } else if (random <= 66) {
    std::cout << "B instance created" << std::endl;
    return (new B());
  } else {
    std::cout << "C instance created" << std::endl;
    return (new C());
  }
  return (NULL);
}

void identify(Base *p) {
  std::cout << "Class type: ";
  if (p == NULL)
    std::cout << "NULL" << std::endl;
  else if (dynamic_cast<A *>(p))
    std::cout << "A" << std::endl;
  else if (dynamic_cast<B *>(p))
    std::cout << "B" << std::endl;
  else if (dynamic_cast<C *>(p))
    std::cout << "C" << std::endl;
  else
    std::cout << "Unknown" << std::endl;
}

void identify(Base &p) {
  std::cout << "Class type: ";
  try {
    (void)dynamic_cast<A &>(p);
    std::cout << "A" << std::endl;
    return;
  } catch (std::exception &e) {
  }
  try {
    (void)dynamic_cast<B &>(p);
    std::cout << "B" << std::endl;
    return;
  } catch (std::exception &e) {
  }
  try {
    (void)dynamic_cast<C &>(p);
    std::cout << "C" << std::endl;
    return;
  } catch (std::exception &e) {
  }
  std::cout << "Unknown" << std::endl;
}

int main() {
  std::srand(std::time(NULL));
  Base *random;
  std::string colors[7] = {RED, GREEN, YELLOW, BLUE, PURPLE, CYAN, WHITE};

  for (int i = 0; i < 14; i++) {
    std::cout << colors[i % 7];
    std::cout << "------ Test [" << i + 1 << "] ------\n";
    std::cout << "Generating random object";
    tic_tac(80000, 5);
    random = generate();
    std::cout << "Identifying object type by pointer";
    tic_tac(80000, 5);
    identify(random);
    std::cout << "Identifying object type by reference";
    tic_tac(80000, 5);
    if (random) {
      identify(*random);
      delete random;
    } else {
      std::cout << "Class type: NULL" << std::endl;
    }
    std::cout << std::endl;
  }
  return (0);
}

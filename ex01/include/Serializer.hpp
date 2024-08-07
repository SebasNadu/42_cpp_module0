/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:06:45 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/08/07 18:27:58 by johnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once

#include <string>
#include <stdint.h>

typedef struct Data {
  std::string name;
  size_t age;
  Data *next;
} Data;

class Serializer {
public:
  static uintptr_t serialize(Data *ptr);
  static Data *deserialize(uintptr_t raw);

private:
  Serializer();
  Serializer(Serializer const &other);
  Serializer &operator=(const Serializer &other);
  ~Serializer();
};

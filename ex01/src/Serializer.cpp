/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:27:48 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/03 12:37:53 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

Serializer::Serializer() {}
Serializer::Serializer(Serializer const &other) { *this = other; }
Serializer &Serializer::operator=(const Serializer &other) {
  (void)other;
  return *this;
}

uintptr_t Serializer::serialize(Data *ptr) {
  return (reinterpret_cast<uintptr_t>(ptr));
}

Data *Serializer::deserialize(uintptr_t raw) {
  return (reinterpret_cast<Data *>(raw));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:16:07 by hurabe            #+#    #+#             */
/*   Updated: 2025/04/11 17:01:18 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// counter
//int g_counterVct = 0;
//int g_counterDeq = 0;

PmergeMe::PmergeMe() : _vct(), _deq() {}

PmergeMe::PmergeMe(int argc, char **argv) : _vct(), _deq() {
	validate(argc, argv);
}

PmergeMe::PmergeMe(const PmergeMe &src) : _vct(src._vct), _deq(src._deq) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &src) {
	if (&src != this) {
		_vct = src._vct;
		_deq = src._deq;
	}
	return (*this);
}

PmergeMe::~PmergeMe() {}


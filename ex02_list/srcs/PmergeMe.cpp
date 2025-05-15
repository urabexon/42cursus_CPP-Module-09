/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urabex <urabex@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:16:07 by hurabe            #+#    #+#             */
/*   Updated: 2025/05/15 19:54:12 by urabex           ###   ########.fr       */
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

void PmergeMe::validate(int ac, char **av) {
	int num;
	t_pairVct tmp;

	// intに変換できて、正の整数（0含まない）か確認
	for (int i = 1; i < ac; i++)
	{
		std::istringstream iss(av[i]);

		iss >> num;
		if (iss.fail() || !iss.eof() || num < 1)
			throw ("Invalid element");

		tmp.num = num;
		_before.push_back(tmp);
	}
}

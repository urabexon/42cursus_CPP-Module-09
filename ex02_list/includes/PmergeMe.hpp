/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:15:40 by hurabe            #+#    #+#             */
/*   Updated: 2025/04/11 16:48:13 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <deque>

typedef struct s_pairVct {
	int	num;
	std::vector<s_pairVct> pair;
}	t_pairVct;

typedef struct s_pairDeq {
	int	num;
	std::deque<s_pairDeq> pair;
}	t_pairDeq;

class PmergeMe {
	private:
		PmergeMe();
		

	public:
		PmergeMe(int argc, char **argv);
		PmergeMe(const PmergeMe &src);
		PmergeMe &operator=(const PmergeMe &src);
		~PmergeMe();
		void		excutePmergeMe(int argc, char **argv);
		static bool compVctElements(const t_pairVct &first, const t_pairVct &second);
		static bool compDeqElements(const t_pairDeq &first, const t_pairDeq &second);
};

#endif

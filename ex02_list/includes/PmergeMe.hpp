/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:15:40 by hurabe            #+#    #+#             */
/*   Updated: 2025/04/11 16:57:08 by hurabe           ###   ########.fr       */
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
		
		std::vector<t_pairVct> _before;
		std::vector<t_pairVct> _vct;
		std::deque<t_pairDeq> _deq;

		// vector
		std::vector<t_pairVct> mergeInsertSortVct(std::vector<t_pairVct> &vct);
		std::vector<int> getIndexVct(int size);
		std::vector<int> getJacobStahlNumVct(int size);
		void	validate(int argc, char **argv);
		void	initVct(int argc, char **argv);
		void	createPairs(std::vector<t_pairVct> &pairs, std::vector<t_pairVct> vct);
		void	createInsertElements(std::vector<t_pairVct> &insertElements, std::vector<t_pairVct> &mainChain, t_pairVct &lastOne);
		void	insertBasedOnJacobsthal(const std::vector<t_pairVct> &jsElements, std::vector<t_pairVct> &mainChain);
		void	binarySearchInsert(std::vector<t_pairVct> &mainChain, t_pairVct &insertElement, int large);
		void	insertFirstElement(std::vector<t_pairVct> &mainChain);

		// deque
		std::deque<t_pairDeq> mergeInsertSortDeq(std::deque<t_pairDeq> &deq);
		std::deque<int> getIndexDeq(int size);
		std::deque<int> getJacobStahlNumDeq(int size);
		void	initDeq(int argc, char **argv);
		void	createPairs(std::deque<t_pairDeq> &pairs, std::deque<t_pairDeq> deq);
		void	createInsertElements(std::deque<t_pairDeq> &insertElements, std::deque<t_pairDeq> &mainChain, t_pairDeq &lastOne);
		void	insertBasedOnJacobsthal(const std::deque<t_pairDeq> &jsElements, std::deque<t_pairDeq> &mainChain);
		void	binarySearchInsert(std::deque<t_pairDeq> &mainChain, t_pairDeq &insertElement, int large);
		void	insertFirstElement(std::deque<t_pairDeq> &mainChain);

		// utils
		void	printContainer(const std::string &title, const std::vector<t_pairVct> &container);
		void	printTime(int size, const std::string &container, std::clock_t sortTime, int count);

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

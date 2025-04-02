/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urabex <urabex@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:49:48 by hurabe            #+#    #+#             */
/*   Updated: 2025/04/02 16:31:54 by urabex           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <deque>
#include <ctime>
#include <cstdlib>
#include <climits>

class PmergeMe {
  private:
    PmergeMe();
    PmergeMe(const PmergeMe &src);
    PmergeMe &operator=(const PmergeMe &src);

    std::vector<int> _vector;
	  std::vector<int> _jacob;

    std::deque<int> _deque;
    std::deque<int> _jacob_deq;

    bool is_ok_arg(std::string str);
    int jacobsthal(int n);

    void setContainers_vec(char **argv);
    void setContainers_deq(char **argv);
    void setJacob();
    void setJacob_deq();
    void set_mainchain_pend(std::vector<int>& vec, std::vector<int>& mainchain, std::vector<int>& pend);
    void set_mainchain_pen_deq(std::deque<int>& vec, std::deque<int>& mainchain, std::deque<int>& pend);

    void rearrange_vec(std::vector<int>& vec, std::vector<int>& indexes);
    void rearrange_deq(std::deque<int>& vec, std::deque<int>& indexes);

  public:
    PmergeMe(char **argv);
    ~PmergeMe();

    void display_vec(std::string str);
    void display_deq(std::string str);

    void sort_vec();
    void sort_deq();

    void merge_insertion_sort(std::vector<int>& vec, std::vector<int>& indexes);
    void merge_insertion_sort_deq(std::deque<int>& vec, std::deque<int>& indexes);
    void binaryInsert(std::vector<int>& mainchain, std::vector<int>& pend, std::vector<int>& i_main, std::vector<int>& i_pend);
    void binaryInsert_deq(std::deque<int>& mainchain, std::deque<int>& pend, std::deque<int>& i_main, std::deque<int>& i_pend);
};

#endif

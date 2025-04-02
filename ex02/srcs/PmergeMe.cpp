/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urabex <urabex@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:49:52 by hurabe            #+#    #+#             */
/*   Updated: 2025/04/02 16:10:03 by urabex           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// https://docs.google.com/presentation/d/15kKgFEli2fFdC-1qmXzEr7Y1hpJT5ABrb9UymUzdXCs/edit?usp=sharing

#include "PmergeMe.hpp"

void display_vec(std::vector<int> vec);
void display_deque(std::deque<int> deq);

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(char **argv) {
    std::clock_t vec_start = std::clock();
    setContainers_vec(argv);
    setJacob();
    sort_vec();
    std::clock_t vec_end = std::clock();

    std::clock_t deq_start = std::clock();
    setContainers_deq(argv);
    setJacob_deq();
    sort_deq();
    std::clock_t deq_end = std::clock();

    display_vec("vector");
    display_deq("deque ");

    double vec_duration = 1000000.0 * (vec_end - vec_start) / CLOCKS_PER_SEC;
    double deq_duration = 1000000.0 * (deq_end - deq_start) / CLOCKS_PER_SEC;

    std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector : " << vec_duration << " us" << std::endl;
    std::cout << "Time to process a range of " << _vector.size() << " elements with std::deque : " << deq_duration << " us" << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe &src) {
    *this = src;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &src)
{
    if (this != &src) {
        this->_vector = src._vector;
        this->_deque = src._deque;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

bool PmergeMe::is_ok_arg(std::string str) {
    if (str.empty())
        return false;
    
    for (size_t i = 0; i < str.length(); i++) {
        if (!isdigit(str[i]))
            return false;
    }
    
    long num = atol(str.c_str());
    if (num <= 0 || num > INT_MAX)
        return false;
        
    return true;
}

void PmergeMe::setContainers_vec(char **argv) {
    argv++;
    while (*argv) {
        if (!is_ok_arg(*argv)) {
            std::cerr << "Error" << std::endl;
            exit(1);
        }
        _vector.push_back(atoi(*argv));
        argv++;
    }
}

int PmergeMe::jacobsthal(int n) {
	if (n == 0)
		return (0);
	if (n == 1)
		return (1);
	return (jacobsthal(n - 1) + 2 * jacobsthal(n - 2));
}

void PmergeMe::setJacob() {
    int index = 2;
    size_t jcobstalIndex;
    while ((jcobstalIndex = jacobsthal(index)) < _vector.size() - 1) {
        _jacob.push_back(jcobstalIndex);
        index++;
    }
}

void PmergeMe::sort_vec() {
    std::vector<int> vec = _vector;
    std::vector<int> indexes;
    merge_insertion_sort(vec, indexes);
    _vector = vec;
}

void PmergeMe::set_mainchain_pend(std::vector<int>& vec, std::vector<int>& mainchain, std::vector<int>& pend) {
    bool is_odd = vec.size() % 2 != 0;

    for (size_t i = 0; i + 1 < vec.size(); i += 2) {
        mainchain.push_back(vec[i]);
        pend.push_back(vec[i + 1]);
    }

    if (is_odd)
        pend.push_back(vec.back());
}

void PmergeMe::rearrange_vec(std::vector<int>& vec, std::vector<int>& indexes) {
    std::vector<int> tmp = vec;
    for (size_t i = 0; i < indexes.size(); i++)
        vec[i] = tmp[indexes[i]];
}

void PmergeMe::merge_insertion_sort(std::vector<int>& vec, std::vector<int>& indexes) {
    if (vec.size() <= 1)
        return ;

    std::vector<int>::iterator it_vec = vec.begin();
    std::vector<int>::iterator it_indexes = indexes.begin();
    bool indexes_empty = indexes.empty();
    
    for (size_t i = 0; i < vec.size() / 2; i++) {
        if (*it_vec < *(it_vec + 1)) {
            std::iter_swap(it_vec, it_vec + 1);
            if (!indexes_empty)
                std::iter_swap(it_indexes, it_indexes + 1);
        }
        it_vec += 2;
        if (!indexes_empty)
            it_indexes += 2;
    }

    std::vector<int> mainchain, i_main, pend, i_pend, newIndexes;
    set_mainchain_pend(vec, mainchain, pend);
    if (!indexes_empty)
        set_mainchain_pend(indexes, i_main, i_pend);
    for (size_t i = 0; i < mainchain.size(); i++)
        newIndexes.push_back(i);

    merge_insertion_sort(mainchain, newIndexes);
    // std::cout << "indexes: " << std::endl;
    // display_vec(indexes);
    rearrange_vec(pend, newIndexes);
    if (!indexes_empty) {
        rearrange_vec(i_main, newIndexes);
        rearrange_vec(i_pend, newIndexes);
    }
    
    // std::cout << "before: " << std::endl;
    // display_vec(mainchain);
    // display_vec(pend);
    binaryInsert(mainchain, pend, i_main, i_pend);
	// std::cout << "after: " << std::endl;
    // display_vec(mainchain);
    // display_vec(pend);
    // std::cout << std::endl;

    vec = mainchain;
    indexes = i_main;
}

void PmergeMe::binaryInsert(std::vector<int>& mainchain, std::vector<int>& pend, std::vector<int>& i_main, std::vector<int>& i_pend) {
    std::vector<int>::iterator	it;

    for (size_t i = 0; i < _jacob.size(); i++) {
        size_t jacobPrev = (_jacob[i] == 1) ? 0 : _jacob[i - 1];

        for (size_t j = _jacob[i]; j > jacobPrev; j--) {
            if (j > pend.size())
                continue ;
            if (j == 1)
                it = mainchain.begin();
            else
                it = std::lower_bound(mainchain.begin(), mainchain.end(), pend[j - 1]);
            if (!i_main.empty())
                i_main.insert(i_main.begin() + std::distance(mainchain.begin(), it), i_pend[j - 1]);
            mainchain.insert(it, pend[j - 1]);
        }
    }
}

void PmergeMe::display_vec(std::string str) {
    std::cout << str << ": ";
    for (size_t i = 0; i < _vector.size(); i++)
        std::cout << _vector[i] << " ";
    std::cout << std::endl;
}

void PmergeMe::display_deq(std::string str) {
    std::cout << str << ": ";
    for (size_t i = 0; i < _deque.size(); i++)
        std::cout << _deque[i] << " ";
    std::cout << std::endl;
}

void PmergeMe::setContainers_deq(char **argv) {
    argv++;
    while (*argv) {
        if (!is_ok_arg(*argv)) {
            std::cerr << "Error" << std::endl;
            exit(1);
        }
        _deque.push_back(atoi(*argv));
        argv++;
    }
}

void PmergeMe::setJacob_deq() {
    int index = 2;
    size_t jcobstalIndex;

    while ((jcobstalIndex = jacobsthal(index)) < _deque.size() - 1) {
        _jacob_deq.push_back(jcobstalIndex);
        index++;
    }
}

void PmergeMe::sort_deq() {
    std::deque<int> deq = _deque;
    std::deque<int> indexes;
    merge_insertion_sort_deq(deq, indexes);
    _deque = deq;
}

void PmergeMe::set_mainchain_pen_deq(std::deque<int>& deq, std::deque<int>& mainchain, std::deque<int>& pend) {
    bool is_odd = deq.size() % 2 != 0;

    for (size_t i = 0; i + 1 < deq.size(); i += 2) {
        mainchain.push_back(deq[i]);
        pend.push_back(deq[i + 1]);
    }

    if (is_odd)
        pend.push_back(deq.back());
}

void PmergeMe::rearrange_deq(std::deque<int>& deq, std::deque<int>& indexes) {
    std::deque<int> tmp = deq;
    for (size_t i = 0; i < indexes.size(); i++)
        deq[i] = tmp[indexes[i]];
}

void PmergeMe::merge_insertion_sort_deq(std::deque<int>& deq, std::deque<int>& indexes) {
    if (deq.size() <= 1)
        return ;

    std::deque<int>::iterator it_deq = deq.begin();
    std::deque<int>::iterator it_indexes = indexes.begin();
    bool indexes_empty = indexes.empty();
    
    for (size_t i = 0; i < deq.size() / 2; i++) {
        if (*it_deq < *(it_deq + 1)) {
            std::iter_swap(it_deq, it_deq + 1);
            if (!indexes_empty)
                std::iter_swap(it_indexes, it_indexes + 1);
        }
        it_deq += 2;
        if (!indexes_empty)
            it_indexes += 2;
    }

    std::deque<int> mainchain, i_main, pend, i_pend, newIndexes;
    set_mainchain_pen_deq(deq, mainchain, pend);
    if (!indexes_empty)
        set_mainchain_pen_deq(indexes, i_main, i_pend);
    for (size_t i = 0; i < mainchain.size(); i++)
        newIndexes.push_back(i);

    merge_insertion_sort_deq(mainchain, newIndexes);
    // std::cout << "indexes: " << std::endl;
    // display_deq(indexes);
    rearrange_deq(pend, newIndexes);
    if (!indexes_empty) {
        rearrange_deq(i_main, newIndexes);
        rearrange_deq(i_pend, newIndexes);
    }
    binaryInsert_deq(mainchain, pend, i_main, i_pend);
    deq = mainchain;
    indexes = i_main;
}

void PmergeMe::binaryInsert_deq(std::deque<int>& mainchain, std::deque<int>& pend, std::deque<int>& i_main, std::deque<int>& i_pend) {
    std::deque<int>::iterator	it;

    for (size_t i = 0; i < _jacob.size(); i++) {
        size_t jacobPrev = (_jacob[i] == 1) ? 0 : _jacob[i - 1];

        for (size_t j = _jacob[i]; j > jacobPrev; j--) {
            if (j > pend.size())
                continue ;
            if (j == 1)
                it = mainchain.begin();
            else
                it = std::lower_bound(mainchain.begin(), mainchain.end(), pend[j - 1]);
            if (!i_main.empty())
                i_main.insert(i_main.begin() + std::distance(mainchain.begin(), it), i_pend[j - 1]);
            mainchain.insert(it, pend[j - 1]);
        }
    }
}

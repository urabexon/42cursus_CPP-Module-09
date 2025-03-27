/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:49:51 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/27 19:54:52 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

bool isAllDigits(std::string str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (!std::isdigit(str.at(i)))
            return false;
    }
    return true;
}

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "Invalid num of args" << std::endl;
		return 1;
	}
	std::string			unsorted = "Before:  ";
	std::vector<pairs>	vec;
	std::deque<pairs>	deq;
	std::vector<int>	ans;


	for (int i = 1; i < argc; i++) {
		if (!isAllDigits(argv[i])) {
			std::cout << "Invalid number" << std::endl;
			return 1;
		}
		int	num = std::atoi(argv[i]);
		pairs pair;
		if (num <= 0) {
			std::cout << "Invalid number" << std::endl;
			return 1;
		}
		unsorted += argv[i];
		unsorted += " ";
		pair.num = num;
		vec.push_back(pair);
		deq.push_back(pair);
		ans.push_back(num);
	}
	//clock()はプログラムスタート時からのクロックチックを取得
	clock_t	start = clock();
	std::vector<pairs> res = vector_sort(vec);
	clock_t	end = clock();
	double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;
	std::sort(ans.begin(), ans.end());
	std::cout << unsorted << std::endl;
	display(res);
	for (std::size_t i = 0; i < res.size(); i++) {
		if (res[i].num != ans[i]) {
			std::cerr << "Vector sort failed" << std::endl;
			return 1;
		}
	}
	std::cout << "Time to process a range of " << vec.size() << " elements with " << "std::vector : " << time << " us" << std::endl;
	start = clock();
	std::deque<pairs> res2 = deque_sort(deq);
	end = clock();
	time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;
	for (std::size_t i = 0; i < res.size(); i++) {
		if (res[i].num != ans[i]) {
			std::cerr << "Deque sort failed" << std::endl;
			return 1;
		}
	}
	std::cout << "Time to process a range of " << vec.size() << " elements with " << "std::deque  : " << time << " us" << std::endl;
	return 0;
}

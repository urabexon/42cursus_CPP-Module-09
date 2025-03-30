/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:49:51 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/30 23:08:05 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// 文字列が0以外の正の整数で構成されているかをチェック
static bool isAllDigits(std::string str) {
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
	/*
	   unsorted:ソート前の数列を格納する文字列
	   vec:std::vectorに格納してソートする対象
	   deq:std::dequeに格納してソートする対象
	   ans:ソート済み結果用
	*/
	std::string			unsorted = "Before:  ";
	std::vector<pairs>	vec;
	std::deque<pairs>	deq;
	std::vector<int>	ans;

	// 全ての引数を確認して数字かどうかをチェックする
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
		// ソート前の数列をunsortedに追加していく
		unsorted += argv[i];
		unsorted += " ";
		// pairに数値を格納してvector, dequeに追加する
		pair.num = num;
		vec.push_back(pair);
		deq.push_back(pair);
		ans.push_back(num);
	}
	/*
	  clock()はプログラムスタート時からのクロックチックを取得する関数
	  ソート前後の時間計測、vector_sortを実行してvecをソートする
	*/
	clock_t	start = clock();
	std::vector<pairs> res = vector_sort(vec);
	clock_t	end = clock();
	// ソートにかかった時間をマイクロ秒単位に変換する
	double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;
	// std::sortでansを正解順にソートしてresと比較する
	std::sort(ans.begin(), ans.end());
	// ソート前の状態を出力して、displayでvectorのソート結果を表示する
	std::cout << unsorted << std::endl;
	display(res);
	// vectorソート結果をansとresの中身が一致するか確認する
	for (std::size_t i = 0; i < res.size(); i++) {
		if (res[i].num != ans[i]) {
			std::cerr << "Vector sort failed" << std::endl;
			return 1;
		}
	}
	// vector のソート時間を表示する
	std::cout << "Time to process a range of " << vec.size() << " elements with " << "std::vector : " << time << " us" << std::endl;
	
	// dequeでのソート処理スタート(vectorと同じようにソート、時間計測する)
	start = clock();
	std::deque<pairs> res2 = deque_sort(deq);
	end = clock();
	time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;
	// dequeソート結果をansとres2の中身が一致するか確認する
	for (std::size_t i = 0; i < res2.size(); i++) {
		if (res2[i].num != ans[i]) {
			std::cerr << "Deque sort failed" << std::endl;
			return 1;
		}
	}
	// deque のソート時間を表示して終了
	std::cout << "Time to process a range of " << vec.size() << " elements with " << "std::deque  : " << time << " us" << std::endl;
	return 0;
}

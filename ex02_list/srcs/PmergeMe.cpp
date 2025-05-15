/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urabex <urabex@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:16:07 by hurabe            #+#    #+#             */
/*   Updated: 2025/05/15 20:25:46 by urabex           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// counter
int g_counterVct = 0;
int g_counterDeq = 0;

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

void PmergeMe::validate(int argc, char **argv) {
	int num;
	t_pairVct tmp;

	// intに変換できて、0を含まない正の整数か確認
	for (int i = 1; i < argc; i++) {
		std::istringstream iss(argv[i]);
		iss >> num;
		if (iss.fail() || !iss.eof() || num < 1)
			throw ("Invalid element");
		tmp.num = num;
		_before.push_back(tmp);
	}
}

void PmergeMe::printContainer(const std::string &title, const std::vector<t_pairVct> &container) {
	std::cout << title;
	for (size_t i = 0; i < container.size(); ++i)
		std::cout << " " << container[i].num;
	std::cout << std::endl;

	// std::cout << title;
	// for (size_t i = 0; i < _deq.size(); ++i)
	// 	std::cout << " " << _deq[i].num;
	// std::cout << std::endl;

}

void PmergeMe::printTime(int size, const std::string &container, std::clock_t sortTime, int count) {
	double time = static_cast<double>(sortTime) * 1000000 / CLOCKS_PER_SEC;

	std::cout << "Time to process a range of " << size << " elements" << " with std::" << container << ": " << time << " µs" << "    Comparison Count:" << count << std::endl;
	// (void)count;
}

void PmergeMe::initVct(int argc, char **argv) {
	int num;
	t_pairVct	tmpVct;

	for (int i = 1; i < argc; i++) {
		std::istringstream iss(argv[i]);
		iss >> num;
		tmpVct.num = num;
		_vct.push_back(tmpVct);
	}

	// printContainer(_vct, "_vct");
}

void PmergeMe::createPairs(std::vector<t_pairVct> &pairs, std::vector<t_pairVct> vct) {
	t_pairVct	tmp;

	// 2つずつ数字を確認してペアにする
	for (size_t i = 0; i < vct.size(); i += 2) {
		// 比較回数を記録,デバッグ用
		// g_counterVct++;
		// std::cout << "[" << g_counterVct << "]  " << vct[i].num << " vs " << vct[i + 1].num << std::endl;

		// 大きい方に小さい方を結びつけてペアにする
		if (vct[i].num > vct[i + 1].num) {
			vct[i].pair.push_back(vct[i + 1]);
			pairs.push_back(vct[i]);
		} else {
			vct[i + 1].pair.push_back(vct[i]);
			pairs.push_back(vct[i + 1]);
		}
	}
}

void PmergeMe::insertFirstElement(std::vector<t_pairVct> &mainChain) {
	// メインチェーンの最初の要素の最後のペアを取り出し、メインチェーンから消す
	t_pairVct	first = mainChain[0].pair.back();
	mainChain[0].pair.pop_back();
	// メインチェーンの先頭に挿入
	mainChain.insert(mainChain.begin(), first);
}

std::vector<int> PmergeMe::getJacobStahlNumVct(int size) {
	std::vector<int> jacobStahl;
	int total = 1;

	if (size > 0)
		jacobStahl.push_back(0);
	if (size >= 1)
		jacobStahl.push_back(1);
	// ヤコブスタール数のトータルの2倍まで取得する
	for (int i = 2; total * 2 < size; ++i) {
		int num = jacobStahl[i - 1] + 2 * jacobStahl[i - 2];
		jacobStahl.push_back(num);
		total += num;
	}
	return (jacobStahl);
}	

std::vector<int> PmergeMe::getIndexVct(int size) {
	std::vector<int> js;
	std::vector<int> js2;
	std::vector<int> idx;

	// ヤコブスタール数取得
	js = getJacobStahlNumVct(size);

	// ヤコブスタール数を2倍にする
	for (size_t i = 0; i < js.size(); ++i)
		js2.push_back(js[i] * 2);

	// 先頭の2つ(0,1)を飛ばすため、インデックスをずらす
	int total = 1;
	for (size_t i = 1; i < js2.size(); ++i) {
		// サイズを超えそうならサイズまでの数にする
		int num = js2[i];
		if (total + num > size + 1)
			num = size + 1 - total;
		// インデックス格納
		for ( ; num > 0; num--)
			idx.push_back(total + num);
		// 作ったインデックスを合計に加算
		total += js2[i];
	}
	return (idx);
}

void PmergeMe::createInsertElements(std::vector<t_pairVct> &insertElements, std::vector<t_pairVct> &mainChain, t_pairVct &lastOne) {
	// ヤコブスタール数列を使って挿入順のindexを作成
	int size = mainChain.size() - 2 + (lastOne.num == -1 ? 0 : 1);
	std::vector<int>	index = getIndexVct(size);
	t_pairVct			tmp;

	// std::cout << "index.size:" << index.size() << std::endl;

	// 挿入順でinsertElementsを作成する　端数はDUMMY(-1)をペア（大）として含める
	for (size_t i = 0; i < index.size(); ++i) {
		if (static_cast<size_t>(index[i]) < mainChain.size()) {
			tmp = mainChain[index[i]];
			mainChain[index[i]].pair.pop_back();
		} else {
			tmp.num = DUMMY;
			tmp.pair.push_back(lastOne);
		}
		insertElements.push_back(tmp);
		tmp.pair.clear();
	}
}

bool PmergeMe::compVctElements(const t_pairVct &first, const t_pairVct &second) {
	// 比較回数を記録,デバッグ
	// g_counterVct++;
	// std::cout << "[" << g_counterVct << "]  " << first.num << " vs " << second.num << std::endl;
	return (first.num < second.num);
}

void PmergeMe::binarySearchInsert(std::vector<t_pairVct> &mainChain, t_pairVct &insertElement, int large) {
	// 探索範囲の終端（挿入する数字のペア（大）の位置）を取得 (※最適化しているので重複している場合に検索範囲が狭くなるので注意)
	std::vector<t_pairVct>::iterator end;
	for (end = mainChain.begin(); end->num != large; ++end) {}

	// 二分探索で挿入位置を特定し、要素を挿入
	mainChain.insert(std::lower_bound(mainChain.begin(), end, insertElement, compVctElements), insertElement);
}

void PmergeMe::insertBasedOnJacobsthal(const std::vector<t_pairVct> &jsElements, std::vector<t_pairVct> &mainChain) {
	t_pairVct	insertElemnt;
	int			large;

	for (size_t i = 0; i < jsElements.size(); ++i) {
		// 挿入する対象と、その対象のペアを取得して二分探索する　端数以外はペア（大）と同じ値の位置までを探索、端数は全範囲で探索
		insertElemnt = jsElements[i].pair.back();
		large = jsElements[i].num;
		if (large != -1)
			binarySearchInsert(mainChain, insertElemnt, large);
		else
			mainChain.insert(std::lower_bound(mainChain.begin(), mainChain.end(), insertElemnt, compVctElements), insertElemnt);
	}
}

std::vector<t_pairVct> PmergeMe::mergeInsertSortVct(std::vector<t_pairVct> &vct) {
	// 大小のペアが1つになるまで再帰を繰り返す
	if (vct.size() < 2)
		return (vct);

	// 奇数なら最後の1つを避けておく
	int oddNumber = vct.size() % 2;
	t_pairVct	lastOne;
	lastOne.num = -1;
	if (oddNumber) {
		lastOne = vct.back();
		vct.pop_back();
	}

	// 大小のペアを作成
	std::vector<t_pairVct> pairs;
	createPairs(pairs, vct);

	// 再帰的にメインチェーンを作成
	std::vector<t_pairVct> mainChain = mergeInsertSortVct(pairs);

	// 最初の要素を挿入
	insertFirstElement(mainChain);

	// ヤコブスタール数列に基づいて残りの要素を取得し、この時に端数も含める
	std::vector<t_pairVct> insertElements;
	createInsertElements(insertElements, mainChain, lastOne);

	// 要素があるなら、二分探索を使って挿入する
	if (!insertElements.empty())
		insertBasedOnJacobsthal(insertElements, mainChain);
	return (mainChain);
}

// Private Function (Deque sort)

void PmergeMe::initDeq(int argc, char **argv) {
	int num;
	t_pairDeq	tmpDeq;

	for (int i = 1; i < argc; i++) {
		std::istringstream iss(argv[i]);
		iss >> num;
		tmpDeq.num = num;
		_deq.push_back(tmpDeq);
	}

}

void PmergeMe::createPairs(std::deque<t_pairDeq> &pairs, std::deque<t_pairDeq> deq) {
	t_pairDeq	tmp;

	// 2つずつ数字を確認してペアにする
	for (size_t i = 0; i < deq.size(); i += 2) {
		// 比較回数を記録,デバッグ
		// g_counterDeq++;
		// std::cout << "[" << g_counterDeq << "]  " << deq[i].num << " vs " << deq[i + 1].num << std::endl;

		// 大きい方に小さい方を結びつけてペアにする
		if (deq[i].num > deq[i + 1].num) {
			deq[i].pair.push_back(deq[i + 1]);
			pairs.push_back(deq[i]);
		} else {
			deq[i + 1].pair.push_back(deq[i]);
			pairs.push_back(deq[i + 1]);
		}
	}
}

void PmergeMe::insertFirstElement(std::deque<t_pairDeq> &mainChain) {
	// メインチェーンの最初の要素の最後のペアを取り出し、メインチェーンから消す
	t_pairDeq	first = mainChain[0].pair.back();
	mainChain[0].pair.pop_back();

	//メインチェーンの先頭に挿入
	mainChain.insert(mainChain.begin(), first);
}

std::deque<int> PmergeMe::getJacobStahlNumDeq(int size) {
	std::deque<int> jacobStahl;
	int total = 1;

	if (size > 0)
		jacobStahl.push_back(0);
	if (size >= 1)
		jacobStahl.push_back(1);
	// ヤコブスタール数のトータルの2倍まで取得する
	for (int i = 2; total * 2 < size; ++i) {
		int num = jacobStahl[i - 1] + 2 * jacobStahl[i - 2];
		jacobStahl.push_back(num);
		total += num;
	}
	return (jacobStahl);
}	

std::deque<int> PmergeMe::getIndexDeq(int size) {
	std::deque<int> js;
	std::deque<int> js2;
	std::deque<int> idx;

	// ヤコブスタール数取得
	js = getJacobStahlNumDeq(size);

	// ヤコブスタール数を2倍にする
	for (size_t i = 0; i < js.size(); ++i)
		js2.push_back(js[i] * 2);
	
	// 先頭の2つ(0,1)を飛ばすため、インデックスをずらす
	int total = 1;
	for (size_t i = 1; i < js2.size(); ++i) {
		// サイズを超えそうならサイズまでの数にする
		int num = js2[i];
		if (total + num > size + 1)
			num = size + 1 - total;
		//インデックスを格納
		for ( ; num > 0; num--)
			idx.push_back(total + num);
		// 作ったインデックスを合計に加算
		total += js2[i];
	}

	return (idx);
}

void PmergeMe::createInsertElements(std::deque<t_pairDeq> &insertElements, std::deque<t_pairDeq> &mainChain, t_pairDeq &lastOne) {
	// ヤコブスタール数列を使って挿入順のindexを作成
	int size = mainChain.size() - 2 + (lastOne.num == -1 ? 0 : 1);
	std::deque<int>	index = getIndexDeq(size);
	t_pairDeq			tmp;

	// std::cout << "index.size:" << index.size() << std::endl;

	// 挿入順でinsertElementsを作成する　端数はDUMMY(-1)をペア（大）として含める
	for (size_t i = 0; i < index.size(); ++i) {
		if (static_cast<size_t>(index[i]) < mainChain.size()) {
			tmp = mainChain[index[i]];
			mainChain[index[i]].pair.pop_back();
		} else {
			tmp.num = DUMMY;
			tmp.pair.push_back(lastOne);
		}
		insertElements.push_back(tmp);
		tmp.pair.clear();
	}
}

bool PmergeMe::compDeqElements(const t_pairDeq &first, const t_pairDeq &second) {
	// 比較回数を記録,デバッグ
	// g_counterDeq++;
	// std::cout << "[" << g_counterDeq << "]  " << first.num << " vs " << second.num << std::endl;
	return (first.num < second.num);
}

void PmergeMe::binarySearchInsert(std::deque<t_pairDeq> &mainChain, t_pairDeq &insertElement, int large) {
	// 探索範囲の終端（挿入する数字のペア（大）の位置）を取得 (※最適化しているので重複している場合に検索範囲が狭くなるので注意)
	std::deque<t_pairDeq>::iterator end;
	for (end = mainChain.begin(); end->num != large; ++end) {}

	// 二分探索で挿入位置を特定し、要素を挿入
	mainChain.insert(std::lower_bound(mainChain.begin(), end, insertElement, compDeqElements), insertElement);
}

void PmergeMe::insertBasedOnJacobsthal(const std::deque<t_pairDeq> &jsElements, std::deque<t_pairDeq> &mainChain) {
	t_pairDeq	insertElemnt;
	int			large;
	
	for (size_t i = 0; i < jsElements.size(); ++i) {
		// 挿入する対象と、その対象のペアを取得して二分探索する　端数以外はペア（大）と同じ値の位置までを探索、端数は全範囲で探索
		insertElemnt = jsElements[i].pair.back();
		large = jsElements[i].num;
		if (large != -1)
			binarySearchInsert(mainChain, insertElemnt, large);
		else
			mainChain.insert(std::lower_bound(mainChain.begin(), mainChain.end(), insertElemnt, compDeqElements), insertElemnt);
	}
}


std::deque<t_pairDeq> PmergeMe::mergeInsertSortDeq(std::deque<t_pairDeq> &deq) {
	// 大小のペアが１つになるまで再帰を繰り返す
	if (deq.size() < 2)
		return (deq);

	// 奇数なら最後の１つを避けておく
	int oddNumber = deq.size() % 2;
	t_pairDeq	lastOne;
	lastOne.num = -1;
	if (oddNumber) {
		lastOne = deq.back();
		deq.pop_back();
	}

	// 大小のペアを作成
	std::deque<t_pairDeq> pairs;
	createPairs(pairs, deq);

	// 再帰的にメインチェーンを作成
	std::deque<t_pairDeq> mainChain = mergeInsertSortDeq(pairs);

	// 最初の要素を挿入
	insertFirstElement(mainChain);

	// ヤコブスタール数列に基づいて残りの要素を取得　この時、端数も含める
	std::deque<t_pairDeq> insertElements;
	createInsertElements(insertElements, mainChain, lastOne);

	// 要素があるなら、二分探索を使って挿入する
	if (!insertElements.empty())
		insertBasedOnJacobsthal(insertElements, mainChain);

	return (mainChain);
}

void PmergeMe::excutePmergeMe(int argc, char **argv) {
	// vectorソート
	std::clock_t startVct = std::clock();
	initVct(argc, argv);
	_vct = mergeInsertSortVct(_vct);
	std::clock_t timeVct = std::clock() - startVct;

	// dequeソート
	std::clock_t startDeq = std::clock();
	initDeq(argc, argv);
	_deq = mergeInsertSortDeq(_deq);
	std::clock_t timeDeq = std::clock() - startDeq;

	// before・after出力
	printContainer("Before: ", _before);
	printContainer("After:  ", _vct);

	// 時間出力 × ２
	printTime(_vct.size(), "vector", timeVct, g_counterVct);
	printTime(_deq.size(), "deque", timeDeq, g_counterDeq);
}
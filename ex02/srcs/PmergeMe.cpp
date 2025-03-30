/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:49:52 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/30 23:08:44 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// 比較用のカウンタ
//int g_counterVct = 0;
//int g_counterDeq = 0;

// ソートされたペアの数列を出力する関数(ソート済みのペア数列を受け取る)
void	display(std::vector<pairs> out) {
	std::cout << "After:  ";
	for (std::vector<pairs>::iterator it = out.begin(); it != out.end(); it++)
		std::cout << (*it).num << " ";
	std::cout << std::endl;
}

// FJAで各挿入段階のグループサイズを返す関数(nはグループ数)
size_t	group_size(size_t n) {
	if (n == 0)
		return 0;
	else if (n == 1)
		return 2;
	size_t prev = 0, curr = 1, next;
	for (size_t i = 2; i < n; i++) {
		next = curr + 2 * prev;
		prev = curr;
		curr = next;
	}
	return curr * 2;
}

/*
  vectorに対する二分探索をする関数
  - resが現在のvector
  - rightが探索する右端の位置
  - valueが挿入対象の値
  - 挿入位置のインデックスを返す
*/
size_t	BS_vec(std::vector<pairs> res, size_t right, int value) {
	size_t left = 0, mid;

	while (left <= right) {
		//g_counterVct++;
		mid = left + (right - left) / 2;
		if (res[mid].num == value) {
			return mid;
		} else if (res[mid].num < value) {
			if (mid == right)
				return mid + 1;
			left = mid + 1;
		} else {
			if (mid == 0)
				return 0;
			right = mid - 1;
		}
	}
	return left;
}

// vector用のMISをする関数
std::vector<pairs>	vector_sort(std::vector<pairs> arr) {
	std::vector<pairs> res, big, small;

	// 配列サイズが1または2の場合、直接処理する
	if (arr.size() == 1) {
		return arr;
	} else if (arr.size() == 2) {
		if (arr[0].num > arr[1].num) {
			std::swap(arr[0], arr[1]);
			return arr;
		}
		return arr;
	}

	// 2つずつペアを比較して大きい方をbig, 小さい方をsmallへ入れる
	for (size_t i = 0; i < arr.size() - 1; i += 2) {
		if (arr[i].num > arr[i + 1].num) {
			arr[i].p.push_back(arr[i + 1]);
			big.push_back(arr[i]);
		} else {
			arr[i + 1].p.push_back(arr[i]);
			big.push_back(arr[i + 1]);
		}
	}

	// bigを再帰的にソートする
	res = vector_sort(big);

	// smallを取り出して挿入する
	if (res[0].p.size() == 0)
		return res;
	for (std::size_t i = 0; i < res.size(); i++) {
		small.push_back(res[i].p[res[i].p.size() - 1]);
		res[i].p.pop_back();
		// smallには、bigがソートされた順番と同じ順番でbigのpairが入る
	}
	// 奇数個の場合、余った要素をsmallに入れる
	if (arr.size() % 2 != 0)
		small.push_back(arr[arr.size() - 1]);
	

	// smallをグループ単位でbinary searchで挿入していく
	size_t	count = 1, group_passed = 0, groupsize;
	if (small.size() > 0) {
		res.insert(res.begin(), small[0]);
		small.erase(small.begin());
	}
	while (small.size() > 0) {
		groupsize = group_size(count);
		if (groupsize > small.size())
			groupsize = small.size();
		for (size_t i = 0; i < groupsize; i++) {
			// insertするsmallのindex
			size_t	BS_point = groupsize - i - 1;
			// resにsmallをbinary searchする際のres右端のindex
			size_t	right_side = 1 + group_passed * 2 + BS_point + i;
			size_t	insert_point = BS_vec(res, right_side, small[BS_point].num);
			res.insert(res.begin() + insert_point, small[BS_point]);
			small.erase(small.begin() + BS_point);
		}
		group_passed += groupsize;
	}
	return res;
}

// dequeに対する二分探索をする関数(動作はvectorのものと同じ)
size_t	BS_deq(std::deque<pairs> res, size_t right, int value) {
	size_t left = 0, mid;

	while (left <= right) {
		//g_counterDeq++;
		mid = left + (right - left) / 2;
		if (res[mid].num == value) {
			return mid;
		} else if (res[mid].num < value) {
			if (mid == right)
				return mid + 1;
			left = mid + 1;
		} else {
			if (mid == 0)
				return 0;
			right = mid - 1;
		}
	}
	return left;
}

// deque用のMISをする関数(動作はvectorのものと同じ)
std::deque<pairs>	deque_sort(std::deque<pairs> arr) {
	std::deque<pairs> res, big, small;

	if (arr.size() == 1) {
		return arr;	
	} else if (arr.size() == 2) {
		if (arr[0].num > arr[1].num) {
			std::swap(arr[0], arr[1]);
			return arr;
		}
		return arr;
	}
	for (size_t i = 0; i < arr.size() - 1; i += 2) {
		if (arr[i].num > arr[i + 1].num) {
			arr[i].p.push_back(arr[i + 1]);
			big.push_back(arr[i]);
		} else {
			arr[i + 1].p.push_back(arr[i]);
			big.push_back(arr[i + 1]);
		}
	}

	res = deque_sort(big);

	if (res[0].p.size() == 0)
		return res;
	for (std::size_t i = 0; i < res.size(); i++) {
		// smallに一つ入れる
		small.push_back(res[i].p[res[i].p.size() - 1]);
		res[i].p.pop_back();
		// smallには、bigがソートされた順番と同じ順番でbigのpairが入る
	}
	if (arr.size() % 2 != 0)
		// 余った要素を入れる
		small.push_back(arr[arr.size() - 1]);
	size_t	count = 1, group_passed = 0, groupsize;
	if (small.size() > 0) {
		res.insert(res.begin(), small[0]);
		small.erase(small.begin());
	}
	while (small.size() > 0) {
		groupsize = group_size(count);
		if (groupsize > small.size())
			groupsize = small.size();
		for (size_t i = 0; i < groupsize; i++) {
			// insertするsmallのindex
			size_t	BS_point = groupsize - i - 1;
			// resにsmallをbinary searchする際のres右端のindex
			size_t	right_side = 1 + group_passed * 2 + BS_point + i;
			size_t	insert_point = BS_deq(res, right_side, small[BS_point].num);
			res.insert(res.begin() + insert_point, small[BS_point]);
			small.erase(small.begin() + BS_point);
		}
		group_passed += groupsize;
	}
	return res;
}

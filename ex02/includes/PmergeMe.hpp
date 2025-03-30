/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:49:48 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/30 22:50:46 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// vector → 処理が高速のため
// deque → ペアでの処理がやりやすくなるため

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

// include
#include <iostream>
#include <vector>    // vectorコンテナ
#include <algorithm> // sortなどのアルゴリズム用
#include <cassert>   // デバッグなどのassert用
#include <deque>     // dequeコンテナ

// 比較関数カウント用
//extern int g_counterVct;
//extern int g_counterDeq;

/*
  ペアの情報を保持する構造体
  フォード・ジョンソンアルゴリズムでは、要素をペアとしてグループ化してソートするため
*/
struct pairs {
	// ペアの数値(ペアの代表値として使用)
	double num;
	// 再帰的なペアのグループ化に使用する
	std::vector<pairs> p;
};

// ソートされたペアの数列を出力する関数
void	display(std::vector<pairs> vec);
// FJAで各挿入段階のグループサイズを返す関数(nはグループ数)
size_t	group_size(size_t n);
// vectorに対する二分探索をする関数
size_t	BS_vec(std::vector<pairs> res, size_t right, int value);
// dequeに対する二分探索をする関数
size_t	BS_deq(std::deque<pairs> res, size_t right, int value);

/*
  vector用のペアソート関数
  vectorに格納されたペアをMerge-InsertionSortでソートする(MISと略す)
*/
std::vector<pairs> 	vector_sort(std::vector<pairs> vec);
/*
  deque用のペアソート関数
  dequeに格納されたペアをMerge-Insertion Sortでソートする
*/
std::deque<pairs>	deque_sort(std::deque<pairs> deq);

#endif

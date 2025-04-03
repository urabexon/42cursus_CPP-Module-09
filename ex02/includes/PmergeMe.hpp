/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urabex <urabex@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:49:48 by hurabe            #+#    #+#             */
/*   Updated: 2025/04/03 16:19:56 by urabex           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
  vectorは処理時間が高速のため使用(連続したメモリ上に確保されているためキャッシュ効率が高い)
  dequeは両端キュー、つまり前後両方からの挿入に強くペアでの操作が用意の為選択
*/

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

    // 入力引数として与えられた整数値を格納するvector
    std::vector<int> _vector;
    // vector用のJacobsthal数列
	  std::vector<int> _jacob;

    // 入力引数として与えられた整数値を格納するdeque
    std::deque<int> _deque;
    // deque用のJacobsthal数列
    std::deque<int> _jacob_deq;

    // 文字列が正しい整数であるかどうかを判定する関数
    bool is_ok_arg(std::string str);
    // Jacobsthal数列のn番目の値を再帰的に取得する関数
    int jacobsthal(int n);

    // argvからvector,dequeに値を格納する関数
    void setContainers_vec(char **argv);
    void setContainers_deq(char **argv);

    // Jacobsthal数列をvector,dequeとしてそれぞれ生成する関数
    void setJacob();
    void setJacob_deq();

     // vector, dequeをそれぞれmainchainとpendingに分割する関数
    void set_mainchain_pend(std::vector<int>& vec, std::vector<int>& mainchain, std::vector<int>& pend);
    void set_mainchain_pen_deq(std::deque<int>& vec, std::deque<int>& mainchain, std::deque<int>& pend);

    // 指定された順序(indexes)に従ってvector, dequeの要素を再配置する関数
    void rearrange_vec(std::vector<int>& vec, std::vector<int>& indexes);
    void rearrange_deq(std::deque<int>& vec, std::deque<int>& indexes);

  public:
    // コンストラクタでコマンドライン引数を受け取れるようにする
    PmergeMe(char **argv);
    ~PmergeMe();

    // vector,dequeに格納された要素をそれぞれ表示する関数
    void display_vec(std::string str);
    void display_deq(std::string str);

    // vector,dequeそれぞれに対してソートを実行する関数
    void sort_vec();
    void sort_deq();

    // vector,dequeそれぞれを用いたマージ挿入ソートのメインロジック関数
    void merge_insertion_sort(std::vector<int>& vec, std::vector<int>& indexes);
    void merge_insertion_sort_deq(std::deque<int>& vec, std::deque<int>& indexes);
    
    // vector,dequeそれぞれのJacobsthal数列の順に従ってpendingの要素をmainchainへ二分探索で挿入していく関数
    void binaryInsert(std::vector<int>& mainchain, std::vector<int>& pend, std::vector<int>& i_main, std::vector<int>& i_pend);
    void binaryInsert_deq(std::deque<int>& mainchain, std::deque<int>& pend, std::deque<int>& i_main, std::deque<int>& i_pend);
};

#endif

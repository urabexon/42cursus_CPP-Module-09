/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urabex <urabex@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:49:51 by hurabe            #+#    #+#             */
/*   Updated: 2025/04/03 16:26:31 by urabex           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
  1. 入力チェック
  2. PmergeMeクラスのインスタンスを生成
  3. 引数をvector, dequeに格納する
  4. FJAでvectorとdequeをそれぞれソート
  5. ソート済みデータを出力し、それぞれの処理時間を表示
  6. プログラムを正常終了
*/

#include "PmergeMe.hpp"

int main(int argc, char **argv) {
    if (argc == 1) {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    PmergeMe pmm(argv);
    
    return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urabex <urabex@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:33:07 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/30 13:49:53 by urabex           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
  1. 入力チェック
  2. RPNクラスのインスタンス作る
  3. 逆ポーランド記法の数式を解析して計算する
  4. 結果の出力、エラー時は例外メッセージを表示する
  5. プログラムの正常終了かエラーを返す
*/

#include "RPN.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Error: Invalid num of Args" << std::endl;
		return 1;
	}
	RPN rpn;
	try {
		rpn.calc(argv[1]);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return (1);
	}

	return (EXIT_SUCCESS);
}

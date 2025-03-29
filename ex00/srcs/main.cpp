/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urabex <urabex@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:36:56 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/29 16:26:46 by urabex           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
  1.data.csvからビットコイン価格の履歴を読み込む
  2.input.txtから指定された日付と価格のペアを読み込む
  3.日付と価格のバリデーションを行う
  4.最も近い過去の日付のレートでビットコインの価値を計算する
  5.エラーハンドリングを行い、例外時にはエラーメッセージを表示する
*/

#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << ERROR_OPEN_FILE << std::endl;
		return (EXIT_FAILURE);
	}
	
	BitcoinExchange btc;

	try {
		// data.csvの処理
		btc.getDataBase();
		// input.txtの処理
		btc.outputBitcoinExchange(argv[1]);
	} catch(char const *mes) {
		std::cout << mes << std::endl;
		return (EXIT_FAILURE);
	}
	
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urabex <urabex@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:37:01 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/29 16:10:45 by urabex           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

// include
#include <iostream>
#include <fstream> // ファイル入出力用
#include <sstream> // 文字列ストリーム
#include <string> 
#include <map>     // マップ（連想配列用）
#include <ctime>   // 日付・時刻処理用
#include <cstdlib> // 例外処理系

// エラーメッセージをまとめた
#define ERROR_OPEN_FILE "Error: could not open file."      // ファイルが開けない場合
#define ERROR_FILE_EMPTY "Error: file is empty."           // ファイルが空の場合
#define ERROR_NEGATIVE_NUM "Error: not a positive number." // 負の値の場合
#define ERROR_LARGE_NUM "Error: too large a number."       // 1000を超える値の場合
#define ERROR_INVALID_VAL "Error: invalid value."          // 無効な値のフォーマット
#define ERROR_INPUT_LINE "Error: bad input => "            // 入力行のフォーマットが不正の場合

#define DATABASE "data.csv"

class BitcoinExchange {
	private:
		// 日付とレートのデータベース(date -> rate)
		std::map<std::string, float>	_dataBase;

		/*
		  日付文字列を解析して std::tm構造体に変換する
		  - date: YYYY-MM-DD形式の文字列
		  - time: 解析後のstd::tm構造体
		*/
		bool parseDateTime(const std::string &date, std::tm &time) const;
		/*
		  日付バリデーション
		  - date: 日付文字列
		*/
		bool isValidDate(const std::string &date) const;
		/*
		  入力行のフォーマットを検証
		  - line: 入力ファイルの1行
		  - date: 日付を格納する変数
		  - val: 価格を格納する変数
		*/
		bool isValidInputLine(const std::string &line, std::string &date, float &val) const;
		/*
		  入力行のフォーマットを検証する
		  - val: チェックする価格
		*/
		bool isValidValue(const float val) const;
		/*
		  指定された日付のレートを取得
		  - date: 参照する日付
		  - レート, 一致する日付がない場合は最も近い過去の日付のレートを返す
		*/
		float getExchangeRate(const std::string &date) const;

	public:
		// 正統派正規クラス形式
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &src);
		BitcoinExchange &operator=(const BitcoinExchange &src);
		~BitcoinExchange();

		// data.csvからデータベースを読み込むメソッド
		void getDataBase();
		// input.txtからデータを読み取り、変換結果を出力する
		void outputBitcoinExchange(const char *inputFile);
};

#endif

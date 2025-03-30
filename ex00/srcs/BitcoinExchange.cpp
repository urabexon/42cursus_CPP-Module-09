/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:36:59 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/30 22:33:21 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// コンストラクタ
BitcoinExchange::BitcoinExchange() : _dataBase() {}

// コピーコンストラクタ
BitcoinExchange::BitcoinExchange(const BitcoinExchange &src) : _dataBase(src._dataBase) {}

// 代入演算子オーバーロード
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src) {
	if (&src != this)
		_dataBase = src._dataBase;
	return (*this);
}

// デストラクタ
BitcoinExchange::~BitcoinExchange() {}

// 日付文字列を解析して std::tm構造体に変換する関数
bool BitcoinExchange::parseDateTime(const std::string &date, std::tm &time) const {
	std::istringstream ss(date);
	// 日付表示の取り扱いを一貫したものにするため、標準のロケールを設定
	ss.imbue(std::locale::classic());

	// 最初に見つかった数字をtm_yearに、次に見つかった文字をdelimに、次の数字をtm_monに・・・と格納していく
	char delim;
	ss >> time.tm_year >> delim >> time.tm_mon >> delim >> time.tm_mday;
	if (ss.fail() || delim != '-')
		return (false);
	
	// 構造体の年は1900年からの差分、月は0-11で格納されるため、西暦・1-12表記に直す
	time.tm_year -= 1900;
	time.tm_mon -= 1;
	
	return (true);
}

// 日付バリデーション用の関数
bool BitcoinExchange::isValidDate(const std::string &date) const {
	// 日付形式が不正な場合はfalse
	if (date.length() != 10 || date.at(4) != '-' || date.at(7) != '-')
		return (false);

	// 時間用の構造体を初期化し、日付を取得する
	std::tm	time = {};
	if (!parseDateTime(date, time))
		return (false);

	// time_t型に変換できるかどうかで日付が正しいかチェックする
	std::time_t t = std::mktime(&time);
	if (t == -1)
		return (false);

	// 一応日付文字列と変換後の日付が同じであることを確認
	char buf[11];
	std::strftime(buf, sizeof(buf), "%Y-%m-%d", &time);

	return (date == buf);
}

// 入力行のフォーマットを検証する関数
bool BitcoinExchange::isValidInputLine (const std::string &line, std::string &date, float &val) const {
	std::istringstream ssl(line);
	std::string value;

	// '|'の前後を文字列として取得する
	if (!std::getline(ssl, date, '|') || date.empty() || !std::getline(ssl, value) || value.empty()) {
		std::cout << ERROR_INPUT_LINE << line << std::endl;
		return (false);
	}

	// 文字列を整える
	date.erase(date.size() - 1); // 末尾の空白を削除
	value.erase(value.begin());  // 先頭の空白を削除

	// 桁数が大きすぎる場合はエラー
	if (value.length() > 10) {
		std::cout << "Error: value is too large to process." << std::endl;
		return (false);
	}

	// float型に変換できるか確認
	std::istringstream ss(value);
	ss >> val;
	if (ss.fail() || !ss.eof()) {
		std::cout << ERROR_INVALID_VAL << std::endl;
		return (false);
	}

	return (true);
}

// 入力行のフォーマットを検証する関数
bool BitcoinExchange::isValidValue(const float val) const {
	if (val < 0) {
		std::cout << ERROR_NEGATIVE_NUM << std::endl;
		return (false);
	}
	if (val > 1000) {
		std::cout << ERROR_LARGE_NUM << std::endl;
		return (false);
	}
	return (true);
}

// 指定された日付のレートを取得する関数
float BitcoinExchange::getExchangeRate(const std::string &date) const {
	// 完全一致する日付があればレートを返す
	std::map<std::string, float>::const_iterator it = _dataBase.find(date);
	if (it != _dataBase.end())
		return (it->second);

	// 一致する日付がなければ最も近い過去の日付を検索し、先頭なら0を返す
	std::map<std::string, float>::const_iterator near = _dataBase.lower_bound(date);
	if (near == _dataBase.begin())
		return (0.0f);
	--near;
	return (near->second);
}

// input.txtからデータを読み取り、変換結果を出力する関数
void BitcoinExchange::outputBitcoinExchange(const char *inputFile) {
	// ファイルが開けられるか
	std::ifstream file(inputFile);
	if (!file.is_open())
		throw (ERROR_OPEN_FILE);

	std::string line;

	// １行目はヘッダーなのでスキップ
	std::getline(file, line);

	// ２行目以降をmapに格納する
	while (std::getline(file, line)) {
		std::string date;
		float	val;
		float	rate;

		// inputの記述形式に問題なければ日付を取得
		if (!isValidInputLine(line, date, val))
			continue;
		// 日付の整合性チェック
		if (!isValidDate(date)) {
			std::cout << ERROR_INPUT_LINE << line << std::endl;
			continue;
		}
		// 値の整合性チェック
		if (!isValidValue(val))
			continue;
		// 問題なければレートを確認して出力（一致する日付がなければ近い日付を参照する）
		rate = getExchangeRate(date);
		std::cout << date << " => " << val << " = " << val * rate << std::endl;
	}

	file.close();
}

// data.csvからデータベースを読み込む関数
void BitcoinExchange::getDataBase() {
	size_t	delim;
	float	rate;

	// ファイルが開けられるか
	std::ifstream file(DATABASE);
	if (!file.is_open())
		throw (ERROR_OPEN_FILE);

	std::string line;

	// １行目はヘッダーなのでスキップ
	std::getline(file, line);

	// ２行目以降をmapに格納する
	while (std::getline(file, line)) {
		// 区切り文字の位置を取得する、区切り文字がなければ次の行へ
		delim = line.find(',');
		if (delim == std::string::npos)
			continue;

		// 日付とレートを取得し、日付に問題がなければmapに格納
		std::string	date = line.substr(0, delim);
		std::istringstream(line.substr(delim + 1)) >> rate;
		if (isValidDate(date))
			_dataBase[date] = rate;
	}

	// もしファイルが空ならエラー
	if (_dataBase.empty())
		throw (ERROR_FILE_EMPTY);

	file.close();
}

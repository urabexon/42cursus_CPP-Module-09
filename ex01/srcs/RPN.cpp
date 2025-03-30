/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:33:04 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/30 22:41:23 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

// コンストラクタ(スタック初期化)
RPN::RPN() {}

// コピーコンストラクタ
RPN::RPN(RPN &src) {
	*this = src;
}

// 代入演算子オーバーロード
RPN &RPN::operator=(RPN &src) {
	if (this != &src)
		*this = src;
	return *this;
}

// デストラクタ
RPN::~RPN() {}

/*
  計算処理用の関数(a,bがオペランド, signが演算子)
  INT_MAXを超えた時に対応できるようにlongにしておく
  - ./RPN "1 1 /" 
*/
long	RPN::calculate(long a, long b, char sign) {
	if (sign == '+')
		return a + b;
	else if (sign == '-')
		return a - b;
	else if (sign == '*')
		return a * b;
	else
	{
		if (b == 0)
			throw SyntaxErrorException();
		return a / b;
	}
}

/*
  逆ポーランド記法の数式を計算する関数(引数は逆ポーランド記法の文字列) 
  - ./RPN "0 2 - 8 8 8 8 8 8 8 8 8 8 * * * * * * * * * * 0 1 - /"(INT_MAXを超えたとき)
  - ./RPN "0 2 - 4 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 * * * * * * * * * * * * * * * * * * * * * 0 1 - /"(LONGケース)
*/
void	RPN::calc(std::string str) {
	// 空文字列は例外処理
	if (str.empty())
		throw SyntaxErrorException();

	// 数式解析スタート
	for (std::string::iterator it = str.begin(); it != str.end(); it++) {
		// 空白飛ばす
		if (std::isspace(*it))
			continue ;
		// 数値の場合はstackにpushする, 演算子の場合はstackの2つの要素で計算する
		if (std::isdigit(*it)) {
			_strage.push((*it) - '0');
		} else {
			// スタックの要素数が2未満の場合は例外
			if (_strage.size() < 2)
				throw SyntaxErrorException();
			// スタックの上2つの要素をpopする
			int	num1 = _strage.top();
			_strage.pop();
			int	num2 = _strage.top();
			_strage.pop();
			// 計算結果をstackにpushする
			long res = calculate(num2, num1, (*it));
			if (res > INT_MAX || res < INT_MIN)
				throw SyntaxErrorException();
			_strage.push(res);
		}
	}
	// スタックの要素数が1でない場合もエラー
	if (_strage.size() != 1)
		throw SyntaxErrorException();
	std::cout << _strage.top() << std::endl;
}

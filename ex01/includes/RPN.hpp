/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:32:58 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/30 22:37:12 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// stack

#ifndef RPN_HPP
#define RPN_HPP

// include
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm> // アルゴリズム用
#include <stack>     // スタック使用のため
#include <limits.h>

class RPN {
	/*
	  コピーコンストラクタと代入演算子を無効化しておく。
	  RPNクラスでは、内部でstackを使用しておりスタックはポインタベースのデータ構造なので、
      デフォルトのコピーコンストラクタや代入演算子によるshallow copyは動作しないため。
	  仮にshallow copyが行われると、2つのオブジェクトが同じスタック領域を共有してしまって
	  不正アクセスの原因となる可能性があるのでprivateで宣言しておく
	*/
	private:
		RPN(RPN &src);
		RPN &operator=(RPN &src);
		// 計算時に使用するスタック
		std::stack<int>	_strage;

	public:
		RPN();  // デフォルトコンストラクタ
		~RPN(); // デストラクタ

		// 逆ポーランド記法の数式を計算する関数(引数は逆ポーランド記法の文字列)
		void	calc(std::string str);
		// 計算処理用の関数
		long	calculate(long a, long b, char sign);

		// 例外時にエラーメッセージ返す
		class	SyntaxErrorException : public std::exception {
			public:
				virtual const char* what() const throw (){
					return "syntax error";
				}
		};
};

#endif

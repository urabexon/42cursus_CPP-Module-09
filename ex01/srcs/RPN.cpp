/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:33:04 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/27 19:38:32 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(RPN &src) {
	*this = src;
}

RPN&	RPN::operator=(RPN &src) {
	if (this != &src)
		*this = src;
	return *this;
}

bool	isnum(std::string &year) {
	for(size_t i = 0; i < year.length(); i++ ) {
		if (!std::isdigit(year.at(i)))
			return false;
	}
	return true;
}

bool	issign(std::string &s) {
	if (s == "*" || s == "/" || s == "+" || s == "-")
		return true;
	return false;
}

void	err() {
	std::cout << "Error: Invalid arg" << std::endl;
	return ;
}

long	calculate(int a, int b, char sign) {
	if (sign == '+')
		return a + b;
	else if (sign == '-')
		return a - b;
	else if (sign == '*')
		return a * b;
	else
		return a / b;
}

void	RPN::calc(std::string str) {
	if (str.empty())
		throw SyntaxErrorException();

	for (std::string::iterator it = str.begin(); it != str.end(); it++) {
		if (std::isspace(*it))
			continue ;
		if (std::isdigit(*it)) {
			_strage.push((*it) - '0');
		} else {
			if (_strage.size() < 2)
				throw SyntaxErrorException();
			int	num1 = _strage.top();
			_strage.pop();
			int	num2 = _strage.top();
			_strage.pop();
			_strage.push(calculate(num2, num1, (*it)));
		}
	}
	if (_strage.size() != 1)
		throw SyntaxErrorException();
	std::cout << _strage.top() << std::endl;
}

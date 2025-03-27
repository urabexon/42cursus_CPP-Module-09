/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:32:58 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/27 19:35:19 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stack>

class RPN {
	private:
		RPN(RPN &src);
		RPN&	operator=(RPN &src);
		std::stack<int>	_strage;

	public:
		RPN();
		~RPN();

		void	calc(std::string str);

		class	SyntaxErrorException : public std::exception {
			public: virtual const char* what() const throw (){ return "syntax error"; }
		};
};

#endif

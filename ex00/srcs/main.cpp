/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:36:56 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/27 16:55:47 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Invalid number of arguments" << std::endl;
		return (1);
	}
	try {
		BitcoinExchange bit("data.csv");
		bit.analyze(argv[1]);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return (1);
	}

}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urabex <urabex@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:15:55 by hurabe            #+#    #+#             */
/*   Updated: 2025/05/15 19:55:42 by urabex           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv) {
    if (argc < 3) {
        std::cout << "Error: Not enough argument" << std::endl;
        return (EXIT_FAILURE);
    }
    try {
        PmergeMe pm(argc, argv);
        pm.excutePmergeMe(argc, argv);
    } catch (const char *msg) {
        std::cout << "Error: " << msg << std::endl;
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

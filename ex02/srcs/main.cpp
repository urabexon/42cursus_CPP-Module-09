/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urabex <urabex@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:49:51 by hurabe            #+#    #+#             */
/*   Updated: 2025/04/02 16:03:14 by urabex           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv) {
    if (argc == 1) {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    PmergeMe pmm(argv);
    
    return 0;
}

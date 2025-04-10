/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:15:40 by hurabe            #+#    #+#             */
/*   Updated: 2025/04/10 22:17:48 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <deque>

typedef struct s_pairVct {
	int	num;
	std::vector<s_pairVct> pair;
}	t_pairVct;

typedef struct s_pairDeq {
	int	num;
	std::deque<s_pairDeq> pair;
}	t_pairDeq;

class PmergeMe {
  private:

  public:
};

#endif

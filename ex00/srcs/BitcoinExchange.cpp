/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:36:59 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/27 19:17:04 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src) {
	*this = src;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &src) {
	if (this != &src)
		*this = src;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

bool	isfloat(std::string &str) {
	bool dot = false;
	for(size_t i = 0; i < str.length(); i++ ) {
		if (str.at(i) == '.' && dot == false) {
			dot = true;
			continue;
		}
		if (!std::isdigit(str.at(i)))
			return false;
	}
	if (str.at(str.length() - 1) == '.')
		return false;
	return true;
}

BitcoinExchange::BitcoinExchange(const std::string &file) {
	std::fstream dataFile(file.c_str());
	if (!dataFile)
		throw BitcoinExchange::CantOpenDataFileException();
	std::string line;
	// first line skip 
	std::getline(dataFile, line);
	size_t	linecount = 0;
	while (std::getline(dataFile, line)) {
		++linecount;
		std::string::size_type split_pos = line.find(',');
		if (split_pos == std::string::npos) {
			std::cerr << "Invalid argument in data, on line " << linecount << std::endl;
			continue ;
		}
		std::string	date = line.substr(0, split_pos);
		std::string	rate_str = line.substr(split_pos + 1);
		//!rateに制限があるならvalueチェックを変える
		if (dateCheck(date) == false || isfloat(rate_str) == false) {
			std::cerr << "Invalid date in data, on line " << linecount << std::endl;
			continue;
		}
		double num;
		std::istringstream(rate_str) >> num;
		_data[date] = num;
	}
	dataFile.close();
	if (_data.size() == 0)
		throw NoValidDataException();
}

bool	BitcoinExchange::dateCheck(std::string &string) {
	//valid year 2000 ~ 2060: month 1~12
	std::istringstream			str(string);
	std::string	year, month, date, check;
	if (!std::getline(str, year, '-'))
		return false;
	if (!std::getline(str, month, '-'))
		return false;
	if (!std::getline(str, date, '-'))
		return false;
	if (std::getline(str, check, '-'))
		return false;
	if (!checkYear(year))
		return false;
	if (!checkMonthDate(year, month, date))
		return false;
	return true;
}

bool	is_num(std::string &year) {
	for(size_t i = 0; i < year.length(); i++) {
		if (!std::isdigit(year.at(i)))
			return false;
	}
	return true;
}

bool	BitcoinExchange::checkYear(std::string &year) {
	if (year.size() != 4 || !is_num(year))
		return false;
	size_t	num;
	std::istringstream(year) >> num;
	return 2000 <= num && num <= 2060;
}

bool	BitcoinExchange::checkMonthDate(std::string &year, std::string &month, std::string &date) {
	if (!(month.size() == 1 || month.size() == 2) || !is_num(month))
		return false;
	else if (!(date.size() == 1 || date.size() == 2) || !is_num(date))
		return false;
	size_t	m, d;
	std::istringstream(month) >> m;
	std::istringstream(date) >> d;
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) {
		return 1 <= d && d <= 31;
	} else if (m == 4 || m == 6 || m == 9 || m == 11) {
		return 1 <= d && d <= 30;
	} else if (m == 2) {
		int y;
		std::istringstream(year) >> y;
		if (y % 4 == 0)
			return 1 <= d && d <= 29;
		else
			return 1 <= d && d <= 28;
	}
	return false;
}

bool	BitcoinExchange::valueCheck(std::string &str) {
	if (!isfloat(str))
		return false;
	float num;
	std::istringstream(str) >> num;
	return (num >= 0 && num <= 1000);
}

void	BitcoinExchange::analyze(const std::string &inputFile) {
	std::fstream InputFile(inputFile.c_str());
	if (!InputFile)
		throw BitcoinExchange::CantOpenInputFileException();
	std::string line;
	// first line skip
	std::getline(InputFile, line);
	while (std::getline(InputFile, line)) {
		std::istringstream stream(line);
		std::string	date, value;
		char		spliter;

		if (!(stream >> date >> spliter >> value)) {
			std::cerr << "Error: Format error: Syntax error" << std::endl;
			continue ;
		} else if (spliter != '|') {
			std::cerr << "Error: Format error: delimiter has to be '|'" << std::endl;
			continue ;
		} else if (!dateCheck(date)) {
			std::cerr << "Error: Format error: Invalid date" << std::endl;
			continue ;
		} else if (!valueCheck(value)) {
			std::cerr << "Error: Format error: Invalid value" << std::endl;
			continue ;
		}
		double rate = findRate(date);
		if (rate < 0) {
			std::cerr << "Error: no exchange rate beofore this date" << std::endl;
		} else {
			double val;
			std::istringstream(value) >> val;
			std::cout << date << " => " << value << " = " <<  val * rate << std::endl;
		}
	}
	InputFile.close();
	return ;
}

double	BitcoinExchange::findRate(std::string &date) {
	std::map<std::string, double>::iterator it = _data.upper_bound(date);
	if (it != _data.begin()) {
		it--;
		return it->second;
	} else {
		return -1;
	}
}

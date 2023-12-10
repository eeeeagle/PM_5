#pragma once
#include "Sort.hpp"
#include <string>
#include <random>

bool is_value(const std::string& str)
{
	for (auto it : str)
		if (!isdigit(it))
			return false;
	return !str.empty();
}

int get_value()
{
	while (true)
	{
		std::cout << "Enter vector size: ";
		std::string input_string;
		getline(std::cin, input_string);

		if (is_value(input_string))
			return std::stoul(input_string);
		else
			std::cout << "Incorrect input. Try again." << std::endl << std::endl;
	}
}

std::vector<int> random_int_vector(const size_t size)
{
	std::vector<int> vector = {};
	for (int i = 0; i < size; vector.push_back(i++));
	std::random_device rd;
	std::mt19937 mt(rd());
	std::shuffle(vector.begin(), vector.end(), mt);
	return vector;
}

int main()
{
	const size_t size = get_value();
	std::cout << std::endl;

	const std::vector vector = random_int_vector(size);
	/*
	for (auto & it : vector)
		std::cout << std::setw(4) << it << std::right;
	std::cout << std::endl << std::endl;
	*/
	
	std::vector<SortStats> stats;
	
	std::vector vector_copy = vector;
	stats.push_back(insertion_sort(vector_copy));

	vector_copy = vector;
	stats.push_back(bubble_sort(vector_copy));

	vector_copy = vector;
	stats.push_back(selection_sort(vector_copy));

	vector_copy = vector;
	stats.push_back(quick_sort(vector_copy));

	vector_copy = vector;
	stats.push_back(merge_sort(vector_copy));

	std::cout << std::setw(10) << "SORT" << std::right << " | TIME (ms)" << std::endl
		<< "-----------|-----------" << std::endl;
	for (auto & it : stats)
		std::cout << std::setw(10) << it.get_name() << std::right << " | " << it.get_total_time() / 1000 << std::endl;
	std::cout << std::endl;

	return 0;
}

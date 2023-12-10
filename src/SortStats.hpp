#pragma once
#ifndef SORT_STATS
#define SORT_STATS
#include <iostream>
#include <iomanip>
#include <chrono>

typedef std::chrono::duration<double, std::micro> Micro;
typedef std::chrono::high_resolution_clock HRC;

class SortStats
{
private:
	double total_time;
	std::string name;
public:
	SortStats(std::chrono::steady_clock::time_point start_time, std::chrono::steady_clock::time_point end_time, std::string name)
		: name(name)
	{
		total_time = Micro(end_time - start_time).count();
	}
	double get_total_time() const
	{
		return total_time;
	}
	std::string get_name() const
	{
		return name;
	}
};
#endif
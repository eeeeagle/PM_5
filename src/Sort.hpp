#pragma once
#ifndef SORT
#define SORT
#include "SortStats.hpp"
#include <vector>
#include <algorithm>

template <typename T>
bool is_sorted(const std::vector<T>& data)
{
    for (auto iter = data.cbegin() + 1; iter != data.cend(); iter++)
    {
        if (*iter < *(iter - 1))
            return false;
    }
    return true;
}

template <typename T>
SortStats selection_sort(std::vector<T>& data)
{
    auto start_time = HRC::now();

    for (size_t i = 0; i < data.size() - 1; i++) 
    {
        size_t min_idx = i;
        for (size_t j = i + 1; j < data.size(); j++)
            if (data[j] < data[min_idx])
                min_idx = j;

        if (min_idx != i)
            std::swap(data[min_idx], data[i]);
    }

    auto end_time = HRC::now();
    return SortStats(start_time, end_time, "Selection");
}

template <typename T>
SortStats insertion_sort(std::vector<T>& data)
{
    auto start_time = HRC::now();

    for (size_t i = 0; i < data.size(); i++)
        for (size_t j = i; j > 0 && data[j - 1] > data[j]; j--)
            std::swap(data[j], data[j - 1]);

    auto end_time = HRC::now();
    return SortStats(start_time, end_time, "Insertion");
}

template <typename T>
SortStats bubble_sort(std::vector<T>& data)
{
    auto start_time = HRC::now();

    for (size_t i = 0; i < data.size() - 1; i++)
        for (size_t j = 0; j < data.size() - i - 1; j++)
            if (data[j] > data[j + 1])
                std::swap(data[j], data[j + 1]);

    auto end_time = HRC::now();
    return SortStats(start_time, end_time, "Bubble");
}

template <typename T>
void quick_sort(std::vector<T>& data, int low, int high)
{
    int i = low;
    int j = high;
    int pivot = data[(i + j) / 2];
    while (i <= j)
    {
        while (data[i] < pivot)
            i++;
        while (data[j] > pivot)
            j--;
        if (i <= j)
        {
            std::swap(data[i], data[j]);
            i++;
            j--;
        }
    }
    if (j > low)
        quick_sort(data, low, j);
    if (i < high)
        quick_sort(data, i, high);
}

template <typename T>
SortStats quick_sort(std::vector<T>& data)
{
    auto start_time = HRC::now();

    if (!is_sorted(data))
        quick_sort(data, 0, int(data.size() - 1));

    auto end_time = HRC::now();
    return SortStats(start_time, end_time, "Quick");
}

template <typename T>
void merge(std::vector<T>& left, std::vector<T>& right, std::vector<T>& bars)
{
    int nL = left.size();
    int nR = right.size();
    int i = 0, j = 0, k = 0;

    while (j < nL && k < nR)
    {
        if (left[j] < right[k]) 
            bars[i] = left[j++];
        else 
            bars[i] = right[k++];
        i++;
    }
    while (j < nL) 
        bars[i++] = left[j++];
    while (k < nR) 
        bars[i++] = right[k++];
}

template <typename T>
void merge(std::vector<T>& data)
{
    if (data.size() <= 1) 
        return;

    int mid = data.size() / 2;
    std::vector<T> left;
    std::vector<T> right;

    for (size_t j = 0; j < mid; j++)
        left.push_back(data[j]);
    for (size_t j = 0; j < (data.size()) - mid; j++)
        right.push_back(data[mid + j]);

    merge(left);
    merge(right);
    merge(left, right, data);
}

template <typename T>
SortStats merge_sort(std::vector<T>& data)
{
    auto start_time = HRC::now();

    merge(data);

    auto end_time = HRC::now();
    return SortStats(start_time, end_time, "Merge");
}
#endif
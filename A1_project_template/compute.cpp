#include "compute.h"
#include <cmath>
#include <stdexcept>
#include <algorithm>

namespace compute {

double mean(const std::vector<double>& data)
{
    if (data.empty())
        throw std::runtime_error("Cannot compute mean of empty data.");

    double sum = 0.0;
    for (double v : data)
        sum += v;

    return sum / data.size();
}

double min(const std::vector<double>& data)
{
    if (data.empty())
        throw std::runtime_error("Cannot compute min of empty data.");

    return *std::min_element(data.begin(), data.end());
}

double max(const std::vector<double>& data)
{
    if (data.empty())
        throw std::runtime_error("Cannot compute max of empty data.");

    return *std::max_element(data.begin(), data.end());
}

double stddev(const std::vector<double>& data)
{
    if (data.size() < 2)
        throw std::runtime_error("Not enough data for stddev.");

    double m = mean(data);

    double sum_sq = 0.0;
    for (double v : data)
        sum_sq += (v - m) * (v - m);

    return std::sqrt(sum_sq / (data.size() - 1));
}

std::vector<std::size_t> find_peaks(const std::vector<double>& data,
                                    double threshold)
{
    std::vector<std::size_t> peaks;

    for (std::size_t i = 1; i + 1 < data.size(); ++i)
    {
        if (data[i] > data[i - 1] &&
            data[i] > data[i + 1] &&
            data[i] > threshold)
        {
            peaks.push_back(i);
        }
    }

    return peaks;
}

double rmssd(const std::vector<double>& data)
{
    if (data.size() < 2)
        throw std::runtime_error("Not enough data for RMSSD.");

    double sum_sq = 0.0;

    for (std::size_t i = 1; i < data.size(); ++i)
    {
        double diff = data[i] - data[i - 1];
        sum_sq += diff * diff;
    }

    return std::sqrt(sum_sq / (data.size() - 1));
}

}
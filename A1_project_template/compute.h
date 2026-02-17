#pragma once
#include <vector>

namespace compute {

    // Basic statistics
    double mean(const std::vector<double>& data);
    double min(const std::vector<double>& data);
    double max(const std::vector<double>& data);
    double stddev(const std::vector<double>& data);

    // Peak detection (simple local maxima)
    std::vector<std::size_t> find_peaks(const std::vector<double>& data,
                                        double threshold = 0.0);

    // Root Mean Square of Successive Differences (HRV-style metric)
    double rmssd(const std::vector<double>& data);

}
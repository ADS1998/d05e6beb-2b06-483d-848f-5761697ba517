#pragma once
#include <vector>
#include <string>

/**
 * @brief Generic time-series signal
 */
struct TimeSeries {
    double sampling_interval{}; /**< optional sampling interval */
    std::vector<double> values; /**< numeric values */
};

/**
 * @brief 2D grayscale image (P2 PGM format)
 */
struct Image2D {
    int width{};                 /**< image width */
    int height{};                /**< image height */
    int max_val{};               /**< max pixel value */
    std::vector<int> pixels;     /**< pixel data, row-major */
};

/**
 * @brief Generic numeric matrix
 */
struct MatrixData {
    size_t rows{};               /**< number of rows */
    size_t cols{};               /**< number of columns */
    std::vector<double> values;  /**< flattened row-major values */
};

/**
 * @brief Text sequence (DNA, RNA, or protein)
 */
struct SequenceData {
    std::string data;            /**< sequence characters */
};

/**
 * @brief Load a numeric time series from file
 * @param filename Path to file
 * @return TimeSeries struct with sampling interval and values
 */
TimeSeries load_time_series(const std::string& filename);

/**
 * @brief Load a 2D P2 PGM image from file
 * @param filename Path to file
 * @return Image2D struct with dimensions and pixel data
 */
Image2D load_pgm_image(const std::string& filename);

/**
 * @brief Load a generic numeric matrix from file
 * @param filename Path to file
 * @return MatrixData struct with row/column info and flattened values
 */
MatrixData load_matrix(const std::string& filename);

/**
 * @brief Load a text sequence (e.g., DNA) from file
 * @param filename Path to file
 * @return SequenceData struct with concatenated sequence
 */
SequenceData load_sequence(const std::string& filename);

// ---------------- Visualisation ----------------
/**
 * @brief Plot a time series in terminal using Termviz
 */
void visualise(const TimeSeries& ts);

/**
 * @brief Plot a PGM image in terminal using Termviz
 */
void visualise(const Image2D& img);

/**
 * @brief Plot a numeric matrix in terminal using Termviz
 */
void visualise(const MatrixData& mat);

/**
 * @brief Print a summary of a sequence and optionally show first N bases
 */
void visualise(const SequenceData& seq, size_t n_bases=50);

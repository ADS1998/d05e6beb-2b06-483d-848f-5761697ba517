#include "file_loader.h"
#include "debug.h"
#include <termviz.h>  // Include Termviz for plotting

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>

namespace {

    /**
     * @brief Opens a file and throws an exception if it fails
     * @param filename Path to file
     * @return std::ifstream object (open)
     */
    std::ifstream open_file(const std::string& filename) {
        std::ifstream infile(filename);
        if (!infile)
            throw std::runtime_error("Failed to open file: " + filename);
        return infile;
    }

    /**
     * @brief Skip lines that start with a comment string
     * @param infile Opened input file stream
     * @param comment_start String that indicates a comment line (e.g., "#" or ">")
     */
    void skip_comment_lines(std::ifstream& infile, const std::string& comment_start) {
        while (true) {
            int c = infile.peek();
            if (c == EOF)
                break;
            if (comment_start.find(static_cast<char>(c)) != std::string::npos)
                infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            else
                break;
        }
    }

    /**
     * @brief Validates the first token in the file against expected header
     * @param infile Opened input file stream
     * @param expected_header Expected string at start of file
     */
    void validate_header(std::ifstream& infile, const std::string_view& expected_header) {
        if (!expected_header.empty()) {
            std::string header;
            if (!(infile >> header))
                throw std::runtime_error("Failed to read header from file");

            if (header != expected_header)
                throw std::runtime_error("Unexpected file identifier: " + header);
        }
    }

} // anonymous namespace

////////////////////////////////////////////////////////////
// 1. TIME SERIES LOADER
////////////////////////////////////////////////////////////

TimeSeries load_time_series(const std::string& filename) {
    std::ifstream infile = open_file(filename);
    TimeSeries data;

    skip_comment_lines(infile, "#");
    constexpr std::string_view expected_header = "ECG";
    validate_header(infile, expected_header);

    // After header, assume sampling interval next
    if (!(infile >> data.sampling_interval))
        throw std::runtime_error("Failed to read sampling interval");

    // Read numeric values
    double val;
    while (infile >> val)
        data.values.push_back(val);

    // Optional: handle 2-column files (time + value)
    // double t;
    // infile.clear();
    // infile.seekg(0);
    // while (infile >> t >> val)
    //     data.values.push_back(val);

    if (data.values.empty())
        throw std::runtime_error("No numeric data found in file");

    return data;
}

////////////////////////////////////////////////////////////
// 2. PGM IMAGE LOADER (P2 format)
////////////////////////////////////////////////////////////

Image2D load_pgm_image(const std::string& filename) {
    std::ifstream infile = open_file(filename);
    skip_comment_lines(infile, "#");
    validate_header(infile, "P2");

    Image2D img;

    // Skip comments before width/height
    skip_comment_lines(infile, "#");
    if (!(infile >> img.width >> img.height))
        throw std::runtime_error("Failed to read PGM width/height");

    // Skip comments before max_val
    skip_comment_lines(infile, "#");
    if (!(infile >> img.max_val))
        throw std::runtime_error("Failed to read PGM max value");

    if (img.width <= 0 || img.height <= 0 || img.max_val <= 0)
        throw std::runtime_error("Invalid PGM header values");

    // Skip comments before pixel data
    skip_comment_lines(infile, "#");

    int pixel;
    while (infile >> pixel)
        img.pixels.push_back(pixel);

    if (img.pixels.size() != static_cast<std::size_t>(img.width * img.height))
        throw std::runtime_error("Pixel count does not match PGM dimensions");

    return img;
}

////////////////////////////////////////////////////////////
// 3. MATRIX LOADER (generic numeric matrix)
////////////////////////////////////////////////////////////

MatrixData load_matrix(const std::string& filename) {
    std::ifstream infile = open_file(filename);
    MatrixData mat;
    std::string line;

    std::vector<double> values;
    std::size_t cols_detected = 0;

    while (std::getline(infile, line)) {
        // Remove whitespace
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        if (line.empty() || line[0] == '#' || line[0] == '>')
            continue;

        std::istringstream iss(line);
        std::vector<double> row;
        double val;
        while (iss >> val)
            row.push_back(val);

        if (row.empty())
            continue;

        if (cols_detected == 0)
            cols_detected = row.size();
        else if (row.size() != cols_detected)
            throw std::runtime_error("Inconsistent row length in matrix file");

        values.insert(values.end(), row.begin(), row.end());
        mat.rows++;
    }

    if (mat.rows == 0)
        throw std::runtime_error("Empty matrix file");

    mat.cols = cols_detected;
    mat.values = std::move(values);

    return mat;
}

////////////////////////////////////////////////////////////
// 4. SEQUENCE LOADER (DNA / text sequence)
////////////////////////////////////////////////////////////

SequenceData load_sequence(const std::string& filename) {
    std::ifstream infile = open_file(filename);
    SequenceData seq;
    std::string line;

    while (std::getline(infile, line)) {
        if (line.empty() || line[0] == '>')
            continue;
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        seq.data += line;
    }

    if (seq.data.empty())
        throw std::runtime_error("No sequence data found");

    return seq;
}

////////////////////////////////////////////////////////////
//  VISUALISATION FUNCTIONS
////////////////////////////////////////////////////////////

// Visualize 1D time series
void visualise(const TimeSeries& ts) {
    if (ts.values.empty()) return;
    termviz::figure(800, 200)
    .plot(ts.values)
    .show();
}
// Visualize 2D image
void visualise(const Image2D& img, const std::string& title) {
    if (img.pixels.empty()) return;
    termviz::Image<float> timg(img.width, img.height);
        for (int y = 0; y < img.height; ++y)
            for (int x = 0; x < img.width; ++x)
                timg(x,y) = img.pixels[x + img.width*y]; // use data vector directly
        
        termviz::imshow(timg, *std::min_element(img.pixels.begin(), img.pixels.end()),
                            *std::max_element(img.pixels.begin(), img.pixels.end()));
}
// Visualize generic 1D array/vector
template<typename T>
void visualise(const std::vector<T>& v) {
    if (v.empty()) return;

    termviz::figure(800, 200)
    .plot(v)
    .show();
}
void visualise(const SequenceData& seq, size_t n_bases) {
    std::cout << "Sequence length: " << seq.data.size() << "\n";
    std::cout << "First " << std::min(n_bases, seq.data.size()) << " bases: "
              << seq.data.substr(0, std::min(n_bases, seq.data.size())) << "\n";
}





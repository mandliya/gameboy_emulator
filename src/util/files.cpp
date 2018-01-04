#include "files.h"
#include "definitions.h"
#include "log.h"
#include <fstream>

std::vector<char> read_bytes(const std::string filename)
{
    std::ifstream stream(filename.c_str(), std::ios::binary | std::ios::ate);

    if (!stream.good()) {
        fatal_error("can't read from file: %s", filename.c_str());
    }

    // determine the size of the file to allocate result char vector
    std::ifstream::pos_type position = stream.tellg();
    size_t file_size = static_cast<size_t>(position);

    // now, create the vector and read the file into it.
    std::vector<char> result(file_size);
    stream.seekg(0, std::ios::beg);
    stream.read(&result[0], position);
    stream.close();

    return result;
}
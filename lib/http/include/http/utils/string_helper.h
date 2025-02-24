#ifndef HTTP_UTILS_STRING_HELPER_H
#define HTTP_UTILS_STRING_HELPER_H

#include <string>
#include <vector>

namespace http::utils {
    /**
    * @brief Splits a string into one or multiple sub strings
    * @param str [in] The string that will be split
    * @param delimiter [in] The substring delimiter
    * @return A vector containing the split string
    */
    std::vector<std::string> split_string(std::string str, const std::string& delimiter);

    std::pair<std::string, std::string> split_string_at_first_delimiter(const std::string& str, const std::string& delimiter);

    std::string trim_string(std::string str, char to_trim);

}

#endif /* !HTTP_UTILS_STRING_HELPER_H */

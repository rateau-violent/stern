#include "http/utils/string_helper.h"

#include <algorithm>

namespace http::utils {
    std::vector<std::string> split_string(std::string str, const std::string& delimiter) {
        if (delimiter.empty()) {
            return {str};
        }

        std::vector<std::string> tokens{};
        if (str.empty()) {
            return tokens;
        }

        std::size_t pos = 0;
        while ((pos = str.find(delimiter)) != std::string::npos) {
            std::string sub_str = str.substr(0, pos);
            tokens.push_back(sub_str);
            str.erase(0, pos + delimiter.length());
        }
        tokens.push_back(str);
        return tokens;
    }

    std::pair<std::string, std::string> split_string_at_first_delimiter(const std::string& str, const std::string& delimiter) {
        if (std::size_t pos = str.find(delimiter); !delimiter.empty() && pos != std::string::npos) {
            return { str.substr(0, pos), str.substr(pos + delimiter.length(), str.size() - 1)};
        }
        return { str, ""};
    }

    std::string trim_string(std::string str, char to_trim) {
        str.erase(str.begin(), std::find_if(str.begin(), str.end(), [to_trim] (char c) {
            return c != to_trim;
        }));
        str.erase(std::find_if(str.rbegin(), str.rend(), [to_trim] (char c) {
            return c != to_trim;
        }).base(), str.end());

        return str;
    }


}

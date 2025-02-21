#include "http/utils/string_helper.h"

namespace http::utils {
    std::vector<std::string> split_string(std::string str, const std::string& delimiter) {
        std::vector<std::string> tokens;
        std::size_t pos = 0;

        while ((pos = str.find(delimiter)) != std::string::npos) {
            std::string sub_str = str.substr(0, pos);
            tokens.push_back(sub_str);
            str.erase(0, pos + delimiter.length());
        }
        tokens.push_back(str);
        return tokens;
    }
}

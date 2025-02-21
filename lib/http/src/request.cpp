#include "http/request.h"
#include "http/utils/string_helper.h"

#include <iostream>

namespace http {
    request::request(const std::string& request_string) {
        auto lines = utils::split_string(request_string, "\r\n");
        if (lines.empty()) {
            throw std::runtime_error("Unable to parse HTTP request");
        }

        {
            auto first_line_split = utils::split_string(lines[0], " ");

            if (first_line_split.size() != 3) {
                throw std::runtime_error("Ill formed HTTP request");
            }
            method = to_method(first_line_split[0]);
            path = first_line_split[1];
            version = to_version(first_line_split[2]);
        }

        // for (std::size_t i = 1; i < lines.size(); ++i) {
        //     headers
        // }
    }

}

#include <stdexcept>
#include <ostream>

#include "http/request.h"
#include "http/utils/string_helper.h"

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

        std::size_t i = 1;
        for (; i < lines.size(); ++i) {
            // headers
            auto [key, value] = utils::split_string_at_first_delimiter(lines[i], ":");
            if (key.empty() && value.empty()) {
                break;
            }
            headers.emplace(key, utils::trim_string(value, ' '));
        }

        for (; i < lines.size(); ++i) {
            // body
            if (lines[i].empty()) {
                continue;
            }
            body += lines[i];
       }
    }

    std::ostream& operator<<(std::ostream& os, const request& r) {
        os << std::to_string(r.method) << " " << r.path << " " << std::to_string(r.version) << "\n";

        for (const auto& [key, value]: r.headers) {
            os << key << ": " << value << "\n";
        }
        os << r.body;
        os << std::endl;
        return os;
    }

}

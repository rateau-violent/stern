#include "http/query.h"
#include "http/utils/string_helper.h"

namespace http {
    query_type::query_type(const std::string& content) {
        for (const auto& param: utils::split_string(content, "&")) {
            auto [key, value] =  utils::split_string_at_first_delimiter(param, "=");
            auto values = utils::split_string(value, ",");
            if (values.size() > 1) {
                auto array = json::array();
                for (const auto&v: values) {
                    try {
                        array.push_back(json::parse(v));
                    } catch (...) {
                        array.push_back(v);
                    }
                }
                _data[key] = array;
            } else {
                try {
                    _data[key] = json::parse(value);
                } catch (...) {
                    _data[key] = value;
                }
            }
        }
    }

    std::string query_type::to_string() const {
        return nlohmann::to_string(_data);
    }

    bool query_type::empty() const {
        return _data.empty();
    }


}

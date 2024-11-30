#ifndef BACKEND_ROUTE_H
#define BACKEND_ROUTE_H

#include <functional>

namespace backend {
    template <typename Request, typename Response>
    class route {
        using route_fct = std::function<Response (const Request&)>;
        public:
            route(route_fct &&fct): _fct{std::move(fct)} {
            }

            Response operator()(const Request &request) {
                return _fct(request);
            }

            // operator route_fct() {
            //     return _fct;
            // }

        private:
            route_fct _fct;
    };
}

#endif /* !BACKEND_ROUTE_H */

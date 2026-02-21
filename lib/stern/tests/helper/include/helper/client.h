#ifndef STERN_TEST_CLIENT_H
#define STERN_TEST_CLIENT_H

#include <http/response.h>

namespace tests::helper {
/**
 * Client that makes basic http requests
 */
class client {
public:
  /**
   *  Creates a client object
   *  @param [in] ip the server's ip
   *  @param [in] port the server's port
   */
  explicit client(const std::string& ip, std::size_t port);

  /**
   * Sends a http GET request to the server
   * @param [in] path the path the request will be made on
   */
  [[nodiscard]] http::response get(const std::string& path) const;

  /**
   * Sends a http POST request to the server
   * @param [in] path the path the request will be made on
   * @param [in] body the request's body content
   */
  [[nodiscard]] http::response post(const std::string& path, const http::body_type& body) const;

  /**
   * Sends a http PUT request to the server
   * @param [in] path the path the request will be made on
   * @param [in] body the request's body content
   */
  [[nodiscard]] http::response put(const std::string& path, const http::body_type& body) const;

  /**
   * Sends a http DELETE request to the server
   * @param [in] path the path the request will be made on
   */
  [[nodiscard]] http::response del(const std::string& path) const;

private:
  std::string _ip;
  std::size_t _port;

  std::string compute_url(const std::string& path) const;
};
}

#endif /* STERN_TEST_CLIENT_H */

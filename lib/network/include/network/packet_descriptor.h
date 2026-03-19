#ifndef NETWORK_PACKET_DESCRIPTOR
#define NETWORK_PACKET_DESCRIPTOR

#include <cstdint>

namespace network {

/**
 * @brief Represents a network packet
 */
struct packet_descriptor {
  /// Packet's data
  std::uint8_t* data;
  /// Size of the packet's data
  std::size_t size;
};

}

#endif /* !NETWORK_PACKET_DESCRIPTOR */
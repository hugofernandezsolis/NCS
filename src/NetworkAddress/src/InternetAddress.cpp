/**
 * @copyright Copyright (c) 2023
 * 
 * @author Hugo Fernandez Solis (hugofernandezsolis@gmail.com)
 * @date 08-08-2024
 * 
 * @file InternetAddress.cpp
 * 
 * @brief
 */


#include <arpa/inet.h>

#include <algorithm> 
#include <regex>

#include <InternetAddress.h>


namespace ncs { // Network Communications System
namespace addr { // Network Communications System Addresses


/** PUBLIC METHODS */
/// PUBLIC //////////////////////////////////////     CONSTRUCTORS    //////////////////////////////////////////////////
/**
 * @brief Default constructor
 * 
 * @param iPort 
 * @param iIp_
 */
InternetAddress::InternetAddress(const ip_t& iIp, const port_t& iPort) {
  memset(&this->get_storage(), 0, sizeof(this->get_storage()));
  this->set_ip(iIp);
  this->set_port(iPort);
}

/**
 * @brief Copy constructor
 * 
 * @param iInternetAddr 
 */
InternetAddress::InternetAddress(const InternetAddress& iInternetAddr) {
  memset(&this->get_storage(), 0, sizeof(this->get_storage()));
  this->set_ip(iInternetAddr.get_ip());
  this->set_port(iInternetAddr.get_port());
}

/**
 * @brief Move constructor
 * 
 * @param iInternetAddr 
 */
InternetAddress::InternetAddress(InternetAddress&& iInternetAddr) noexcept {
  memset(&this->get_storage(), 0, sizeof(this->get_storage()));
  this->set_ip(std::move(iInternetAddr.get_ip()));
  this->set_port(iInternetAddr.get_port());
  iInternetAddr.clear();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PUBLIC //////////////////////////////////////    CLASS METHODS    //////////////////////////////////////////////////
/**
 * @brief
 * 
 * @return
 */
[[nodiscard]] bool InternetAddress::is_valid(void) const {
  return this->has_valid_ip() && this->has_valid_port();
}

/**
 * @brief
 * 
 * @return
 */
[[nodiscard]] bool InternetAddress::has_valid_ip(void) const {
  switch (this->address_family()) {
    case IPV4_FAMILY:
      return this->has_valid_v4_ip();
    break;
    case IPV6_FAMILY:
      return this->has_valid_v6_ip();
    break;
    default:
      return false;
    break;
  }
}

/**
 * @brief
 * 
 * @return
 */
[[nodiscard]] bool InternetAddress::has_valid_port(void) const {
  return (this->get_port() > MIN_VALID_PORT) && (this->get_port() < MAX_VALID_PORT);
}

/**
 * @brief
 * 
 * @return
 */
[[nodiscard]] addr_family_e InternetAddress::address_family(void) const {
  switch (this->get_storage().ss_family) {
    case AF_INET:
      return IPV4_FAMILY;
    break;
    case AF_INET6:
      return IPV6_FAMILY;
    break;
    default:
      return ERROR_FAMILY;
    break;
  }
}


/**
 * @brief
 */
void InternetAddress::clear(void) {
  memset(&this->get_storage(), 0, sizeof(this->get_storage()));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PUBLIC //////////////////////////////////////  SETTERS & GETTERS  //////////////////////////////////////////////////
/**
 * @brief
 * 
 * @param iIp 
 */
void InternetAddress::set_ip(const ip_t& iIp) {
  if (this->address_family() == IPV4_FAMILY) {
    sockaddr_in* addrIn = reinterpret_cast<sockaddr_in*>(&this->get_storage());
    inet_pton(AF_INET, iIp.c_str(), &addrIn->sin_addr);
  }
  else if (this->address_family() == IPV6_FAMILY) {
    sockaddr_in6* addrIn6 = reinterpret_cast<sockaddr_in6*>(&this->get_storage());
    inet_pton(AF_INET, iIp.c_str(), &addrIn6->sin6_addr);
  }
}

/**
 * @brief
 * 
 * @param iPort 
 */
void InternetAddress::set_port(const port_t& iPort) {
  if (this->address_family() == IPV4_FAMILY) {
    sockaddr_in* addrIn = reinterpret_cast<sockaddr_in*>(&this->get_storage());
    addrIn->sin_port = htons(iPort);
  }
  else if (this->address_family() == IPV6_FAMILY) {
    sockaddr_in6* addrIn6 = reinterpret_cast<sockaddr_in6*>(&this->get_storage());
    addrIn6->sin6_port = htons(iPort);
  }
}

/**
 * @brief
 * 
 * @return
 */
[[nodiscard]] ip_t InternetAddress::get_ip(void) const {
  char ip[INET6_ADDRSTRLEN];
  memset(&ip, 0, sizeof(ip));
  if (this->address_family() == IPV4_FAMILY) {
    const sockaddr_in* addrIn = reinterpret_cast<const sockaddr_in*>(&this->get_storage());
    inet_ntop(AF_INET, &addrIn->sin_addr, ip, sizeof(ip));
  }
  else if (this->address_family() == IPV6_FAMILY) {
    const sockaddr_in6* addrIn6 = reinterpret_cast<const sockaddr_in6*>(&this->get_storage());
    inet_ntop(AF_INET, &addrIn6->sin6_addr, ip, sizeof(ip));
  }
  return ip;
}

/**
 * @brief
 * 
 * @return
 */
[[nodiscard]] port_t InternetAddress::get_port(void) const {
  port_t port;
  if (this->address_family() == IPV4_FAMILY) {
    const sockaddr_in* addrIn = reinterpret_cast<const sockaddr_in*>(&this->get_storage());
    port = ntohs(addrIn->sin_port);
  }
  else if (this->address_family() == IPV6_FAMILY) {
    const sockaddr_in6* addrIn6 = reinterpret_cast<const sockaddr_in6*>(&this->get_storage());
    port = ntohs(addrIn6->sin6_port);
  }
  return port;
}

/**
 * @brief
 * 
 * @return
 */
[[nodiscard]] const sockaddr_storage& InternetAddress::get_storage(void) const {
  return this->addrStorage_;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PUBLIC //////////////////////////////////////  OUTPUT FORMATTERS  //////////////////////////////////////////////////
/**
 * @brief
 * 
 * @return
 */
[[nodiscard]] std::string InternetAddress::to_string(void) const {
  char delimiter = this->address_family() == IPV4_FAMILY ? ':' : '-';
  return this->get_ip() + delimiter + std::to_string(this->get_port());
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PUBLIC //////////////////////////////////////       OPERATORS     //////////////////////////////////////////////////
/**
 * @brief Copy assignment operator
 * 
 * @param iInternetAddr
 * 
 * @return
 */
InternetAddress& InternetAddress::operator=(const InternetAddress& iInternetAddr) {
  if (this != &iInternetAddr) {
    this->set_ip(iInternetAddr.get_ip());
    this->set_port(iInternetAddr.get_port());
  }
  return *this;
}

/**
 * @brief Move assignment operator
 * 
 * @param iInternetAddr
 * 
 * @return
 */
InternetAddress& InternetAddress::operator=(InternetAddress&& iInternetAddr) noexcept {
  if (this != &iInternetAddr) {
    this->set_ip(std::move(iInternetAddr.get_ip()));
    this->set_port(iInternetAddr.get_port());
    iInternetAddr.clear();
  }
  return *this;
}

/**
 * @brief
 * 
 * @param iInternetAddr
 * 
 * @return
 */
[[nodiscard]] bool InternetAddress::operator==(const InternetAddress& iInternetAddr) const {
  if (this == &iInternetAddr) {return true;}
  return (this->get_ip() == iInternetAddr.get_ip()) && (this->get_port() == iInternetAddr.get_port());
}

/**
 * @brief
 * 
 * @param iInternetAddr
 * 
 * @return
 */
[[nodiscard]] bool InternetAddress::operator!=(const InternetAddress& iInternetAddr) const {
  if (this != &iInternetAddr) {return true;}
  return (this->get_ip() != iInternetAddr.get_ip()) || (this->get_port() != iInternetAddr.get_port());
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PUBLIC ///////////////////////////////////////  FRIEND FUNCTIONS  //////////////////////////////////////////////////
/**
 * @brief
 * 
 * @param os 
 * @param iInternetAddr
 * 
 * @return
 */
std::ostream& operator<<(std::ostream& os, const InternetAddress& iInternetAddr) {
  os << iInternetAddr.to_string();
  return os;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PUBLIC //////////////////////////////////////     DESTRUCTORS     //////////////////////////////////////////////////
/**
 * @brief
 */
InternetAddress::~InternetAddress() {
  memset(&this->get_storage(), 0, sizeof(this->get_storage()));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  

/** PROTECTED METHODS **/
/// PROTECTED ///////////////////////////////////     CONSTRUCTORS    //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PROTECTED ///////////////////////////////////    CLASS METHODS    //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PROTECTED ///////////////////////////////////  SETTERS & GETTERS  //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PROTECTED ///////////////////////////////////  OUTPUT FORMATTERS  //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PROTECTED ///////////////////////////////////       OPERATORS     //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PROTECTED ///////////////////////////////////     DESTRUCTORS     //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  

/** PRIVATE METHODS **/
/// PRIVATE /////////////////////////////////////     CONSTRUCTORS    //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PRIVATE /////////////////////////////////////    CLASS METHODS    //////////////////////////////////////////////////
/**
 * @brief
 * 
 * @return
 */
[[nodiscard]] bool InternetAddress::has_valid_v4_ip(void) const {
  const std::regex IPV4_PATTERN(
      "^"                     // Start of string
      "(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])"  // 1st octet
      "\\."                   // Dot separator
      "(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])"  // 2nd octet
      "\\."                   // Dot separator
      "(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])"  // 3rd octet
      "\\."                   // Dot separator
      "(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])"  // 4th octet
      "$"                     // End of string
  );
  return std::regex_match(this->get_ip(), IPV4_PATTERN);
}


/**
 * @brief
 * 
 * @return
 */
[[nodiscard]] bool InternetAddress::has_valid_v6_ip(void) const {
  const std::regex IPV6_PATTERN(
      "^(" // Start of pattern

      // An IPv6 address consists of 8 groups of 4 hexadecimal digits:
      "([0-9A-Fa-f]{1,4}:){7}([0-9A-Fa-f]{1,4})" // Uncompressed

      // Or fewer groups, with "::" to represent one or more groups of 0000:
      "|(([0-9A-Fa-f]{1,4}:){1,7}:)"                      // Leading groups compressed
      "|(:([0-9A-Fa-f]{1,4}:){1,7})"                      // Trailing groups compressed
      "|(([0-9A-Fa-f]{1,4}:){1,6}([0-9A-Fa-f]{1,4}:)?)"   // Middle groups compressed
      "|(::([0-9A-Fa-f]{1,4}:){1,5})"                     // Multiple internal groups compressed
      "|(:{2}([0-9A-Fa-f]{1,4}:){1,4})"                   // More compressed groups
      "|(:{2}([0-9A-Fa-f]{1,4}:){1,3})"                   // More compressed groups
      "|(:{2}([0-9A-Fa-f]{1,4}:){1,2})"                   // More compressed groups
      "|(:{2}([0-9A-Fa-f]{1,4}:){1})"                     // More compressed groups
      "|(:{2}([0-9A-Fa-f]{1,4}){1})"                      // Single compressed group
      "|(:{2})"                                           // All zeros compressed
      
      // Loopback, unspecified addresses
      "|(::)"                   // Unspecified and loopback address
      "|(::1)"                  // Loopback address
      "|(0:0:0:0:0:0:0:1)"      // Full loopback address

      // End of string
      ")$"
  );
  return std::regex_match(this->get_ip(), IPV6_PATTERN);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PRIVATE /////////////////////////////////////  SETTERS & GETTERS  //////////////////////////////////////////////////

/**
 * @brief
 * 
 * @return
 */
[[nodiscard]] sockaddr_storage& InternetAddress::get_storage(void) {
  return this->addrStorage_;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PRIVATE /////////////////////////////////////  OUTPUT FORMATTERS  //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PRIVATE /////////////////////////////////////       OPERATORS     //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PRIVATE /////////////////////////////////////     DESTRUCTORS     //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


} // namespace addr
} // namespace ncs
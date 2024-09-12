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


#include <InternetAddress.h>

#include <arpa/inet.h>

#include <algorithm> 
#include <regex>


namespace ncs { // Network Communications System
namespace addr { // Network Communications System Addresses


/** PUBLIC METHODS */
/// PUBLIC //////////////////////////////////////     CONSTRUCTORS    //////////////////////////////////////////////////
/**
 * @brief Default constructor
 */
InternetAddress::InternetAddress(void) {
  this->set_ip(LOCAL_HOST);
  this->set_port(-1);
}

/**
 * @brief Parameters constructor
 * 
 * @param iPort 
 * @param iIp_
 */
InternetAddress::InternetAddress(const ip_t& iIp, const port_t& iPort) {
  this->set_ip(iIp);
  this->set_port(iPort);
}

/**
 * @brief Copy constructor
 * 
 * @param iOther 
 */
InternetAddress::InternetAddress(const InternetAddress& iOther) {
  this->set_ip(iOther.get_ip());
  this->set_port(iOther.get_port());
}

/**
 * @brief Move constructor
 * 
 * @param iOther 
 */
InternetAddress::InternetAddress(InternetAddress&& iOther) noexcept {
  this->set_ip(std::move(iOther.get_ip()));
  this->set_port(iOther.get_port());
  iOther.clear();
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
  switch (this->get_address_family()) {
    case AF_INET:
      return this->has_valid_v4_ip();
    break;
    case AF_INET6:
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
  return (this->get_port() >= MIN_VALID_PORT) && (this->get_port() <= MAX_VALID_PORT);
}

/**
 * @brief
 */
void InternetAddress::clear(void) {
  this->set_ip("");
  this->set_port(-1);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PUBLIC //////////////////////////////////////  SETTERS & GETTERS  //////////////////////////////////////////////////
/**
 * @brief
 * 
 * @param iIp 
 */
void InternetAddress::set_ip(const ip_t& iIp) {
  this->ip_ = iIp;
}

/**
 * @brief
 * 
 * @param iPort 
 */
void InternetAddress::set_port(const port_t& iPort) {
  this->port_ = iPort;
}


/**
 * @brief
 * 
 * @return
 */
[[nodiscard]] const ip_t& InternetAddress::get_ip(void) const {
  return this->ip_;
}

/**
 * @brief
 * 
 * @return
 */
[[nodiscard]] const port_t& InternetAddress::get_port(void) const {
  return this->port_;
}

/**
 * @brief
 * 
 * @return
 */
[[nodiscard]] addr_family_e InternetAddress::get_address_family(void) const {
  if (this->has_valid_v4_ip()) {
    return NET_ADDR_FAM_INET;
  }
  if (this->has_valid_v6_ip()) {
    return NET_ADDR_FAM_INET6;
  }
  return NET_ADDR_FAM_UNKNOWN;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PUBLIC //////////////////////////////////////  OUTPUT FORMATTERS  //////////////////////////////////////////////////
/**
 * @brief
 * 
 * @return
 */
[[nodiscard]] std::string InternetAddress::to_string(void) const {
  std::string result;
  switch (this->get_address_family()) {
    case AF_INET:
      result = this->get_ip() + ':';
    break;
    case AF_INET6:
      result = '[' + this->get_ip() + "]:";
    break;
    default:
      result = "Invalid_IP(" + this->get_ip() + "):";
    break;
  }
  result += this->has_valid_port() ? std::to_string(this->get_port())
                                   : "Invalid_Port(" + std::to_string(this->get_port()) + ")";
  return result;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PUBLIC //////////////////////////////////////       OPERATORS     //////////////////////////////////////////////////
/**
 * @brief Copy assignment operator
 * 
 * @param iOther
 * 
 * @return
 */
InternetAddress& InternetAddress::operator=(const InternetAddress& iOther) {
  if (this != &iOther) {
    this->set_ip(iOther.get_ip());
    this->set_port(iOther.get_port());
  }
  return *this;
}

/**
 * @brief Move assignment operator
 * 
 * @param iOther
 * 
 * @return
 */
InternetAddress& InternetAddress::operator=(InternetAddress&& iOther) noexcept {
  if (this != &iOther) {
    this->set_ip(std::move(iOther.get_ip()));
    this->set_port(iOther.get_port());
    iOther.clear();
  }
  return *this;
}

/**
 * @brief
 * 
 * @param iOther
 * 
 * @return
 */
[[nodiscard]] bool InternetAddress::operator==(const InternetAddress& iOther) const {
  if (this == &iOther) {return true;}
  return (this->get_ip() == iOther.get_ip()) && (this->get_port() == iOther.get_port());
}

/**
 * @brief
 * 
 * @param iOther
 * 
 * @return
 */
[[nodiscard]] bool InternetAddress::operator!=(const InternetAddress& iOther) const {
  if (this == &iOther) {return false;}
  return (this->get_ip() != iOther.get_ip()) || (this->get_port() != iOther.get_port());
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PUBLIC ///////////////////////////////////////  FRIEND FUNCTIONS  //////////////////////////////////////////////////
/**
 * @brief
 * 
 * @param oStream
 * @param iOther
 * 
 * @return
 */
std::ostream& operator<<(std::ostream& oStream, const InternetAddress& iOther) {
  oStream << iOther.to_string();
  return oStream;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PUBLIC //////////////////////////////////////     DESTRUCTORS     //////////////////////////////////////////////////
/**
 * @brief
 */
InternetAddress::~InternetAddress() {}
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
      "^((" // Start of pattern
      "([0-9A-Fa-f]{1,4}:){7}([0-9A-Fa-f]{1,4})" // Uncompressed

      // Compressed with various positions for ::
      "|(([0-9A-Fa-f]{1,4}:){1,7}:)"                    
      "|(:([0-9A-Fa-f]{1,4}:){1,7})"
      "|(([0-9A-Fa-f]{1,4}:){1,6}:([0-9A-Fa-f]{1,4}))" // Improved pattern for middle compression
      "|(::([0-9A-Fa-f]{1,4}:){1,5})"
      "|(:{2}([0-9A-Fa-f]{1,4}:){1,4})"
      "|(:{2}([0-9A-Fa-f]{1,4}:){1,3})"
      "|(:{2}([0-9A-Fa-f]{1,4}:){1,2})"
      "|(:{2}([0-9A-Fa-f]{1,4}:){1})"
      "|(:{2}([0-9A-Fa-f]{1,4}){1})"
      "|(:{2})"

      // Loopback, unspecified addresses
      "|(::1)"
      "|(::)"
      "|([0:0:0:0:0:0:0:1])" // Full loopback address

      ")$)"
  );
  return std::regex_match(this->get_ip(), IPV6_PATTERN);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PRIVATE /////////////////////////////////////  SETTERS & GETTERS  //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PRIVATE /////////////////////////////////////  OUTPUT FORMATTERS  //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PRIVATE /////////////////////////////////////       OPERATORS     //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PRIVATE /////////////////////////////////////     DESTRUCTORS     //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


} // namespace addr
} // namespace ncs
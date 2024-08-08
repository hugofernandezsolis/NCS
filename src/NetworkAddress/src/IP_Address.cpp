/**
 * @copyright Copyright (c) 2023
 * 
 * @author Hugo Fernandez Solis (hugofernandezsolis@gmail.com)
 * @date 08-08-2024
 * 
 * @file IP_Address.cpp
 * 
 * @brief 
 */


#include <IP_Address.h>


namespace ncs { // Network Communications System
namespace addr { // Network Communications System Addresses


/**
 * @brief Set the port object
 * 
 * @param iPort 
 */
void IP_Address::set_port(const int& iPort) {
  this->port_ = iPort;
}

/**
 * @brief Set the ip object
 * 
 * @param iIp 
 */
void IP_Address::set_ip(const ip_t& iIp) {
  this->ip_ = iIp;
}

/**
 * @brief Get the port object
 * 
 * @return int& 
 */
[[nodiscard]] int& IP_Address::get_port(void) {
  return this->port_;
}

/**
 * @brief Get the ip object
 * 
 * @return ip_t& 
 */
[[nodiscard]] ip_t& IP_Address::get_ip(void) {
  return this->ip_;
}

/**
 * @brief Get the port object
 * 
 * @return const int& 
 */
[[nodiscard]] const int& IP_Address::get_port(void) const {
  return this->port_;
}

/**
 * @brief Get the ip object
 * 
 * @return const ip_t& 
 */
[[nodiscard]] const ip_t& IP_Address::get_ip(void) const {
  return this->ip_;
}

/**
 * @brief 
 * 
 * @return std::string 
 */
[[nodiscard]] std::string IP_Address::to_string(void) const {
  return this->get_ip() + ':' + std::to_string(this->get_port());
}

/**
 * @brief Destroy the IP_Address object
 */
IP_Address::~IP_Address() {}

/**
 * @brief Construct a new IP_Address object
 */
IP_Address::IP_Address(const int& iPort, const ip_t& iIp_) {
  this->set_port(iPort);
  this->set_ip(iIp_);
}


} // namespace addr
} // namespace ncs
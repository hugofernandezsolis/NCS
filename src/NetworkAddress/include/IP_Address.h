/**
 * @copyright Copyright (c) 2023
 * 
 * @author Hugo Fernandez Solis (hugofernandezsolis@gmail.com)
 * @date 08-08-2024
 * 
 * @file IP_Address.h
 * 
 * @brief 
 */


#ifndef NCS_IP_ADDRESS_H
#define NCS_IP_ADDRESS_H


#include <string>


namespace ncs { // Network Communications System
namespace addr { // Network Communications System Addresses

/**
 * IP_Address types
 */
using ip_t    = std::string;    // IP Address
using port_t  = int;            // Connection port

/**
 * IP_Address constants
 */
constexpr char LOCAL_IP[]   = "127.0.0.1";      // Use for local communication in the machine
constexpr char INVALID_IP[] =   "0.0.0.0";      // Use to set an invalid IP

constexpr port_t RANDOM_PORT  =  0;     // Use to allow the machine to select the port
constexpr port_t INVALID_PORT = -1;     // Use to set an invalid port


/**
 * @brief 
 */
class IP_Address {
  public:

    /**
     * @brief Set the port object
     * 
     * @param iPort 
     */
    void set_port(const int& iPort);

    /**
     * @brief Set the ip object
     * 
     * @param iIp 
     */
    void set_ip(const ip_t& iIp);
    
    /**
     * @brief Get the port object
     * 
     * @return int& 
     */
    [[nodiscard]] int& get_port(void);

    /**
     * @brief Get the ip object
     * 
     * @return ip_t& 
     */
    [[nodiscard]] ip_t& get_ip(void);

    /**
     * @brief Get the port object
     * 
     * @return const int& 
     */
    [[nodiscard]] const int& get_port(void) const;

    /**
     * @brief Get the ip object
     * 
     * @return const ip_t& 
     */
    [[nodiscard]] const ip_t& get_ip(void) const;

    /**
     * @brief 
     * 
     * @return std::string 
     */
    [[nodiscard]] std::string to_string(void) const;

    /**
     * @brief 
     * 
     * @return 
     */
    [[nodiscard]] virtual bool is_valid(void) const = 0;

    /**
     * @brief Destroy the IP_Address object
     */
    virtual ~IP_Address();
  
  protected:
    /**
     * @brief Construct a new IP_Address object
     */
    IP_Address(const int& iPort, const ip_t& iIp_);
  
  private:
    int port_;    // Port
    ip_t ip_;     // IP Address

};


} // namespace addr
} // namespace ncs


#endif // NCS_NETWORK_ADDRESS_H

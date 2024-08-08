/**
 * @copyright Copyright (c) 2023
 * 
 * @author Hugo Fernandez Solis (hugofernandezsolis@gmail.com)
 * @date 08-08-2024
 * 
 * @file NetworkAddress.h
 * 
 * @brief 
 */


#ifndef NCS_NETWORK_ADDRESS_H
#define NCS_NETWORK_ADDRESS_H


namespace ncs { // Network Communications System
namespace addr { // Network Communications System Addresses


/**
 * @brief 
 */
class NetworkAddress {
  public:
    /**
     * @brief Destroy the NetworkAddress object
     */
    virtual ~NetworkAddress();
  
  protected:
    /**
     * @brief Construct a new NetworkAddress object
     */
    NetworkAddress(void);
};


} // namespace addr
} // namespace ncs


#endif // NCS_NETWORK_ADDRESS_H

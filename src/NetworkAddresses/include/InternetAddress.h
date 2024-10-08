/**
 * @copyright Copyright (c) 2023
 * 
 * @author Hugo Fernandez Solis (hugofernandezsolis@gmail.com)
 * @date 08-08-2024
 * 
 * @file InternetAddress.h
 * 
 * @brief
 */


#ifndef NC_INTERNET_ADDRESS_H
#define NC_INTERNET_ADDRESS_H


#include <string>

#include <NetworkAddress.h>


namespace ncs { // Network Communications System
namespace addr { // Network Communications System Addresses

/**
 * InternetAddress types
 */
using ip_t    = std::string;    // IP Address
using port_t  = int;            // Connection port

/**
 * InternetAddress constants
 */
constexpr char LOCAL_HOST[] = "localhost";      // Use for local communication in the machine

constexpr port_t RANDOM_PORT =  0;     // Use to allow the machine to select the port

constexpr port_t MIN_VALID_PORT =  1023;     // Use to set the minimum valid port value
constexpr port_t MAX_VALID_PORT = 65535;     // Use to set the maximum valid port value


/**
 * @brief
 */
class InternetAddress : NetworkAddress {
public:
/// PUBLIC //////////////////////////////////////     CONSTRUCTORS    //////////////////////////////////////////////////
  /**
   * @brief Default constructor
   */
  InternetAddress(void);

  /**
   * @brief
   * 
   * @param iPort 
   * @param iIp_
   */
  InternetAddress(const ip_t& iIp, const port_t& iPort);

  /**
   * @brief Copy constructor
   * 
   * @param iOther 
   */
  InternetAddress(const InternetAddress& iOther);

  /**
   * @brief Move constructor
   * 
   * @param iOther 
   */
  InternetAddress(InternetAddress&& iOther) noexcept;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PUBLIC //////////////////////////////////////    CLASS METHODS    //////////////////////////////////////////////////
  /**
   * @brief
   * 
   * @return
   */
  [[nodiscard]] bool is_valid(void) const;

  /**
   * @brief
   * 
   * @return
   */
  [[nodiscard]] bool has_valid_ip(void) const;

  /**
   * @brief
   * 
   * @return
   */
  [[nodiscard]] bool has_valid_port(void) const;

  /**
   * @brief
   */
   void clear(void);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PUBLIC //////////////////////////////////////  SETTERS & GETTERS  //////////////////////////////////////////////////
  /**
   * @brief
   * 
   * @param iIp 
   */
  void set_ip(const ip_t& iIp);

  /**
   * @brief
   * 
   * @param iPort 
   */
  void set_port(const port_t& iPort);
  
  /**
   * @brief
   * 
   * @return
   */
  [[nodiscard]] const ip_t& get_ip(void) const;

  /**
   * @brief
   * 
   * @return
   */
  [[nodiscard]] const port_t& get_port(void) const;

  /**
   * @brief
   * 
   * @return
   */
  [[nodiscard]] addr_family_e get_address_family(void) const;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PUBLIC //////////////////////////////////////  OUTPUT FORMATTERS  //////////////////////////////////////////////////
  /**
   * @brief
   * 
   * @return
   */
  [[nodiscard]] std::string to_string(void) const;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PUBLIC //////////////////////////////////////       OPERATORS     //////////////////////////////////////////////////
  /**
   * @brief Copy assignment operator
   * 
   * @param iOther
   * 
   * @return
   */
  InternetAddress& operator=(const InternetAddress& iOther);

  /**
   * @brief Move assignment operator
   * 
   * @param iOther
   * 
   * @return
   */
  InternetAddress& operator=(InternetAddress&& iOther) noexcept;

  /**
   * @brief
   * 
   * @param iOther
   * 
   * @return
   */
  [[nodiscard]] bool operator==(const InternetAddress& iOther) const;

  /**
   * @brief
   * 
   * @param iOther
   * 
   * @return
   */
  [[nodiscard]] bool operator!=(const InternetAddress& iOther) const;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PUBLIC ///////////////////////////////////////  FRIEND FUNCTIONS  //////////////////////////////////////////////////
  /**
   * @brief
   * 
   * @param oStream 
   * @param iInternetAddr
   * 
   * @return
   */
  friend std::ostream& operator<<(std::ostream& oStream, const InternetAddress& iInternetAddr);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PUBLIC //////////////////////////////////////     DESTRUCTORS     //////////////////////////////////////////////////
  /**
   * @brief Destructor
   */
  ~InternetAddress();
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  

protected:
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
  

private:
/// PRIVATE /////////////////////////////////////     CONSTRUCTORS    //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PRIVATE /////////////////////////////////////    CLASS METHODS    //////////////////////////////////////////////////
  /**
   * @brief
   * 
   * @return
   */
  [[nodiscard]] bool has_valid_v4_ip(void) const;


  /**
   * @brief
   * 
   * @return
   */
  [[nodiscard]] bool has_valid_v6_ip(void) const;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PRIVATE /////////////////////////////////////  SETTERS & GETTERS  //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PRIVATE /////////////////////////////////////  OUTPUT FORMATTERS  //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PRIVATE /////////////////////////////////////       OPERATORS     //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// PRIVATE /////////////////////////////////////     DESTRUCTORS     //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  

private:
  ip_t ip_;
  port_t port_;
};


} // namespace addr
} // namespace ncs


#endif // NC_INTERNET_ADDRESS_H

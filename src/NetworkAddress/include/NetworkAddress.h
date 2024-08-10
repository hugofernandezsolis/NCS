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


#include <sys/socket.h>

namespace ncs { // Network Communications System
namespace addr { // Network Communications System Addresses


/**
 * NetworkAddress types
 */
enum addr_family_e {
  ERROR_FAMILY      = -1,
  UNSPEC_FAMILY     = AF_UNSPEC,
  LOCAL_FAMILY      = AF_LOCAL,
  UNIX_FAMILY       = AF_UNIX,
  FILE_FAMILY       = AF_FILE,
  IPV4_FAMILY       = AF_INET,
  AX25_FAMILY       = AF_AX25,
  IPX_FAMILY        = AF_IPX,
  APPLETALK_FAMILY  = AF_APPLETALK,
  NETROM_FAMILY     = AF_NETROM,
  BRIDGE_FAMILY     = AF_BRIDGE,
  ATMPVC_FAMILY     = AF_ATMPVC,
  X25_FAMILY        = AF_X25,
  IPV6_FAMILY       = AF_INET6,
  ROSE_FAMILY       = AF_ROSE,
  DECNET_FAMILY     = AF_DECnet,
  NETBEUI_FAMILY    = AF_NETBEUI,
  SECURITY_FAMILY   = AF_SECURITY,
  KEY_FAMILY        = AF_KEY,
  NETLINK_FAMILY    = AF_NETLINK,
  ROUTE_FAMILY      = AF_ROUTE,
  PACKET_FAMILY     = AF_PACKET,
  ASH_FAMILY        = AF_ASH,
  ECONET_FAMILY     = AF_ECONET,
  ATMSVC_FAMILY     = AF_ATMSVC,
  RDS_FAMILY        = AF_RDS,
  SNA_FAMILY        = AF_SNA,
  IRDA_FAMILY       = AF_IRDA,
  PPPOX_FAMILY      = AF_PPPOX,
  WANPIPE_FAMILY    = AF_WANPIPE,
  LLC_FAMILY        = AF_LLC,
  IB_FAMILY         = AF_IB,
  MPLS_FAMILY       = AF_MPLS,
  CAN_FAMILY        = AF_CAN,
  TIPC_FAMILY       = AF_TIPC,
  BLUETOOTH_FAMILY  = AF_BLUETOOTH,
  IUCV_FAMILY       = AF_IUCV,
  RXRPC_FAMILY      = AF_RXRPC,
  ISDN_FAMILY       = AF_ISDN,
  PHONET_FAMILY     = AF_PHONET,
  IEEE802154_FAMILY = AF_IEEE802154,
  CAIF_FAMILY       = AF_CAIF,
  ALG_FAMILY        = AF_ALG,
  NFC_FAMILY        = AF_NFC,
  VSOCK_FAMILY      = AF_VSOCK,
  KCM_FAMILY        = AF_KCM,
  QIPCRTR_FAMILY    = AF_QIPCRTR,
  SMC_FAMILY        = AF_SMC,
  XDP_FAMILY        = AF_XDP,
  MCTP_FAMILY       = AF_MCTP,
  MAX_FAMILY        = AF_MAX
};


/**
 * @brief 
 */
class NetworkAddress {
  public:
  /**
   * @brief
   * 
   * @return
   */
  [[nodiscard]] virtual addr_family_e address_family(void) const = 0;

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

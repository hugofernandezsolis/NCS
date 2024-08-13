/**
 * @copyright Copyright (c) 2023
 * 
 * @author Hugo Fernandez Solis (hugofernandezsolis@gmail.com)
 * @date 08-08-2024
 * 
 * @file InternetAddress_tests.h
 * 
 * @brief
 */


#include <InternetAddressTest.h>

#include <gtest/gtest.h>

#include <map>
#include <random>
#include <array>


namespace ncs::addr {
namespace tests {


/**
 * @brief
 */
TEST_F(InternetAddressTest, Default_Constructor) {
  InternetAddress addr;
  EXPECT_FALSE(addr.is_valid());
  EXPECT_FALSE(addr.has_valid_ip());
  EXPECT_FALSE(addr.has_valid_port());
  EXPECT_EQ   (addr.address_family(), ERROR_FAMILY);
}

/**
 * @brief
 */
TEST_F(InternetAddressTest, Ip_And_Port_Constructor) {
}

/**
 * @brief
 */
TEST_F(InternetAddressTest, Copy_Constructor) {
  InternetAddress addr = defaultAddr_;
  EXPECT_EQ(addr, defaultAddr_);
}

/**
 * @brief
 */
TEST_F(InternetAddressTest, Move_Constructor) {
  InternetAddress copy = defaultAddr_;
  InternetAddress addr(std::move(copy));
  EXPECT_NE(addr, copy);
  EXPECT_EQ(addr, defaultAddr_);
}

/**
 * @brief
 */
TEST_F(InternetAddressTest, Check_Validity) {
  std::map<std::string, InternetAddress> ipv4;
  std::map<std::string, InternetAddress> ipv6;

  const std::string VALID_ADDRESS =   "VALID_ADDRESS";
  const std::string INVALID_IP =      "INVALID_IP";
  const std::string INVALID_PORT =    "INVALID_PORT";
  const std::string INVALID_ADDRESS = "INVALID_ADDRESS";

  ipv4.insert({VALID_ADDRESS,   {generate_ipv4(true),  get_random_number(MIN_VALID_PORT, MAX_VALID_PORT)}});
  ipv4.insert({INVALID_IP,      {generate_ipv4(false), get_random_number(MIN_VALID_PORT, MAX_VALID_PORT)}});
  ipv4.insert({INVALID_PORT,    {generate_ipv4(true),  get_random_number(0 - MAX_VALID_PORT, MIN_VALID_PORT - 1)}});
  ipv4.insert({INVALID_ADDRESS, {generate_ipv4(false), get_random_number(0 - MAX_VALID_PORT, MIN_VALID_PORT - 1)}});

  ipv6.insert({VALID_ADDRESS,   {generate_ipv6(true),  get_random_number(MIN_VALID_PORT, MAX_VALID_PORT)}});
  ipv6.insert({INVALID_IP,      {generate_ipv6(false), get_random_number(MIN_VALID_PORT, MAX_VALID_PORT)}});
  ipv6.insert({INVALID_PORT,    {generate_ipv6(true),  get_random_number(0 - MAX_VALID_PORT, MIN_VALID_PORT - 1)}});
  ipv6.insert({INVALID_ADDRESS, {generate_ipv6(false), get_random_number(0 - MAX_VALID_PORT, MIN_VALID_PORT - 1)}});
  // Ipv4 Valid Address
  EXPECT_TRUE(ipv4[VALID_ADDRESS].is_valid());
  EXPECT_TRUE(ipv4[VALID_ADDRESS].has_valid_ip());
  EXPECT_TRUE(ipv4[VALID_ADDRESS].has_valid_port());
  EXPECT_EQ  (ipv4[VALID_ADDRESS].address_family(), IPV4_FAMILY);
  
  // Ipv4 Invalid Ip
  EXPECT_FALSE(ipv4[INVALID_IP].is_valid());
  EXPECT_FALSE(ipv4[INVALID_IP].has_valid_ip());
  EXPECT_TRUE (ipv4[INVALID_IP].has_valid_port());
  EXPECT_EQ   (ipv4[INVALID_IP].address_family(), ERROR_FAMILY);
  
  // Ipv4 Invalid Port
  EXPECT_FALSE(ipv4[INVALID_PORT].is_valid());
  EXPECT_TRUE (ipv4[INVALID_PORT].has_valid_ip());
  EXPECT_FALSE(ipv4[INVALID_PORT].has_valid_port());
  EXPECT_EQ   (ipv4[INVALID_PORT].address_family(), IPV4_FAMILY);
  
  // Ipv4 Invalid Address
  EXPECT_FALSE(ipv4[INVALID_ADDRESS].is_valid());
  EXPECT_FALSE(ipv4[INVALID_ADDRESS].has_valid_ip());
  EXPECT_FALSE(ipv4[INVALID_ADDRESS].has_valid_port());
  EXPECT_EQ   (ipv4[INVALID_ADDRESS].address_family(), ERROR_FAMILY);

  // Ipv6 Valid Address
  EXPECT_TRUE(ipv6[VALID_ADDRESS].is_valid());
  EXPECT_TRUE(ipv6[VALID_ADDRESS].has_valid_ip());
  EXPECT_TRUE(ipv6[VALID_ADDRESS].has_valid_port());
  EXPECT_EQ  (ipv6[VALID_ADDRESS].address_family(), IPV6_FAMILY);
  
  // Ipv6 Invalid Ip
  EXPECT_FALSE(ipv6[INVALID_IP].is_valid());
  EXPECT_FALSE(ipv6[INVALID_IP].has_valid_ip());
  EXPECT_TRUE (ipv6[INVALID_IP].has_valid_port());
  EXPECT_EQ   (ipv6[INVALID_IP].address_family(), ERROR_FAMILY);
  
  // Ipv6 Invalid Port
  EXPECT_FALSE(ipv6[INVALID_PORT].is_valid());
  EXPECT_TRUE (ipv6[INVALID_PORT].has_valid_ip());
  EXPECT_FALSE(ipv6[INVALID_PORT].has_valid_port());
  EXPECT_EQ   (ipv6[INVALID_PORT].address_family(), IPV6_FAMILY);
  
  // Ipv6 Invalid Address
  EXPECT_FALSE(ipv6[INVALID_ADDRESS].is_valid());
  EXPECT_FALSE(ipv6[INVALID_ADDRESS].has_valid_ip());
  EXPECT_FALSE(ipv6[INVALID_ADDRESS].has_valid_port());
  EXPECT_EQ   (ipv6[INVALID_ADDRESS].address_family(), ERROR_FAMILY);
}

/**
 * @brief
 */
TEST_F(InternetAddressTest, Address_Family) {
  EXPECT_EQ(defaultAddr_.address_family(), defaultFamily_);
}

/**
 * @brief
 */
TEST_F(InternetAddressTest, Clear) {
  defaultAddr_.clear();
  EXPECT_FALSE(defaultAddr_.is_valid());
  EXPECT_FALSE(defaultAddr_.has_valid_ip());
  EXPECT_FALSE(defaultAddr_.has_valid_port());
  EXPECT_EQ   (defaultAddr_.address_family(), ERROR_FAMILY);
}

/**
 * @brief
 */
TEST_F(InternetAddressTest, Setters_And_Getters) {
  EXPECT_EQ(defaultAddr_.get_ip(), defaultIp_);
  EXPECT_EQ(defaultAddr_.get_port(), defaultPort_);

  addr_family_e newFamily = get_random_number(0, 1) ? IPV4_FAMILY : IPV6_FAMILY;
  ip_t newIp = newFamily == IPV4_FAMILY ? generate_ipv4(true) : generate_ipv6(true);
  port_t newPort = get_random_number(MIN_VALID_PORT, MAX_VALID_PORT);

  defaultAddr_.set_ip(newIp);
  EXPECT_EQ(defaultAddr_.get_ip(), newIp);
  EXPECT_EQ(defaultAddr_.address_family(), newFamily);

  defaultAddr_.set_port(newPort);
  EXPECT_EQ(defaultAddr_.get_port(), newPort);
}

/**
 * @brief
 */
TEST_F(InternetAddressTest, Assignment_Operators) {
  InternetAddress aux;
  aux = defaultAddr_;
  EXPECT_EQ(aux, defaultAddr_);

  InternetAddress aux2 = defaultAddr_;
  aux = std::move(defaultAddr_);
  EXPECT_NE(aux, defaultAddr_);
  EXPECT_EQ(aux, aux2);
}

/**
 * @brief
 */
TEST_F(InternetAddressTest, Comparison_Operators) {
  InternetAddress auxiliaryIpAddr1(defaultAddr_.get_ip(), defaultAddr_.get_port());
  EXPECT_EQ(auxiliaryIpAddr1, defaultAddr_);

  auxiliaryIpAddr1.set_port((auxiliaryIpAddr1.get_port() + 1) % MAX_VALID_PORT);
  EXPECT_NE(auxiliaryIpAddr1, defaultAddr_);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


} // namespace tests
} // namespace ncs::addr
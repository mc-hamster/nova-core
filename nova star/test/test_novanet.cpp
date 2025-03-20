#include <unity.h>
#include "NovaNet.h"
#include "messaging.pb.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_crc16_ccitt_calculation() {
    NovaNet net;
    const uint8_t testData[] = {0x01, 0x02, 0x03, 0x04};
    uint16_t crc = net.crc16_ccitt(testData, sizeof(testData));
    
    // Test with known good CRC value
    // You'll need to replace this with the actual expected CRC
    uint16_t expectedCrc = 0x89C3;  // Example value
    TEST_ASSERT_EQUAL_HEX16(expectedCrc, crc);
}

void test_message_header_validation() {
    NovaNet net;
    uint8_t validHeader[] = {0xF0, 0x9F, 0x92, 0xA5}; // "fire" emoji header
    uint8_t invalidHeader[] = {0x00, 0x00, 0x00, 0x00};
    
    // Test valid header
    TEST_ASSERT_TRUE(net.validateHeader(validHeader));
    
    // Test invalid header
    TEST_ASSERT_FALSE(net.validateHeader(invalidHeader));
}

int main() {
    UNITY_BEGIN();
    
    RUN_TEST(test_crc16_ccitt_calculation);
    RUN_TEST(test_message_header_validation);
    
    return UNITY_END();
}
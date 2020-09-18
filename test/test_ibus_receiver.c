#include "unity.h"
#include "ibus_receiver.h"
ibus_receiver ibus_rec;
uint32_t channels = 6;
uint32_t channel_length = 14;
uint8_t valid_ibus_packet[14] = {0x20, 0x40, 0x10, 0x10,
                                 0x20, 0x20, 0x10, 0x10,
                                 0x10, 0x10, 0x10, 0x10, 0x10, 0x10};

uint8_t stub_read_byte()
{
    static uint32_t counter = 0;

    if (counter > channel_length)
    {
        {
            counter = 0;
        }
    }
    uint8_t value_to_return = valid_ibus_packet[counter];
    counter++;
    return value_to_return;
}
void setUp(void)
{
    ibus_rec = ibus_receiver_create(channels);
}

void tearDown(void)
{
}

void test_ibus_receiver_get_channel_value(void)
{
    while (!ibus_receiver_is_new_frame_avaible(ibus_rec))
    {
        uint8_t value = stub_read_byte();
        ibus_receiver_set_new_received_value(ibus_rec, value);
    }
    uint16_t actual_channel_value = ibus_receiver_get_channel_value(ibus_rec, 1);
    uint16_t expected_channel_value = (0x10 << 8) + (0x10);
    TEST_ASSERT_EQUAL_UINT32(expected_channel_value, actual_channel_value);
}

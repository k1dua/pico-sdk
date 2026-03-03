#include "pico/stdlib.h"
#include "bsp/board.h"
#include "tusb.h"
#include <string.h>

void tuh_hid_mount_cb(uint8_t dev_addr,
                      uint8_t instance,
                      uint8_t const* desc_report,
                      uint16_t desc_len)
{
    // Force boot protocol for keyboard (8-byte reports)
    tuh_hid_set_protocol(dev_addr, instance, HID_PROTOCOL_BOOT);

    // Start receiving reports
    tuh_hid_receive_report(dev_addr, instance);
}

void tuh_hid_umount_cb(uint8_t dev_addr, uint8_t instance)
{
    // Device unplugged
}

void tuh_hid_keyboard_report_cb(uint8_t dev_addr,
                                uint8_t instance,
                                uint8_t const* report,
                                uint16_t len)
{
    if (len < 8) return;

    uint8_t modifier = report[0];
    uint8_t keycodes[6];
    memcpy(keycodes, &report[2], 6);

    if (tud_hid_ready())
    {
        tud_hid_keyboard_report(0, modifier, keycodes);
    }

    // Request next report
    tuh_hid_receive_report(dev_addr, instance);
}

int main(void)
{
    board_init();
    tusb_init();

    while (1)
    {
        tuh_task();  // USB Host task
        tud_task();  // USB Device task
    }
}
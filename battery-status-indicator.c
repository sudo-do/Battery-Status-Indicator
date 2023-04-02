#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#include <unistd.h>

#include <fcntl.h>

#include <syslog.h>

#include <linux/input.h>

#define BATTERY_STATUS_FILE "/sys/class/power_supply/BAT0/capacity"

#define KEYBOARD_DEVICE_FILE "/dev/input/event0"

#define KEYBOARD_LED_IOCTL 0x4B32

#define LED_CAPSL 0x01

#define LED_NUML 0x02

#define LED_SCROLLL 0x04

int read_battery_status() {

    int battery_status_file = open(BATTERY_STATUS_FILE, O_RDONLY);

    if (battery_status_file == -1) {

        syslog(LOG_ERR, "Error opening battery status file.");

        exit(EXIT_FAILURE);

    }

    char battery_status[4];

    if (read(battery_status_file, battery_status, sizeof(battery_status)) == -1) {

        syslog(LOG_ERR, "Error reading battery status file.");

        exit(EXIT_FAILURE);

    }

    close(battery_status_file);

    return atoi(battery_status);

}

void set_keyboard_leds(bool caps_lock, bool num_lock, bool scroll_lock) {

    struct input_event ie;

    int keyboard_device_file = open(KEYBOARD_DEVICE_FILE, O_WRONLY);

    if (keyboard_device_file == -1) {

        syslog(LOG_ERR, "Error opening keyboard device file.");

        exit(EXIT_FAILURE);

    }

    if (ioctl(keyboard_device_file, EVIOCGNAME(sizeof(ie)), &ie) == -1) {

        syslog(LOG_ERR, "Error getting keyboard device name.");

        exit(EXIT_FAILURE);

    }

    ie.type = EV_LED;

    ie.code = LED_CAPSL;

    ie.value = caps_lock ? 1 : 0;

    if (write(keyboard_device_file, &ie, sizeof(ie)) == -1) {

        syslog(LOG_ERR, "Error writing caps lock led value.");

        exit(EXIT_FAILURE);

    }

    ie.code = LED_NUML;

    ie.value = num_lock ? 1 : 0;

    if (write(keyboard_device_file, &ie, sizeof(ie)) == -1) {

        syslog(LOG_ERR, "Error writing num lock led value.");

        exit(EXIT_FAILURE);

    }

    ie.code = LED_SCROLLL;

    ie.value = scroll_lock ? 1 : 0;

    if (write(keyboard_device_file, &ie, sizeof(ie)) == -1) {

        syslog(LOG_ERR, "Error writing scroll lock led value.");

        exit(EXIT_FAILURE);

    }

    close(keyboard_device_file);

}

int main() {

    openlog("battery-status-indicator", LOG_PID | LOG_CONS, LOG_USER);

    syslog(LOG_INFO, "Battery status indicator started.");

    while (true) {

        int battery_status = read_battery_status();

        if (battery_status >= 75) {

            set_keyboard_leds(true, false, false);

            syslog(LOG_INFO, "Battery status: over 75%% (%d). Caps Lock LED turned on.", battery_status);

        } else if (battery_status >= 50) {

            set_keyboard_leds(false, true, false);

            syslog(LOG_INFO, "Battery status: over 50%% (%d). Num Lock LED turned on.", battery_status);

        } else if (battery_status >= 25) {

            set_keyboard_leds(false, false, true);

            syslog(LOG_INFO, "Battery status: over 25%% (%d). Scroll Lock LED turned on.", battery_status);

        } else {

            set_keyboard_leds(false, false, false);

            syslog(LOG_INFO, "Battery status:        25%% or below (%d). All LED lights turned off.", battery_status);

    }

    sleep(60);

}

closelog();

return 0;

}

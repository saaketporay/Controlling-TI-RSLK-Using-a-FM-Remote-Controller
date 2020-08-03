#ifndef WIFI_REMOTE_H
#define WIFI_REMOTE_H

// Core library for code-sense - IDE-based
#include <Energia.h>
#include <WiFi.h>

void custom_logic();
void wifi_setup();
void wifiLoop();

extern bool left_button_pressed;
extern bool right_button_pressed;
extern bool up_button_pressed;
extern bool down_button_pressed;
extern bool up_down_pressed;
#endif
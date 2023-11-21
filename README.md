# Xiao Round TFT Display Swatch Internet Hour
Internet hour was a concept created by Charly Alberti, Soda Stereo drummer, in 1998. Some months later, Swatch company released the same idea with a series of watches displaying time in Beats.
This clock calculates beats using a formula to display Internet Time.

# Parts required 

Seeed Studio Xiao nrf52840
Seeed Studio Xiao TFT Round Display
Helping Hands Soldering Station with 3X Magnifying Glass

# Libraries

TFT_eSPI by Bodmer
I2C BM8563 RTC by tanaka
LVGL
https://github.com/Seeed-Studio/Seeed_Arduino_RoundDisplay

# Round Display library configuration

Cut lv_conf.h from Seeed_Arduino_RoundDisplay and paste into libraries root
Open User_Setup_Select.h and uncomment #include <User_Setups/Setup66_Seeed_XIAO_Round.h>  // Setup file for Seeed XIAO with GC9A01 240x240

# Hour configuration

Check UTC +1 hour at https://time.is/UTC+1 
Configure inside .ino code uint8_t h = 13, m = 44, s = 40; before uploading.

# Demo

https://www.youtube.com/watch?v=FyPsmtE1eLw


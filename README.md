# ESP-Wifi-AP-Neopixel-Control

The files in this repository should work for setting an ESP first into Access Point (AP) mode and then allowing you to send your SSID
and password to the ESP and then flip it to be a clinet and connect your chosen network. Once connected you should be able to use another
html page to control RGB Lights.

I worked on this a couple years ago so can't remember exactly how it works at this time (but it did work), and haven't had the chance to test it, but I am just posting it in case it may be helpful to someone. If there are any issues chances are low that I will be able to solve them in the near future.

Also note that this is really basic, and probably is not coded by any means in a very good way, but I was new to it at the time and just happy it worked.

# Device
I believe this was done on an ESP-12

# Device Code
Being that I used the Arduino IDE to make this, you will have to do the necessary things to add the ESP-12 as a device to your IDE.
I assume I used something similar to this https://github.com/esp8266/arduino#installing-with-boards-manager and installed it with boards manager.

# HTML Pages
I don't think all the html pages are necessary just the login page and the RGB page. From what I remember the ESP will send a request on power up to tell your computer to open that html file at whatever path you put it at (this needs to be changed in the IDE). I think you have to then open the RGB slider page to control the RGB LEDs

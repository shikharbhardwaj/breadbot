breadbot
========
## TL;DR
Simple **Arduino** based robot on a breadboard.

## This is..
the code repository for the BreadBot project I undertook for designing a **barebones** "robot" that's controlled by an IR remote that usually controls your TV.

Simple wiring digrams will be up soon.

## Technical
The code used here uses a simple function to retrieve the data sent by a Samsung remote. However, if you want to support a variety of manufacturers and makes, take a look at the excellent [IR remote library](http://www.righto.com/2009/08/multi-protocol-infrared-remote-library.html) by Ken Shirriff. I did not use it because it was marginally oversize for the ATmega-8L 8PU.

I eventually ran this code on an ATmega-16L 16PU

If you want some help regarding setting up an Arduino on a breadboard, read the excellent [tutorial](http://arduino.cc/en/Main/Standalone) at the Arduino website.

## Compatibility
The code provided here is compatible with **ATmega-8L 8PU** running a `12Mhz` clock. Should be fine with higher MCs too. Compiled and running under **Arduino v1.0.5**.

## Configuration
The `config` folder contains the boards.txt file that needs to be patched to program the 
AVR on the breadboard. Feel free to tinker with the settings to suit your configuration. The programmer I used was based on the [USBasp](http://www.fischl.de/usbasp/).

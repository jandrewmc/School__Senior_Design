# SeniorDesign


# Important Software:

Raspberry Pi Operating System (Currently using Raspbian Jesse):
https://www.raspberrypi.org/downloads/raspbian/

For Prepping the SD Card for the Raspberry Pi:
https://www.sdcard.org/downloads/formatter_4/

For burning the OS image to the SD Card:

Mac:
http://www.tweaking4all.com/hardware/raspberry-pi/macosx-apple-pi-baker/

Windows:
http://sourceforge.net/projects/win32diskimager/


# Important Websites:


VNC Viewer for remote access:
https://www.realvnc.com/

Setup RF24Mesh for RPi:
http://tmrh20.github.io/RF24Mesh/Setup-Config.html

# Prepping the Raspberry Pi Model B+:

After installing the OS image to the SD card, place in RPi and boot up.

Step 1: Set up internet access.

Step 2: Go to Menu->Preferences->Mouse and Keyboard Settings.  Select the Keyboard tab.  Click on Keyboard Layout.  Select Unites States.  Select English (US).

Step 3: Run 'sudo raspi-config' from the terminal (leave out the quotation marks) and select "expand file system."

Step 4: Run 'sudo apt-get update' from the terminal.

Step 5: Run 'sudo apt-get upgrade' from the terminal.

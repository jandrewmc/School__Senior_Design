current server vnc access:
jandrewmc.ddns.net::999

current ssh address
jandrewmc.ddns.net
Port: 888

Trello board link:
https://trello.com/b/kzxt0wgR/senior-design-project

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

Step 4: After the reboot, Run 'sudo raspi-config' and select Advanced Options->SPI, Enable SPI Interface and enable the SPI kernel module to be loaded by default.

Step 5: Run the following commands one line at a time from the terminal.

sudo apt-get update

sudo apt-get upgrade

sudo rpi-update

sudo modprobe spi_bcm2835

mkdir temp

cd temp

git clone https://github.com/TMRh20/RF24.git

cd RF24

sudo make install

cd ..

git clone https://github.com/TMRh20/RF24Network.git

cd RF24Network

sudo make install

cd ..

git clone https://github.com/TMRh20/RF24Mesh.git

cd RF24Mesh

sudo make install

cd ..

cd ..

rm -rf temp


Notes 1/5/16:  Need to include sending from the transmitter.

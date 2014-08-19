#    Serial Port emulators used for developing the Robotic Construction Kit 
#    (ROCK) for the BD970 GNSS receiver from Trimble.
#    Copyright (C) 2014  Vassilios Tsounis
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#    
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#    
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#    bd970_run.sh  Copyright (C) 2014  Vassilios Tsounis
#    This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
#    This is free software, and you are welcome to redistribute it
#    under certain conditions; type `show c' for details.


#!/bin/bash


#
# This emulator creates an end-to-end serial port using two virtual tty 
# terminals. They are created in the user's home directory so that sudo will
# not be required to access them.
# 
# NOTE: Remember to build the application first by invoking "amake" in the 
#       ROCK library's directory.
#
# USAGE: 
#   
#   [1]: $ /bd970_emu.sh        # for emualting only the data transmission.
#
#   [2]: $ /bd970_emu.sh +rx    # for emualting both data Tx and Rx.
# 

# Retrieve the home directory
USER_HOME=$(eval echo ~${SUDO_USER})

# Set the desired location for the virtual ttys.
TTY_RX=${USER_HOME}/ttyV0
TTY_TX=${USER_HOME}/ttyV1

# Create the virtual ttys in a gnome terminal
gnome-terminal -e "socat -d -d PTY,raw,echo=0,link=${TTY_RX} PTY,raw,echo=0,link=${TTY_TX}";

# Open the transmitting tty to emualte the bd970
gnome-terminal -e "./bd970_tx.bin ${TTY_TX}";

# If specified at the commandline, also create another listening terminal to 
# verify the transmission of data.

if [ "$1" = "+rx" ];
then 
    gnome-terminal -e "./bd970_rx.bin ${TTY_RX}"
fi;






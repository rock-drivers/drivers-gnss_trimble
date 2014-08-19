/*    Serial Port emulators used for developing the Robotic Construction Kit 
 *    (ROCK) for the BD970 GNSS receiver from Trimble.
 *    Copyright (C) 2014  Javier Hidalgo Carrio
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *    
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *    
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *    serial.h  Copyright (C) 2014  Javier Hidalgo Carrio
 *    This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 *    This is free software, and you are welcome to redistribute it
 *    under certain conditions; type `show c' for details.
 */


/**\file serial.h
* Header function file and defines
*/

#ifndef _SERIAL_H
#define _SERIAL_H


#include <stdio.h>   /**< Standard input/output definitions */
#include <string.h>  /**< String function definitions */
#include <unistd.h>  /**< UNIX standard function definitions */
#include <fcntl.h>   /**< File control definitions */
#include <errno.h>   /**< Error number definitions */
#include <termios.h> /**< POSIX terminal control definitions */
#include <stdlib.h>

#include <signal.h>
#include <time.h>

#include <sys/time.h>
#include <sys/sem.h>
#include <sys/shm.h>


/**
* @brief DEFINES FOR SERIAL LIBRARY
*
* Defines for the serial library
*/
#define OK  0 /**< Integer value in order to return when everything is all right. */
#define ERROR   -1 /**< Integer value in order to return when an error occur. */

#define MESSAGE_NMEA_GGA "$GPGGA,184622.00,0001.123000000,N,00004.56700000,E,0,00,0.0,0.000,M,0.000,M,,*56\r\n"
#define MESSAGE_NMEA_AVR "$PTNL,AVR,184622.00,+1.2345,Yaw,+6.7890,Tilt,,,0.100,0,0.1,01*3C\r\n"
#define MESSAGE_NMEA_HDT "$GPHDT,0,T*4F\r\n"

#define PORT_BD970_USB      "/dev/ttyUSB0"
#define PORT_BD970_EXOTER   "/dev/ttyXR0"


int open_port (char* name);

int init_serial (char *name);

int write_serial(int fd, char* command, int nbytes);

int read_serial(int fd, unsigned char * bufferpr, int nbytes);

int close_port (int fd);

#endif

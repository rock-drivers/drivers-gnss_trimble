/*    Serial Port emulators used for developing the Robotic Construction Kit 
 *    (ROCK) for the BD970 GNSS receiver from Trimble.
 *    Copyright (C) 2014  Vassilios Tsounis
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
 *    main_tx.c  Copyright (C) 2014  Vassilios Tsounis
 *    This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 *    This is free software, and you are welcome to redistribute it
 *    under certain conditions; type `show c' for details.
 */



#include "serial.h"


/** define the messages **/
static char const *message_gga = MESSAGE_NMEA_GGA;
static char const *message_avr = MESSAGE_NMEA_AVR;
static char const *message_hdt = MESSAGE_NMEA_HDT;



int main  (int argc, char **argv)
{
    
    int run_true = 0;
    int number_bytes;
    char buffer[512];

    /* Check inputs parameters */
    if (argc < 2)
    {
        fprintf (stderr, "./bd970_tx <serial_port_path>\n");
        return ERROR;
    }
    
    
    /* Open serial port*/
    printf ("Connecting to serial port [%s].......\r\n", argv[1]);
    
    /* Argv[1]  is the normal "/dev/ttyUSB0" driver description file on Linux system*/
    int fd = init_serial (argv[1]);
    
    if (fd != ERROR)
    {
        /* Print text information confirming that the connection was stabilize */
        printf ("OK.\n");

                while (!run_true)
                {
                    sleep(1.0);
                    
                    strcpy(buffer, (char *)message_gga);
                    write_serial(fd, buffer, strlen(message_gga));
                    
                    strcpy(buffer, (char *)message_avr);
                    write_serial(fd, buffer, strlen(message_avr));
                    
                    strcpy(buffer, (char *)message_hdt);
                    write_serial(fd, buffer, strlen(message_hdt));
                    
                    number_bytes = strlen(message_gga) + strlen(message_avr) + strlen(message_hdt);
                    
                    printf("Wrote nymber_bytes = %d, at: fd (%d) \n", number_bytes, fd);
                    
                    if (number_bytes != ERROR)
                    {
                        fprintf (stdout, "%s%s%s\r\n", message_gga, message_avr, message_hdt);
                    }
                    
                    if (0)
                    {
                        run_true = 1;
                    }                    
                }

                close(fd);

        } //End if of file description (serial port)


    return OK;
}


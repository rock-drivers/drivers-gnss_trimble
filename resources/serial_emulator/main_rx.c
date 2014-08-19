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
 *    main_rx.c  Copyright (C) 2014  Vassilios Tsounis
 *    This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 *    This is free software, and you are welcome to redistribute it
 *    under certain conditions; type `show c' for details.
 */


#include "serial.h"



int main  (int argc, char **argv)
{
    
    int i,j, number_bytes;
    unsigned char buffer[512];

    /* Check inputs parameters */
    if (argc < 2)
    {
        fprintf (stderr, "./bd970_rx <serial_port_path>\n");
        return ERROR;
    }
    
    
    /* Open serial port*/
    printf ("Connecting to BD970_EMU [%s].......", argv[1]);
    
    /* Argv[1]  is the normal "/dev/ttyUSB0" driver description file on Linux system*/
    int fd = init_serial (argv[1]);

    if (fd != ERROR)
    {
        /* Print text information confirming that the connection was stabilize */
        printf ("OK.\n");

        for (i=0; i < 10; ++i)
        {
            sleep(1.0);
            
            number_bytes = read_serial(fd, buffer, 512);
            
            printf("Read %d bytes from fd (%d) \n", number_bytes, fd);

            if (number_bytes != ERROR)
            {
                for (j=0; j < number_bytes; j++)
                {
                    fprintf (stdout, "%c", buffer[j]);
                }
            }
        }
        
        close(fd);

    } //End if of file description (serial port)
    
    

    return OK;
}


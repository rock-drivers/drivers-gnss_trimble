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
 *    serial.c  Copyright (C) 2014  Javier Hidalgo Carrio
 *    This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 *    This is free software, and you are welcome to redistribute it
 *    under certain conditions; type `show c' for details.
 */


#include "serial.h"

/**
* @brief Function to open a serial port connection.
* 
* This function open a serial port. It is used in init_serial
*
* @author Javier Hidalgo Carrio.
* @param[in] name string of path of the serial port file descriptor.
*
* @return Returns the file descriptor on success or -1 on error.
*
*/
int open_port(char * name)
{
    int fd; /**< File descriptor for the port */ 

    fd = open (name, O_RDWR | O_NOCTTY | O_NONBLOCK);
    
    if (fd == ERROR)
    {
        /*
        *  Could not open the port.
        */

        perror("open_port: Unable to open ");
    }
    
    else
    {
         fcntl(fd, F_SETFL, FNDELAY);
    }
    
    return (fd);
}

/**
* @brief Function to initialize a serial port connection.
* 
* This function open and initialize a serial port connection with a fixed
* flag parameters.
*
* @author Javier Hidalgo Carrio.
* @param[in] name string of path of the serial port  file descriptor
*
* @return Returns the file descriptor on success or ERROR on error.
*
*/
int init_serial(char* name)
{

    /****** variables ******/
    int fd = 0;
    struct termios PortSettings;

    
    if ((fd = open_port(name)) != ERROR)
    {

        /** Get the current options for the port **/
        tcgetattr(fd, &PortSettings);

        /** Set the baud rates to  38400 **/
        cfsetispeed(&PortSettings, B38400); 
        cfsetospeed(&PortSettings, B38400);

        /*
         * Enable hardware flow control
         */

        PortSettings.c_cflag |= CRTSCTS;

        /*
         * Set port character size to eight bits
         */

        PortSettings.c_cflag |= CS8;

        /*
         * Enable port receiver
         */

        PortSettings.c_cflag |= CREAD;

        /*
         * Enable local control
         */

        PortSettings.c_cflag |= CLOCAL;

        /*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           Set up input modes in terminal control descriptor
           %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */

        /*
         * Ignore parity errors
         */

        PortSettings.c_iflag = IGNPAR;

        /*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           Set up output modes in terminal control descriptor
           %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */

        /*
         * No special output modes used
         */

        PortSettings.c_oflag = 0;

        /*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           Set up local modes in terminal control descriptor
           %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */

        /*
         * No special local modes used
         */

        PortSettings.c_lflag = 0;

        /*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           Set up control characters in terminal control descriptor
           %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */

        /*
         * Set minimum number of characters for non-canonical read to one; input is
         * read one character at a time from serial port
         */

        PortSettings.c_cc[VMIN] = 1;

        /*
         * Set timeout for non-canonical read to zero; block until a character is
         * available
         */

        PortSettings.c_cc[VTIME] = 0;

        
        /*trash the initial IMT30 message */
        if (tcflush(fd,TCIOFLUSH) == ERROR)
        {
            perror("init_serial: cannot flush terminal buffer: ");
            return ERROR;
        }
        
        

        if (tcsetattr(fd, TCSANOW, &PortSettings) == ERROR)
        {
            perror("init_serial: cannot set tc atrributes: ");
            return ERROR;
        }
        
        return fd;
    }
    
    perror("init_serial: invalid file descriptor: ");
    
    return ERROR;
}

/**
* @brief Function to write values to a serial port connection.
* 
* This function send nbytes of the command parameter to an open serial port
* connection specified in the file descriptor.
*
* @author Javier Hidalgo Carrio.
* @param[in] fd file descriptor
* @param[in] command pointer to char with the values to be sent
* @param[in] nbytes number of bytes to send.
*
* @return OK if everything all right, ERROR on error.
*
*/
int write_serial(int fd, char* command, int nbytes)
{
    int n = 0;  
    
    if (fd != ERROR)
    {
        //printf ("In write function: %s tamanio: %d", command, nbytes);
        n = write(fd, command, nbytes);
        if (n<0)
        {
            fputs("write()  failed!\n", stderr);
            perror("write_serial: write syscall error: ");
            return ERROR;
        }
        else
        {
            return OK;
        }   
    }
    
    perror("write_serial: invalid file descriptor: ");
    
    return ERROR;
}

/**
* @brief Function to read values from a serial port connection.
* 
* This function read nbytes from an open serial port
* connection specified in the file descriptor.
*
* @author Javier Hidalgo Carrio.
* @param[in] fd file descriptor
* @param[out] bufferpr pointer to char. Buffer to store the values read
* @param[in] nbytes number of bytes to read.
*
* @return OK if everything all right, ERROR on error.
*
*/
int read_serial(int fd,  unsigned char * bufferpr, int nbytes)
{
    static int n = 0;
    
    if (fd != ERROR)
    {
        if ((n = read (fd, (unsigned char *) bufferpr, nbytes)) > 0)
        {
            return n;
        }
        
        perror("read_serial: read syscall error: ");
    }
    
    return ERROR;
}
/**
* @brief Function to close an open serial port connection.
* 
* This function closes a preexisting serial port connection.
*
* @author Javier Hidalgo Carrio.
* @param[in] fd file descriptor
*
* @return OK if everything all right, ERROR on error.
*
*/
int close_port (int fd)
{
    if (fd != ERROR)
    {
        return close (fd); /**< Returns OK if no errors*/
        
    }
    
    perror("open_port: invalid file descriptor: ");
    
    return ERROR;
}

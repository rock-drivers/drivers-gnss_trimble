/*    Robotic Construction Kit (ROCK) Driver  for the BD970 GNSS receiver 
 *    from Trimble.
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
 *    Config.hpp  Copyright (C) 2014  Vassilios Tsounis
 *    This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 *    This is free software, and you are welcome to redistribute it
 *    under certain conditions; type `show c' for details.
 */


#ifndef _GNSS_TRIMBLE_CONFIG_HPP_
#define _GNSS_TRIMBLE_CONFIG_HPP_

/** Std headers **/
#include <stdint.h>


namespace gnss_trimble
{
    /**
     * 
     * TODO
     * 
    **/
    
    struct Config
    {
        /** Configuration Parameters **/
        int8_t config1;
        
        /** Configurations Constructor **/
        Config(void)
            : config1(0)
        {
        }
        
        /** Configurations Destuctor **/
        ~Config(void)
        {
        }
    };
}

#endif // _GNSS_TRIMBLE_CONFIG_HPP_

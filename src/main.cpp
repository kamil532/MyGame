/*     MyGame 
*      
*      Copyright 2011 Lolcio < kamil532@interia.eu >
*      
*      This program is free software; you can redistribute it and/or modify
*      it under the terms of the GNU General Public License as published by
*      the Free Software Foundation; either version 2 of the License, or
*      (at your option) any later version.
*      
*      This program is distributed in the hope that it will be useful,
*      but WITHOUT ANY WARRANTY; without even the implied warranty of
*      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*      GNU General Public License for more details.
*      
*      You should have received a copy of the GNU General Public License
*      along with this program; if not, write to the Free Software
*      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
*      MA 02110-1301, USA.     
*/      

#include "App.hpp"

int main( int argc, char** argv ){

    std::cout<<INFO;
    App* application;

    try {
        if (argc == 2) application = new App(new string(argv[1]));
        else  application = new App(new string(""));
        application->Run();
    }
    catch (const char* Error) {
        std::cout<<Error<<std::endl;
        return -1;
    }
    
 return 0;	
}	

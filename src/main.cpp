/*     Pyrex 2D 
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
#include <exception>

int main( void ){

    App* application;

    try {
        Engine::Get().LoadLua();
        application = new App();
        application->Run();
    }
    catch (std::exception& e)  {
	cout << e.what() << endl;
	return -1;
    }
    catch (const char* Error) {
        std::cout<<Error<<std::endl;
        return -1;
    }    
    
 return 0;	
}	

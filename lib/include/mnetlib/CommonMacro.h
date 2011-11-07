/*
 * CommonMacro.h
 *
 *  Created on: 05/nov/2011
 *      Author: totoro
 */

#ifndef COMMONMACRO_H_
#define COMMONMACRO_H_

#include <ctime>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/resource.h>


#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif
//Info Message. Red Color
#define INFO_MSG(str) do { \
    time_t curr;time(&curr); \
    std::string t(ctime(&curr) );\
    std::string sTime = t.substr( 0, t.length() -1  );\
    std::cout << sTime << " - APP INFO: " << "\E[1m\E[32m" << str << "\E[0m" <<std::endl; \
}\
while( false )
//Error Message. Red Color
#define ERROR_MSG(str) do { std::cout << "\E[1m\E[31m" << str << "\E[0m" <<std::endl; } while( false )

#endif /* COMMONMACRO_H_ */

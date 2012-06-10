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
#include <boost/foreach.hpp>

#define foreach BOOST_FOREACH


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

#define CATCH_XML(ret)\
catch (const XMLException& toCatch) {\
        char* message = XMLString::transcode(toCatch.getMessage());\
        cout << "Exception message is: \n"\
            << message << "\n";\
        XMLString::release(&message);\
        return ret;\
    }\
    catch (const DOMException& toCatch) {\
        char* message = XMLString::transcode(toCatch.msg);\
        cout << "Exception message is: \n"\
            << message << "\n";\
        XMLString::release(&message);\
        return ret;\
    }\
    catch (const SAXParseException& toCatch) {\
        char* message = XMLString::transcode(toCatch.getMessage());\
        cout << "Exception message is: \n"\
            << message << "\n";\
        XMLString::release(&message);\
        return ret;\
    }\
    catch (std::exception& e) {\
        DEBUG_MSG( "Unexpected Exception " );\
        DEBUG_MSG( e.what());\
        return ret;\
    }\

#endif /* COMMONMACRO_H_ */


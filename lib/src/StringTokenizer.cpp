/**
*  StringTokenizer.cpp
*  Mnetlib
*
*  This file is part of Mnetlib.
*
*  Mnetlib is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  Mnetlib is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with Mnetlib; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*
*  Copyright (C) 2007 by francesco.amenta
*   francesco.amenta@gmail.com
*
*/

#include "StringTokenizer.h"

using namespace std;
using std::cout;

StringTokenizer::StringTokenizer(const std::string& _str, const std::string& _delim)
{

   if ((_str.length() == 0) || (_delim.length() == 0)) return;

   token_str = _str;
   delim     = _delim;

  /*
     Remove sequential delimiter
  */
   unsigned long curr_pos = 0;
   
   //cout<<token_str.find(delim,curr_pos)<<","<<std::string::npos<<"\n";

   while(true)
   {
	   //cout<<token_str.find(delim,curr_pos)<<","<<std::string::npos<<"\n";
	   //cout<<((curr_pos = token_str.find(delim,curr_pos)) != std::string::npos)<<"\n";
      if ((curr_pos = token_str.find(delim,curr_pos)) != std::string::npos)
      {
         curr_pos += delim.length();
		 // cout<<token_str.find(delim,curr_pos)<<","<<std::string::npos<<"\n";

         while(token_str.find(delim,curr_pos) == curr_pos)
         {
            token_str.erase(curr_pos,delim.length());
         }
      }
      else
       break;
   }

   /*
     Trim leading delimiter
   */
   if (token_str.find(delim,0) == 0)
   {
      token_str.erase(0,delim.length());
   }

   /*
     Trim ending delimiter
   */
   curr_pos = 0;
   if ((curr_pos = token_str.rfind(delim)) != std::string::npos)
   {
      if (curr_pos != (token_str.length() - delim.length())) return;
      token_str.erase(token_str.length() - delim.length(),delim.length());
   }

}


int StringTokenizer::countTokens()
{

   unsigned long prev_pos = 0;
   int num_tokens        = 0;

   if (token_str.length() > 0)
   {
      num_tokens = 0;

      unsigned long curr_pos = 0;
      while(true)
      {
         if ((curr_pos = token_str.find(delim,curr_pos)) != std::string::npos)
         {
            num_tokens++;
            prev_pos  = curr_pos;
            curr_pos += delim.length();
         }
         else
          break;
      }
      return ++num_tokens;
   }
   else
   {
      return 0;
   }

}


bool StringTokenizer::hasMoreTokens()
{
   return (token_str.length() > 0);
}


std::string StringTokenizer::nextToken()
{

   if (token_str.length() == 0)
     return "";

   std::string  tmp_str = "";
   unsigned long pos     = token_str.find(delim,0);

   if (pos != std::string::npos)
   {
      tmp_str   = token_str.substr(0,pos);
      token_str = token_str.substr(pos+delim.length(),token_str.length()-pos);
   }
   else
   {
      tmp_str   = token_str.substr(0,token_str.length());
      token_str = "";
   }

   return tmp_str;
}


int StringTokenizer::nextIntToken()
{
   return atoi(nextToken().c_str());
}


double StringTokenizer::nextFloatToken()
{
   return atof(nextToken().c_str());
}


std::string StringTokenizer::nextToken(const std::string& delimiter)
{
   if (token_str.length() == 0)
     return "";

   std::string  tmp_str = "";
   unsigned long pos     = token_str.find(delimiter,0);

   if (pos != std::string::npos)
   {
      tmp_str   = token_str.substr(0,pos);
      token_str = token_str.substr(pos + delimiter.length(),token_str.length() - pos);
   }
   else
   {
      tmp_str   = token_str.substr(0,token_str.length());
      token_str = "";
   }

   return tmp_str;
}


std::string StringTokenizer::remainingString()
{
   return token_str;
}


std::string StringTokenizer::filterNextToken(const std::string& filterStr)
{
   std::string  tmp_str    = nextToken();
   unsigned long currentPos = 0;

   while((currentPos = tmp_str.find(filterStr,currentPos)) != std::string::npos)
   {
      tmp_str.erase(currentPos,filterStr.length());
   }

   return tmp_str;
}

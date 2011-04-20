/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_DETAILS_TYPE_ID_HPP_INCLUDED
#define NT2_SDK_DETAILS_TYPE_ID_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Type name display
// Documentation: http://nt2.lri.fr/sdk/details/sdk/details/type_id.html
////////////////////////////////////////////////////////////////////////////////

#if (__GNUC__ && __cplusplus && __GNUC__ >= 3)
////////////////////////////////////////////////////////////////////////////////
// Includes abi::__cxa_demangle
////////////////////////////////////////////////////////////////////////////////
#include <cxxabi.h>
#endif

#include <cstdlib>
#include <typeinfo>
#include <string>
#include <iostream>

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // demangle a type name retrieved through typeid()
  //////////////////////////////////////////////////////////////////////////////
  inline std::string demangle(const char* name)
  {
    ////////////////////////////////////////////////////////////////////////////
    // use g++ ABI interface to perform demangling
    ////////////////////////////////////////////////////////////////////////////
    #if(__GNUC__ && __cplusplus && __GNUC__ >= 3)
    std::size_t len;
    int         stat;

    char* realname = ::abi::__cxa_demangle(name,NULL,&len,&stat);

    if(realname != NULL)
    {
      std::string out(realname);
      ::free(realname);
      return out;
    }
    else
    {
      return std::string("?");
    }
    #else
    ////////////////////////////////////////////////////////////////////////////
    // Other compiler don't need or can't do that, so just return the type name
    ////////////////////////////////////////////////////////////////////////////
    std::string out(name);
    return out;
    #endif
  }
  
  std::ostream& indent(std::ostream& os, size_t depth)
  {
    for(size_t i=0; i<depth; ++i)
      os << "    ";
      
    return os;
  }
  
} }

namespace nt2
{
  //////////////////////////////////////////////////////////////////////////////
  // Return a string containing the demangled typename of a given type
  //////////////////////////////////////////////////////////////////////////////
  template<class T> inline std::string type_id(const T& = *((T*)0))
  {
    return details::demangle(typeid(T).name());
  }
  
  template<typename T>
  inline void display_type(const T& = *((T*)0))
  {
    std::string s = type_id<T>();
    
    size_t depth = 0;
    bool prevspace = true;
    for(std::string::const_iterator it = s.begin(); it != s.end(); ++it)
    {
      switch(*it)
      {
        case '<':
          depth++;
          std::cout << *it;
          std::cout << '\n';
          details::indent(std::cout, depth);
          prevspace = true;
          break;
          
        case '>':
          depth--;
          std::cout << '\n';
          details::indent(std::cout, depth);
          std::cout << *it;
          prevspace = false;
          break;
          
        case ',':
          std::cout << *it;
          std::cout << '\n';
          details::indent(std::cout, depth);
          prevspace = true;
          break;
          
        case ' ':
          if(!prevspace)
            std::cout << *it;
          break;
          
        default:
          std::cout << *it;
          prevspace = false;
      }
    }
    std::cout << std::endl;
  }
}

#endif

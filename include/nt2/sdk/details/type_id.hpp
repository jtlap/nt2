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

#if (__GNUC__ && __cplusplus && __GNUC__ >= 3)
#include <cxxabi.h>
#endif

#include <string>
#include <typeinfo>
#include <boost/config.hpp>

namespace nt2 { namespace details
{
  static inline std::string demangle(const char* name)
  {
    ////////////////////////////////////////////////////////////////////////////
    // use g++ ABI interface to perform demangling
    ////////////////////////////////////////////////////////////////////////////
    #if(__GNUC__ && __cplusplus && __GNUC__ >= 3)
    std::size_t len;
    int         stat;

    char* realname = abi::__cxa_demangle(name,NULL,&len,&stat);

    if(realname != NULL)
    {
      std::string out(realname);
      free(realname);
      return out;
    }
    else
    {
      return std::string("?");
    }
    #else
    ////////////////////////////////////////////////////////////////////////////
    // Other compiler don't need or can't do that, so jus return the type id
    ////////////////////////////////////////////////////////////////////////////
    return name;
    #endif
  }
} }

namespace nt2
{
  //////////////////////////////////////////////////////////////////////////////
  // Return a string containing the demangled typename of a given variable
  //////////////////////////////////////////////////////////////////////////////
  template<class T> inline std::string type_id(const T& )
  {
    std::string const demangled = details::demangle(typeid(T).name());
    return demangled;
  }

  //////////////////////////////////////////////////////////////////////////////
  // Return a string containing the demangled typename of a given type
  //////////////////////////////////////////////////////////////////////////////
  template<class T> inline std::string type_id()
  {
    std::string const demangled = details::demangle(typeid(T).name());
    return demangled;
  }
}

#endif

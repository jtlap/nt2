//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_DETAILS_TYPE_ID_HPP_INCLUDED
#define NT2_SDK_DETAILS_TYPE_ID_HPP_INCLUDED

/*!
 * \file
 * \brief Defines types to string conversion utility functions
 *
 */

/*!
 * \ingroup meta
 * \defgroup metadebug Meta-Programming Debug Utilities
 * This module gathers functions and meta-functions to help debugging template
 * meta-programms in a Human rights compatible way.
 */

#if (__GNUC__ && __cplusplus && __GNUC__ >= 3)
//==============================================================================
// Includes abi::__cxa_demangle
//==============================================================================
#include <cxxabi.h>
#endif

#include <string>
#include <cstdlib>
#include <typeinfo>
#include <iostream>
#include <boost/dispatch/details/ignore_unused.hpp>

namespace nt2 {  namespace details
{
  //============================================================================
  // demangle a type name retrieved through typeid()
  //============================================================================
  inline std::string demangle(const char* name)
  {
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
    std::string out(name);
    return out;
    #endif
  }
  
  inline std::ostream& indent(std::ostream& os, size_t depth)
  {
    for(size_t i=0; i<depth; ++i)
      os << "    ";
      
    return os;
  }
  
} }

namespace nt2
{
  //////////////////////////////////////////////////////////////////////////////
  /*!
   * \ingroup metadebug
   * Returns a string containing the demangled typename of a given type
   *
   * \param expr Expression which type is to be stringized
   * \return \c T type name as a readable \c std::string
   *
   * \par Example Usage:
   *
   * \include type_id.cpp
   *
   * This examples output:
   *
   * \code
   * char [21]
   * float
   * std::vector<long*, std::allocator<long*> >
   * \endcode
   */
  //////////////////////////////////////////////////////////////////////////////
  template<typename T> inline std::string type_id()
  {
    std::string s = details::demangle(typeid(T).name());
    if(boost::is_const<T>::value)
      s += " const";
    if(boost::is_reference<T>::value)
      s += "&";
    return s;
  }
  
  template<typename T> inline std::string type_id(const T&)
  {
    return type_id<T>();
  }
  
  //////////////////////////////////////////////////////////////////////////////
  /*!
   * \ingroup metadebug
   * Display the demangled typename of a given type on the standard output.
   *
   * \param expr Expression which type is to be displayed
   *
   * \par Example Usage:
   *
   * \include display_type.cpp
   *
   * This examples outpus:
   *
   * \code
   * char [21]
   * float
   * std::vector<
   *              long*
   *              ,std::allocator<
   *                              long*
   *                              >
   *            >
   * \endcode
   */
  //////////////////////////////////////////////////////////////////////////////
  template<typename T> inline void display_type()
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
          std::cout << '\n';
          details::indent(std::cout, depth);
          std::cout << *it;
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
  
  template<typename T> inline void display_type(T const&)
  {
    return display_type<T>();
  }
}

#endif

//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_TYPE_ID_HPP_INCLUDED
#define NT2_SDK_META_TYPE_ID_HPP_INCLUDED

/**
* @file
* @brief Defines types to string conversion utility functions
**/
#include <nt2/sdk/meta/details/demangle.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace nt2
{
  /**
  * @brief Type name demangling function
  *
  * For any given type @c T, returns a human readable string containing the fully
  * qualified name of @c T.
  *
  * @tparam T   Type to turn into a string
  * @return @c std::string containing the type of @c T
  *
  * @usage
  * @include type_id.cpp
  *
  * This examples output:
  *
  * @code
  * char [21]
  * float
  * std::vector<long*, std::allocator<long*> >
  * @endcode
  **/
  template<typename T> inline std::string type_id()
  {
    std::string s = details::demangle(typeid(T).name());
    if(boost::is_const<typename boost::remove_reference<T>::type>::value)
      s += " const";
    if(boost::is_reference<T>::value)
      s += "&";
    return s;
  }

  /**
  * @brief Type name demangling function
  *
  * For any given value @c x of type @c T, returns a human readable string
  * containing the fully qualified name of @c T.
  *
  * @param  x   Value to analyze
  * @return @c  std::string containing the type of @c x
  *
  * @usage
  * @include type_id.cpp
  *
  * This examples output:
  *
  * @code
  * char [21]
  * float
  * std::vector<long*, std::allocator<long*> >
  * @endcode
  **/
  template<typename T> inline std::string type_id( const T& )
  {
    return type_id<T>();
  }
}

#endif

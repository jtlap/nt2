/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_SIGN_OF_HPP_INCLUDED
#define NT2_SDK_META_SIGN_OF_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Sign is Ok for arithmetic types
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class Hierarchy> struct sign_of { typedef signed type; };

  //////////////////////////////////////////////////////////////////////////////
  // Sign has no meanign on other types most of the time
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct sign_of<T, meta::unspecified_<T> > {  typedef unsigned type; };

  //////////////////////////////////////////////////////////////////////////////
  // ... unless they are unsigned of course
  //////////////////////////////////////////////////////////////////////////////
  template<class Hierarchy>
  struct sign_of<uint8_t ,Hierarchy> { typedef unsigned type; };
  template<class Hierarchy>
  struct sign_of<uint16_t,Hierarchy> { typedef unsigned type; };
  template<class Hierarchy>
  struct sign_of<uint32_t,Hierarchy> { typedef unsigned type; };
  template<class Hierarchy>
  struct sign_of<uint64_t,Hierarchy> { typedef unsigned type; };
  template<class Hierarchy>
  struct sign_of<bool    ,Hierarchy> { typedef unsigned type; };
} }

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Return trues or false depending on T is signed or not
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct  sign_of
        : details::sign_of< typename strip<T>::type
                          , typename meta::hierarchy_of<T>::type
                          >
  {};
} }


#endif

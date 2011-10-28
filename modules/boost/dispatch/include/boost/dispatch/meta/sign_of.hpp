//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_SIGN_OF_HPP_INCLUDED
#define BOOST_DISPATCH_META_SIGN_OF_HPP_INCLUDED

#include <boost/dispatch/meta/is_signed.hpp>

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  /*! Computes the signedness of a given type.
   *
   * \tparam T Type to compute signedness from.
   * \return If \c T is signed, \c sign_of<T>::type is \c signed, otherwsie, it
   * is \c unsigned.
   **/
  //============================================================================
  template<class T> struct sign_of;
} } }

namespace boost { namespace dispatch { namespace details
{
  template<class T, class Enable = void> 
  struct sign_of
  {
    typedef unsigned type;
  };

  template<class T>
  struct sign_of<T, typename enable_if< meta::is_signed<T> >::type>
  {
    typedef signed type;
  };
} } }

namespace boost { namespace dispatch { namespace meta
{
  template<class T> struct  sign_of           : details::sign_of<T> {};
  template<class T> struct  sign_of<T&>       : sign_of <T>         {};
  template<class T> struct  sign_of<T const>  : sign_of <T>         {};
} } }
#endif

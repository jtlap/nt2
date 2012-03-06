//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_CONTAINER_TRAITS_HPP_INCLUDED
#define NT2_SDK_META_CONTAINER_TRAITS_HPP_INCLUDED

#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/dispatch/meta/enable_if_type.hpp>
#include <boost/dispatch/meta/strip.hpp>

namespace nt2 { namespace meta
{
  //==============================================================================
  //==============================================================================
  template<class T, class Enable=void> 
  struct reference_ : boost::add_reference<T>
  {};

  //==============================================================================
  //==============================================================================
  template<class T, class Enable=void> 
  struct  const_reference_ 
        : boost::add_reference< typename boost::add_const<T>::type >
  {};

  //==============================================================================
  //==============================================================================
  template<class T, class Enable=void> 
  struct value_type_
  {
    typedef T type;
  };

  template<class T>
  struct reference_ < T 
                    , typename  boost::dispatch::meta::
                      enable_if_type< typename boost::dispatch::meta::
                                      strip<T>::type::reference
                                    >::type
                    >
  {
    typedef typename T::reference type;
  };

  template<class T>
  struct const_reference_ < T 
                          , typename  boost::dispatch::meta::
                            enable_if_type< typename boost::dispatch::meta::
                                            strip<T>::type::const_reference
                                          >::type
                          >
  {
    typedef typename T::const_reference type;
  };

  template<class T>
  struct value_type_< T 
                    , typename  boost::dispatch::meta::
                      enable_if_type< typename boost::dispatch::meta::
                                      strip<T>::type::value_type
                                    >::type
                    >
  {
    typedef typename T::value_type type;
  };
} }

#endif

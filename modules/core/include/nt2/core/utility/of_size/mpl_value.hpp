//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_OF_SIZE_MPL_VALUE_HPP_INCLUDED
#define NT2_CORE_UTILITY_OF_SIZE_MPL_VALUE_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <boost/mpl/int.hpp>
#include <boost/type_traits/is_class.hpp>

namespace nt2
{
  //============================================================================
  // If the result of a size computation is a MPL Integral, keep it;
  // If not, return -1 so the of_size will be flagged as dynamic
  //============================================================================
  template<class T, class Enable = void>
  struct mpl_value : boost::mpl::int_<-1> {};

  template<class T>
  struct mpl_value < T
                   , typename boost::
                     enable_if < boost::
                                 is_class< typename meta::strip<T>::type >
                               >::type
                   >
    : meta::strip<T>::type
  {};

  //============================================================================
  // If the result of a size computation is a MPL Integral, extract its type;
  // If not, return the original type
  //============================================================================
  template<class T, class Enable = void>
  struct mpl_value_type { typedef T type; };

  template<class T>
  struct mpl_value_type < T
                        , typename boost::
                          enable_if < boost::
                                    is_class< typename meta::strip<T>::type >
                                    >::type
                        >
  {
    typedef typename meta::strip<T>::type::value_type type;
  };
}

#endif

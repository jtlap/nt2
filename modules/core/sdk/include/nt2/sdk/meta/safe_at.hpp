//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_SAFE_AT_HPP_INCLUDED
#define NT2_SDK_META_SAFE_AT_HPP_INCLUDED

#include <boost/mpl/size_t.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/dispatch/attributes.hpp>

namespace nt2 { namespace meta
{
  template<int N, int D, class T> BOOST_FORCEINLINE
  typename boost::lazy_enable_if_c
  < (0 <= N && N < boost::fusion::result_of::size<T>::type::value)
    , boost::fusion::result_of::at_c<const T, N>
  >::type default_at_c(const T& t)
  {
    return boost::fusion::at_c<N>(t);
  }

  template<int N, int D, class T> BOOST_FORCEINLINE
  typename boost::disable_if_c
  < (0 <= N && N < boost::fusion::result_of::size<T>::type::value)
    , boost::mpl::size_t<D>
  >::type default_at_c(const T&)
  {
    return boost::mpl::size_t<D>();
  }

  template<int N, class T> BOOST_FORCEINLINE
  typename boost::lazy_enable_if_c
  < (0 <= N && N < boost::fusion::result_of::size<T>::type::value)
    , boost::fusion::result_of::at_c<const T, N>
  >::type safe_at_c(const T& t)
  {
    return boost::fusion::at_c<N>(t);
  }

  template<int N, class T> BOOST_FORCEINLINE
  typename boost::disable_if_c
  < (0 <= N && N < boost::fusion::result_of::size<T>::type::value)
    , boost::mpl::size_t<1>
  >::type safe_at_c(const T&)
  {
    return boost::mpl::size_t<1>();
  }
} }

#endif

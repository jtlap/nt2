//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_CACHE_PADDING_HPP_INCLUDED
#define NT2_SDK_MEMORY_CACHE_PADDING_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/config/cache.hpp>
#include <boost/simd/sdk/memory/align_on.hpp>

namespace nt2 { namespace memory
{
  //============================================================================
  /*!
   * cache_padding is a padding strategy that align the lead dimension of a
   * dimensions set on the cache line size of current architecture.
   */
  //============================================================================
  struct cache_padding
  {
    typedef boost::mpl::true_ padding_status;

    template<class Sig> struct result;
    template<class T, int N> struct result_impl;

    template<class This, class T, class N, class V>
    struct  result<This(T,N,V)>
          : result_impl<T,meta::strip<N>::type::value> {};

    template<class T,int N> struct result_impl  { typedef T           type; };
    template<class T> struct result_impl<T,0>   { typedef std::size_t type; };

    template<class T, class N, class V>
    typename result<cache_padding(T const&, N const&, V const&)>::type
    operator()(T const& t, N const& n, V const& v) const
    {
      return eval(t,n,v,boost::mpl::bool_<N::value==0>());
    }

    template<class T, class N, class V>
    typename result<cache_padding(T const&, N const&, V const&)>::type
    eval(T const& t, N const&, V const&, boost::mpl::true_ const&) const
    {
      static const std::size_t  tz = sizeof(typename V::type);

      const std::size_t sz =
            boost::simd::memory::align_on ( t*tz
                                          , config::shared_cache_line_size()
                                          );
      return sz/tz;
    }

    template<class T, class N, class V> T const&
    eval(T const& t, N const&, V const&, boost::mpl::false_ const&) const
    {
      return t;
    }
  };
} }

#endif

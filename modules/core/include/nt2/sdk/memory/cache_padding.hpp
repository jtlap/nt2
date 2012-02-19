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
    template<class Sig> struct result;
    template<class T, int N> struct result_impl;

    template<class This, class T, class N>
    struct result<This(T,N)> : result_impl<T,N::value> {};

    template<class T,int N> struct result_impl  { typedef T type; };

    template<class T> struct result_impl<T,1>
    {
      typedef typename boost::dispatch::meta::
              call<boost::simd::tag::align_on_(T const&, int)>::type  type;
    };

    template<class T, class N>
    typename result<cache_padding(T const&, N const&)>::type
    operator()(T const& t, N const&) const
    {
      return eval(t,boost::mpl::bool_<N::value==1>());
    }

    template<class T, class N>
    typename result<cache_padding(T const&, N const&)>::type
    eval(T const& t, N const&, boost::mpl::true_ const&) const
    {
      return boost::simd::memory::align_on(t,config::shared_cache_line_size());
    }

    template<class T, class N>
    typename result<cache_padding(T const&, N const&)>::type
    eval(T const& t, N const&, boost::mpl::false_ const&) const
    {
      return t;
    }
  };
} }

#endif

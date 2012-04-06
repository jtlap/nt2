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

    template<class Target> struct apply
    {
      struct type
      {
        template<class Sig> struct result;
        template<class V, int N> struct result_impl;

        template<class This, class V, class N>
        struct  result<This(V,N)>
              : result_impl<V,meta::strip<N>::type::value> {};

        template<class V,int N> struct result_impl  : meta::strip<V> {};
        template<class V> struct result_impl<V,0>   { typedef std::size_t type; };

        template<class V, class N>
        typename result<cache_padding(V const&, N const&)>::type
        operator()(V const& v, N const& n) const
        {
          return eval(v,n,boost::mpl::bool_<N::value==0>());
        }

        template<class V, class N>
        typename result<cache_padding(V const&, N const&)>::type
        eval(V const& v, N const&, boost::mpl::true_ const&) const
        {
          static const std::size_t  tz = sizeof(Target);

          const std::size_t sz =
                boost::simd::memory::align_on ( v*tz
                                              , config::shared_cache_line_size()
                                              );
          return sz/tz;
        }

        template<class V, class N>
        typename result<cache_padding(V const&, N const&)>::type
        eval(V const& v, N const&, boost::mpl::false_ const&) const
        {
          return v;
        }
      };
    };
  };
} }

#endif

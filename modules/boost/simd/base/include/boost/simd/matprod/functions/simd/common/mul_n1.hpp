//==============================================================================
//         Copyright 2014               Jean-Thierry Lapreste
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MATPROD_FUNCTIONS_SIMD_COMMON_MUL_N1_HPP_INCLUDED
#define BOOST_SIMD_MATPROD_FUNCTIONS_SIMD_COMMON_MUL_N1_HPP_INCLUDED

#include <boost/simd/matprod/functions/mul_n1.hpp>
#include <boost/simd/include/functions/broadcast.hpp>
#include <boost/simd/include/functions/fma.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace simd {

  namespace details
  {
    template < size_t I, class A, class V, class result_type> struct do_fma
    {
      void operator()(const A& a, const V & x, result_type & r) const
      {
        r = fma(a[I], broadcast<I>(x), r);
        do_fma<I-1, A, V, result_type>()(a, x, r);
      }
    };
    template <class A, class V, class result_type > struct do_fma < 0, A, V, result_type>
    {
      void operator()(const A& a, const V & x, result_type & r) const
      {
        r = fma(a[0], broadcast<0>(x), r);
      }
    };
  }

namespace ext
{

  // return a*v
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_n1_
                                    , boost::simd::tag::cpu_
                                    , (A)(V)(X)
                                    , ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<V>::value>>
                                       ))
                                      ((simd_<floating_<V>,X>))
                                    )

  {
    typedef V result_type;

    BOOST_FORCEINLINE  result_type operator()(const A& a, const V & x) const
    {
      static const size_t N = meta::cardinal_of<V>::value;
      result_type r = a[N-1]*broadcast<N-1>(x);
      details::do_fma<N-2, A, V, result_type>()(a, x, r);
      return r;
    }
  };

  //a*v is added to r
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_n1_
                                    , boost::simd::tag::cpu_
                                    , (A)(V)(R)(X)
                                    , ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<V>::value>>
                                       ))
                                      ((simd_<floating_<V>,X>))
                                      ((simd_<floating_<R>,X>))
                                    )

  {
    typedef void result_type;

    BOOST_FORCEINLINE  result_type operator()(const A& a, const V & x, R & r) const
    {
      static const size_t N = meta::cardinal_of<V>::value;
      r += a[N-1]*broadcast<N-1>(x);
      details::do_fma<N-2, A, V, R>()(a, x, r);
    }
  };

  //alpha*a*v is added to r
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_n1_
                                    , boost::simd::tag::cpu_
                                    , (ALPHA)(A)(V)(R)(X)
                                    , (scalar_<arithmetic_<ALPHA>>)
                                      ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<V>::value>>
                                       ))
                                      ((simd_<floating_<V>,X>))
                                      ((simd_<floating_<R>,X>))
                                    )

  {
    typedef void result_type;
    typedef typename meta::scalar_of<typename A::value_type>::type ftype;
    BOOST_FORCEINLINE  result_type operator()(const ALPHA& alpha, const A & a, const V & x, R & r) const
    {
      static const size_t N = meta::cardinal_of<V>::value;
      V xx = x*static_cast<ftype>(alpha);
      r += a[N-1]*broadcast<N-1>(xx);
      details::do_fma<N-2, A, V, R>()(a, xx, r);
    }
  };

  //r receives beta*r+ alpha*a*v
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_n1_
                                    , boost::simd::tag::cpu_
                                    , (ALPHA)(A)(V)(BETA)(R)(X)
                                    , (scalar_<arithmetic_<ALPHA>>)
                                      ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<V>::value>>
                                       ))
                                      ((simd_<floating_<V>,X>))
                                      (scalar_<arithmetic_<BETA>>)
                                      ((simd_<floating_<R>,X>))
                                    )

  {
    typedef void result_type;
    typedef typename meta::scalar_of<typename A::value_type>::type ftype;

    BOOST_FORCEINLINE  result_type operator()(const ALPHA& alpha, const A & a, const V & x, const BETA & beta, R & r) const
    {
      static const size_t N = meta::cardinal_of<V>::value;
      V xx = x*static_cast<ftype>(alpha);
      r *= static_cast<ftype>(beta);
      r += a[N-1]*broadcast<N-1>(xx);
      details::do_fma<N-2, A, V, R>()(a, xx, r);
    }
  };


} } }

#endif

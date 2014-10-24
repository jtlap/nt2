//==============================================================================
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
    template < size_t I, class A0, class A1, class result_type> struct do_fma
    {
      void operator()(const A0& a, const A1 & x, result_type & r) const
      {
        r = fma(a[I], broadcast<I>(x), r);
        do_fma<I-1, A0, A1, result_type>()(a, x, r);
      }
    };
    template <class A0, class A1, class result_type > struct do_fma < 0, A0, A1, result_type>
    {
      void operator()(const A0& a, const A1 & x, result_type & r) const
      {
        r = fma(a[0], broadcast<0>(x), r);
      }
    };
  }

namespace ext
{


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_n1_
                                    , boost::simd::tag::cpu_
                                    , (A0)(A1)(X)
                                    , ((array_<simd_<floating_<A0>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<A1>::value>>
                                       ))
                                      ((simd_<floating_<A1>,X>))
                                    )

  {
    typedef A1 result_type;

    BOOST_FORCEINLINE  result_type operator()(const A0& a, const A1 & x) const
    {
      static const size_t N = meta::cardinal_of<A1>::value;
      result_type r = a[N-1]*broadcast<N-1>(x);
      details::do_fma<N-2, A0, A1, result_type>()(a, x, r);
      return r;
    }
  };


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_n1_
                                    , boost::simd::tag::cpu_
                                    , (A0)(A1)(A2)(X)
                                    , ((array_<simd_<floating_<A0>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<A1>::value>>
                                       ))
                                      ((simd_<floating_<A1>,X>))
                                      ((simd_<floating_<A2>,X>))
                                    )

  {
    typedef void result_type;

    BOOST_FORCEINLINE  result_type operator()(const A0& a, const A1 & x, A2 & r) const
    {
      static const size_t N = meta::cardinal_of<A1>::value;
      r += a[N-1]*broadcast<N-1>(x);
      details::do_fma<N-2, A0, A1, A2>()(a, x, r);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_n1_
                                    , boost::simd::tag::cpu_
                                    , (A0)(A1)(A2)(A3)(X)
                                    , (scalar_<arithmetic_<A0>>)
                                      ((array_<simd_<floating_<A1>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<A2>::value>>
                                       ))
                                      ((simd_<floating_<A2>,X>))
                                      ((simd_<floating_<A3>,X>))
                                    )

  {
    typedef void result_type;
    typedef typename meta::scalar_of<typename A1::value_type>::type ftype;
    BOOST_FORCEINLINE  result_type operator()(const A0& alpha, const A1 & a, const A2 & x, A3 & r) const
    {
      static const size_t N = meta::cardinal_of<A2>::value;
      A2 xx = x*static_cast<ftype>(alpha);
      r += a[N-1]*broadcast<N-1>(xx);
      details::do_fma<N-2, A1, A2, A3>()(a, xx, r);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_n1_
                                    , boost::simd::tag::cpu_
                                    , (A0)(A1)(A2)(A3)(A4)(X)
                                    , (scalar_<arithmetic_<A0>>)
                                      ((array_<simd_<floating_<A1>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<A2>::value>>
                                       ))
                                      ((simd_<floating_<A2>,X>))
                                      (scalar_<arithmetic_<A3>>)
                                      ((simd_<floating_<A4>,X>))
                                    )

  {
    typedef void result_type;
    typedef typename meta::scalar_of<typename A1::value_type>::type ftype;

    BOOST_FORCEINLINE  result_type operator()(const A0& alpha, const A1 & a, const A2 & x, const A3 & beta, A4 & r) const
    {
      static const size_t N = meta::cardinal_of<A2>::value;
      A2 xx = x*static_cast<ftype>(alpha);
      r *= static_cast<ftype>(beta);
      r += a[N-1]*broadcast<N-1>(xx);
      details::do_fma<N-2, A1, A2, A4>()(a, xx, r);
    }
  };


} } }

#endif

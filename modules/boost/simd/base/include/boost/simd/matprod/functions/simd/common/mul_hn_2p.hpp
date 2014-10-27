//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MATPROD_FUNCTIONS_SIMD_COMMON_MUL_HN_2P_HPP_INCLUDED
#define BOOST_SIMD_MATPROD_FUNCTIONS_SIMD_COMMON_MUL_HN_2P_HPP_INCLUDED

#include <boost/simd/matprod/functions/mul_hn_2p.hpp>
#include <boost/simd/matprod/functions/simd/common/mul_hn.hpp>
#include <boost/simd/include/functions/broadcast.hpp>
#include <boost/simd/include/functions/fma.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/fma.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/mpl/int.hpp>
#include <iostream>

namespace boost { namespace simd {

  namespace details
  {

    template <size_t I, class A, class B, class R> struct do_unroll_no_add
    {
      void operator()(const A& a, const B & b, R & r) const
      {
        r[I/4-1] = mul_hn(a, b, mpl::size_t<I-4>()); // this computes the part of the result
                                                     // which is the product of (N/2)x(2*N) matrix a
                                                     // by the  (2*N)x2 matrix with correspond to
                                                     // the slice b(I-4:I-1) of b
                                                     // i.e.
                                                     //  a * [b[I-4], b[I-2]
                                                     //       b[I-3], b[I-1]]
        do_unroll_no_add<I-4, A, B, R>()(a, b, r);
      }
    };
    template <class A, class B, class R> struct do_unroll_no_add<0, A, B, R>
    {
      void operator()(const A& , const B & , R & ) const {}
    };

    template <size_t I, class A, class B, class R> struct do_unroll
    {
      void operator()(const A& a, const B & b, R & r) const
      {
        r[I/4-1] += mul_hn(a, b, mpl::size_t<I-4>());
        do_unroll<I-4, A, B, R>()(a, b, r);
      }
    };
    template <class A, class B, class R> struct do_unroll<0, A, B, R>
    {
      void operator()(const A& , const B & , R & ) const {}
    };

    template <size_t I, class ALPHA, class A, class B, class R> struct do_unroll_scale
    {
      void operator()(const ALPHA& alpha, const A& a, const B & b, R & r) const
      {
        r[I/4-1] = fma(alpha, mul_hn(a, b, mpl::size_t<I-4>()), r[I/4-1]);
        do_unroll_scale<I-4, ALPHA, A, B, R>()(alpha, a, b, r);
      }
    };
    template <class ALPHA, class A, class B, class R> struct do_unroll_scale<0, ALPHA, A, B, R>
    {
      void operator()(const ALPHA& , const A& , const B & , R & ) const {}
    };

    template < size_t I, class M, class S> struct do_scale
    {
      void operator()(M & m, const S & s) const
      {
        m[I-1] *= s;
        do_scale<I-1, M, S>()(m, s);
      }
    };
    template <class M, class S> struct do_scale<0, M, S>
    {
      void operator()(M & , const S & ) const {}
    };
  }

namespace ext
{


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_hn_2p_
                                    , boost::simd::tag::cpu_
                                    , (A)(B)(X)(P)
                                    , ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<typename A::value_type>::value>>
                                       ))
                                      ((array_<simd_<floating_<B>,X>, P>))
                                    )

  {
    typedef typename A::value_type vtype;
    typedef boost::array < vtype, P::value/4 > result_type;

    BOOST_FORCEINLINE  result_type operator()(const A& a, const B & b) const
    {
      result_type r;
      details::do_unroll_no_add<P::value, A, B, result_type>()(a, b, r);
      return r;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_hn_2p_
                                    , boost::simd::tag::cpu_
                                    , (A)(B)(R)(X)(P)(Q)
                                    , ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<typename A::value_type>::value>>
                                       ))
                                      ((array_<simd_<floating_<B>,X>, P>))
                                      ((array_<simd_<floating_<R>,X>, Q>))
                                    )

  {
    typedef typename A::value_type vtype;
    typedef void result_type;

    BOOST_FORCEINLINE  result_type operator()(const A& a, const B & b, R & r) const
    {
      details::do_unroll<P::value, A, B, R>()(a, b, r);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_hn_2p_
                                    , boost::simd::tag::cpu_
                                    , (ALPHA)(A)(B)(R)(X)(P)(Q)
                                    , (scalar_<arithmetic_<ALPHA>>)
                                      ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<typename A::value_type>::value>>
                                       ))
                                      ((array_<simd_<floating_<B>,X>, P>))
                                      ((array_<simd_<floating_<R>,X>, Q>))
                                    )

  {
    typedef typename A::value_type vtype;
    typedef typename meta::scalar_of<vtype>::type stype;
    typedef void result_type;

    BOOST_FORCEINLINE  result_type operator()(const ALPHA& alpha, const A& a, const B & b
                                             , R & r) const
    {
      details::do_unroll_scale<P::value, ALPHA, A, B, R>()(stype(alpha), a, b, r);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_hn_2p_
                                    , boost::simd::tag::cpu_
                                    , (ALPHA)(A)(B)(BETA)(R)(X)(P)(Q)
                                    , (scalar_<arithmetic_<ALPHA>>)
                                      ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<typename A::value_type>::value>>
                                       ))
                                      ((array_<simd_<floating_<B>,X>, P>))
                                      (scalar_<arithmetic_<BETA>>)
                                      ((array_<simd_<floating_<R>,X>, Q>))
                                    )

  {
    typedef typename A::value_type vtype;
    typedef typename meta::scalar_of<vtype>::type stype;
    typedef void result_type;

    BOOST_FORCEINLINE  result_type operator()(const ALPHA& alpha, const A& a, const B & b
                                             , const BETA& beta, R & r) const
    {

      details::do_scale<Q::value, R, stype>()(r, stype(beta));
      details::do_unroll_scale<P::value, ALPHA, A, B, R>()(stype(alpha), a, b, r);
    }
  };
} } }

#endif

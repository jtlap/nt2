//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MATPROD_FUNCTIONS_SIMD_COMMON_MUL_NP_HPP_INCLUDED
#define BOOST_SIMD_MATPROD_FUNCTIONS_SIMD_COMMON_MUL_NP_HPP_INCLUDED

#include <boost/simd/matprod/functions/mul_np.hpp>
#include <boost/simd/matprod/functions/simd/common/mul_n1.hpp>
#include <boost/simd/include/functions/broadcast.hpp>
#include <boost/simd/include/functions/fma.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace simd { namespace ext
{


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_np_
                                    , boost::simd::tag::cpu_
                                    , (A0)(A1)(X)(P)
                                    , ((array_<simd_<floating_<A0>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<typename A0::value_type>::value>>
                                       ))
                                      ((array_<simd_<floating_<A1>,X>, P>))
                                    )

  {
    typedef typename dispatch::meta::strip<A1>::type result_type;

    BOOST_FORCEINLINE  result_type operator()(const A0& a, const A1 & x) const
    {
      result_type r;
      do_funroll<P::value-1>()(a, x, r);
      return r;
    }
  private:
    template < size_t I, class dummy = void> struct do_funroll
    {
      void operator()(const A0& a, const A1 & x, result_type & r) const
      {
        r[I] = mul_n1(a, x[I]);
        do_funroll<I-1>()(a, x, r);
      }
    };
    template <class dummy > struct do_funroll<0, dummy>
    {
      void operator()(const A0& a, const A1 & x, result_type & r) const
      {
        r[0] = mul_n1(a, x[0]);
      }
    };
  };


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_np_
                                    , boost::simd::tag::cpu_
                                    , (A)(B)(R)(X)(P)
                                    , ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<typename A::value_type>::value>>
                                       ))
                                      ((array_<simd_<floating_<B>,X>, P>))
                                      ((array_<simd_<floating_<R>,X>, P>))
                                     )

  {
    typedef void result_type;

    BOOST_FORCEINLINE  result_type operator()(const A& a, const B & b, R & r) const
    {
      do_funroll<P::value-1>()(a, b, r);
    }
  private:
    template < size_t I, class dummy = void> struct do_funroll
    {
      void operator()(const A& a, const B & b, R & r) const
      {
        r[I] += mul_n1(a, b[I]);
        do_funroll<I-1>()(a, b, r);
      }
    };
    template <class dummy > struct do_funroll<0, dummy>
    {
      void operator()(const A& a, const B & b, R & r) const
      {
        r[0] += mul_n1(a, b[0]);
      }
    };
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_np_
                                    , boost::simd::tag::cpu_
                                    , (ALPHA)(A)(B)(R)(X)(P)
                                    , (scalar_<arithmetic_<ALPHA>>)
                                      ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<typename A::value_type>::value>>
                                       ))
                                      ((array_<simd_<floating_<B>,X>, P>))
                                      ((array_<simd_<floating_<R>,X>, P>))
                                     )

  {
    typedef void result_type;
    typedef typename  dispatch::meta::scalar_of<typename A::value_type>::type ftype;
    BOOST_FORCEINLINE  result_type operator()(const ALPHA& alpha,const A& a, const B & b, R & r) const
    {
      do_funroll<P::value-1>()(ftype(alpha), a, b, r);
    }
  private:
    template < size_t I, class dummy = void> struct do_funroll
    {
      void operator()(const ftype& alpha, const A& a, const B & b, R & r) const
      {
        mul_n1(alpha, a, b[I], r[I]);
        do_funroll<I-1>()(alpha, a, b, r);
      }
    };
    template <class dummy > struct do_funroll<0, dummy>
    {
      void operator()(const ftype& alpha, const A& a, const B & b, R & r) const
      {
        mul_n1(alpha, a, b[0], r[0]);
      }
    };
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_np_
                                    , boost::simd::tag::cpu_
                                    , (ALPHA)(A)(B)(BETA)(R)(X)(P)
                                    , (scalar_<arithmetic_<ALPHA>>)
                                      ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<typename A::value_type>::value>>
                                       ))
                                      ((array_<simd_<floating_<B>,X>, P>))
                                      (scalar_<arithmetic_<BETA>>)
                                      ((array_<simd_<floating_<R>,X>, P>))
                                     )

  {
    typedef void result_type;
    typedef typename  dispatch::meta::scalar_of<typename A::value_type>::type ftype;
    BOOST_FORCEINLINE  result_type operator()(const ALPHA& alpha,const A& a, const B & b, const BETA& beta, R & r) const
    {
      do_funroll<P::value-1>()(ftype(alpha), a, b, ftype(beta), r);
    }
  private:
    template < size_t I, class dummy = void> struct do_funroll
    {
      void operator()(const ftype& alpha, const A& a, const B & b, const ftype& beta, R & r) const
      {
        mul_n1(alpha, a, b[I], beta, r[I]);
        do_funroll<I-1>()(alpha, a, b, beta, r);
      }
    };
    template <class dummy > struct do_funroll<0, dummy>
    {
      void operator()(const ftype& alpha, const A& a, const B & b, const ftype& beta, R & r) const
      {
        mul_n1(alpha, a, b[0], beta, r[0]);
      }
    };
  };
} } }

#endif

//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_SHUFFLE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_SHUFFLE_HPP_INCLUDED

#include <boost/simd/swar/functions/shuffle.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/simd/include/functions/make.hpp>
#include <boost/simd/sdk/meta/as_arithmetic.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>

#include <boost/simd/sdk/simd/preprocessor/repeat.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/int.hpp>

#include <cstdio>

#define M0(z,n,t)                                                              \
typedef typename boost::mpl::apply<perm_t,boost::mpl::int_<n>,card_t>::type    \
                                                                    i##n##_t;  \
/**/

#define M1(z,n,var) pick(BOOST_DISPATCH_PP_STRIP(var),i##n##_t())

#define M2(z,n,t)                                                              \
BOOST_FORCEINLINE                                                              \
result_type eval(A0 const& a0, boost::mpl::size_t<n> const&) const             \
{                                                                              \
  BOOST_PP_REPEAT(n,M0,~)                                                      \
  return make<result_type>( BOOST_PP_ENUM(n,M1,a0) );                          \
}                                                                              \
/**/

#define M3(z,n,t)                                                              \
BOOST_FORCEINLINE                                                              \
result_type eval( A0 const& a0, A0 const& a1                                   \
                , boost::mpl::size_t<n> const&) const                          \
{                                                                              \
  BOOST_PP_REPEAT(n,M0,~)                                                      \
  return make<result_type>( BOOST_PP_ENUM(n,M1,(a0,a1)) );                     \
}                                                                              \
/**/

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::shuffle_, tag::cpu_
                                      , (A0)(X)(P)
                                      , ( mpl::equal_to < mpl::sizeof_<A0>
                                                        , mpl::sizeof_<typename A0::type>
                                                        >
                                        )
                                      , ((simd_< logical_<A0>, X>))
                                        (target_< unspecified_<P> >)
                                      )
  {
    typedef A0                        result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, P const&) const
    {
      typedef typename meta::as_arithmetic<A0>::type type;
      return  bitwise_cast <result_type>
              ( shuffle<typename P::type>( bitwise_cast<type>(a0) ));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_, tag::cpu_
                                    , (A0)(X)(P)
                                    , ((simd_< arithmetic_<A0>, X>))
                                      (target_< unspecified_<P> >)
                                    )
  {
    typedef A0                                                result_type;
    typedef typename P::type                                  perm_t;
    typedef meta::cardinal_of<result_type>                    card_t;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, P const&) const
    {
      return eval(a0, typename card_t::type());
    }

    template<typename I>
    BOOST_FORCEINLINE typename A0::value_type pick(A0 const& a0, I const&) const
    {
      typedef typename A0::value_type type;
      return (I::value >= 0) ? a0[std::size_t(I::value)]: type(0);
    }

    BOOST_SIMD_PP_REPEAT_POWER_OF_2(M2,~)
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::shuffle_, tag::cpu_
                                      , (A0)(X)(P)
                                      , ( mpl::equal_to < mpl::sizeof_<A0>
                                                        , mpl::sizeof_<typename A0::type>
                                                        >
                                        )
                                      , ((simd_< logical_<A0>, X>))
                                        ((simd_< logical_<A0>, X>))
                                        (target_< unspecified_<P> >)
                                      )
  {
    typedef A0                        result_type;
    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A0 const& a1, P const&) const
    {
      typedef typename meta::as_arithmetic<A0>::type type;
      return bitwise_cast <result_type>
                          ( shuffle<typename P::type> ( bitwise_cast<type>(a0)
                                                      , bitwise_cast<type>(a1)
                                                      )
                          );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_, tag::cpu_
                                    , (A0)(X)(P)
                                    , ((simd_< arithmetic_<A0>, X>))
                                      ((simd_< arithmetic_<A0>, X>))
                                      (target_< unspecified_<P> >)
                                    )
  {
    typedef A0                              result_type;
    typedef typename P::type                perm_t;
    typedef meta::cardinal_of<result_type>  card_t;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A0 const& a1, P const&) const
    {
      return eval(a0, a1, typename card_t::type());
    }

    template<typename I>
    BOOST_FORCEINLINE typename A0::value_type
    pick(A0 const& a0, A0 const& a1, I const&) const
    {
      typedef typename A0::value_type type;
      std::ptrdiff_t c = std::ptrdiff_t(card_t::value);
      return (I::value >= 0) ?  ( (I::value < c)  ? a0[std::size_t(I::value)]
                                                  : a1[std::size_t(I::value - c)]
                                )
                             : type(0);
    }

    BOOST_SIMD_PP_REPEAT_POWER_OF_2(M3,~)
  };
} } }

#undef M0
#undef M1
#undef M2
#undef M3

#endif

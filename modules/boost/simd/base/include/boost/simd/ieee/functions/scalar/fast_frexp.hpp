//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_FAST_FREXP_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_FAST_FREXP_HPP_INCLUDED

#include <boost/simd/ieee/functions/fast_frexp.hpp>
#include <boost/dispatch/meta/adapted_traits.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/simd/sdk/config/compiler.hpp>
#include <boost/simd/sdk/math.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::fast_frexp_, tag::cpu_
                                      , (A0)(A2)
                                      , ( boost::is_same
                                          < typename dispatch::meta::
                                                     as_integer<A0,signed>::type
                                          , A2
                                          >
                                        )
                                      , (scalar_< floating_<A0> >)
                                        (scalar_< floating_<A0> >)
                                        (scalar_< integer_<A2> >)
                                      )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A0 & a1,A2 & a2) const
    {
      a1 = boost::simd::fast_frexp(a0, a2);
    }
  };

  // frexpf appears to be buggy on GCC 4.6.3
  #if defined(BOOST_SIMD_HAS_FREXPF) && !(defined(__GNUC__) && BOOST_SIMD_GCC_VERSION < 40700)
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::fast_frexp_, tag::cpu_
                                   , (A0)(A2)
                                   , (scalar_< single_<A0> >)
                                     (scalar_< int32_<A2> >)
                                   )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A2 & a2) const
    {
      return ::frexpf(a0, &a2);
    }
  };
  #endif

  #ifdef BOOST_SIMD_HAS_FREXP
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::fast_frexp_, tag::cpu_
                                   , (A0)(A2)
                                   , (scalar_< double_<A0> >)
                                     (scalar_< int64_<A2> >)
                                   )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A2 & a2) const
    {
      int r;
      A0 that = ::frexp(a0, &r);
      a2 = r;
      return that;
    }
  };
  #endif

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::fast_frexp_, tag::cpu_
                                      , (A0)(A2)
                                      , ( boost::is_same
                                          < typename dispatch::meta::
                                                     as_integer<A0,signed>::type
                                          , A2
                                          >
                                        )
                                      , (scalar_< floating_<A0> >)
                                        (scalar_< integer_<A2> >)
                                      )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A2 & a2) const
    {
      int r;
      A0 that = std::frexp(a0, &r);
      a2 = r;
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::fast_frexp_, tag::cpu_
                                    , (A0)
                                    , (scalar_ < floating_<A0> > )
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0,signed>::type  exponent;
    typedef std::pair<A0,exponent>                          result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      A0 first;
      exponent second;
      boost::simd::fast_frexp(a0, first, second);
      return result_type(first, second);
    }
  };
} } }

#endif

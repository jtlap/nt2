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
#include <math.h>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - map to ::frexp
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::fast_frexp_, tag::cpu_
                                    , (A0)(A2)
                                    , (scalar_< double_<A0> >)
                                      (scalar_< double_<A0> >)
                                      (scalar_< int64_<A2> >)
                                    )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A0 & a1,A2 & a2) const
    {
      boost::simd::int32_t r = 0;
      a1 = ::frexp(a0, &r);
      a2 = r;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::fast_frexp_, tag::cpu_
                                    , (A0)(A2)
                                    , (scalar_< single_<A0> >)
                                      (scalar_< single_<A0> >)
                                      (scalar_< int32_<A2> >)
                                    )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A0 & a1,A2 & a2) const
    {
      a2 = 0;
      a1 = ::frexpf(a0, &a2);
    }
  };

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
      A0 a1;
      boost::simd::fast_frexp(a0, a1, a2);
      return a1;
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

//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_MAX_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_MAX_HPP_INCLUDED
#include <boost/simd/toolbox/arithmetic/functions/max.hpp>
#include <boost/simd/include/functions/scalar/is_nan.hpp>
#include <boost/simd/include/constants/nan.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::max_, tag::cpu_
                                    , (A0)
                                    , (scalar_< arithmetic_<A0> >)
                                      (scalar_< arithmetic_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return (a0 > a1) ? a0 : a1;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::max_, tag::cpu_
                                    , (A0)(A1)
                                    , (mpl_integral_< scalar_< fundamental_<A0> > >)
                                      (scalar_< arithmetic_<A1> >)
                                    )
  {
    typedef A1 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const&, A1 a1) const
    {
      return (A0::value > a1) ? A0::value : a1;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::max_, tag::cpu_
                                    , (A0)(A1)
                                    , (scalar_< arithmetic_<A0> >)
                                      (mpl_integral_< scalar_< fundamental_<A1> > >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 a0, A1 const&) const
    {
      return (a0 > A1::value) ? a0 : A1::value;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::max_, tag::cpu_
                                    , (A0)(A1)
                                    , (mpl_integral_< scalar_< fundamental_<A0> > >)
                                      (mpl_integral_< scalar_< fundamental_<A1> > >)
                                    )
  {
    typedef typename  boost::
                      common_type < typename A0::value_type
                                  , typename A1::value_type
                                  >::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const&, A1 const&) const
    {
      return (A0::value > A1::value) ? A0::value : A1::value;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::max_, tag::cpu_
                                    , (A0)
                                    , (scalar_< floating_<A0> >)
                                      (scalar_< floating_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      if (is_nan(a0) || is_nan(a1)) return Nan<result_type>();
      return (a0 > a1) ? a0 : a1;
    }
  };
} } }

#endif

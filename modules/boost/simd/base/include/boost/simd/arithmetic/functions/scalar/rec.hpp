//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_REC_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_REC_HPP_INCLUDED
#include <boost/simd/arithmetic/functions/rec.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/functions/abs.hpp>

namespace boost { namespace simd { namespace ext
{
   BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::rec_, tag::cpu_
                            , (A0)
                            , (scalar_< int_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      if (!a0) return Valmax<A0>();
      return abs(a0) == One<A0>()?  a0 : Zero<A0>();
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::rec_, tag::cpu_
                            , (A0)
                            , (scalar_< uint_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      if (!a0) return Valmax<A0>();
      return (a0 == One<A0>());
    }
  };

#ifdef BOOST_MSVC
  #pragma warning(push)
  #pragma warning(disable: 4723) // potential divide by 0
#endif

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::rec_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return One<result_type>()/a0;
    }
  };
} } }

#ifdef BOOST_MSVC
  #pragma warning(pop)
#endif

#endif

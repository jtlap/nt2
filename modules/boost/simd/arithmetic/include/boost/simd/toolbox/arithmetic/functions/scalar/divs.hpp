//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_DIVS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_DIVS_HPP_INCLUDED
#include <boost/simd/toolbox/arithmetic/functions/divs.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/mone.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divs_, tag::cpu_ , (A0)
                            , (scalar_< int_<A0> >)
                              (scalar_< int_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      if ((a0 == Valmin<result_type>()) && (a1 == Mone<result_type>()))
        return Valmax<result_type>();
      else if (a1) return a0/a1;
      else if (a0 > 0) return Valmax<result_type>();
      else if (a0 < 0) return Valmin<result_type>();
      else return Zero<result_type>();
    }
  };
} } }

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divs_, tag::cpu_ , (A0)
                            , (scalar_< uint_<A0> >)
                              (scalar_< uint_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      if (a1) return a0/a1;
      else if (a0 > 0) return Valmax<result_type>();
      else return Zero<result_type>();
    }
  };
} } }


#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4723) // potential divide by 0
#endif

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divs_, tag::cpu_, (A0)
                            , (scalar_< floating_<A0> >)
                        (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2) { return a0/a1; }
  };
} } }

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif

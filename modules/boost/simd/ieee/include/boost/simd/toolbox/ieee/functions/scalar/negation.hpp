//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_NEGATION_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_NEGATION_HPP_INCLUDED
#include <boost/simd/toolbox/ieee/functions/negation.hpp>
#include <boost/simd/include/functions/scalar/is_nez.hpp>
#include <boost/simd/include/functions/scalar/is_gez.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::negation_, tag::cpu_
                            , (A0)
                            , (scalar_< signed_<A0> >)(scalar_< signed_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return bool(is_nez(a1))*(is_gez(a1)?a0:-a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::negation_, tag::cpu_
                            , (A0)
                            , (scalar_< unsigned_<A0> >)(scalar_< unsigned_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return bool(is_nez(a1))*a0;
    }
  };
} } }


#endif

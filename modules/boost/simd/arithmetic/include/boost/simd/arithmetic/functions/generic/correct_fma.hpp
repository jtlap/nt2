//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_GENERIC_CORRECT_FMA_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_GENERIC_CORRECT_FMA_HPP_INCLUDED
#include <boost/simd/arithmetic/functions/correct_fma.hpp>
#include <boost/simd/include/functions/simd/two_prod.hpp>
#include <boost/simd/include/functions/simd/two_add.hpp>
#include <boost/simd/include/functions/simd/plus.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::correct_fma_, tag::cpu_
                                   , (A0)
                                   , (generic_< integer_<A0> >)
                                     (generic_< integer_<A0> >)
                                     (generic_< integer_<A0> >)
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(3)
    {
      return a0*a1+a2;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::correct_fma_, tag::cpu_
                                   , (A0)
                                   , (generic_< floating_<A0> >)
                                     (generic_< floating_<A0> >)
                                     (generic_< floating_<A0> >)
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(3)
    {
      A0 p, rp, s, rs;
      two_prod(a0, a1, p, rp);
      two_add(p, a2, s, rs);
      return s+(rp+rs);
    }
  };

} } }


#endif

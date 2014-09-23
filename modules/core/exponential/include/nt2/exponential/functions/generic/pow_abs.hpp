//==============================================================================
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 NUMSCALE SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_GENERIC_POW_ABS_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_GENERIC_POW_ABS_HPP_INCLUDED

#include <nt2/exponential/functions/pow_abs.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/scalar/is_odd.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_abs_, tag::cpu_
                            , (A0)(A1)
                            , (generic_< arithmetic_<A0> >)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      A0 base = a0;
      A1 exp = a1;

      result_type result = One<result_type>();
      while(exp)
      {
        if(is_odd(exp))
            result *= base;
        exp >>= 1;
        base = sqr(base);
      }

      return result;
    }
  };
} }

#endif

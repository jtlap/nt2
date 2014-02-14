//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_SCALAR_SINH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_SCALAR_SINH_HPP_INCLUDED

#include <nt2/hyperbolic/functions/sinh.hpp>
#include <nt2/include/functions/scalar/exp.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/functions/scalar/fms.hpp>
#include <nt2/include/functions/scalar/bitofsign.hpp>
#include <nt2/include/functions/scalar/bitwise_xor.hpp>

#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/maxlog.hpp>
#include <nt2/include/constants/log_2.hpp>
#include <nt2/hyperbolic/functions/details/sinh_kernel.hpp>


namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sinh_, tag::cpu_
                            , (A0)
                            , ((scalar_<floating_<A0> >))
                            )
  {

    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      result_type x = nt2::abs(a0);
      if( x < A0(1.0))
      {
       A0 x2 = sqr(x);
       return details::sinh_kernel<A0>::compute(a0, x2);
      }
      else
      {
        A0 r;
        if (BOOST_UNLIKELY( x > Maxlog<A0>()-Log_2<A0>()))
        {
          A0 tmp = exp(Half<A0>()*x);
          r = (Half<A0>()*tmp)*tmp;
        }
        else
        {
          A0 tmp = exp(x);
          r =  fms(tmp, Half<A0>(), Half<A0>()*rec(tmp));
        }
        return b_xor(r, bitofsign(a0));
      }
    }
  };

} }


#endif

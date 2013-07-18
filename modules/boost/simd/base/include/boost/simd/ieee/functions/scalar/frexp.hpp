//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_FREXP_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_FREXP_HPP_INCLUDED

#include <boost/simd/ieee/functions/frexp.hpp>
#include <boost/simd/include/functions/scalar/is_invalid.hpp>
#include <boost/simd/include/functions/scalar/bitwise_notand.hpp>
#include <boost/simd/include/functions/scalar/bitwise_and.hpp>
#include <boost/simd/include/functions/scalar/bitwise_or.hpp>
#include <boost/simd/include/functions/scalar/shr.hpp>
#include <boost/simd/include/functions/scalar/minus.hpp>
#include <boost/simd/include/functions/scalar/bitwise_cast.hpp>
#include <boost/simd/include/constants/maxexponent.hpp>
#include <boost/simd/include/constants/nbmantissabits.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::frexp_
                                    , tag::cpu_
                                    , (A0)(A1)
                                    , (scalar_< floating_<A0> >)
                                      (scalar_< floating_<A0> >)
                                      (scalar_< integer_<A1>  >)
                                    )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A0 & r0,A1& r1) const
    {
      if (a0 == 0 || is_invalid(a0))
      {
        r0 = a0;
        r1 = Zero<A1>();
      }
      else
      {
        typedef typename dispatch::meta::as_integer<A0, signed>::type int_type;
        const int_type me = Maxexponent<A0>()-1;
        const int_type nmb= Nbmantissabits<A0>();
        const int_type n1 = ((2*me+3)<<nmb);
        const int_type n2 = me<<nmb;

        A0 ci = simd::bitwise_cast<A0>(n1);
           r1 = simd::bitwise_cast<int_type>(b_and(ci, a0));  // extract exp.
        A0 x  = b_notand(ci, a0);                             // clear exp. in a0
           r1 = sub(shri(r1,nmb), me);                        // compute exp.
           r0 = b_or(x,n2);                                   // insert exp.+1 in x
        if (r1 > Maxexponent<A0>())
        {
          r1   = 0;
          r0  += a0;
        }
      }
    }
  };
} } }

#endif

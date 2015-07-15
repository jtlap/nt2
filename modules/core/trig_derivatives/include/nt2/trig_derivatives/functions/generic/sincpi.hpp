//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_SINCPI_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_SINCPI_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/sincpi.hpp>
#include <nt2/include/functions/simd/sincpi.hpp>
#include <nt2/include/functions/simd/sinc.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace ext
  {

    BOOST_DISPATCH_IMPLEMENT  ( sincpi_, tag::cpu_
                              , (order)(A0)
                              , (unspecified_<order>)
                                (generic_<unspecified_<A0>>)
                              )
    {
      typedef A0                                            result_type;
      typedef typename meta::scalar_of<A0>::type                    sA0;
      BOOST_FORCEINLINE result_type operator()(const order&
                                              , const A0& u) const
      {
        return sinc(order(), u)*pow<order::value>(Pi<A0>());
      }
   };
  }
}


#endif

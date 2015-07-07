//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_ATANPI_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_ATANPI_HPP_INCLUDED
#include <nt2/include/functions/simd/atanpi.hpp>
#include <nt2/include/functions/simd/atan.hpp>
#include <nt2/include/constants/invpi.hpp>
#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace ext
  {

    BOOST_DISPATCH_IMPLEMENT  ( atanpi_, tag::cpu_
                              , (order)(A0)
                              , (unspecified_<order>)
                                (generic_<unspecified_<A0>>)
                              )
    {
      typedef A0                                            result_type;
      BOOST_FORCEINLINE result_type operator()(const order&
                                              , const A0& u) const
      {
        return nt2::Invpi<result_type>()*atan(order(), u);
      }
    };
  }
}


#endif

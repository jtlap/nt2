//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_IEEE_FUNCTIONS_COMPLEX_GENERIC_MAXNUMMAG_HPP_INCLUDED
#define NT2_IEEE_FUNCTIONS_COMPLEX_GENERIC_MAXNUMMAG_HPP_INCLUDED
#include <nt2/ieee/functions/maxnummag.hpp>
#include <nt2/include/functions/maxnummag.hpp>
#include <nt2/include/functions/maxmag.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>
#include <nt2/include/functions/real.hpp>



namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( boost::simd::tag::maxnummag_, tag::cpu_,
                                     (A0),
                                     (generic_<complex_<floating_<A0> > >)
                                     (generic_<complex_<floating_<A0> > >)
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return if_else(is_nan(a0),
                     a1,
                     if_else(is_nan(a1),
                             a0,
                             maxmag(a0, a1)
                            )
                    );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( boost::simd::tag::maxnummag_, tag::cpu_,
                                     (A0),
                                     (generic_<dry_<floating_<A0> > >)
                                     (generic_<dry_<floating_<A0> > >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return bitwise_cast<A0>(maxnummag(real(a0), real(a1)));
    }

  };
} }


#endif

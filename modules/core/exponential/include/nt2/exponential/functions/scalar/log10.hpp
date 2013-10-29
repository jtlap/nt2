//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SCALAR_LOG10_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SCALAR_LOG10_HPP_INCLUDED

#include <nt2/exponential/functions/log10.hpp>
#include <nt2/include/functions/scalar/tofloat.hpp>
#include <nt2/include/functions/scalar/toint.hpp>
#include <nt2/include/functions/scalar/touint.hpp>
#include <boost/simd/sdk/simd/meta/is_native.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log10_, tag::cpu_
                            , (A0)
                            , (scalar_< int_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return toint(nt2::log10(nt2::tofloat(a0)));
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log10_, tag::cpu_
                            , (A0)
                            , (scalar_< uint_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return touint(nt2::log10(nt2::tofloat(a0)));
    }
  };

} }


#endif
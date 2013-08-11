//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SCALAR_EXPM1_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SCALAR_EXPM1_HPP_INCLUDED
#include <nt2/exponential/functions/expm1.hpp>
#include <nt2/include/functions/scalar/log.hpp>
#include <nt2/include/functions/scalar/exp.hpp>
#include <nt2/include/functions/scalar/minusone.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/is_invalid.hpp>
#include <nt2/include/constants/zero.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expm1_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return minusone(nt2::exp(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expm1_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      const A0 u = nt2::exp(a0);
      if( is_invalid(u) || (nt2::abs(a0) > Half<A0>()))
      {
        return u-One<A0>();
      }
      else if (u!=One<A0>())
      {
        return (u-One<A0>())*a0/nt2::log(u);
      }
      else
      {
        return nt2::Zero<A0>();
      }
    }
  };
} }


#endif

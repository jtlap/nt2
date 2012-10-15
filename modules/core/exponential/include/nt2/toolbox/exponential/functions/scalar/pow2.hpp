//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_POW2_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_POW2_HPP_INCLUDED
#include <nt2/toolbox/exponential/functions/pow2.hpp>
#include <nt2/include/functions/scalar/ldexp.hpp>
#include <nt2/include/functions/scalar/toint.hpp>
#include <nt2/include/constants/one.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow2_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< floating_<A0> >)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return nt2::ldexp(a0, a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow2_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                              (scalar_< floating_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return nt2::ldexp(a0, nt2::toint(a1));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow2_, tag::cpu_
                              , (A0)(A1)
                              , (scalar_< integer_<A0> >)
                              (scalar_< integer_<A1> >)
                              )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return nt2::ldexp(a0, a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow2_, tag::cpu_
                              , (A0)
                              , (scalar_< arithmetic_<A0> >)
                              )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(1)
    {
      return nt2::ldexp(One<A0>(), a0);
    }
  };    
} }


#endif

//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_BOOST_MATH_FUNCTIONS_SCALAR_SPHERICAL_HARMONIC_I_HPP_INCLUDED
#define NT2_TOOLBOX_BOOST_MATH_FUNCTIONS_SCALAR_SPHERICAL_HARMONIC_I_HPP_INCLUDED
#include <nt2/toolbox/boost_math/functions/spherical_harmonic_i.hpp>
#include <nt2/sdk/error/policies.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::boost_math::tag::spherical_harmonic_i_, tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , (scalar_< integer_<A0> >)(scalar_< integer_<A1> >)(scalar_< arithmetic_<A2> >)(scalar_< arithmetic_<A3> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A2, A3>::type result_type;

    NT2_FUNCTOR_CALL(4)
    {
      return spherical_harmonic_i(a0, a1, result_type(a2), result_type(a3));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::boost_math::tag::spherical_harmonic_i_, tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , (scalar_< integer_<A0> >)(scalar_< integer_<A1> >)(scalar_< floating_<A2> >)(scalar_< floating_<A3> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A2, A3>::type result_type;

    NT2_FUNCTOR_CALL(4)
    { return boost::math::spherical_harmonic_i(a0, a1, a2, a3, nt2_policy()); }
  };
} }


#endif

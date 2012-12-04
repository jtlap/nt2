//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_BOOST_MATH_FUNCTIONS_SCALAR_IBETAC_INVB_HPP_INCLUDED
#define NT2_TOOLBOX_BOOST_MATH_FUNCTIONS_SCALAR_IBETAC_INVB_HPP_INCLUDED

#include <nt2/sdk/error/policies.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::boost_math::tag::ibetac_invb_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< arithmetic_<A0> >)(scalar_< arithmetic_<A1> >)(scalar_< arithmetic_<A2> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0, A1, A2>::type result_type;

    NT2_FUNCTOR_CALL(3)
    {
      return nt2::boost_math::ibetac_invb(result_type(a0), result_type(a1), result_type(a2));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::boost_math::tag::ibetac_invb_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< floating_<A0> >)(scalar_< floating_<A1> >)(scalar_< floating_<A2> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0, A1, A2>::type result_type;

    NT2_FUNCTOR_CALL(3)
    { return boost::math::ibetac_invb(a0, a1, a2, nt2_policy()); }
  };
} }


#endif

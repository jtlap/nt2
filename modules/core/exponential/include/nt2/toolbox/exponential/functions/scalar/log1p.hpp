//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_LOG1P_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_LOG1P_HPP_INCLUDED
#include <nt2/toolbox/exponential/functions/log1p.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/mone.hpp>

#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/log.hpp>
#include <nt2/include/functions/scalar/minusone.hpp>
#include <nt2/include/functions/scalar/oneplus.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log1p_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::log(oneplus(result_type(a0)));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log1p_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      typedef result_type type;
      if (nt2::abs(a0) < Eps<A0>()) return a0;
      if (a0 < Mone<A0>())   return Nan<A0>();
      if (a0 == Inf<A0>())   return Inf<A0>();
      volatile type u = oneplus(a0);
      type uu = u;
      volatile type t =(minusone(uu)-a0);
      type v = u;
      type r =nt2::log(v);
      if (t)
        return r*(a0/minusone(v)); //-t/u; /* cancels errors with IEEE arithmetic */
      else
        return r;
    }
  };
} }


#endif

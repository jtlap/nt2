//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_ULP_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_ULP_HPP_INCLUDED
#include <nt2/include/constants/properties.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/constants/infinites.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_bits.hpp>
#include <nt2/include/constants/eps_related.hpp>
#include <nt2/include/functions/prev.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/abs.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::ulp_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {

    typedef typename meta::result_of<meta::arithmetic(A0)>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
       ignore_unused(a0);
       return One<A0>();
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::ulp_, tag::cpu_
                            , (A0)
                            , (scalar_< real_<A0> >)
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0,signed>::type int_type;
      if (is_eqz(a0)) return Mindenormal<A0>();
      const A0 x = nt2::abs(a0);
      if (x == Inf<A0>()) return x; 
      typename meta::as_bits<A0>::type aa = {x},  bb = aa;
      --bb.bits;
      ++aa.bits;
      return nt2::min(x-bb.value, aa.value-x);
    }
  };
} }


#endif

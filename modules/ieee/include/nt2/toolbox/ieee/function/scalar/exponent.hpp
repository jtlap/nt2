//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_EXPONENT_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_EXPONENT_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/functions/is_invalid.hpp>

#include <nt2/include/functions/shri.hpp>
#include <nt2/include/functions/exponentbits.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/is_eqz.hpp>

#include <nt2/toolbox/ieee/details/math.hpp>

#ifdef NT2_TOOLBOX_IEEE_HAS_ILOGB
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::exponent_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                            )
  {

    typedef typename meta::as_integer<A0, signed>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      if (is_invalid(a0)) return Zero<A0>(); 
      return a0 ? ::ilogb(a0) : Zero<A0>();
    }
  };
} }

#endif

#ifdef NT2_TOOLBOX_IEEE_HAS_ILOGBF
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::exponent_, tag::cpu_
                            , (A0)
                            , (scalar_< float_<A0> >)
                            )
  {

    typedef typename meta::as_integer<A0, signed>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      if (is_invalid(a0) || is_eqz(a0)) return Zero<A0>(); 
      return ilogbf(a0); 
    }
  };
} }

#endif

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::exponent_, tag::cpu_
                            , (A0)
                            , (scalar_< real_<A0> >)
                            )
  {

    typedef typename meta::as_integer<A0, signed>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      const int nmb= Nbmantissabits<A0>();
      const result_type x = shri(exponentbits(a0), nmb);
      return x-b_and(Maxexponent<A0>(), A0(is_nez(a0)));
    }
  };
} }


#endif

//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_POW_ABS_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_POW_ABS_HPP_INCLUDED
#include <nt2/toolbox/exponential/functions/pow_abs.hpp>
#include <nt2/include/functions/scalar/pow_absi.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/is_odd.hpp>
#include <nt2/include/functions/scalar/is_flint.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_abs_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< arithmetic_<A0> >)(scalar_< integer_<A1> >)
                            )
  {
    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::pow_absi(result_type(a0), a1);
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is double
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_abs_, tag::cpu_
                              , (A0)(A1)
                            , (scalar_< unspecified_<A0> >)(scalar_< double_<A1> >)
                            )
  {

    typedef A1 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return  ::pow(nt2::abs(a0), a1);
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is float
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_abs_, tag::cpu_
                              , (A0)(A1)
                            , (scalar_< unspecified_<A0> >)(scalar_< single_<A1> >)
                            )
  {

    typedef A1 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return  ::powf(nt2::abs(a0), a1);
    }
  };
} }


#endif

//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_POW_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_POW_HPP_INCLUDED
#include <nt2/toolbox/exponential/functions/pow.hpp>
#include <nt2/include/functions/scalar/powi.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/is_odd.hpp>
#include <nt2/include/functions/scalar/is_flint.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/zero.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< arithmetic_<A0> >)(scalar_< integer_<A1> >)
                            )
  {
    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::powi(result_type(a0), a1);
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is double
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)(scalar_< double_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      bool ltza0 = a0 < Zero<A0>(); 
      if ((a0 == a1 && a0 == Minf<A0>()) ||
	  (ltza0 && !is_flint(a1))
	  ) return Nan<A0>(); 
      A0 res =  ::pow(nt2::abs(a0), a1);
      return  (ltza0&&nt2::is_odd(a1)) ? -res : res; 
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is float
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)(scalar_< single_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      bool ltza0 = a0 < Zero<A0>(); 
      if ((a0 == a1 && a0 == Minf<A0>()) ||
	  (ltza0 && !is_flint(a1))
	  ) return Nan<A0>(); 
      A0 res =  ::powf(nt2::abs(a0), a1);
      return  (ltza0&&nt2::is_odd(a1)) ? -res : res; 
    }
  };
} }


#endif

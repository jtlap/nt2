//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_CORRECT_FMA_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_CORRECT_FMA_HPP_INCLUDED
#include <nt2/include/functions/two_prod.hpp>
#include <nt2/include/functions/two_add.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::correct_fma_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< arithmetic_<A0> >)(scalar_< arithmetic_<A1> >)(scalar_< arithmetic_<A2> >)
                            )
  {

    typedef typename meta::result_of<meta::arithmetic(A0,A1,A2)>::type result_type;

    NT2_FUNCTOR_CALL(3)
    {
       return a0*a1+a2;
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::correct_fma_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< real_<A0> >)(scalar_< real_<A1> >)(scalar_< real_<A2> >)
                            )
  {

    typedef typename meta::result_of<meta::arithmetic(A0,A1,A2)>::type result_type;

    NT2_FUNCTOR_CALL(3)
    {
        A0 p, rp, s, rs;
        boost::fusion::tie(p, rp) = two_prod(a0, a1);
        boost::fusion::tie(s, rs) = two_add(p, a2);
        return s+(rp+rs);
	//         return ::fma(a0, a1, a2);
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::correct_fma_, tag::cpu_,
                             (A0)(A1)(A2),
                             (float_<A0>)(float_<A1>)(float_<A2>)
                            )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::correct_fma_(tag::float_,tag::float_,tag::float_),
              tag::cpu_, Dummy> : callable
  {
    typedef float result_type; 

    NT2_FUNCTOR_CALL(3)
    {
      return float(double(a0)*a1+a2); 
    }
  };
} }

#endif

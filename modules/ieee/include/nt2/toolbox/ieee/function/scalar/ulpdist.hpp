//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_ULPDIST_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_ULPDIST_HPP_INCLUDED
#include <nt2/include/constants/eps_related.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/include/constants/digits.hpp>
#include <boost/fusion/tuple.hpp>

#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/frexp.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/dist.hpp>
#include <nt2/include/functions/is_nan.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::ulpdist_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< arithmetic_<A0> >)(scalar_< arithmetic_<A1> >)
                            )
  {

    typedef typename meta::result_of<meta::arithmetic(A0,A1)>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return dist(a0, a1);
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is bool_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::ulpdist_, tag::cpu_
                            , (A0)(A1)
                            , (bool_<A0>)(bool_<A1>)
                            )
  {

    typedef typename meta::result_of<meta::arithmetic(A0,A1)>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return dist(a0, is_nez(a1));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::ulpdist_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< real_<A0> >)(scalar_< real_<A1> >)
                            )
  {

    typedef typename meta::result_of<meta::arithmetic(A0,A1)>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::result_of<meta::arithmetic(A0, A1) >::type type;
      typedef typename meta::as_integer<A0>::type itype;
      if (a0 == a1)               return Zero<type>();
      if (is_nan(a0)&&is_nan(a1)) return Zero<type>();
      itype e1, e2;
      type m1, m2;
      boost::fusion::tie(m1, e1) = nt2::frexp(type(a0));
      boost::fusion::tie(m2, e2) = nt2::frexp(type(a1));
      itype expo = -nt2::max(e1, e2);
      double e = (e1 == e2) ? nt2::abs(m1-m2)
      : nt2::abs(nt2::ldexp(a0, expo)-nt2::ldexp(a1, expo));
      return e/Eps<type>();
    }
  };
} }


#endif

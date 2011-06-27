//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_TWO_PROD_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_TWO_PROD_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <nt2/include/functions/two_split.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION(tag::two_add_, tag::cpu_,
                             (A0)(A1),
                             (scalar_< real_<A0> >)(scalar_< real_<A1> >)
                            )
  {
    typedef typename meta::result_of<meta::floating(A0, A1)>::type rtype;
    typedef typename boost::fusion::tuple<rtype,rtype>             result_type;

    NT2_FUNCTOR_CALL(2)
    {
      result_type res;
      eval(a0,a1, boost::fusion::at_c<0>(res),boost::fusion::at_c<1>(res));
      return res;
    }
  private:
    template<class R0,class R1> inline void
    eval(A0 const& a, A1 const& b,R0& r0, R1& r1)const
    {
      r0  = a*b;
      if (is_invalid(r0))
      {
        r1 = Zero<R1>();
        return;
      }
      A0 a1, a2, b1, b2;
      boost::fusion::tie(a1, a2) = two_split(a);
      boost::fusion::tie(b1, b2) = two_split(b);
      r1 = a2*b2 -(((r0-a1*b1)-a2*b1)-a1*b2);
    }
  };
} }

#endif

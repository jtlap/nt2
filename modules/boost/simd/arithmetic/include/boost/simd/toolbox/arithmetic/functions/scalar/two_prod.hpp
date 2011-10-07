//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_TWO_PROD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_TWO_PROD_HPP_INCLUDED
#include <boost/dispatch/meta/adapted_traits.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/simd/include/functions/is_invalid.hpp>
#include <boost/simd/include/functions/two_split.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is floating_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  //TODO ref implementation
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::two_prod_, tag::cpu_,
                             (A0),
                             (scalar_< floating_<A0> >)(scalar_< floating_<A0> >)
                            )
  {
    typedef typename boost::dispatch::meta::result_of<boost::dispatch::meta::floating(A0)>::type       rtype;
    typedef typename boost::fusion::tuple<rtype,rtype>             result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      result_type res;
      eval(a0,a1, boost::fusion::at_c<0>(res),boost::fusion::at_c<1>(res));
      return res;
    }
  private:
    template<class AA0, class R0, class R1> inline void
    eval(AA0 const& a, AA0 const& b, R0& r0, R1& r1)const
    {
      r0  = a*b;
      if (is_invalid(r0))
      {
        r1 = Zero<R1>();
        return;
      }
      AA0 a1, a2, b1, b2;
      boost::fusion::tie(a1, a2) = two_split(a);
      boost::fusion::tie(b1, b2) = two_split(b);
      r1 = a2*b2 -(((r0-a1*b1)-a2*b1)-a1*b2);
    }
  };
} } }

#endif

//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_TWO_ADD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_TWO_ADD_HPP_INCLUDED
#include <boost/dispatch/meta/adapted_traits.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/simd/include/functions/is_invalid.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::two_add_, tag::cpu_,
                             (A0)(A1),
                             (scalar_< real_<A0> >)(scalar_< real_<A1> >)
                            )
  {
    typedef typename boost::dispatch::meta::result_of<boost::dispatch::meta::floating(A0, A1)>::type rtype;
    typedef typename boost::fusion::tuple<rtype,rtype>             result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      result_type res;
      eval(a0,a1, boost::fusion::at_c<0>(res),boost::fusion::at_c<1>(res));
      return res;
    }
    
  private:
    template<class R0,class R1> inline void
    eval(A0 const& a, A1 const& b,R0& r0, R1& r1)const
    {
      r0 = a+b;
      if (is_invalid(r0))
      {
        r1 = Zero<R1>();
        return;
      }
      A0 z = (r0-a);
      r1 =  (a-(r0-z))+(b-z);
    }
  };
} } }

#endif

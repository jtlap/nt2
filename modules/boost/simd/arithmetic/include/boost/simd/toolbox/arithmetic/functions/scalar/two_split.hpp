//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_TWO_SPLIT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_TWO_SPLIT_HPP_INCLUDED
#include <boost/simd/include/constants/properties.hpp>
#include <boost/dispatch/meta/adapted_traits.hpp>
#include <boost/fusion/tuple.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  //TODO ref implementation
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::two_split_, tag::cpu_,
                             (A0),
                             (scalar_< floating_<A0> >)
                            )
  {
    typedef typename boost::fusion::tuple<A0,A0> result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type res;
      eval(a0,boost::fusion::at_c<0>(res),boost::fusion::at_c<1>(res));
      return res;
    }
  private:
    template<class R0,class R1> inline void
    eval(A0 const& a,R0& r0, R1& r1)const
    {
      // TODO: make local constant ?
      static const int N = int(Nbmantissabits<A0>())-int((Nbmantissabits<A0>())>>1)+1;
      static const A0 fac = (1<<N)+1;
      A0 c = fac*a;
      r0 =  c-(c-a);
      r1 = a-r0;
    }
  };
} } }

#endif

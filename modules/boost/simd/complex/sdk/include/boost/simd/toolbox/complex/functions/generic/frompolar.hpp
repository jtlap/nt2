//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_COMPLEX_FUNCTIONS_GENERIC_FROMPOLAR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_COMPLEX_FUNCTIONS_GENERIC_FROMPOLAR_HPP_INCLUDED
#include <boost/simd/toolbox/complex/functions/frompolar.hpp>
#include <boost/simd/sdk/complex/complex.hpp>
#include <boost/simd/sdk/complex/meta/as_complex.hpp>
//#include <nt2/include/functions/sincos.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::frompolar_, tag::cpu_, (A0)
                            , (generic_< arithmetic_<A0> >)
                              (generic_< arithmetic_<A0> >)
                            )
  {
    typedef typename meta::as_complex<A0>::type  result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      A0 s, c;
      ::sincos(a1, s, c); //TO DO nt2::sincos
      return a0*result_type(c, s); 
    }
  };
  
} } }

#endif

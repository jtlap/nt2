//==============================================================================
//        Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//        Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//         Distributed under the Boost Software License, Version 1.0.
//                See accompanying file LICENSE.txt or copy at
//                    http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMPLEX_COMMON_SPLAT_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMPLEX_COMMON_SPLAT_HPP_INCLUDED
#include <nt2/toolbox/operator/functions/splat.hpp>
#include <nt2/include/functions/insert.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::splat_, tag::cpu_
                            , (A0)(A1)(X)
                            , (unspecified_<A0>)
                              ((target_<simd_<complex_<arithmetic_<A1> >, X > >))
                            )
  {
    typedef typename A1::type result_type;
    inline result_type operator()(const A0& a0, const A1&) const
    {
      typedef typename meta::as_real<A1>::type rtype; 
      return result_type(splat < rtype>(real(a0)),  splat<rtype>(imag(a0))); 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::splat_, tag::cpu_
                            , (A0)(A1)(X)
                            , (unspecified_<A0>)
                              ((target_<simd_<imaginary_< arithmetic_<A1> >, X > >))
                            )
  {
    typedef typename A1::type result_type;
    inline result_type operator()(const A0& a0, const A1&) const
    {
      typedef typename meta::as_real<A1>::type rtype; 
      return result_type(splat<rtype>(imag(a0))); 
    }
  };  
} }

#endif

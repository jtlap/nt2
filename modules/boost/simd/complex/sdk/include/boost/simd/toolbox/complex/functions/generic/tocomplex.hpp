//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_COMPLEX_FUNCTIONS_GENERIC_TOCOMPLEX_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_COMPLEX_FUNCTIONS_GENERIC_TOCOMPLEX_HPP_INCLUDED
#include <boost/simd/toolbox/complex/functions/tocomplex.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/sdk/complex/imaginary.hpp>
#include <boost/simd/sdk/complex/complex.hpp>
#include <boost/simd/sdk/complex/meta/as_real.hpp>
#include <boost/simd/sdk/complex/meta/as_complex.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::tocomplex_, tag::cpu_, (A0)
                            , (generic_< arithmetic_<A0> >)
                            )
  {
    typedef typename meta::as_complex<A0>::type  result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return result_type(a0);
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::tocomplex_, tag::cpu_, (A0)
                            , (generic_< imaginary_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      typedef typename meta::as_real<A0>::type rtype;
      return result_type(Zero<rtype>(), imag(a0));
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::tocomplex_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_complex<A0>::type const &result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return a0;
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::tocomplex_, tag::cpu_, (A0)
                            , (generic_< arithmetic_<A0> >)
                              (generic_< arithmetic_<A0> >)              
                            )
  {
    typedef typename meta::as_complex<A0>::type const &result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      return result_type(a0, a1);
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::tocomplex_, tag::cpu_, (A0)(A1)
                            , (generic_< arithmetic_<A0> >)
                              (generic_< imaginary_<A1> >)              
                            )
  {
    typedef typename meta::as_complex<A0>::type const &result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return result_type(a0, imag(a1));
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::tocomplex_, tag::cpu_, (A0)(A1)
                            , (generic_< imaginary_<A0> >)
                              (generic_< arithmetic_<A1> >)              
                            )
  {
    typedef typename meta::as_complex<A0>::type const &result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return result_type(a1, imag(a0));
    }
  };
} } }

#endif

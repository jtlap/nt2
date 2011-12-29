//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Averageributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_AVERAGE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_AVERAGE_HPP_INCLUDED
#include <boost/simd/toolbox/arithmetic/functions/average.hpp>
#include <boost/simd/include/functions/real.hpp>
#include <boost/simd/include/functions/imag.hpp>
#include <boost/simd/include/functions/hypot.hpp>
#include <boost/simd/include/functions/abs.hpp>
#include <boost/simd/include/functions/minus.hpp>
#include <boost/simd/include/constants/half.hpp>
#include <boost/simd/sdk/complex/meta/as_complex.hpp>
#include <boost/simd/sdk/complex/meta/as_real.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::average_, tag::cpu_, (A0)(A1)
                            , (generic_< complex_ < arithmetic_<A0> > > )
                              (generic_< complex_ < arithmetic_<A1> > > )
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return result_type(average(real(a0), real(a1)),average(imag(a0), imag(a1))) ; 
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::average_, tag::cpu_, (A0)(A1)
                            , (generic_< imaginary_< arithmetic_<A0> > >)
                              (generic_< complex_< arithmetic_<A1> > >)
                            )
  {
    typedef A1 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_real<A1>::type rA1;
      return result_type(real(a1)*Half<rA1>(),average(imag(a0), imag(a1))) ; 
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::average_, tag::cpu_, (A0)(A1)
                            ,  (generic_< complex_< arithmetic_<A0> > >)
                               (generic_< imaginary_< arithmetic_<A1> > >)
                             
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_real<A0>::type rA0;
      return result_type(real(a0)*Half<rA0>(),average(imag(a0), imag(a1))) ; 
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::average_, tag::cpu_, (A0)(A1)
                            ,  (generic_< imaginary_< arithmetic_<A0> > >)
                               (generic_< imaginary_< arithmetic_<A1> > >)
                             
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return result_type(average(imag(a0), imag(a1))); 
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::average_, tag::cpu_, (A0)(A1)
                            ,  (generic_< arithmetic_<A0> >)
                               (generic_< imaginary_< arithmetic_<A1> > >)
                             
                            )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return result_type(a0, imag(a1))*Half<A0>() ; 
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::average_, tag::cpu_, (A0)(A1)
                            ,  (generic_< imaginary_< arithmetic_<A0> > >)
                               (generic_< arithmetic_<A1> >)
                             
                            )
  {
    typedef typename meta::as_complex<A1>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return result_type(a1, imag(a0))*Half<A1>() ; 
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::average_, tag::cpu_, (A0)(A1)
                            ,  (generic_< arithmetic_<A0> >)
                               (generic_< complex_< arithmetic_<A1> > >)
                             
                            )
  {
    typedef A1 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return result_type(average(real(a0), real(a1)),imag(a1)*Half<A0>()) ; 
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::average_, tag::cpu_, (A0)(A1)
                            ,  (generic_< complex_< arithmetic_<A0> > >)
                               (generic_< arithmetic_<A1> >)
                             
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return result_type(average(real(a0), real(a1)),imag(a0)*Half<A1>()) ; 
    }
  };  
} } }

#endif

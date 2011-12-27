//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_COMPLEX_GENERIC_IS_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_COMPLEX_GENERIC_IS_EQUAL_HPP_INCLUDED
#include <boost/simd/include/functions/is_equal.hpp>
#include <boost/simd/include/functions/logical_and.hpp>
#include <boost/simd/include/functions/is_real.hpp>
#include <boost/simd/include/functions/is_imag.hpp>
#include <boost/simd/include/functions/imag.hpp>
#include <boost/simd/include/functions/real.hpp>
#include <boost/simd/sdk/complex/complex.hpp>
#include <boost/simd/sdk/complex/imaginary.hpp>

namespace boost { namespace simd { namespace ext
{
  // complex/complex
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_equal_, tag::cpu_, (A0)(A1)
                            , (generic_< complex_< arithmetic_<A0> > >)
                              (generic_< complex_< arithmetic_<A1> > >)
                            )
  {
    typedef typename  meta::real_of<A0>::type rA0; 
    typedef typename meta::as_logical<rA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return logical_and(is_equal(real(a0),real(a1)), is_equal(imag(a0),imag(a1))); 
    }
  };
  // complex/arithmetic
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_equal_, tag::cpu_, (A0)(A1)
                            , (generic_< complex_< arithmetic_<A0> > >)
                              (generic_< arithmetic_<A1> >)
                            )
  {
    typedef typename  meta::real_of<A0>::type rA0; 
    typedef typename meta::as_logical<rA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return logical_and(is_equal(real(a0), a1), is_real(a0)); 
    }
  };
  // arithmetic/complex
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_equal_, tag::cpu_, (A0)(A1), 
                              (generic_< arithmetic_<A0> >)
                              (generic_< complex_< arithmetic_<A1> > >)
                            )
  {
    typedef typename  meta::real_of<A0>::type rA0; 
    typedef typename meta::as_logical<rA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return logical_and(is_equal(real(a1),a0), is_real(a1)); 
    }
  };
  // complex/imaginary
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_equal_, tag::cpu_, (A0)(A1)
                            , (generic_< complex_< arithmetic_<A0> > >)
                              (generic_< imaginary_< arithmetic_<A1> > >)
                            )
  {
    typedef typename  meta::real_of<A0>::type rA0; 
    typedef typename meta::as_logical<rA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return logical_and(is_equal(imag(a0), imag(a1)), is_imag(a0)); 
    }
  };
  // imaginary/complex
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_equal_, tag::cpu_, (A0)(A1), 
                              (generic_< imaginary_< arithmetic_<A0> > > )
                              (generic_< complex_< arithmetic_<A1> > >)
                            )
  {
    typedef typename  meta::real_of<A0>::type rA0; 
    typedef typename meta::as_logical<rA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return logical_and(is_equal(imag(a1),imag(a0)), is_imag(a1)); 
    }
  };
  // imaginary/imaginary
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_equal_, tag::cpu_, (A0)(A1), 
                              (generic_< imaginary_< arithmetic_<A0> > > )
                              (generic_< imaginary_< arithmetic_<A1> > >)
                            )
  {
    typedef typename  meta::real_of<A0>::type rA0; 
    typedef typename meta::as_logical<rA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return is_equal(imag(a0),imag(a1)); 
    }
  };
  // imaginary/arithmetic
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_equal_, tag::cpu_, (A0)(A1), 
                              (generic_< imaginary_< arithmetic_<A0> > > )
                              (generic_< arithmetic_<A1> >)
                            )
  {
    typedef typename  meta::real_of<A0>::type rA0; 
    typedef typename meta::as_logical<rA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return logical_and(is_real(a0), is_imag(a1)); 
    }
  };
  // arithmetic/imaginary
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_equal_, tag::cpu_, (A0)(A1), 
                              (generic_< arithmetic_<A0> >)
                              (generic_< imaginary_< arithmetic_<A1> > > )
                            )
  {
    typedef typename  meta::real_of<A0>::type rA0; 
    typedef typename meta::as_logical<rA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return logical_and(is_real(a1), is_imag(a0)); 
    }
  };

} } }

#endif

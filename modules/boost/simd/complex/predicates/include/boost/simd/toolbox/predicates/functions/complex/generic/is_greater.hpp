//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_COMPLEX_GENERIC_IS_GREATER_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_COMPLEX_GENERIC_IS_GREATER_HPP_INCLUDED
#include <boost/simd/include/functions/is_greater.hpp>
#include <boost/simd/include/functions/logical_and.hpp>
#include <boost/simd/include/functions/is_real.hpp>
#include <boost/simd/include/functions/is_imag.hpp>
#include <boost/simd/include/functions/imag.hpp>
#include <boost/simd/include/functions/real.hpp>
#include <boost/simd/include/functions/is_gtz.hpp>
#include <boost/simd/include/functions/is_ltz.hpp>
#include <boost/simd/include/functions/is_greater.hpp>
#include <boost/simd/sdk/complex/complex.hpp>
#include <boost/simd/sdk/complex/imaginary.hpp>
#include <boost/simd/include/constants/false.hpp>

namespace boost { namespace simd { namespace ext
{
  // complex/complex
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_greater_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                              (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef typename  meta::real_of<A0>::type rA0; 
    typedef typename meta::as_logical<rA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return is_greater(real(a0),real(a1)); 
    }
  };
  // complex/arithmetic
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_greater_, tag::cpu_, (A0)(A1)
                            , (generic_< complex_< arithmetic_<A0> > >)
                              (generic_< arithmetic_<A1> >)
                            )
  {
    typedef typename  meta::real_of<A0>::type rA0; 
    typedef typename meta::as_logical<rA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return is_greater(real(a0), a1); 
    }
  };
  // arithmetic/complex
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_greater_, tag::cpu_, (A0)(A1), 
                              (generic_< arithmetic_<A0> >)
                              (generic_< complex_< arithmetic_<A1> > >)
                            )
  {
    typedef typename  meta::real_of<A0>::type rA0; 
    typedef typename meta::as_logical<rA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return is_greater(real(a1),a0); 
    }
  };
  // complex/imaginary
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_greater_, tag::cpu_, (A0)(A1)
                            , (generic_< complex_< arithmetic_<A0> > >)
                              (generic_< imaginary_< arithmetic_<A1> > >)
                            )
  {
    typedef typename  meta::real_of<A0>::type rA0; 
    typedef typename meta::as_logical<rA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return is_gtz(real(a0)); 
    }
  };
  // imaginary/complex
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_greater_, tag::cpu_, (A0)(A1), 
                              (generic_< imaginary_< arithmetic_<A0> > > )
                              (generic_< complex_< arithmetic_<A1> > >)
                            )
  {
    typedef typename  meta::real_of<A0>::type rA0; 
    typedef typename meta::as_logical<rA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return is_ltz(real(a1)); 
    }
  };
  // imaginary/imaginary
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_greater_, tag::cpu_, (A0), 
                              (generic_< imaginary_< arithmetic_<A0> > > )
                              (generic_< imaginary_< arithmetic_<A0> > >)
                            )
  {
    typedef typename  meta::real_of<A0>::type rA0; 
    typedef typename meta::as_logical<rA0>::type result_type;
    inline result_type operator()(const A0&, const A0&) const
    {
      return False<result_type>(); 
    }
  };
  // imaginary/arithmetic
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_greater_, tag::cpu_, (A0)(A1), 
                              (generic_< imaginary_< arithmetic_<A0> > > )
                              (generic_< arithmetic_<A1> >)
                            )
  {
    typedef typename  meta::real_of<A0>::type rA0; 
    typedef typename meta::as_logical<rA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return is_ltz(a1); 
    }
  };
  // arithmetic/imaginary
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_greater_, tag::cpu_, (A0)(A1), 
                              (generic_< arithmetic_<A0> >)
                              (generic_< imaginary_< arithmetic_<A1> > > )
                            )
  {
    typedef typename  meta::real_of<A0>::type rA0; 
    typedef typename meta::as_logical<rA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return  is_gtz(a0); 
    }
  };

} } }

#endif

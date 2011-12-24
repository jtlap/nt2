//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_COMPLEX_GENERIC_PLUS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_COMPLEX_GENERIC_PLUS_HPP_INCLUDED
#include <boost/simd/toolbox/operator/functions/plus.hpp>
#include <boost/simd/include/functions/real.hpp>
#include <boost/simd/include/functions/imag.hpp>
#include <boost/simd/sdk/complex/imaginary.hpp>
#include <boost/simd/sdk/complex/meta/as_complex.hpp>

namespace boost { namespace simd { namespace ext
{
  // complex/complex
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::plus_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                              (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return result_type( real(a0) + real(a1)
                        , imag(a0) + imag(a1)
                        );
    }
  };
  
  // complex/real
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::plus_, tag::cpu_, (A0)(A1)
                            , (generic_< arithmetic_<A0> >)
                              (generic_< complex_< arithmetic_<A1> > >)
                            )
  {
    typedef A1 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return result_type( real(a0) + real(a1)
                        , imag(a1)
                        );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::plus_, tag::cpu_, (A0)(A1)
                            , (generic_< complex_< arithmetic_<A0> > >)
                              (generic_< arithmetic_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return result_type( real(a0) + real(a1)
                        , imag(a0)
                        );
    }
  };
  
  // complex/imaginary
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::plus_, tag::cpu_, (A0)(A1)
                            , (generic_< imaginary_< arithmetic_<A0> > >)
                              (generic_< complex_< arithmetic_<A1> > >)
                            )
  {
    typedef A1 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return result_type( real(a1)
                        , imag(a0) + imag(a1)
                        );
    }
  };
  

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::plus_, tag::cpu_, (A0)(A1)
                            , (generic_< complex_< arithmetic_<A0> > >)
                              (generic_< imaginary_< arithmetic_<A1> > >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return result_type( real(a0)
                        , imag(a0) + imag(a1)
                        );
    }
  };
  
  // imaginary/real
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::plus_, tag::cpu_, (A0)(A1)
                            , (generic_< arithmetic_<A0> >)
                              (generic_< imaginary_< arithmetic_<A1> > >)
                            )
  {
    typedef typename meta::as_complex<A1>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return result_type( real(a0)
                        , imag(a1)
                        );
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::plus_, tag::cpu_, (A0)(A1)
                            , (generic_< imaginary_< arithmetic_<A0> > >)
                              (generic_< arithmetic_<A1> >)
                            )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return result_type( real(a1)
                        , imag(a0)
                        );
    }
  };
  
  // imaginary/imaginary
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::plus_, tag::cpu_, (A0)(A1)
                            , (generic_< imaginary_< arithmetic_<A0> > >)
                              (generic_< imaginary_< arithmetic_<A1> > >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return result_type(imag(a0) + imag(a1));
    }
  };
  
} } }

#endif

//============================================================================== 
// Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II 
// Copyright 2009 - 2011 LRI UMR 8623 CNRS/Univ Paris Sud XI 
// 
// Distributed under the Boost Software License, Version 1.0.  
// See accompanying file LICENSE.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt 
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_COMPLEX_COMMON_PUT_FIRST_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_COMPLEX_COMMON_PUT_FIRST_HPP_INCLUDED
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/sdk/complex/meta/as_complex.hpp>
#include <boost/simd/sdk/complex/meta/as_real.hpp>
#include <boost/simd/include/functions/imag.hpp>
#include <boost/simd/include/functions/real.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::put_first_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<complex_<arithmetic_<A0> >,X>))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return result_type(put_first(real(a0), a1), put_first(imag(a0), a1)); 
    }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::put_first_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<imaginary_<arithmetic_<A0> >,X>))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return result_type(put_first(imag(a0), a1)); 
    }
  };
} } }


#endif

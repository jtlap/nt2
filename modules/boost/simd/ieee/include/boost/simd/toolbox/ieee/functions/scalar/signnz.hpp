//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_SIGNNZ_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_SIGNNZ_HPP_INCLUDED
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/functions/is_ltz.hpp>
#include <boost/simd/include/functions/is_gez.hpp>
#include <boost/simd/include/functions/is_nan.hpp>
#include <boost/simd/include/functions/is_positive.hpp>
#include <boost/simd/include/functions/is_negative.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::signnz_, tag::cpu_
                            , (A0)
                            , (scalar_< signed_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1) { return is_gez(a0)-is_ltz(a0); }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::signnz_, tag::cpu_
                            , (A0)
                            , (scalar_< unsigned_<A0> >)
                            )
  {
    typedef A0 result_type;
    inline result_type operator()(A0 const &)const { return One<A0>(); }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::signnz_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1) { return is_nan(a0)?a0:is_positive(a0)-is_negative(a0); }
  };
} } }

#endif

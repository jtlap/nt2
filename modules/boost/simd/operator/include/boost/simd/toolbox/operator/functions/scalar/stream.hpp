//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SCALAR_STREAM_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SCALAR_STREAM_HPP_INCLUDED
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/simd/sdk/memory/details/category.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::stream_, tag::cpu_, (A0)(A1)(A2)
                            , (scalar_< fundamental_<A0> >)
                              (iterator_< scalar_< fundamental_<A1> > >)
                              (scalar_< integer_<A2> >)
                            )
  {
    // TODO : _mm_stream_si32/64
    
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(3)
    {
      A1 that = a1;
      std::advance(that,a2);
      return *that = a0;
    }
  };
} } }

#endif

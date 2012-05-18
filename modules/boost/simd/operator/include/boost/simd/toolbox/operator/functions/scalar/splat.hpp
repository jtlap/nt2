//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SCALAR_SPLAT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SCALAR_SPLAT_HPP_INCLUDED
#include <boost/simd/toolbox/operator/functions/splat.hpp>
#include <boost/dispatch/meta/as.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::splat_ , tag::cpu_ , (A0)(A1)
                            , (scalar_< fundamental_<A0> >)
                              (target_< scalar_< fundamental_<A1> > >)
                            )
  {
    typedef typename A1::type result_type;
    inline result_type operator()(const A0& a0, const A1&) const
    {
      result_type that = static_cast<result_type>(a0);
      return that;
    }
  };
} } }

#endif

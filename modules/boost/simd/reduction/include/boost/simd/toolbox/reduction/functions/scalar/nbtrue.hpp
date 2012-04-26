//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SCALAR_NBTRUE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SCALAR_NBTRUE_HPP_INCLUDED

#include <boost/simd/toolbox/reduction/functions/nbtrue.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/sdk/meta/templatize.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::nbtrue_, tag::cpu_
                                   , (A0)
                                   , (scalar_< fundamental_<A0> >)
                                   )
  {
    typedef typename meta::int32_t_<A0>::type result_type;
    inline result_type operator()(A0 const & a0, A1 const &) const
    {
      return a0 ? One<result_type>() : Zero<result_type>();
    }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::nbtrue_, tag::cpu_
                                   , (A0)(A1)
                                   , (scalar_< fundamental_<A0> >)
                                     (scalar_< integer_<A1> > )
                                   )
  {
    typedef typename meta::int32_t_<A0>::type result_type;
    inline result_type operator()(A0 const & a0, A1 const &) const
    {
      return a0 ? One<result_type>() : Zero<result_type>();
    }
  };  
} } }


#endif

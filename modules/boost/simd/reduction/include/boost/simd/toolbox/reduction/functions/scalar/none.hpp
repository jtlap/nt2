//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SCALAR_NONE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SCALAR_NONE_HPP_INCLUDED
#include <boost/simd/include/functions/scalar/is_nez.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::none_, tag::cpu_,
                     (A0),
                     (scalar_ < fundamental_<A0> > )
                    )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
      {
        return is_eqz(a0);
      };
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::none_, tag::cpu_,
                     (A0)(A1),
                     (scalar_<arithmetic_<A0> >)
                     (scalar_<integer_<A1> >)                 
                    )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    inline result_type operator()(A0 const & a0, A1 const &) const
      { return is_eqz(a0); };
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::none_, tag::cpu_,
                     (A0)(A1),
                     (scalar_<logical_<A0> >)
                     (scalar_<integer_<A1> >)                 
                                    )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    inline result_type operator()(A0 const & a0, A1 const &) const
      { return a0; };
  };    
} } }
#endif

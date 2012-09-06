//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_COMMON_INBTRUE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_COMMON_INBTRUE_HPP_INCLUDED

#include <boost/simd/toolbox/reduction/functions/inbtrue.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::inbtrue_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<fundamental_<A0>,X>))
                            )
  {
    typedef boost::simd::int32_t result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type z = a0[0] != 0;
      for(size_t i = 1; i< boost::simd::meta::cardinal_of<A0>::value; ++i)
      {
          z += a0[i] != 0;
      }
      return z;
    }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::inbtrue_, tag::cpu_
                                     , (A0)(A1)(X)
                                     , ((simd_<fundamental_<A0>,X>))
                                     (scalar_< integer_<A1> > )
                                     )
  {
    typedef boost::simd::int32_t result_type;
    inline result_type operator()(A0 const & a0, A1 const &) const
    {
      result_type z = a0[0] != 0;
      for(size_t i = 1; i< boost::simd::meta::cardinal_of<A0>::value; ++i)
      {
          z += a0[i] != 0;
      }
      return z;
    }
  };
} } }


#endif

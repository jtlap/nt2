//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_COMMON_GENMASK_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_COMMON_GENMASK_HPP_INCLUDED

#include <boost/simd/toolbox/bitwise/functions/genmask.hpp>
#include <boost/simd/include/functions/is_nez.hpp>
#include <boost/simd/include/functions/if_else_zero.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/simd/include/constants/allbits.hpp>
#include <boost/simd/sdk/meta/as_arithmetic.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::genmask_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<fundamental_<A0>,X>))
                            )
  {
    typedef typename meta::as_arithmetic<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return if_else_zero(a0, Allbits<result_type>());
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::genmask_, tag::cpu_
                            , (A0)(X)
                            , (mpl::equal_to< mpl::sizeof_<A0>, mpl::sizeof_<typename A0::type> >)
                            , ((simd_<logical_<A0>,X>))
                            )
  {
    typedef typename A0::type const& result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return bitwise_cast<typename A0::type>(a0);
    }
  };
} } }

#endif

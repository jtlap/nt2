//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_MEMORY_DETAILS_IS_POWER_OF_2_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_DETAILS_IS_POWER_OF_2_HPP_INCLUDED

#include <boost/dispatch/meta/mpl.hpp>
#include <boost/simd/sdk/memory/details/category.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>

//==============================================================================
// is_power_of_2 on integers
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_power_of_2_, tag::cpu_
                                   , (A0), (scalar_< integer_<A0> >)
                                   )
  {
    typedef bool result_type;
    BOOST_SIMD_FUNCTOR_CALL(1) { return (!(a0 & (a0 - 1)) && a0); }
  };
} } }

//==============================================================================
// is_power_of_2 on mpl integral
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_power_of_2_, tag::cpu_
                                   , (A0), (mpl_integral_< scalar_< arithmetic_<A0> > >)
                                   )
  {
    typedef bool result_type;
    inline result_type operator()(A0 const&)const
    {
      return boost::simd::meta::is_power_of_2<A0>::value;
    }
  };
} } }

#endif

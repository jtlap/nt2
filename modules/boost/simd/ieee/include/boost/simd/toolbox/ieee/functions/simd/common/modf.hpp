//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_MODF_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_MODF_HPP_INCLUDED
#include <boost/simd/toolbox/ieee/functions/modf.hpp>
#include <boost/simd/include/functions/simd/trunc.hpp>
#include <boost/fusion/include/std_pair.hpp>

namespace boost { namespace simd { namespace ext
{
    BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::modf_, tag::cpu_
                                      , (A0)(X)
                                      , ((simd_< arithmetic_<A0>, X>))
                                        ((simd_< arithmetic_<A0>, X>))
                                        ((simd_< arithmetic_<A0>, X>))
                                      )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A0 & r1,A0 & r0) const
    {
      r1 = boost::simd::trunc(a0);
      r0 = a0-r1;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::modf_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_< arithmetic_<A0>, X>))
                                      ((simd_< arithmetic_<A0>, X>))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE A0 operator()(A0 const& a0,A0 & r1) const
    {
      r1 = boost::simd::trunc(a0);
      return a0-r1;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::modf_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<arithmetic_<A0>,X>))
                                    )
  {
    typedef std::pair<A0, A0> result_type;
    BOOST_FORCEINLINE A0 operator()(A0 const& a0) const
    {
      result_type res;
      res.first = boost::simd::modf(a0,res.second);
      return res;
    }
  };
} } }
#endif

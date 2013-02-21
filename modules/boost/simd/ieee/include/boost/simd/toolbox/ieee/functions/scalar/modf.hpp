//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_MODF_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_MODF_HPP_INCLUDED
#include <boost/simd/toolbox/ieee/functions/modf.hpp>
#include <boost/simd/include/functions/scalar/trunc.hpp>
#include <boost/fusion/include/std_pair.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::modf_, tag::cpu_
                                    , (A0)
                                    , (scalar_ < arithmetic_<A0> > )
                                      (scalar_ < arithmetic_<A0> > )
                                      (scalar_ < arithmetic_<A0> > )
                                    )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A0 & r0,A0 & r1) const
    {
      r0 = boost::simd::trunc(a0);
      r1 = a0 - r0;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::modf_, tag::cpu_
                                    , (A0)
                                    , (scalar_ < arithmetic_<A0> > )
                                      (scalar_ < arithmetic_<A0> > )
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE A0 operator()(A0 const& a0,A0 & a1) const
    {
      result_type r;
      boost::simd::modf(a0,r,a1);
      return r;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::modf_, tag::cpu_
                                    , (A0)
                                    , (scalar_ < arithmetic_<A0> > )
                                    )
  {
    typedef std::pair<A0,A0> result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      result_type res;
      boost::simd::modf(a0, res.first, res.second);
      return res;
    }
  };
} } }

#endif

//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SCALAR_INSERT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SCALAR_INSERT_HPP_INCLUDED

#include <boost/simd/toolbox/operator/functions/insert.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::insert_, tag::cpu_, (A0)(A1)(A2)
                            , (scalar_< fundamental_<A0> >)
                              (scalar_< fundamental_<A1> >)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef A1& result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1& a1, A2 const&) const
    {
      return a1 = a0;
    }
  };
} } }

#endif

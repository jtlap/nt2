/*******************************************************************************
 *         Copyright 2003-2011 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SCALAR_LOGICAL_ORNOT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SCALAR_LOGICAL_ORNOT_HPP_INCLUDED
#include <boost/simd/sdk/simd/logical.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::logical_ornot_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< fundamental_<A0> >)
                              (scalar_< fundamental_<A1> >)
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2) { return result_type(a0 || !a1); }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::logical_ornot_, tag::cpu_
                             , (A0)(A1)
                             , (scalar_< logical_<A0> >)
                               (scalar_< logical_<A1> >)
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2) { return result_type(a0.value() || !a1.value()); }
  };

} } }

#endif


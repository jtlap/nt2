//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SCALAR_MULTIPLIES_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SCALAR_MULTIPLIES_HPP_INCLUDED

#include <boost/simd/toolbox/operator/functions/multiplies.hpp>
#include <boost/mpl/times.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::multiplies_, tag::cpu_, (A0)
                            , (scalar_< arithmetic_<A0> >)
                              (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2) { return a0 * a1; }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::multiplies_, tag::cpu_, (A0)(A1)
                            , (mpl_integral_< scalar_< arithmetic_<A0> > >)
                              (mpl_integral_< scalar_< arithmetic_<A1> > >)
                            )
  {
    typedef typename mpl::times<A0, A1>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const&, A1 const&) const
    {
      return result_type();
    }
  };
} } }

#endif

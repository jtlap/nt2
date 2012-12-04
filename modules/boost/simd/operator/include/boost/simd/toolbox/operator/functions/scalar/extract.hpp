//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SCALAR_EXTRACT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SCALAR_EXTRACT_HPP_INCLUDED

#include <boost/simd/toolbox/operator/functions/extract.hpp>
#include <boost/dispatch/meta/as_ref.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::extract_, tag::cpu_, (A0)(A1)
                            , (scalar_< fundamental_<A0> >)
                              (scalar_< integer_<A1> >)
                            )
  {
    template<class Sig>
    struct result;

    template<class This, class A0_, class A1_>
    struct result<This(A0_, A1_)>
         : dispatch::meta::as_ref<A0_>
    {
    };

    template<class A0_>
    BOOST_FORCEINLINE A0_& operator()(A0_& a0, A1 const&) const
    {
      return a0;
    }
  };
} } }

#endif

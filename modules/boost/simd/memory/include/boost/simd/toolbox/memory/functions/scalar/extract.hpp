//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_MEMORY_FUNCTIONS_SCALAR_EXTRACT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_MEMORY_FUNCTIONS_SCALAR_EXTRACT_HPP_INCLUDED

#include <boost/simd/toolbox/memory/functions/extract.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>
#include <boost/simd/sdk/functor/hierarchy.hpp>
#include <boost/dispatch/meta/as_ref.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::extract_
                                    , tag::cpu_
                                    , (A0)(A1)
                                    , (scalar_< fundamental_<A0> >)
                                      (scalar_< integer_<A1> >)
                                    )
  {
    /// This is required as extract should keep A0 const-ness in return type
    template<typename Sig> struct result;

    template<typename This, typename A0_, typename A1_>
    struct result<This(A0_, A1_)> : dispatch::meta::as_ref<A0_>
    {};

    template<typename A0_>
    BOOST_FORCEINLINE A0_& operator()(A0_& a0, A1) const
    {
      return a0;
    }
  };
} } }

#endif

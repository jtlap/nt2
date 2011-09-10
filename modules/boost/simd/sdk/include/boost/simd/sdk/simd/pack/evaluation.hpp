/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_PACK_EVALUATION_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_EVALUATION_HPP_INCLUDED

#include <boost/dispatch/dsl/compute.hpp>
#include <boost/dispatch/dsl/category.hpp>
#include <boost/simd/sdk/dsl/evaluation.hpp>

//==============================================================================
// Evaluation of simd native pack
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::evaluate_, tag::cpu_
                            , (A0)(Tag)
                              (expr_< unspecified_<A0>, boost::simd::domain, Tag >)
                            )
  {
    typedef typename A0::result_type result_type;
    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(A0 const& a0) const
    {
      return dispatch::meta::
             compile< dispatch::meta::
                      compute< mpl::_1
                             , BOOST_SIMD_DEFAULT_SITE
                             >
                    >()(a0);
    }
  };
} } }

#endif

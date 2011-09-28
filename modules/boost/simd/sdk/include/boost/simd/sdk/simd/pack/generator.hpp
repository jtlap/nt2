/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_PACK_GENERATOR_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_GENERATOR_HPP_INCLUDED

#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/simd/sdk/dsl/lambda_generator.hpp>
#include <boost/simd/sdk/dsl/typed_expression.hpp>

namespace boost { namespace simd
{
  typedef meta::
          lambda_pod_generator< meta::
                                typed_expression< typename mpl::
                                                  lambda< expression<mpl::_1, mpl::_2> >::type
                                                >
                              > generator;
} }

#endif

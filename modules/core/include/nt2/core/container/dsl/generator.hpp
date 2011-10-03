//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_GENERATOR_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_GENERATOR_HPP_INCLUDED

#include <nt2/core/container/dsl/forward.hpp>
#include <boost/simd/sdk/dsl/lambda_generator.hpp>
#include <boost/simd/sdk/dsl/typed_expression.hpp>
#include <boost/mpl/lambda.hpp>

namespace nt2 { namespace container
{
  typedef boost::simd::meta::
          lambda_generator< boost::simd::meta::
                            typed_expression< typename boost::mpl::
                                              lambda< expression<boost::mpl::_1, boost::mpl::_2> >::type
                                            >
                          > generator;
} }

#endif

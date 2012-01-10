//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_OPTIMIZE_IS_NOT_GREATER_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_OPTIMIZE_IS_NOT_GREATER_EQUAL_HPP_INCLUDED
#include <boost/simd/toolbox/predicates/functions/is_not_greater_equal.hpp>
#include <boost/simd/toolbox/predicates/functions/is_greater_equal.hpp>
#include <boost/simd/toolbox/operator/functions/logical_not.hpp>
#include <boost/simd/dsl/functions/optimize.hpp>
#include <boost/dispatch/dsl/category.hpp>
#include <boost/dispatch/functor/meta/call.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::logical_not_
                                    , boost::simd::tag::optimize_
                                    , (A0)(Domain)(Arity)
                                    , ((expr_< unspecified_<A0>
                                            , Domain
                                            , boost::simd::tag::is_greater_equal_
                                            , Arity
                                            >
                                      ))
                                    )
  {
    typedef typename dispatch::meta::call< tag::is_not_greater_equal_(
          typename boost::proto::result_of::child_c<A0, 0>::type const&
      ) >::type result_type; 
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return is_not_greater_equal(boost::proto::child_c<0>(a0));
    }
  };
} } }

#endif

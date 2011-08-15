/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_RECOGNITION_IS_NOT_LESS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_RECOGNITION_IS_NOT_LESS_HPP_INCLUDED

#include <boost/dispatch/dsl/category.hpp>
#include <boost/simd/sdk/dsl/recognition.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/toolbox/predicates/functions/is_not_less.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::logical_not_
                                   , boost::simd::tag::recognition_, (A0)(Dom)(Sema)
                                   , ((expr_<A0,Dom,boost::simd::tag::is_less_,Sema>))
                                   )
  {
    typedef typename dispatch::meta::call< tag::is_not_less_(
          typename boost::proto::result_of::child_c<A0, 0>::type
      ) >::type result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return is_not_less(boost::proto::child_c<0>(a0));
    }
  };
} } }

#endif

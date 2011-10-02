//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_EVALUATE_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_EVALUATE_HPP_INCLUDED

#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/core/container/dsl/recognize.hpp>
#include <nt2/core/container/dsl/preprocess.hpp>
#include <nt2/core/container/dsl/compile.hpp>
#include <nt2/sdk/dsl/evaluate.hpp>

#include <nt2/sdk/functor/hierarchy.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>

//==============================================================================
// Evaluation of container expressions
//==============================================================================
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::evaluate_, tag::formal_
                            , (A0)(Tag)
                            , ((expr_< unspecified_<A0>, nt2::container::domain, Tag >))
                            )
  {
    typedef typename dispatch::meta::semantic_of<A0>::type result_type;
    
    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(A0 const& a0) const
    {
      return compile(preprocess(recognize(a0)))(a0);
    }
  };
} }

#endif

//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_HORZCAT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_HORZCAT_HPP_INCLUDED

#include <nt2/core/functions/horzcat.hpp>
#include <nt2/core/functions/common/horzcat.hpp>
#include <nt2/include/functions/arecatcompatible.hpp>

#include <nt2/sdk/memory/copy.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/utility/box.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/include/functions/length.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates horzcat from 1 expression 
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::horzcat_, tag::cpu_,
                              (A0),
                              (ast_<A0>)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return a0; 
    }
  };

  //============================================================================
  // Generates linearize_ from 2 expressions
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::horzcat_, tag::cpu_,
                              (A0)(A1),
                              (ast_<A0>)
                              (ast_<A1>)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::horzcat_
                                          , container::domain
                                          , A0 const&
                                          , A1 const&
                                          , box<of_size_max>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A1 const& a1) const
    {
      BOOST_ASSERT_MSG(arecatcompatible(a0, a1, 2),
                       "horzcat arguments dimensions are not consistent."); 
      // Expressions must be  matrices
      of_size_max sizee = of_size_max(a0.extent());
      sizee[1] += boost::fusion::at_c<1>(a1.extent());
      return boost::proto::make_expr<
          nt2::tag::horzcat_
        , container::domain 
        > (boost::cref(a0),boost::cref(a1), boxify(sizee));
    }
  };
  
} }

#endif

//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_BLKDIAG_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_BLKDIAG_HPP_INCLUDED

#include <nt2/core/functions/blkdiag.hpp>
#include <nt2/core/functions/common/blkdiag.hpp>

#include <nt2/sdk/memory/copy.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/utility/box.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/include/functions/isrow.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/ismatrix.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates blkdiag from 1 expression 
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::blkdiag_, tag::cpu_,
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
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::blkdiag_, tag::cpu_,
                              (A0)(A1),
                              (ast_<A0>)
                              (ast_<A1>)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::blkdiag_
                                          , container::domain
                                          , A0 const&
                                          , A1 const&
                                          , box<_2D>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A1 const& a1) const
    {
      // Expressions must be  matrices
      BOOST_ASSERT_MSG( nt2::ismatrix(a0)
                      , "Error using blkdiag: First input must be 2D."
                      );
      BOOST_ASSERT_MSG( nt2::ismatrix(a1)
                      , "Error using blkdiag: Second input must be 2D."
                      );
      _2D sizee = _2D(a0.extent());
      for(int i=0; i < 2; ++i) sizee[i] += a1.extent()[i]; 
      return boost::proto::make_expr<
          nt2::tag::blkdiag_
        , container::domain 
        > (boost::cref(a0),boost::cref(a1), boxify(sizee));
    }
  };
  
} }

#endif

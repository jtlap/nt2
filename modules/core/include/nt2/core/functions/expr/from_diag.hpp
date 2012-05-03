//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_FROM_DIAG_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_FROM_DIAG_HPP_INCLUDED

#include <nt2/core/functions/from_diag.hpp>
#include <nt2/core/utility/box.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/isvector.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // diag_of extracts the diagonal of a 2D matrix
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::from_diag_, tag::cpu_, (A0), (ast_<A0>) )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::from_diag_
                                          , container::domain
                                          , A0 const&
                                          , box<_2D>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      // Expression must be a matrix
      BOOST_ASSERT_MSG( nt2::isvector(a0)
                      , "??? Error using ==> from_diag"
                        "First input must be a vector"
                      );

      std::size_t n = nt2::length(a0);

      return boost::proto::make_expr< nt2::tag::from_diag_
                                    , container::domain
                                    > ( boost::cref(a0)
                                      , boxify(_2D(n,n))
                                      );
    }
  };
} }

#endif

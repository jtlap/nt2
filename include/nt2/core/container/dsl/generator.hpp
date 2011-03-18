/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_CONTAINER_DSL_GENERATOR_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_GENERATOR_HPP_INCLUDED

#include <nt2/sdk/error/assert.hpp>
#include <nt2/sdk/error/static_assert.hpp>

namespace nt2 { namespace container
{
  //////////////////////////////////////////////////////////////////////////////
  // Container Expression check if their size are compatible before being built
  // Depending on tag and types, a static or runtime assertion can be triggered
  //////////////////////////////////////////////////////////////////////////////
  template<class Tag, class Dimension>
  struct generator
  {
    template<class Sig> struct result;
    template<class This, class Expr>
    struct result<This(Expr)>
    {
      /*
      NT2_STATIC_ASSERT ( meta::call<tag::check_size_(Expr,Tag)>::type::value
                        , NT2_STATIC_SIZE_MISMATCH_IN_CONTAINER_EXPRESSION
                        , "Container(s) with uncompatible static size have been "
                          "used in an expression. Checks dimensions and size "
                          "of containers in your current statement."
      );
    */
      typedef expression<Expr,Tag,Dimension> type;
    };

    template<class Expr>
    expression<Expr,Tag,Dimension> const operator()(Expr const &xpr) const
    {
      /*
      NT2_ASSERT( check_size(xpr,Tag())
                  && "Dynamic size mismatch in container expression"
                );
      */
      expression<Expr,Tag,Dimension> const that(xpr);
      return that;
    }
  };
} }

#endif

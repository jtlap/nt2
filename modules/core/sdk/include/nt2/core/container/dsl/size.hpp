//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_SIZE_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_SIZE_HPP_INCLUDED

#include <nt2/core/container/dsl/details/trait_transform.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/dsl/functions/terminal.hpp>
#include <boost/proto/traits.hpp>

namespace nt2 { namespace ext
{
  //==========================================================================
  /*!
   * This extension point specify the way a given expression stores its size.
   * If most expression uses a reference to the proper size of their children,
   * some may require to store a computed of_size_ by value. This meta-function
   * enables a fine grain specification of this scheme.
   *
   * \tparam Tag    Top most tag of the expression
   * \tparam Domain Domain of the expression
   * \tparam Arity  Number of children of the expression
   * \tparam Expr   The expression itself
   *
   * \return the type usable by an nt2::container::expression to store its size
   *
  **/
  //==========================================================================
  template<class Tag, class Domain, int Arity, class Expr> struct size_of;
} }

namespace nt2 { namespace container
{
  //============================================================================
  /*!
   * proto::transfrom performing the computation of the type able to store
   * an expression in a given domain
   **/
  //============================================================================
  template<class Domain>
  struct size_transform : details::trait_transform< ext::size_of, Domain >
  {};
} }

#include <nt2/core/container/dsl/details/size/terminal.hpp>
#include <nt2/core/container/dsl/details/size/elementwise.hpp>

#endif


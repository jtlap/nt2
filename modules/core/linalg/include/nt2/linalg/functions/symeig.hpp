//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SYMEIG_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SYMEIG_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
    struct symeig_ : ext::tieable_<symeig_>
    {
      typedef ext::tieable_<symeig_>  parent;
    };
  }

  /**
    symeig can be called:
    w = symeig(a)
    w = symeig(a, matrix_/vector_/'U'/'L')
    w = symeig(a, matrix_/vector_, 'U'/'L')
    [w, v] = symeig(a)
    [w, v] = symeig(a, matrix_/vector_/'U'/'L')
    [w, v] = symeig(a, matrix_/vector_, 'U'/'L')

    w will contain the eigenvalues which are real in vector_ or diagonal matrix_ form
    v will contain the eigenvectors in a matrix of element of the same type as the input

   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::symeig_, symeig, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::symeig_, symeig, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::symeig_, symeig, 3)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::symeig_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

} }

#endif

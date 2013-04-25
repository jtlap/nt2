//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_QR_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_QR_HPP_INCLUDED

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
    struct qr_ : ext::tieable_<qr_>
    {
      typedef ext::tieable_<qr_>  parent;
    };
  }

  /**
   * @brief Perform QR factorization
   *
   * For any given matrix expression, performs a QR factorization of
   * said matrix using the specified output layout for the QR method.
   *
   * Contrary to the nt2::factorization::qr function which performs a partial evaluation of
   * said decomposition, nt2::qr returns a result similar to the Matlab interface,
   * making it useful for Matlab like usage.
   *
   * @param  xpr                   Matrix expression to factorize
   * @param  0/pivot_/no_pivot_    Optimize computation and choose qr function call
   * @param  Matrix/vector         return type of permutation vector/matrix
   *
   * @return A tuple-like type containing the factorized matrix and an indicator
   * of the success of the factorization
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::qr_, qr, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::qr_, qr, 2)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::qr_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::qr_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif

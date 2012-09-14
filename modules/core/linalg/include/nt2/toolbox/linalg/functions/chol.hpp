//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_CHOL_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_CHOL_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/toolbox/linalg/functions/details/chol.hpp>

namespace nt2
{
  namespace tag
  {
    namespace factorization
    {
      struct chol_ : ext::unspecified_<factorization::chol_>
      {
        typedef ext::unspecified_<factorization::chol_> parent;
      };
    }

    struct chol_ : ext::tieable_<chol_>
    {
      typedef ext::tieable_<chol_>  parent;
    };
  }

  /**
   * @brief Perform Cholesky factorization
   *
   * For any given matrix expression, performs a Cholesky factorization of
   * said matrix using the specified output layout for the Cholevsky method.
   *
   * Contrary to the nt2::factorization::chol function which performs a partial
   * evaluation of said decomposition, nt2::chol returns a result similar to the
   * Matlab interface.
   *
   * @param  xpr  Matrix expression to factorize
   * @param  low  Notify if chol should return a lower triangular matrix
   *
   * @return A tuple-like type containing the factorized matrix and an indicator
   * of the success of the factorization
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::chol_, chol, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::chol_, chol, 2)

  namespace factorization
  {
    /**
     * @brief Initialize a Cholevsky factorization
     *
     * For any given matrix expression, initialize a Cholevsky factorization of
     * said matrix using the specified output layout for the Cholevsky method
     * and return a precomputed factorization object.
     *
     * Contrary to the chol function which performs such a factorization and
     * return a Matlab like output, factorization::chol returns an object
     * containing the initial evaluation of said factorization. This object can
     * then be used to fasten other algorithms implementation.
     *
     * @param  xpr  Matrix expression to factorize
     * @param  uplo Notify if chol should return a lower or upper result
     * @param  ip   Notify if chol should be performaed in-place over xpr
     *
     * @return A unspecified type containing the precomputed elements of the
     * Cholesky factorization.
     **/
    NT2_FUNCTION_IMPLEMENTATION(tag::factorization::chol_, chol, 2)
    NT2_FUNCTION_IMPLEMENTATION_SELF(tag::factorization::chol_, chol, 3)
  }
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::chol_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::chol_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif

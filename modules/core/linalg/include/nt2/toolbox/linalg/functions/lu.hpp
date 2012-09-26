//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_LU_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_LU_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/toolbox/linalg/functions/details/lu.hpp>

namespace nt2
{
  namespace tag
  {
    namespace factorization
    {
      struct lu_ : ext::unspecified_<factorization::lu_>
      {
        typedef ext::unspecified_<factorization::lu_> parent;
      };
    }

    struct lu_ : ext::tieable_<lu_>
    {
      typedef ext::tieable_<lu_>  parent;
    };
  }

  /**
   * @brief Perform Lu factorization
   *
   * For any given matrix expression, performs a Lu factorization of
   * said matrix using the specified output layout for the Lu method.
   *
   * Contrary to the nt2::factorization::lu function which performs a partial evaluation of
   * said decomposition, nt2::lu returns a result similar to the Matlab interface,
   * making it useful for Matlab like usage.
   *
   * @param  xpr  Matrix expression to factorize
   *
   * @return A tuple-like type containing the factorized matrix and an indicator
   * of the success of the factorization
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::lu_, lu, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::lu_, lu, 2)

  namespace factorization
  {
    /**
     * @brief Initialize a Lu factorization
     *
     * For any given matrix expression, initialize a Lu factorization of
     * said matrix using the specified output layout for the Lu method
     * and return a precomputed factorization object.
     *
     * Contrary to the lu function which performs such a factorization and
     * return a Matlab like output, factorization::lu returns an object
     * containing the initial evaluation of said factorization. This object can
     * then be used to fasten other algorithms implementation.
     *
     * @param  xpr  Matrix expression to factorize
     * @param  ip   Notify if lu should be performed in-place over xpr
     *
     * @return A unspecified type containing the precomputed elements of the
     * Lu factorization.
     **/
    NT2_FUNCTION_IMPLEMENTATION(tag::factorization::lu_, lu, 1)
    NT2_FUNCTION_IMPLEMENTATION_SELF(tag::factorization::lu_, lu, 2)
   }
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::lu_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::lu_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif

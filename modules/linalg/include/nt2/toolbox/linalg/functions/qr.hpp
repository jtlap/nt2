//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_QR_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_QR_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/toolbox/linalg/functions/details/qr.hpp>

namespace nt2
{
  namespace tag
  {
    namespace factorization
    {
      struct qr_ : ext::unspecified_<factorization::qr_>
      {
        typedef ext::unspecified_<factorization::qr_> parent;
      };
    }

    struct qr_ :  ext::tieable_<qr_>
    {
      typedef ext::tieable_<qr_>  parent;
    };
  }

  /**
   * @brief Perform Qr factorization
   *
   * For any given matrix expression, performs a qr factorization of
   * said matrix using the specified output layout for the qr method.
   *
   * Contrary to the nt2::factorization::qr function which performs a partial evaluation of
   * said decomposition, nt2::qr returns a result similar to the Matlab interface,
   * making it useful for Matlab like usage.
   *
   * @param  xpr  Matrix expression to factorize
   *
   * @return A tuple-like type containing the factorized matrix and an indicator
   * of the success of the factorization
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::qr_, qr, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::qr_, qr, 2)

  namespace factorization
  {
    /**
     * @brief Initialize a qr factorization
     *
     * For any given matrix expression, initialize a qr factorization of
     * said matrix using the specified output layout for the qr method
     * and return a precomputed factorization object.
     *
     * Contrary to the qr function which performs such a factorization and
     * return a Matlab like output, factorization::qr returns an object
     * containing the initial evaluation of said factorization. This object can
     * then be used to fasten other algorithms implementation.
     *
     * @param  xpr  Matrix expression to factorize
     *
     * @return A unspecified type containing the precomputed elements of the
     * qr factorization.
     **/
    NT2_FUNCTION_IMPLEMENTATION(tag::factorization::qr_, qr, 2)
    NT2_FUNCTION_IMPLEMENTATION_SELF(tag::factorization::qr_, qr, 3)
  }
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

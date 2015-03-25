//==============================================================================
//         Copyright 2014 - 2015  Jean-Thierry Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_QZ_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_QZ_HPP_INCLUDED

#include <nt2/linalg/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/size_as.hpp>

namespace nt2 {
  namespace tag {
    struct qz_ : ext::tieable_<qz_>
    {
      typedef ext::tieable_<qz_>  parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_qz_( ext::adl_helper(),
                                static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::qz_, Site> dispatching_qz_(adl_helper,
        boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::qz_, Site>();
    }
    template<class... Args>
    struct impl_qz_;
  }

  /**
   * @brief Perform qz generalized factorization
   *
   * For any given matrix expression a and b, performs a qz factorization of
   * said matrix using the specified output layout for the qz method.
   *
   *
   * possible calls are
   * tie(aa, bb, {q, z, {vr, vl}, {alpha, beta}}) =  qz(a, b{, option1, {option2}});
   *     if a or b is complex the complex qz form is returned if option is not present
   *
   *     if a and b are real, or have only real elements two different
   *     decompositions are available.
   *
   *     tie(aa, bb, ...) = qz(a,b, real_) returns real matrices with hessenberg aa and
   *     upper triangular bb. The complex eigenvalue can be reached in 2-by-2 blocks on
   *     the diagonal or directly with alpha and beta.
   *     tie(aa, bb, ...) = qz(a,b, cmplx_) returns complex matrices with  upper
   *     triangular aa and bb. The eigenvalues  can be obtained directly on the diagonals
   *     or with  alpha and beta.
   *     In any cases v and w and alpha are mandatorily complex arrays,  but beta can
   *     be real if the inputs are real and/or real_ option is used
   *
   *     alpha and beta are returned as vectors (Not diagonal matrices).
   *
   *     if required vr and vl are respectively right and left eigenvectors for the problem
   *     if two options are present the routine must receive 6 ouputs and the
   *     option alphabeta_/eigs_ allow to choose the two last outputs
   *     with 5 or 7 outputs:
   *     tie(aa, bb, q, z{, vr, vl}, lambda}) =  qz(a, b) return lambda =  alpha/beta
   *     as a complex vector. This is not recommanded as some (alpha and) beta can be zero.
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::qz_, qz, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::qz_, qz, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::qz_, qz, 4)
}

namespace nt2 {
  namespace ext {
    template<class Domain, int N, class Expr>
    struct  size_of<tag::qz_,Domain,N,Expr>
      : meta::size_as<Expr,0>
    {};
  }
}

#endif

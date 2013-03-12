//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_KMS_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_KMS_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>

#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/size.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_kms kms
 *   a = kms(n, rho) is the n-by-n kac-murdock-szego
 *   toeplitz matrix such that
 *      a(i,j) = rho^(abs(i-j)), for real rho.
 *   for complex rho, the same formula holds except that elements
 *   below the diagonal are conjugated. rho defaults to 0.5.
 *
 *   properties:
 *     a has an ldl' factorization with
 *       l = trnsconj(inv(triw(n,-rho,1))), and
 *       d(i,i) = (1-abs(rho)^2)*eye(n),
 *     except d(1,1) = 1.
 *     a is positive definite if and only if 0 < abs(rho) < 1.
 *     inv(a) is tridiagonal.
 *
 *    Reference:
 *    W. F. Trench, Numerical solution of the eigenvalue problem
 *    for Hermitian Toeplitz matrices, SIAM J. Matrix Analysis
 *    and Appl., 10 (1989), pp. 135-146.
 *
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/kms.hpp>
 * \endcode
 *
 *
**/
//==============================================================================
// kms actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag kms_ of functor kms
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct kms_ :  ext::unspecified_<kms_>
    {
      typedef ext::unspecified_<kms_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::kms_, kms, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::kms_, kms, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::kms_, kms, 3)

  template < class T> container::table<T> kms(size_t n)
  {
    return nt2::kms(n, T(0.5), meta::as_<T>());
  }

}


namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::kms_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return boost::proto::value(boost::proto::child_c<1>(e));
    }
  };
  template <class Domain, class Expr>
  struct value_type < tag::kms_, Domain,1,Expr>
  {
    typedef double                    type;
  };
  template <class Domain, class Expr, int N>
  struct value_type < tag::kms_, Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,1>::type      tmp_type;
    typedef typename  meta::strip<tmp_type>::type                              type;
  };
} }
#endif

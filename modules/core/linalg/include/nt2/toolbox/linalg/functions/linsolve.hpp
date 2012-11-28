//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_LINSOLVE_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_LINSOLVE_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

//  linsolve solve linear system a*x=b.
//     x = linsolve(a,b) solves the linear system a*x=b using
//     lu factorization with partial pivoting when a is square,
//     and qr factorization with column pivoting otherwise.
//     warning is given if a is ill conditioned for square matrices
//     and rank deficient for rectangular matrices.

//     [x, r] = linsolve(a,b) suppresses these warnings and returns r
//     the reciprocal of the condition number of a for square matrices,
//     and the rank of a if a is rectangular.

//     x = linsolve(a,b,opts) solves the linear system a*x=b,
//     with an appropriate solver determined by the properties of
//     the matrix a as described by the structure opts. the fields of opts
//     must contain logicals. all field values are defaulted to false.
//     no test is performed to verify whether a possesses such properties.

//     [x, r] = linsolve(a,b,opts) suppresses these warnings and returns r,
//     the reciprocal of the condition number of a, or the rank of a (depending
//     on opts). see table below for more information.

//     below is the list of all possible field names and
//     their corresponding matrix properties.

//     field name : matrix property
//     ------------------------------------------------
//     lt         : lower triangular
//     ut         : upper triangular
//     uhess      : upper hessenberg
//     sym        : real symmetric or complex hermitian
//     posdef     : positive definite
//     rect       : general rectangular
//     transa     : (conjugate) transpose of a

//     here is a table containing all possible combinations of options:

//     lt  ut  uhess  sym  posdef  rect  transa   output r
//     -----------------------------------------  ----------------
//     t   f   f      f    f       t/f   t/f      condition number
//     f   t   f      f    f       t/f   t/f      condition number
//     f   f   t      f    f       f     t/f      condition number
//     f   f   f      t    t/f     f     t/f      condition number
//     f   f   f      f    f       t/f   t/f      rank

//     example:
//     a = triu(rand(5,3)); x = [1 1 1 0 0]'; b = a'*x;
//     y1 = (a')\b
//     opts.ut = true; opts.transa = true;
//     y2 = linsolve(a,b,opts)
namespace nt2
{
  namespace tag
  {
    namespace factorization
    {
      struct linsolve_ : ext::unspecified_<factorization::linsolve_>
      {
        typedef ext::unspecified_<factorization::linsolve_> parent;
      };
    }

    struct linsolve_ :  ext::tieable_<linsolve_>
    {
      typedef ext::tieable_<linsolve_>  parent;
    };
  }

  /**
   * @brief Perform Linsolve factorization
   *
   * For any given matrix expression, performs a Linsolve factorization of
   * said matrix using the specified output layout for the Linsolve method.
   *
   * Contrary to the nt2::factorization::linsolve function which performs a partial evaluation of
   * said decomposition, nt2::linsolve returns a result similar to the Matlab interface,
   * making it useful for Matlab like usage.
   *
   * @param  xpr  Matrix expression to factorize
   *
   * @return A tuple-like type containing the factorized matrix and an indicator
   * of the success of the factorization
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::linsolve_, linsolve, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::linsolve_, linsolve, 2)

  namespace factorization
  {
    /**
     * @brief Initialize a Linsolve factorization
     *
     * For any given matrix expression, initialize a Linsolve factorization of
     * said matrix using the specified output layout for the Linsolve method
     * and return a precomputed factorization object.
     *
     * Contrary to the linsolve function which performs such a factorization and
     * return a Matlab like output, factorization::linsolve returns an object
     * containing the initial evaluation of said factorization. This object can
     * then be used to fasten other algorithms implementation.
     *
     * @param  xpr  Matrix expression to factorize
     * @param  ip   Notify if linsolve should be performed in-place over xpr
     *
     * @return A unspecified type containing the precomputed elements of the
     * Linsolve factorization.
     **/
    NT2_FUNCTION_IMPLEMENTATION(tag::factorization::linsolve_, linsolve, 2)
    NT2_FUNCTION_IMPLEMENTATION_SELF(tag::factorization::linsolve_, linsolve, 3)
  }
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::linsolve_,Domain,N,Expr>
  {
    typedef _2D result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      _2D sizee;
      sizee[0] = size(boost::proto::child_c<0>(e), 2);
      sizee[1] = size(boost::proto::child_c<1>(e), 2);
      return sizee;
    }

  };

  template<class Domain, int N, class Expr>
  struct  value_type<tag::linsolve_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif

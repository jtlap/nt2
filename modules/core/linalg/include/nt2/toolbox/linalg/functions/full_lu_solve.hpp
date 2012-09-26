//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_FULL_LU_SOLVE_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_FULL_LU_SOLVE_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/toolbox/linalg/functions/details/full_lu_solve.hpp>

//  full_lu_solve solve linear system a*x=b.
//     x = full_lu_solve(a,b) solves the linear system a*x=b using
//     lu factorization with partial pivoting. a must be square,

namespace nt2
{
  namespace tag
  {
    namespace solvers
    {
      struct full_lu_solve_ : ext::unspecified_<solvers::full_lu_solve_>
      {
        typedef ext::unspecified_<solvers::full_lu_solve_> parent;
      };
    }

    struct full_lu_solve_ :  ext::tieable_<full_lu_solve_>
    {
      typedef ext::tieable_<full_lu_solve_>  parent;
    };
  }

  /**
   * @brief Perform Full_Lu_solve factorization
   *
   * For any given matrix expression a, and right hand side b performs
   * Full_Lu_solve resolution of
   * said system using the specified output layout for the Full_Lu_solve method.
   *
   * Contrary to the nt2::factorization::full_lu_solve function which
   * performs a partial evaluation of
   * said resolution, nt2::full_lu_solve returns a result similar to the Matlab interface,
   * making it useful for Matlab like usage.
   *
   * @param  xpr  Matrix expression
   * @param  b    rigt hand side expression
   *
   * @return A tuple-like type containing the solution and optionnaly the rcond number of the system
   * of the success of the factorization
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::full_lu_solve_, full_lu_solve, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::full_lu_solve_, full_lu_solve, 3)

  namespace solvers
  {
    /**
     * @brief Initialize a Full_Lu_solve factorization
     *
     * For any given matrix expression, initialize a Full_Lu_solve factorization of
     * said matrix using the specified output layout for the Full_Lu_solve method
     * and return a precomputed factorization object.
     *
     * Contrary to the full_lu_solve function which performs such a factorization and
     * return a Matlab like output, factorization::full_lu_solve returns an object
     * containing the initial evaluation of said factorization. This object can
     * then be used to fasten other algorithms implementation.
     *
     * @param  xpr  Matrix expression to factorize
     * @param  ip   Notify if full_lu_solve should be performed in-place over xpr
     *
     * @return A unspecified type containing the precomputed elements of the
     * Full_Lu_solve factorization.
     **/
    NT2_FUNCTION_IMPLEMENTATION(tag::solvers::full_lu_solve_, full_lu_solve, 2)
    NT2_FUNCTION_IMPLEMENTATION(tag::solvers::full_lu_solve_, full_lu_solve, 3)
    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::solvers::full_lu_solve_, full_lu_solve,(A0&)(A1&)(const A2&), 3)
    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::solvers::full_lu_solve_, full_lu_solve,(A0&)(A1&)(const A2&)(const A3&), 4)
  }
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::full_lu_solve_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::full_lu_solve_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif

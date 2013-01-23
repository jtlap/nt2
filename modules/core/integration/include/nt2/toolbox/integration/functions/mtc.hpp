/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_INTEGRATION_FUNCTIONS_MTC_HPP_INCLUDED
#define NT2_TOOLBOX_INTEGRATION_FUNCTIONS_MTC_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::mtc function
 */
#include <nt2/toolbox/integration/interface.hpp>

namespace nt2
{
  namespace tag
  {
    struct mtc_ : ext::unspecified_<mtc_>
    {
      typedef ext::unspecified_<mtc_> parent;
    };

    // definition  of abstol constant for mtc method
    BOOST_SIMD_CONSTANT_REGISTER( Mtcabstol, double
                                  , 0, 0x3a83126f             //1.0e-3
                                  , 0x3eb0c6f7a0b5ed8dll      //1.0e-6
      );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Mtcabstol, Mtcabstol);

  // specialization of abstol for mtc method
  template<class T, class V> struct integ_params<T, V, tag::mtc_>
  : integ_params<T, V, void>
  {
    typedef typename nt2::integ_params<T, V, void>::real_t real_t;
    static real_t        abstol(){return Mtcabstol<real_t>(); }
    static size_t    maxintvcnt(){return 512; }
  };

  //============================================================================
  /*!
   * Apply mtc algorithm to integrate a function over a real interval
   *
   * \param func  Function to optimize
   * \param x    required points in the interval or 2 abscissae a and b
   * \param opt   Options pack related to the tolerance handling
   *
   * \return  a tuple containing the results of the integration, the last error value,
   * the number of required function evaluation and a boolean
   * notifying success of the whole process.
   *
   *    q = mtc(fun,range) tries to approximate the nxintegral of a scalar-valued
   *    function fun in the range hypercube using a simple montecarlo approach
   *
   * fun must be a functor taking a matrix with n lines and any
   * columns number able to return a line matrix of one value by
   * data column.
   * range is a nX2 expression containing the the ranges of
   * integration for each coeficient of the functor parameter
   */
  //============================================================================


  template<class F, class X> BOOST_FORCEINLINE
  typename details::integration<F, X, tag::mtc_>::result_type
  mtc(F f, X ranges)
  {
    return details::integration<F, X, tag::mtc_>::call(f, ranges);
  }

  template<class F, class X, class Xpr> BOOST_FORCEINLINE
  typename details::integration<F, X, tag::mtc_>::result_type
  mtc(F f, X ranges, nt2::details::option_expr<Xpr> const& opt)
  {
    return details::integration<F, X, tag::mtc_>::call(f, ranges, opt);
  }

}

#endif


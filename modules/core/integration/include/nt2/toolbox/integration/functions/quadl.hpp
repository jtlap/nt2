//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_INTEGRATION_FUNCTIONS_QUADL_HPP_INCLUDED
#define NT2_TOOLBOX_INTEGRATION_FUNCTIONS_QUADL_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::quadl function
 */
#include <nt2/toolbox/integration/interface.hpp>

namespace nt2
{
  namespace tag
  {
    struct quadl_ : ext::unspecified_<quadl_>
    {
      typedef ext::unspecified_<quadl_> parent;
    };
    // definition  of abstol constant for integ method
    BOOST_SIMD_CONSTANT_REGISTER( Quadlabstol, double
                                  , 0, 0x3a83126f             //1.0e-3
                                  , 0x3eb0c6f7a0b5ed8dll      //1.0e-6
      );
   }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Quadlabstol, Quadlabstol);
  template<class T,  class V> struct integ_params<T, V, tag::quadl_>
  : integ_params<T, V, void>
  {
    typedef typename nt2::integ_params<T, V, void>::real_t real_t;
    static real_t        abstol(){return Quadlabstol<real_t>(); }
  };

  //============================================================================
  /*!
   * Apply quadl algorithm to integrate a function over a real interval by lobatto quadrature
   *
   * \param func  Function to optimize
   * \param x    required points in the interval in ascending order
   *             (x can be replaced by 2 abscissae a and b)
   * \param opt   Options pack related to the tolerance handling
   *
   * \return  a tuple containing the results of the integration, the last error value,
   * the number of required function evaluation and a boolean
   * notifying success of the whole process.
   */
  //============================================================================



  template<class F, class X> BOOST_FORCEINLINE
  typename details::integration<F, X, tag::quadl_>::result_type
  quadl(F f, X x)
  {
    return details::integration<F, X, tag::quadl_>::call(f, x);
  }

  template<class F, class X, class Xpr> BOOST_FORCEINLINE
  typename details::integration<F, X, tag::quadl_>::result_type
  quadl(F f, X x, nt2::details::option_expr<Xpr> const& opt)
  {
    return details::integration<F, X, tag::quadl_>::call(f, x, opt);
  }

  template<class F, class A> BOOST_FORCEINLINE
  typename details::integration<F, typename details::h2_t<A>::ab_t, tag::quadl_>::result_type
  quadl(F f, A a, A b)
  {
    typedef typename details::h2_t<A>::ab_t ab_t;
    return details::integration<F, ab_t, tag::quadl_>::call(f, nt2::cath(a, b));
  }

  template<class F, class A, class Xpr> BOOST_FORCEINLINE
  typename details::integration<F, typename details::h2_t<A>::ab_t, tag::quadl_>::result_type
  quadl(F f, A a, A b, nt2::details::option_expr<Xpr> const& opt)
  {
    typedef typename details::h2_t<A>::ab_t ab_t;
    return details::integration<F, ab_t, tag::quadl_>::call(f, nt2::cath(a, b), opt);
  }

}

#endif


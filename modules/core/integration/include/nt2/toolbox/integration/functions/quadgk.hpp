/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_INTEGRATION_FUNCTIONS_QUADGK_HPP_INCLUDED
#define NT2_TOOLBOX_INTEGRATION_FUNCTIONS_QUADGK_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::quadgk function
 */
#include <nt2/toolbox/integration/interface.hpp>

namespace nt2
{
  namespace tag
  {
    struct quadgk_ : ext::unspecified_<quadgk_>
    {
      typedef ext::unspecified_<quadgk_> parent;
    };
    // definition  of abstol constant for quadgk method
    BOOST_SIMD_CONSTANT_REGISTER( Quadgkabstol, double
                                  , 0, 0x3727c5ac             //1.0e-5
                                  , 0x3ddb7cdfd9d7bdbbll      //1.0e-10
      );
    // definition  of reltol constant for quadgk method
    BOOST_SIMD_CONSTANT_REGISTER( Quadgkreltol, double
                                  , 0, 0x38d1b717             //1.0e-4
                                  , 0x3eb0c6f7a0b5ed8dll      //1.0e-6
      );
  }
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Quadgkabstol, Quadgkabstol);
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Quadgkreltol, Quadgkreltol);

  // specialization of abstol for quadgk method
  template<class T, class V> struct integ_params<T, V, tag::quadgk_>
  : integ_params<T, V, void>
  {
    typedef typename nt2::integ_params<T, V, void>::real_type real_type;
    static real_type        abstol(){return Quadgkabstol<real_type>(); }
    static real_type        reltol(){return Quadgkreltol<real_type>(); }
  };

  //============================================================================
  /*!
   * Apply quadgk algorithm to integrate a function over a real interval
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
  template<class T, class V, class F, class X> BOOST_FORCEINLINE
  typename integration_call<T, V, F, tag::quadgk_, X>::result_type
  quadgk(F f, X x)
  {
    return integ_call<T, V, tag::quadgk_>(f, x);
  }

  template<class T, class V, class F, class X, class Xpr> BOOST_FORCEINLINE
  typename integration_call<T, V, F, tag::quadgk_, X>::result_type
  quadgk(F f, X x, nt2::details::option_expr<Xpr> const& opt)
  {
    return integ_call<T, V, tag::quadgk_>(f, x, opt);
  }

  template<class T, class V, class F, class A, class B> BOOST_FORCEINLINE
  typename integration_call<T, V, F, tag::quadgk_, typename xtype<T>::type>::result_type
  quadgk(F f, A a, B b)
  {
    return integ_call<T, V, tag::quadgk_>(f, a, b);
  }

  template<class T, class V, class F, class A,  class B, class Xpr> BOOST_FORCEINLINE
  typename integration_call<T, V, F, tag::quadgk_, typename xtype<T>::type>::result_type
  quadgk(F f, A a, B b, nt2::details::option_expr<Xpr> const& opt)
  {
    return integ_call<T, V, tag::quadgk_>(f, a, b, opt);
  }

}

#endif


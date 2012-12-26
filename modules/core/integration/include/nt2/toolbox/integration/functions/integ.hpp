/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_INTEGRATION_FUNCTIONS_INTEG_HPP_INCLUDED
#define NT2_TOOLBOX_INTEGRATION_FUNCTIONS_INTEG_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::integ function
 */
#include <nt2/toolbox/integration/interface.hpp>

namespace nt2
{
  namespace tag
  {
    struct integ_ : ext::unspecified_<integ_>
    {
      typedef ext::unspecified_<integ_> parent;
    };

    // definition  of abstol constant for integ method
    BOOST_SIMD_CONSTANT_REGISTER( Integabstol, double
                                  , 0, 0x3a83126f             //1.0e-3
                                  , 0x3eb0c6f7a0b5ed8dll      //1.0e-6
      );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Integabstol, Integabstol);

  // specialization of abstol for integ method
  template<class T, class V> struct integ_params<T, V, tag::integ_>
  : integ_params<T, V, void>
  {
    typedef typename nt2::integ_params<T, V, void>::real_type real_type;
    static real_type        abstol(){return Integabstol<real_type>(); }
  };

  //============================================================================
  /*!
   * Apply integ algorithm to integrate a function over a real interval
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
  typename integration_call<T, V, F, tag::integ_, X>::result_type
  integ(F f, X x)
  {
    return integ_call<T, V, tag::integ_>(f, x);
  }

  template<class T, class V, class F, class X, class Xpr> BOOST_FORCEINLINE
  typename integration_call<T, V, F, tag::integ_, X>::result_type
  integ(F f, X x, nt2::details::option_expr<Xpr> const& opt)
  {
    return integ_call<T, V, tag::integ_>(f, x, opt);
  }

  template<class T, class V, class F, class A, class B> BOOST_FORCEINLINE
  typename integration_call<T, V, F, tag::integ_, typename xtype<T>::type>::result_type
  integ(F f, A a, B b)
  {
    return integ_call<T, V, tag::integ_>(f, a, b);
  }

  template<class T, class V, class F, class A,  class B, class Xpr> BOOST_FORCEINLINE
  typename integration_call<T, V, F, tag::integ_, typename xtype<T>::type>::result_type
  integ(F f, A a, B b, nt2::details::option_expr<Xpr> const& opt)
  {
    return integ_call<T, V, tag::integ_>(f, a, b, opt);
  }


}

#endif


/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_INTEGRATION_INTERFACE_HPP_INCLUDED
#define NT2_TOOLBOX_INTEGRATION_INTERFACE_HPP_INCLUDED


/*!
 * \file
 * \brief Defines and implements the calls for integration methods
 */

#include <nt2/include/functor.hpp>
#include <nt2/sdk/option/options.hpp>
#include <nt2/toolbox/integration/options.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>

namespace nt2
{
  namespace details
  {
    template<class T, class V, class F, class TAG, class X> struct integration_call
    {
      typedef V                                                                       value_type;
      typedef T                                                                       input_type;
      typedef typename meta::as_real<T>::type                                          real_type;
      typedef typename details::integration_settings<T,V,TAG>                      settings_type;
      typedef typename boost::dispatch::meta::call<TAG(F,X,settings_type )>::type    result_type;

      static result_type integ_call(F f, X x)
      {
        typename boost::dispatch::make_functor<TAG, F>::type callee;
        return callee ( f,x, settings_type());
      }
      template<class Xpr>
      static result_type integ_call(F f, X x, nt2::details::option_expr<Xpr> const& opt)
      {
        typename boost::dispatch::make_functor<TAG, F>::type callee;
        return callee (f, x, settings_type(opt));
      }
    };

    template < class X > struct xtype
    {
      typedef typename boost::dispatch::meta::call<tag::horzcat_(X, X)>::type type;
    };

    template < class V, class T> struct restype
    {
      typedef typename meta::is_complex<V>::type                  v_is_cplx_t;
      typedef typename boost::mpl::if_<v_is_cplx_t,V,T>::type        result_t;
    };

//////////////////////////////////////////////////////////////////////////////

    template<class T, class V, class TAG, class F, class X> BOOST_FORCEINLINE
    typename integration_call<T, V, F, TAG, X>::result_type
    integ_call(F f, X x)
    {
      return integration_call<T, V, F, TAG, X >::integ_call(f, x);
    }

    template<class T, class V, class TAG, class F, class X, class Xpr>
    BOOST_FORCEINLINE
    typename integration_call<T, V, F, TAG, X>::result_type
    integ_call(F f, X x, nt2::details::option_expr<Xpr> const& opt)
    {
      return integration_call<T, V, F, TAG, X >::integ_call(f, x, opt);
    }

    template<class T, class V, class TAG, class F, class A, class B>
    BOOST_FORCEINLINE
    typename integration_call<T, V, F, TAG, typename xtype<T>::type>::result_type
    integ_call(F f, A a, B b)
    {
      return integration_call<T, V, F, TAG, typename xtype<T>::type>::
        integ_call(f, nt2::cath(static_cast<T>(a), static_cast<T>(b)));
    }

    template<class T, class V, class TAG, class F, class A,  class B, class Xpr>
    BOOST_FORCEINLINE
    typename integration_call<T, V, F, TAG, typename xtype<T>::type>::result_type
    integ_call(F f, A a, B b, nt2::details::option_expr<Xpr> const& opt)
    {
      return integration_call<T, V, F, TAG, typename xtype<T>::type>::
        integ_call(f, nt2::cath(static_cast<T>(a), static_cast<T>(b)), opt);
    }
  }
}

#endif

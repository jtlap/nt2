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
  }
  template<> struct integ_params<double, tag::integ_>
  {
    typedef double                                             value_type;
    typedef double                                              real_type;
    typedef typename meta::as_logical<real_type>                bool_type;
    typedef container::table<value_type>                         tab_type;
    typedef container::table<bool>                              btab_type;
    static std::size_t  maxfunccnt(){return 10001; }
    static std::size_t  maxintvcnt(){return 0; }             //unused by integ
    static value_type       abstol(){return 1.0e-6; }
    static value_type       reltol(){return Nan<double>(); } //unused by integ
    static tab_type      waypoints(){ return tab_type(of_size(1, 0));    }
    static std::size_t  singular_a(){ return 0;                          }
    static std::size_t  singular_b(){ return 0;                          }
  };
  template<> struct integ_params<float, tag::integ_>
  {
    typedef float                                              value_type;
    typedef float                                               real_type;
    typedef typename meta::as_logical<real_type>                bool_type;
    typedef container::table<value_type>                         tab_type;
    typedef container::table<bool>                              btab_type;
    static std::size_t  maxfunccnt(){return 10001; }
    static std::size_t  maxintvcnt(){return 0; }             //unused by integ
    static value_type       abstol(){return 1.0e-3; }
    static value_type       reltol(){return Nan<double>(); } //unused by integ
    static tab_type      waypoints(){ return tab_type(of_size(1, 0));    }
    static std::size_t  singular_a(){ return 0;                          }
    static std::size_t  singular_b(){ return 0;                          }
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


  template<class T,class F, class X> BOOST_FORCEINLINE
  typename integration_call<T, F, tag::integ_, X>::result_type
  integ(F f, X x)
  {
    return integ_call<T, tag::integ_>(f, x);
  }

  template<class T,class F, class X, class Xpr> BOOST_FORCEINLINE
  typename integration_call<T, F, tag::integ_, X>::result_type
  integ(F f, X x, nt2::details::option_expr<Xpr> const& opt)
  {
    return integ_call<T, tag::integ_>(f, x, opt);
  }

  template<class T,class F, class A, class B> BOOST_FORCEINLINE
  typename integration_call<T, F, tag::integ_, typename xtype<T>::type>::result_type
  integ(F f, A a, B b)
  {
    return integ_call<T, tag::integ_>(f, a, b);
  }

  template<class T,class F, class A,  class B, class Xpr> BOOST_FORCEINLINE
  typename integration_call<T, F, tag::integ_, typename xtype<T>::type>::result_type
  integ(F f, A a, B b, nt2::details::option_expr<Xpr> const& opt)
  {
    return integ_call<T, tag::integ_>(f, a, b, opt);
  }


}

#endif


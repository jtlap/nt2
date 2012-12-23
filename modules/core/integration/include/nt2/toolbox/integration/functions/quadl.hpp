/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_INTEGRATION_FUNCTIONS_QUADL_HPP_INCLUDED
#define NT2_TOOLBOX_INTEGRATION_FUNCTIONS_QUADL_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::quadl function
 */

#include <nt2/include/functor.hpp>
#include <nt2/sdk/option/options.hpp>
#include <nt2/toolbox/integration/options.hpp>
#include <nt2/include/functions/horzcat.hpp>

namespace nt2
{
  namespace tag
  {
    struct quadl_ : ext::unspecified_<quadl_>
    {
      typedef ext::unspecified_<quadl_> parent;
    };
  }
  template<> struct integ_params<double, tag::quadl_>
  {
    typedef double value_type;
    static std::size_t  maxfunccnt(){return 10001; }
    static std::size_t  maxintvcnt(){return 0; }//unused by quad
    static value_type       abstol(){return 1.0e-6; }
    static value_type       reltol(){return Nan<double>(); } //unused by quad
  };
  template<> struct integ_params<float, tag::quadl_>
  {
    typedef float value_type;
    static std::size_t  maxfunccnt(){return 10001; }
    static std::size_t  maxintvcnt(){return 0; }//unused by quad
    static value_type       abstol(){return 1.0e-3; }
    static value_type       reltol(){return Nan<double>(); } //unused by quad
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
//   template<class T,class F, class X> BOOST_FORCEINLINE
//   typename boost::dispatch::meta
//                 ::call<tag::quadl_( F
//                                   , X
//                                   , details::integration_settings<T> const&
//                                   )
//                       >::type
//   quadl(F f, X x)
//   {
//     typename boost::dispatch::make_functor<tag::quadl_, F>::type callee;
//     return callee ( f
//                   ,x
//                   , details::integration_settings<T, tag::quadl_>()
//                   );
//   }

//   template<class T,class F, class X, class Xpr>
//   BOOST_FORCEINLINE
//   typename boost::dispatch::meta
//                 ::call<tag::quadl_( F
//                                   , X
//                                   , details::integration_settings<T, tag::quadl_> const&
//                                   )
//                   >::type
//   quadl(F f, X x, nt2::details::option_expr<Xpr> const& opt)
//   {
//     typename boost::dispatch::make_functor<tag::quadl_, F>::type callee;
//     return callee ( f
//                     , x
//                     , details::integration_settings<T, tag::quadl_>(opt)
//       );
//   }


  template<class T,class F, class A, class B> BOOST_FORCEINLINE
  typename boost::dispatch::meta
                ::call<tag::quadl_( F
                                   , T, T
                                   , details::integration_settings<T, tag::quadl_> const&
    )
                  >::type
  quadl(F f, A a, B b)
  {
     typename boost::dispatch::make_functor<tag::quadl_, F>::type callee;
    return callee ( f
                    , static_cast <T>(a), static_cast <T>(b),
                    details::integration_settings<T, tag::quadl_>()
                   );
  }

  template<class T,class F, class A, class B, class Xpr>
  BOOST_FORCEINLINE
  typename boost::dispatch::meta
                ::call<tag::quadl_( F
                                   , T, T
                                   , details::integration_settings<T, tag::quadl_> const&
                         )
                      >::type
  quadl(F f, A a, B b, nt2::details::option_expr<Xpr> const& opt)
  {
    typename boost::dispatch::make_functor<tag::quadl_, F>::type callee;
    return callee ( f
                    , static_cast<T>(a), static_cast<T>(b)
                    , details::integration_settings<T, tag::quadl_>(opt)
                  );
  }
}

#endif


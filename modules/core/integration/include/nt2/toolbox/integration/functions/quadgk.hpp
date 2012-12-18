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

#include <nt2/include/functor.hpp>
#include <nt2/sdk/option/options.hpp>
#include <nt2/toolbox/integration/options.hpp>
#include <nt2/include/functions/horzcat.hpp>

namespace nt2
{
  namespace tag
  {
    struct quadgk_ : ext::unspecified_<quadgk_>
    {
      typedef ext::unspecified_<quadgk_> parent;
    };
  }
  template<> struct integ_params<double, tag::quadgk_>
  {
    typedef double value_type;
    static std::size_t  maxfunccnt(){return 10001; }
    static std::size_t  maxintvcnt(){return 0; }//unused by quad
    static value_type       abstol(){return 1.0e-10; }
    static value_type       reltol(){return 1.0e-6; }
  };
  template<> struct integ_params<float, tag::quadgk_>
  {
    typedef float value_type;
    static std::size_t  maxfunccnt(){return 10001; }
    static std::size_t  maxintvcnt(){return 0; }//unused by quad
    static value_type       abstol(){return 1.0e-5; }
    static value_type       reltol(){return N.0e-4; }
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
  template<class T,class F, class X> BOOST_FORCEINLINE
  typename boost::dispatch::meta
                ::call<tag::quadgk_( F
                                  , X
                                  , details::integration_settings<T> const&
                                  )
                      >::type
  quadgk(F f, X x)
  {
    typename boost::dispatch::make_functor<tag::quadgk_, F>::type callee;
    return callee ( f
                  ,x
                  , details::integration_settings<T, tag::quadgk_>()
                  );
  }

  template<class T,class F, class X, class Xpr>
  BOOST_FORCEINLINE
  typename boost::dispatch::meta
                ::call<tag::quadgk_( F
                                  , X
                                  , details::integration_settings<T, tag::quadgk_> const&
                                  )
                  >::type
  quadgk(F f, X x, nt2::details::option_expr<Xpr> const& opt)
  {
    typename boost::dispatch::make_functor<tag::quadgk_, F>::type callee;
    return callee ( f
                    , x
                    , details::integration_settings<T, tag::quadgk_>(opt)
      );
  }


  template<class T,class F, class A, class B> BOOST_FORCEINLINE
  typename boost::dispatch::meta
                ::call<tag::quadgk_( F
                                   , typename boost::dispatch::meta
                                          ::call<tag::horzcat_(A, B)>::type
                                   , details::integration_settings<T, tag::quadgk_> const&
    )
                  >::type
  quadgk(F f, A a, B b)
  {
    typename boost::dispatch::make_functor<tag::quadgk_, F>::type callee;
    return callee ( f
                    , nt2::cath(static_cast <T>(a),static_cast <T>(b)),
                    details::integration_settings<T, tag::quadgk_>()
                  );
  }

  template<class T,class F, class A, class B, class Xpr>
  BOOST_FORCEINLINE
  typename boost::dispatch::meta
                ::call<tag::quadgk_( F
                                   , typename boost::dispatch::meta
                                         ::call<tag::horzcat_(A, B)>::type
                                   , details::integration_settings<T, tag::quadgk_> const&
                         )
                      >::type
  quadgk(F f, A a, B b, nt2::details::option_expr<Xpr> const& opt)
  {
    typename boost::dispatch::make_functor<tag::quadgk_, F>::type callee;
    return callee ( f
                    , nt2::cath(static_cast<T>(a), static_cast<T>(b))
                    , details::integration_settings<T, tag::quadgk_>(opt)
                  );
  }
}

#endif


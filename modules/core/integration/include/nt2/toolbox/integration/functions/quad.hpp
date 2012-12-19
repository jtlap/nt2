/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_INTEGRATION_FUNCTIONS_QUAD_HPP_INCLUDED
#define NT2_TOOLBOX_INTEGRATION_FUNCTIONS_QUAD_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::quad function
 */

#include <nt2/include/functor.hpp>
#include <nt2/sdk/option/options.hpp>
#include <nt2/toolbox/integration/options.hpp>
#include <nt2/include/functions/horzcat.hpp>

namespace nt2
{
  namespace tag
  {
    struct quad_ : ext::unspecified_<quad_>
    {
      typedef ext::unspecified_<quad_> parent;
    };
  }
  template<> struct integ_params<double, tag::quad_>
  {
    typedef double                                             value_type;
    typedef double                                              real_type;
    typedef typename meta::as_logical<real_type>                bool_type;
    typedef container::table<value_type>                         tab_type;
    typedef container::table<bool>                              btab_type;
    static std::size_t  maxfunccnt(){return 10001; }
    static std::size_t  maxintvcnt(){return 0; }             //unused by quad
    static value_type       abstol(){return 1.0e-6; }
    static value_type       reltol(){return Nan<double>(); } //unused by quad
    static tab_type      waypoints(){ return tab_type(of_size(1, 0));    }
    static std::size_t  singular_a(){ return 0;                          }
    static std::size_t  singular_b(){ return 0;                          }
  };
  template<> struct integ_params<float, tag::quad_>
  {
    typedef float                                              value_type;
    typedef float                                               real_type;
    typedef typename meta::as_logical<real_type>                bool_type;
    typedef container::table<value_type>                         tab_type;
    typedef container::table<bool>                              btab_type;
    static std::size_t  maxfunccnt(){return 10001; }
    static std::size_t  maxintvcnt(){return 0; }             //unused by quad
    static value_type       abstol(){return 1.0e-3; }
    static value_type       reltol(){return Nan<double>(); } //unused by quad
    static tab_type      waypoints(){ return tab_type(of_size(1, 0));    }
    static std::size_t  singular_a(){ return 0;                          }
    static std::size_t  singular_b(){ return 0;                          }
  };
  //============================================================================
  /*!
   * Apply quad algorithm to integrate a function over a real interval
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
                ::call<tag::quad_( F
                                  , X
                                   , details::integration_settings<T, tag::quad_> const&
                                  )
                      >::type
  quad(F f, X x)
  {
    typename boost::dispatch::make_functor<tag::quad_, F>::type callee;
    return callee ( f
                  ,x
                  , details::integration_settings<T, tag::quad_>()
                  );
  }

  template<class T,class F, class X, class Xpr>
  BOOST_FORCEINLINE
  typename boost::dispatch::meta
                ::call<tag::quad_( F
                                  , X
                                  , details::integration_settings<T, tag::quad_> const&
                                  )
                  >::type
  quad(F f, X x, nt2::details::option_expr<Xpr> const& opt)
  {
    typename boost::dispatch::make_functor<tag::quad_, F>::type callee;
    return callee ( f
                    , x
                    , details::integration_settings<T, tag::quad_>(opt)
      );
  }


  template<class T,class F, class A, class B> BOOST_FORCEINLINE
  typename boost::dispatch::meta
                ::call<tag::quad_( F
                                   , typename boost::dispatch::meta
                                          ::call<tag::horzcat_(A, B)>::type
                                   , details::integration_settings<T, tag::quad_> const&
    )
                  >::type
  quad(F f, A a, B b)
  {
    typename boost::dispatch::make_functor<tag::quad_, F>::type callee;
    return callee ( f
                    , nt2::cath(static_cast <T>(a),static_cast <T>(b)),
                    details::integration_settings<T, tag::quad_>()
                  );
  }

  template<class T,class F, class A, class B, class Xpr>
  BOOST_FORCEINLINE
  typename boost::dispatch::meta
                ::call<tag::quad_( F
                                   , typename boost::dispatch::meta
                                         ::call<tag::horzcat_(A, B)>::type
                                   , details::integration_settings<T, tag::quad_> const&
                         )
                      >::type
  quad(F f, A a, B b, nt2::details::option_expr<Xpr> const& opt)
  {
    typename boost::dispatch::make_functor<tag::quad_, F>::type callee;
    return callee ( f
                    , nt2::cath(static_cast<T>(a), static_cast<T>(b))
                    , details::integration_settings<T, tag::quad_>(opt)
                  );
  }
}

#endif


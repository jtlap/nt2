//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_FUNCTIONS_AD_GRADIENT_HPP_INCLUDED
#define NT2_AD_FUNCTIONS_AD_GRADIENT_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief ad_gradient generic tag

     Represents the ad_gradient function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct ad_gradient_ : ext::tieable_<ad_gradient_>
    {
      /// @brief Parent hierarchy
      typedef ext::tieable_<ad_gradient_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY(
        dispatching_ad_gradient_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::ad_gradient_, Site>
   dispatching_ad_gradient_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::ad_gradient_, Site>();
   }
   template<class... Args>
   struct impl_ad_gradient_;
  }
  /*!
    Computes the ad forward gradient of f.


    @par Semantic:

    For every functor f from \f$K^m$\f to  \f$K$\f and x of floating
    or complex type T of dimension mxk

    @code
    dfdx = ad_gradient(f, x);
    @endcode

    return a full precision computation of the partial derivatives of f
    at the x column vectors. So the result is a matrix expression of size mxk
    (same as x), each column containing the derivatives
    dfdx(i, j) =  (df/dxi)(x(_,j))

    if you want to compute the gradient of a function f,  f has to be constructed
    with a template type VD that you can think as a table of floating entries each column
    being a vector and using the elementwise nt2 functors
    (See the unit tests for an example). However the type VD must be at
    least ad::valder<table<T>> or template.

    However the
    @return the gradient values

  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::ad_gradient_, ad_gradient, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::ad_gradient_, ad_gradient, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::ad_gradient_, ad_gradient, 4)
}

 namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<tag::ad_gradient_,Domain,N,Expr>
  {
    typedef _2D result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      _2D sizee = boost::proto::child_c<1>(e).extent();
      return sizee;
    }
  };


  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  value_type<tag::ad_gradient_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type      F;
    typedef typename boost::proto::result_of::child_c<Expr&,1>::value_type      X;
    typedef typename X::value_type                                         elem_t;
    typedef typename nt2::container::table<elem_t>                          tab_t;
    typedef tab_t type;
//   typedef decltype(std::declval<F>()(std::declval<X>()))              rtype_t;

 };
} }
#endif

// namespace nt2 { namespace ext
// {
//   /// INTERNAL ONLY
//   template<class Domain, int N, class Expr>
//   struct  size_of<nt2::tag::ad_gradient_,Domain,N,Expr>
//   {
//     typedef _2D result_type;

//     BOOST_FORCEINLINE result_type operator ()(Expr& e) const
//     {
//       result_type sizee;
//       sizee[0] = 1; //+= boost::fusion::at_c<0>(boost::proto::child_c<1>(e).extent());
//       sizee[1] = boost::fusion::at_c<0>(boost::proto::child_c<1>(e).extent());

//       return sizee;
//     }

//   };
// } }
// #endif


//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DERIVATION_FUNCTIONS_DF_HPP_INCLUDED
#define NT2_DERIVATION_FUNCTIONS_DF_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>



namespace nt2 { namespace tag
  {
   /*!
     @brief df generic tag

     Represents the df function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct df_ : ext::unspecified_<df_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<df_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY(
        dispatching_df_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::df_, Site>
   dispatching_df_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::df_, Site>();
   }
   template<class... Args>
   struct impl_df_;
  }
  /*!
    Computes the numerical approximation first order derivatives of a function f
    from \f$R^n$\f to \f$K^m$\f (wwhere \f$K\f$ is \f$R\f$ or \f$C\f$),  using
     forward,  backward,  centered or vand (very acurate numerical derivative method).

    vand is reserved to real functions of the real variable that can be evaluated
    for complex inputs (this method is insensitive to epsi and pow2den_ parameters) ;

    @par Semantic:

    For every functor f and matrix expresion x of floating type T elements

    @code
    dfdx = df(f, x,  method{, epsi}{,  pow2den_});
    @endcode

    is respectively equivalent to

    @code
    dfdx = (f(x+h)-f(x-h))/(2*h); if method is nt2::tag::centered_
    dfdx = (f(x+h)-f(x))/h;       if method is nt2::tag::forward_
    dfdx = (f(x)-f(x-h))/h;       if method is nt2::tag::backward_
    dfdx = imag(f(x)/Eps<T>());   if method is nt2::tag::vand_
    @endcode

    h is computed automatically using the inputs and Derivinc constant.
    If you want more control on epsi use one of @funcref{forward}, @funcref{backward},
    @funcref{centered} functors or/and the pow2den_ parameter.

    @see @funcref{forward}, @funcref{backward}, @funcref{centered}, @funcref{vand}, @funcref{Derivinc}
    @param f function to derivate
    @param x points of derivation
    @param method used in numerical derivation
    @param pow2den_  try enhancing precision by computing a h value that is a power of 2.

    @return the derivative value
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::df_, df, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::df_, df, 4)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::df_,Domain,N,Expr>
  {
    // TODO: case for dual static of_size_
    typedef _2D result_type;

    BOOST_FORCEINLINE result_type operator ()(Expr& e) const
    {
      result_type sizee;
      sizee[0] = 1; //+= boost::fusion::at_c<0>(boost::proto::child_c<1>(e).extent());
      sizee[1] = boost::fusion::at_c<0>(boost::proto::child_c<1>(e).extent());

      return sizee;
    }

  };
} }
#endif


//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_NUMERICAL_DERIVATIVES_FUNCTIONS_VAND_HPP_INCLUDED
#define NT2_NUMERICAL_DERIVATIVES_FUNCTIONS_VAND_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief vand generic tag

     Represents the vand function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct vand_ : ext::unspecified_<vand_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<vand_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY(
        dispatching_vand_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::vand_, Site>
   dispatching_vand_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::vand_, Site>();
   }
   template<class... Args>
   struct impl_vand_;
  }
  /*!
    Computes the vand very accurate numerical derivative scheme to evaluate a derivative.
    If applicable the scheme gives a quasi perfect value of the derivative to a few ulps.

    @par Semantic:

    For every functor f from Rn (height(x)) to Rm  and  matrix expression x of size nxp
    of floating elements of type T will produce a matrix expression of size mxnxp (
    one line by f-component (m), one colon by x colon vector component (n), one page by x colon (p)

    @code
    dfdx = vand(f, x);
    @endcode

    is equivalent to

    @code
    for (i = 1, i <= n, ++i)
      for (j = 1, i <= m, ++j)
      {
        x(j, _) = x(j, _) + I<type_t>()*Eps<type_t>();
        dfdx(_, j, _) = imag(f(x)/Eps<T>());
        x(j, _) = real( x(j, _));
      }
    @endcode

    f is supposed real for real entries and also computable for complex entries.
    Also  x is a matrix each colon is supposed to be an f entry and f must be able
    to produce a matrix of mxn outputs for each colon of x.

    @see @funcref{forward}, @funcref{backward}, @funcref{centered}
    @param f function to derivate
    @param x points of numerical_derivatives

    @return an expression which will eventually evaluates to the derivative
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::vand_, vand, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::vand_, vand, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::vand_, vand, 4)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::vand_,Domain,N,Expr>
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


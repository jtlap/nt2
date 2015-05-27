//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DERIVATION_FUNCTIONS_GILLMURRAY_HPP_INCLUDED
#define NT2_DERIVATION_FUNCTIONS_GILLMURRAY_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief gillmurray generic tag

     Represents the gillmurray function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct gillmurray_ : ext::unspecified_<gillmurray_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<gillmurray_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY(
        dispatching_gillmurray_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::gillmurray_, Site>
   dispatching_gillmurray_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::gillmurray_, Site>();
   }
   template<class... Args>
   struct impl_gillmurray_;
  }
  /*!
    Computes  (second order derivative) numerical derivative the using the  Gill-Murray formula.

    @par Semantic:

    For every functor f from \f$R^n$\f (height(x)) to \f$R$\f and  matrix expression x of size nxp
    of floating elements of type T will produce a matrix expression of size mxnxn (
    the kth result page is the hessian of f computed at the kth column of the entry

    It computes only the onal of the gillmurray matrix at each point as
    columns vectors of a matrix result.

    @code
    dfdx = gillmurray(f, x{, epsi}{,  pow2den_});
    @endcode

    is equivalent to

    @code
    for (k = 1, k <= p, ++k)
    {
      for (i = 1, i <= n, ++i)
      {
        for (j = 1, j <= n, ++j)
        {
          d2fdx2(_, i, j) = (f(x+hi*ei+hj*ej)-f(x+hi*ei)-f(x+hj*ej)+f(x))/(hi*hj)
        }
      }
    }
    @endcode

    the hi values computed values are max(epsi*abs(xi), epsi) except if pow2den_ option is used
    in which case it is given by hi = max(e*ldexp(1, (exponent(xi)), e)
    where  e = ldexp(T(1), exponent(epsi)) that insures that the denominator of the quotient
    is a power of 2 and can help gain some more correct digits on the result.

    @see @funcref{forward}, @funcref{backward}, @funcref{centered}
    @param f function to derivate
    @param x points of derivation

    @return an expression which will eventually evaluates to the derivative
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::gillmurray_, gillmurray, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::gillmurray_, gillmurray, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::gillmurray_, gillmurray, 4)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::gillmurray_,Domain,N,Expr>
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


//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DERIVATION_FUNCTIONS_CENTERED_HPP_INCLUDED
#define NT2_DERIVATION_FUNCTIONS_CENTERED_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>



namespace nt2 { namespace tag
  {
   /*!
     @brief centered generic tag

     Represents the centered function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct centered_ : ext::unspecified_<centered_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<centered_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY(
        dispatching_centered_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::centered_, Site>
   dispatching_centered_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::centered_, Site>();
   }
   template<class... Args>
   struct impl_centered_;
  }
  /*!
    Computes the divided centered difference to evaluate a derivative.


    @par Semantic:

    For every functor f and matrix expresion x of floating type T elements

    @code
    dfdx = centered(f, x{, epsi}{,  pow2den_});
    @endcode

    is equivalent to

    @code
    dfdx = (f(x+h)-f(x-h))/(2*h));
    @endcode

    h computed value is max(epsi*abs(x), epsi) except if pow2den_ option is used
    in which case it is given by h = max(e*ldexp(1, (exponent(x)), e)
    where  e = ldexp(T(1), exponent(epsi)) that insures that the denominator of the quotient
    is a power of 2 and can help gain some more correct digits on the result.

    @see @funcref{forward}, @funcref{centered}, @funcref{vand}
    @param f function to derivate
    @param x points of derivation
    @param epsi default to Derivinc<T>())
    @param pow2den_  try enhancing precision by computing a h value that is a power of 2.

    @return the derivative value
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::centered_, centered, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::centered_, centered, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::centered_, centered, 4)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::centered_,Domain,N,Expr>
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


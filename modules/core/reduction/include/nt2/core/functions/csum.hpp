//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_CSUM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_CSUM_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the csum functor
    **/
    struct csum_ : ext::abstract_<csum_>
    {
      /// @brief Parent hierarchy
      typedef ext::abstract_<csum_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_csum_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::csum_, Site> dispatching_csum_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::csum_, Site>();
    }
    template<class... Args>
    struct impl_csum_;
  }
  /*!
   @brief compensated sum of a table along a given dimension

    Compute the sum of the  elements of a table expression
    along a given dimension using the compensated sum algorithm
    described in Accuracy and Stability of Numerical Algorithms (2002) Higham,
    Algorithm 4.2 p84.

    @par Semantic

    For any table  expression @c t and any integer @c n:

    @code
    auto r = csum(t{, n});
    @endcode


    @par Note:
    n default to firstnonsingleton(t)
    @see @funcref{firstnonsingleton}, @funcref{sum}, @funcref{size},

    @param t Table to process
    @param n Dimension along which to process t

    @return An expression eventually evaluated to the result
   */
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::csum_       , csum, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::csum_       , csum, 1)
}

#endif

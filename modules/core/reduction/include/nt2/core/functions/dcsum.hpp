//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DCSUM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DCSUM_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the dcsum functor
    **/
    struct dcsum_ : ext::abstract_<dcsum_>
    {
      /// @brief Parent hierarchy
      typedef ext::abstract_<dcsum_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_dcsum_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::dcsum_, Site> dispatching_dcsum_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::dcsum_, Site>();
    }
    template<class... Args>
    struct impl_dcsum_;
  }
  /*!
   @brief doubly compensated sum of a table along a given dimension

    Compute the sum of the  elements of a table expression
    along a given dimension using the doubly compensated error
    described in Accuracy and Stability of Numerical Algorithms (2002) Higham,
    Algorithm 4.3 p87.

    @par Semantic

    For any table  expression @c t and any integer @c n:

    @code
    auto r = dcsum(t{, n});
    @endcode


    @par Note:
    n default to firstnonsingleton(t)
    percent default to 0.5
    option default to both_

    @see @funcref{firstnonsingleton}, @funcref{sum}, @funcref{size},

    @param t Table to process
    @param n Dimension along which to process t

    @return An expression eventually evaluated to the result
   */
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::dcsum_       , dcsum, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::dcsum_       , dcsum, 1)
}

#endif

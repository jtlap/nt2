//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_GEOMMEAN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_GEOMMEAN_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the geommean functor
    **/
    struct geommean_ : ext::abstract_<geommean_>
    {
      /// @brief Parent hierarchy
      typedef ext::abstract_<geommean_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_geommean_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::geommean_, Site> dispatching_geommean_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::geommean_, Site>();
    }
    template<class... Args>
    struct impl_geommean_;
  }
  /*!
   @brief geometric mean of a table along a given dimension

    Compute the geometric mean of the  elements of a table expression
    along a given dimension.

    @par Semantic

    For any table  expression @c t and any integer @c n:

    @code
    auto r = geommean(t,n);
    @endcode

    is similar to:

    @code
    auto r = pow(prod(rec(t),n)), rec(size(a, n));
    @endcode


    @par Note:
    n default to firstnonsingleton(t)

    @see @funcref{firstnonsingleton}, @funcref{sum}, @funcref{size},

    @param a0 Table to process
    @param a1 Dimension along which to process a0

    @return An expression eventually evaluated to the result
   */
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::geommean_       , geommean, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::geommean_       , geommean, 1)
}

#endif

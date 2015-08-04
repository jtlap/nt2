//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TRIMMEAN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TRIMMEAN_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the trimmean functor
    **/
    struct trimmean_ : ext::abstract_<trimmean_>
    {
      /// @brief Parent hierarchy
      typedef ext::abstract_<trimmean_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_trimmean_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::trimmean_, Site> dispatching_trimmean_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::trimmean_, Site>();
    }
    template<class... Args>
    struct impl_trimmean_;
  }
  /*!
   @brief trimed arithmetic mean of a table along a given dimension

    Compute the trimed arithmetic mean mean of the  elements of a table expression
    along a given dimension.

    @par Semantic

    For any table  expression @c t and any integer @c n:

    @code
    auto r = trimmean(t,{,percent}{,lower_/upper_/both_}}{, n});
    @endcode


    @par Note:
    n default to firstnonsingleton(t)
    percent default to 0.5
    option default to both_

    @see @funcref{firstnonsingleton}, @funcref{sum}, @funcref{size},

    @param t Table to process
    @param percent of values t discard
    @param option if option is both_ percent/2 are discarded at each end of the sorted values
                  else percent is discarded at lower_ or upper_ end  of the sorted values
    @param n Dimension along which to process t

    @return An expression eventually evaluated to the result
   */
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::trimmean_       , trimmean, 4)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::trimmean_       , trimmean, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::trimmean_       , trimmean, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::trimmean_       , trimmean, 1)
}

#endif

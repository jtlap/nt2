//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_INCSUM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_INCSUM_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the incsum functor
    **/
    struct incsum_ : ext::abstract_<incsum_>
    {
      /// @brief Parent hierarchy
      typedef ext::abstract_<incsum_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY(
        dispatching_incsum_( ext::adl_helper(), static_cast<Args&&>(args)... )
      )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::incsum_, Site>
    dispatching_incsum_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::incsum_, Site>();
    }
    template<class... Args>
    struct impl_incsum_;
  }
  /*!
   @brief compensated sum of a table along a given dimension

    Compute the sum of the  elements of a table expression
    along a given dimension with an a priori sorting in increasing order

    @par Semantic

    For any table  expression @c t and any integer @c dim:

    @code
    auto r = incsum(t {, dim});
    @endcode

    @par Note:
    This function has only interest for the most precise available floating type
    (curently double) as for float for instance it can be cheaper to perform the
    computations in double with the ordinary sum functor and then cast the result
    for quite the same benefit, at a cheaper price.

    If quite 2 or 3 ulp accuracy is needed (in double) perhaps csum or dcsum are a better
    choice.

    @see @funcref{firstnonsingleton}, @funcref{sum}, @funcref{csum}, @funcref{dcsum},

    @param t Table to process
    @param  sort_ optionnal sorting parameter. If present the input is sorted along
            dim in decreasing magnitude order to improve accuracy
    @param dim Dimension along which to process td (default to firstnonsingleton(t))

    @return An expression eventually evaluated to the result
   */
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::incsum_       , incsum, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::incsum_       , incsum, 1)
}

#endif

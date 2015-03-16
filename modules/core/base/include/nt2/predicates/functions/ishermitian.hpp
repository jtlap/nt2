//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_ISHERMITIAN_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_ISHERMITIAN_HPP_INCLUDED

/*!
  @file
  @brief Defines the ishermitian function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for ishermitian functor
    **/
    struct ishermitian_ : ext::abstract_<ishermitian_>
    {
      typedef ext::abstract_<ishermitian_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_ishermitian_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::ishermitian_, Site> dispatching_ishermitian_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::ishermitian_, Site>();
    }
    template<class... Args>
    struct impl_ishermitian_;
  }

  /*!
    @brief Is an expression hermitian ?

    Checks if an expression is an hermitian matrix.

    @param a0 Expression to inspect
    @param a1 absolute tolerance on the conjugate symetry (default is 0 exact conjugate)

    @return Boolean value evaluating to the result of the test
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ishermitian_, ishermitian, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ishermitian_, ishermitian, 2)
}

#endif


//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_ISHESS_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_ISHESS_HPP_INCLUDED

/*!
  @file
  @brief Defines the ishess function
**/

#include <nt2/include/functor.hpp>

namespace nt2 {
  namespace tag {
    /*!
      @brief Tag for ishess functor
    **/
    struct ishess_ : ext::abstract_<ishess_>
    {
      typedef ext::abstract_<ishess_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_ishess_( ext::adl_helper(),
                                static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::ishess_, Site> dispatching_ishess_
    (adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::ishess_, Site>();
    }
    template<class... Args>
    struct impl_ishess_;
  }

  /*!
    @brief is a matrix in hessenberg form

    A matrix is in hessenberg form if it is zero below the first subdiagonal.

    @param a

    @return a bool
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ishess_, ishess, 1)
}

#endif

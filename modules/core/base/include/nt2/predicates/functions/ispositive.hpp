//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_ISPOSITIVE_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_ISPOSITIVE_HPP_INCLUDED

/*!
  @file
  @brief Define and implements the ispositive function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the ispositive functor
    **/
    struct ispositive_ : ext::abstract_<ispositive_>
    {
      typedef ext::abstract_<ispositive_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_ispositive_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::ispositive_, Site> dispatching_ispositive_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::ispositive_, Site>();
    }
    template<class... Args>
    struct impl_ispositive_;
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ispositive_, ispositive, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ispositive_, issemidefinite, 1)
}

#endif

//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_ISPOSITIVEDEFINITE_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_ISPOSITIVEDEFINITE_HPP_INCLUDED

/*!
  @file
  @brief Define and implements the ispositivedefinite function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the ispositivedefinite functor
    **/
    struct ispositivedefinite_ : ext::abstract_<ispositivedefinite_>
    {
      typedef ext::abstract_<ispositivedefinite_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_ispositivedefinite_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::ispositivedefinite_, Site> dispatching_ispositivedefinite_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::ispositivedefinite_, Site>();
    }
    template<class... Args>
    struct impl_ispositivedefinite_;
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ispositivedefinite_, ispositivedefinite, 1)
}

#endif

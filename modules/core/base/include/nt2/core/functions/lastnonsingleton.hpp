//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_LASTNONSINGLETON_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_LASTNONSINGLETON_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the nt2::lastnonsingleton function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for lastnonsingleton functor
    **/
    struct lastnonsingleton_ : ext::abstract_<lastnonsingleton_>
    {
      typedef ext::abstract_<lastnonsingleton_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_lastnonsingleton_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::lastnonsingleton_, Site> dispatching_lastnonsingleton_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::lastnonsingleton_, Site>();
    }
    template<class... Args>
    struct impl_lastnonsingleton_;
  }

  /*!
    @brief Last non-singleton dimension

    For a given expression, returns the last dimension which is not equal to 1.

    @param a0 Expression to inspect
    @return The value of the last dimension of a0 not equal to 1.
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::lastnonsingleton_,lastnonsingleton,1)
}

#endif

//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_HISTC_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_HISTC_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the histc functor
    **/
    struct histc_ : ext::abstract_<histc_>
    {
      typedef ext::abstract_<histc_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_histc_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::histc_, Site> dispatching_histc_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::histc_, Site>();
    }
    template<class... Args>
    struct impl_histc_;
  }

  /*!
    @brief

    @param a0
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::histc_, histc, 1)

  /*!
    @brief

    @param a0
    @param a1
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::histc_, histc, 2)

  /*!
    @brief

    @param a0
    @param a1
    @param a2
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::histc_, histc, 3)
}

#endif

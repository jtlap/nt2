/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_FUNCTOR_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_FUNCTOR_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Main generic functor class
//* TODO : Documentation:http://nt2.lri.fr/sdk/functor/functor.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/config.hpp>
#include <boost/tr1/functional.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/errors/static_assert.hpp>
#include <nt2/sdk/functor/forward.hpp>
#include <nt2/sdk/functor/meta/dominant.hpp>
#include <nt2/sdk/functor/meta/enable_call.hpp>
#include <nt2/sdk/functor/details/call.hpp>
#include <nt2/sdk/functor/details/validate.hpp>

#if !defined(BOOST_HAS_VARIADIC_TMPL)
#include <nt2/extension/parameters.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#endif

namespace nt2 { namespace functors
{
  template<class Function, class Info> struct functor
  {
    struct validate
    {
      template<class Sig> struct result;
      #if defined(BOOST_HAS_VARIADIC_TMPL)
      #include <nt2/sdk/functor/details/validate_0x.hpp>
      #else
      #include <nt2/sdk/functor/details/validate_98.hpp>
      #endif
    };

    template<class Sig> struct result;
    #if defined(BOOST_HAS_VARIADIC_TMPL)
    #include <nt2/sdk/functor/details/call_0x.hpp>
    #else
    #include <nt2/sdk/functor/details/call_98.hpp>
    #endif
  };
} }

#endif

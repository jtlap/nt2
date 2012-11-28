/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_SETTINGS_SHARING_HPP_INCLUDED
#define NT2_CORE_SETTINGS_SHARING_HPP_INCLUDED

#include <boost/cstdint.hpp>
#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/forward/sharing.hpp>

namespace nt2
{

  namespace meta
  {
    template<class Default> struct option<shared_, tag::sharing_, Default>
    {
      typedef shared_ type;
    };

    template<class Default> struct option<owned_, tag::sharing_, Default>
    {
      typedef owned_ type;
    };
  }
}

#include <nt2/core/settings/details/sharing.hpp>

#endif

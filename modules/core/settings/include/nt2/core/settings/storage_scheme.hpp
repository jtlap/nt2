//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_STORAGE_SCHEME_HPP_INCLUDED
#define NT2_CORE_SETTINGS_STORAGE_SCHEME_HPP_INCLUDED

#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/forward/storage_scheme.hpp>
namespace nt2
{

  namespace meta
  {
    template<class Default> struct option<conventional_
                                          , tag::storage_scheme_
                                          , Default>
    {
      typedef conventional_ type;
    };

    template<class Default> struct option<packed_
                                          , tag::storage_scheme_
                                          , Default>
    {
      typedef packed_ type;
    };
  }
}

#include <nt2/core/settings/details/storage_scheme.hpp>

#endif

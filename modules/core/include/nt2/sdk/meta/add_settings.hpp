//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_ADD_SETTINGS_HPP_INCLUDED
#define NT2_SDK_META_ADD_SETTINGS_HPP_INCLUDED

#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/normalize.hpp>
#include <nt2/core/settings/semantic.hpp>
#include <nt2/core/utility/of_size.hpp>
#include <nt2/sdk/meta/settings_of.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/memory/forward/container.hpp>
#include <boost/dispatch/meta/transfer_qualifiers.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>

namespace nt2 { namespace meta
{
  template<class Type, class Settings>
  struct add_settings
  {
    typedef typename settings_of<Type>::type init_settings;
    typedef typename option<init_settings, tag::semantic_, tag::table_>::type Tag;
    typedef typename strip<typename scalar_of<Type>::type>::type T;
    typedef typename normalize<Tag, T, nt2::settings(init_settings, Settings)>::type new_settings;

    typedef typename option<new_settings, tag::of_size_>::type size_type;
    typedef typename boost::mpl::
            if_< boost::is_same< size_type, _0D >
               , T
               , memory::container<T, new_settings>
               >::type base;

    typedef typename boost::dispatch::meta::
            transfer_qualifiers< base
                               , Type
                               >::type type;
  };
} }

#endif

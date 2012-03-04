//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_GENERATIVE_GENERATIVE_HPP_INCLUDED
#define NT2_CORE_UTILITY_GENERATIVE_GENERATIVE_HPP_INCLUDED

#include <cstddef>
#include <nt2/sdk/meta/as.hpp>
#include <nt2/core/settings/size.hpp>
#include <nt2/core/settings/index.hpp>
#include <nt2/core/settings/option.hpp>
#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/core/utility/generative/adapted.hpp>
#include <nt2/core/settings/normalize_settings.hpp>

namespace nt2 { namespace details
{
  //============================================================================
  /*!
   * generative is a lazy type acting as a container but containing no
   * memory block. Values from the container are computed on the fly everytime
   * a value is requested.
   **/
  //============================================================================
  template<class Tag, class Functor, class T, class S>
  struct generative
  {
    typedef T                                                 value_type;
    typedef Tag                                               tag_type;
    typedef Functor                                           generator_type;
    typedef typename meta::normalize_settings<Tag,T,S>::type  settings_type;
    typedef typename meta::option<S,tag::of_size_>::type      sizes_type;
    typedef sizes_type const&                                 extent_type;

    generative( extent_type sz, generator_type const& g = generator_type() )
              :  generator_(g), sizes_(sz) {}

    generative( generative const& src )
              :  generator_(src.generator_), sizes_(src.sizes_) {}

    generative& operator=( generative const& src )
    {
      generator_  = src.generator_;
      sizes_      = src.sizes_;
      return *this;
    }

    template<class Position,class Target>
    BOOST_FORCEINLINE typename Target::type
    operator()( Position const& pos, Target const& t ) const
    {
      return generator_(pos,sizes_,t);
    }

    generator_type  generator_;
    sizes_type      sizes_;
  };
} }

#endif

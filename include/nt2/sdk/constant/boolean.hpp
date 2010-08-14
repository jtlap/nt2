/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_BOOLEAN_HPP_INCLUDED
#define NT2_SDK_CONSTANT_BOOLEAN_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Make True and False
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/constant/constant.hpp>

namespace nt2 { namespace constants
{
  struct true_  {};
  struct false_ {};
} }

namespace nt2
{
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::true_ , True  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::false_, False )
}

namespace nt2 { namespace functors
{
  template<class Category,class Info>
  struct  call<constants::true_,tag::constant_(Category),Info>
  {
    template<class Sig> struct result;
    template<class This,class Target>
    struct result<This(nt2::meta::as_<Target>)> { typedef Target type; };

    template<class Target> inline typename Target::type const
    operator()( Target const& ) const
    {
      return true;
    }
  };

  template<class Category,class Info>
  struct  call<constants::false_,tag::constant_(Category),Info>
  {
    template<class Sig> struct result;
    template<class This,class Target>
    struct result<This(nt2::meta::as_<Target>)> { typedef Target type; };

    template<class Target> inline typename Target::type const
    operator()( Target const& ) const
    {
      return false;
    }
  };
} }

#endif

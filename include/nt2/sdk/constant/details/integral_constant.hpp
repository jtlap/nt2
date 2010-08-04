/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_DETAILS_INTEGRAL_CONSTANT_HPP_INCLUDED
#define NT2_SDK_CONSTANT_DETAILS_INTEGRAL_CONSTANT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Base class for generating an integral constant
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/constant/splat.hpp>
#include <nt2/sdk/functor/category.hpp>

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // For any type Target that can be constructed from an integer, generate
  // the proper conversion and value return.
  //////////////////////////////////////////////////////////////////////////////
  template<class Value,class Category> struct integral_constant
  {
    template<class Sig> struct result;
    template<class This,class Target>
    struct result<This(nt2::meta::as_<Target>)>
    {
      typedef Target type;
    };

    template<class Target> inline typename Target::type const
    operator()( Target const& ) const
    {
      typename Target::type that = splat<typename Target::type>(Value::value);
      return that;
    }
  };
} }

#endif

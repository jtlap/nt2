//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_SIMD_DETAILS_NATIVE_META_AS_REAL_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_NATIVE_META_AS_REAL_HPP_INCLUDED

#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/simd/category.hpp>
#include <boost/mpl/placeholders.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/make_real.hpp>

namespace nt2 { namespace details
{
  template<class Type, class C, class X>
  struct  as_real<Type,tag::simd_(C,X) >
        : meta::make_real< sizeof(typename meta::scalar_of<Type>::type)
                          , simd::native<boost::mpl::_,X>
                          >
  {};
} }

#endif

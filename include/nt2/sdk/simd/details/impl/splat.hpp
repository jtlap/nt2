//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SPLAT_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SPLAT_HPP_INCLUDED

#include <nt2/sdk/simd/preprocessor/include.hpp>

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // We dispatch on the scalar T type for SIMD splat
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class Category, class Extension, class Info>
  struct  dispatch<splat_<T>,tag::simd_(Category,Extension),Info> 
        : boost::mpl::always<typename meta::scalar_of<T>::type>
  {};
} }

#include NT2_SIMD_INCLUDE(splat.hpp)

#endif

//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_COMMON_FALSE_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_COMMON_FALSE_HPP_INCLUDED

#include <nt2/include/constants/digits.hpp>

////////////////////////////////////////////////////////////////////////////////
// in SIMD, False is simply 0 and forward to its actual optimized version
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::False, tag::cpu_
                            , (A0)(X)
                            , ((target_< simd_< arithmetic_<A0> ,X> >))
                            )
  {
    typedef typename meta::strip<A0>::type::type result_type;
    NT2_FUNCTOR_CALL(1) { return Zero<result_type>(); }
  };
} }

#endif

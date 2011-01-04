//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_COMMON_ANY_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_COMMON_ANY_HPP_INCLUDED
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/hmsb.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/include/functions/split.hpp>

namespace nt2 { namespace functors
{
  //  no special validate for any

  /////////////////////////////////////////////////////////////////////////////
  // Compute any(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int8_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension, class Info>
  struct call<any_,tag::simd_(tag::arithmetic_,Extension),int8_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>  { typedef bool type; };

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type                            stype;
      typedef typename meta::upgrade<stype>::type                           utype;
      typedef simd::native<utype,tag::sse_>                                 ttype;
      ttype a0h, a0l;
      boost::fusion::tie(a0h, a0l) = split(a0); 
      return (hmsb(is_nez(a0h)) || hmsb(is_nez(a0l)));  
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is uint8_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension, class Info>
  struct call<any_,tag::simd_(tag::arithmetic_,Extension),uint8_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>  { typedef bool type; };

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type                            stype;
      typedef typename meta::upgrade<stype>::type                           utype;
      typedef simd::native<utype,tag::sse_>                                 ttype;
      ttype a0h, a0l;
      boost::fusion::tie(a0h, a0l) = split(a0);
      return (hmsb(is_nez(a0h)) || hmsb(is_nez(a0l)));  
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension, class Info>
  struct call<any_,tag::simd_(tag::arithmetic_,Extension),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>  { typedef bool type; };

    NT2_FUNCTOR_CALL(1)
    {
      return hmsb(is_nez(a0));  
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010

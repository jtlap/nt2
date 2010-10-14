//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_ROL_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_ROL_HPP_INCLUDED
#include <nt2/sdk/meta/size.hpp>
#include <nt2/sdk/meta/strip.hpp>


namespace nt2 { namespace functors
{
//   template<class Extension,class Info>
//   struct validate<rol_,tag::simd_(tag::arithmetic_,Extension),Info>
//   {
//     template<class Sig> struct result;
//     template<class This,class A0,class A1>
//     struct result<This(A0,A1)> : 
//       boost::mpl::and_ < meta::is_integral<A1>,
// 			 meta::has_same_size<A0, A1, meta::scalar_of < boost::mpl::_> > >{};
//   };
  /////////////////////////////////////////////////////////////////////////////
  // Compute rol(const A0& a0, const A0& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<rol_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      return map(functor<rol_>(), a0, a1);
    }
  };
} }

      
#endif

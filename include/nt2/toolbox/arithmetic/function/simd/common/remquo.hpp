//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_REMQUO_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_REMQUO_HPP_INCLUDED
#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/idivfix.hpp>


namespace nt2 { namespace functors
{
  //  no special validate for remquo

  /////////////////////////////////////////////////////////////////////////////
  // Compute remquo(const A0& a0, const A0& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<remquo_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
    {
      typedef typename meta::strip<A0>::type                 stA0; 
      typedef boost::fusion::tuple<stA0,stA0>                type;
    };

    NT2_FUNCTOR_CALL(2)
    {
      typename NT2_CALL_RETURN_TYPE(2)::type res;
      eval( a0, a1
          , boost::fusion::at_c<0>(res),  boost::fusion::at_c<1>(res)
          );
      return res;
    }
  private:
    template<class A0,class A1,class R0,class R1> inline void
    eval(A0 const& a0,A1 const& a1,R0& r0, R1& r1) const
    {
      r1 = idivfix(a0, a1);
      r0 = a0-r1*a1;
    }
//     template<class A0,class A1,class R0,class R1> inline void
//     eval(A0 const& a0,A1 const& a1,R0& r0, R1& r1, arithmetic_ const &) const
//     {
//       r1 = rdivide(a0, a1);
//       r0 = a0-r1*a1;
//     }

  };
} }

      
#endif

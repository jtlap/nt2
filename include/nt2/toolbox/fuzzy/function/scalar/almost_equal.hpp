//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_FUZZY_FUNCTION_SCALAR_ALMOST_EQUAL_HPP_INCLUDED
#define NT2_TOOLBOX_FUZZY_FUNCTION_SCALAR_ALMOST_EQUAL_HPP_INCLUDED
#include <nt2/sdk/constant/real.hpp>

#include <nt2/include/functions/dist.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/successor.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for almost_equal

  /////////////////////////////////////////////////////////////////////////////
  // Compute almost_equal(const A0& a0, const A1& a1, const A2& a2)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<almost_equal_,tag::scalar_(tag::arithmetic_),real_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1,class A2>
    struct result<This(A0,A1,A2)> {typedef bool type; }; 

    NT2_FUNCTOR_CALL(3)
    {
      if (a0 == a1) return true;
      if (is_inf(a0) || is_inf(a1)) return (a0 == a1);
      if (is_nan(a0) || is_nan(a1)) return false;
      // see http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
      // by Bruce Dawson
      // Do not choose a2 negative or too large
      // assert(aa2 > 0 && aa2 < bitinteger(Nan<select_type>()) );
      return  (a0 <= successor(a1, a2)) && (a0 >= successor(a1, -a2));
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<almost_equal_,tag::scalar_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1,class A2>
    struct result<This(A0,A1,A2)> {typedef bool type; }; 

    NT2_FUNCTOR_CALL(3)
    {
      return dist(a0, a1) <= a2;
    }
  };

} }

#endif
/// Revised by jt the 14/11/2010

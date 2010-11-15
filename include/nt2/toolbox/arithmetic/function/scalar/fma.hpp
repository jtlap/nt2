//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_FMA_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_FMA_HPP_INCLUDED
#include <boost/fusion/tuple.hpp>

#include <nt2/include/functions/two_add.hpp>
#include <nt2/include/functions/two_prod.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for fma

  /////////////////////////////////////////////////////////////////////////////
  // Compute fma(const A0& a0, const A1& a1, const A2& a2)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is float
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<fma_,tag::scalar_(tag::arithmetic_),float,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1,class A2>
    struct  result<This(A0,A1,A2)>
          : boost::result_of<meta::arithmetic(A0,A1,A2)>{};

    NT2_FUNCTOR_CALL(3)
    {
//       A0 p, rp, s, rs;
//       boost::fusion::tie(p, rp) = two_prod(a0, a1);
//       boost::fusion::tie(s, rs) = two_add(p, a2);
//       return s+(rp+rs);
      //       fma is incorrect this is Bugzilla Bug 3268 for glibc
      return a0*a1+a2;
      //         return ::fma(a0, a1, a2);
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<fma_,tag::scalar_(tag::arithmetic_),double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1,class A2>
    struct  result<This(A0,A1,A2)>
          : boost::result_of<meta::arithmetic(A0,A1,A2)>{};

    NT2_FUNCTOR_CALL(3)
    {
//       A0 p, rp, s, rs;
//       boost::fusion::tie(p, rp) = two_prod(a0, a1);
//       boost::fusion::tie(s, rs) = two_add(p, a2);
//       return s+(rp+rs);
      //      fma is incorrect this is Bugzilla Bug 3268 for glibc
      return a0*a1+a2;
      //         return ::fma(a0, a1, a2);
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<fma_,tag::scalar_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1,class A2>
    struct  result<This(A0,A1,A2)>
          : boost::result_of<meta::arithmetic(A0,A1,A2)>{};

    NT2_FUNCTOR_CALL(3)
    {
      return a0*a1+a2;
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010

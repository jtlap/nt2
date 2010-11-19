//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_FDLIBM_FUNCTION_SCALAR_FREXP_HPP_INCLUDED
#define NT2_TOOLBOX_FDLIBM_FUNCTION_SCALAR_FREXP_HPP_INCLUDED
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>


namespace nt2 { namespace functors
{
  extern "C"{
    extern double fd_frexp ( double,int* );
  }
  template<class Info>
  struct validate<fdlibm::frexp_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::is_floating_point<A0> {};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute frexp(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is fundamental_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<fdlibm::frexp_,tag::scalar_(tag::arithmetic_),fundamental_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0> struct result<This(A0)>
    {
      typedef boost::fusion::vector<double,int>             type;
    };

    NT2_FUNCTOR_CALL(1)
    {
      typename NT2_CALL_RETURN_TYPE(1)::type res;
      eval( a0
          , boost::fusion::at_c<0>(res)
          , boost::fusion::at_c<1>(res)
          );
      return res;
    }
  private:
    NT2_FUNCTOR_CALL_DEFAULT(1)

    template<class A0,class R0,class R1> inline void
    eval(A0 const& a0,R0& r0, R1& r1)const
    {
      int r1t;
      r0 = fd_frexp(a0, &r1t);
      r1 = r1t;
    }
  };
} }

#endif
/// Revised by jt the 16/11/2010

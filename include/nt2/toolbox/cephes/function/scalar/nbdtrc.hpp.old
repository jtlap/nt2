//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_CEPHES_FUNCTION_SCALAR_NBDTRC_HPP_INCLUDED
#define NT2_TOOLBOX_CEPHES_FUNCTION_SCALAR_NBDTRC_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>

namespace nt2 { namespace functors
{
  extern "C"{
    extern float cephes_nbdtrcf ( int,int,float );
    extern double cephes_nbdtrc ( int,int,double );
    extern long double cephes_nbdtrcl ( int,int,long double );
  }
  template<class Info>
  struct validate<cephes::nbdtrc_,tag::scalar_(tag::arithmetic_),Info>
    {
      template<class Sig> struct result;
      template<class This,class A0, class A1, class A2>
      struct result<This(A0, A1, A2)> :
        boost::mpl::and_<
           meta::is_integral<A0>,
           meta::is_integral<A1>
        >{};
    };
  /////////////////////////////////////////////////////////////////////////////
  // Compute nbdtrc(const A0& a0, const A1& a1, const A2& a2)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A2 is float
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<cephes::nbdtrc_,tag::scalar_(tag::arithmetic_),float,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1, class A2>
    struct result<This(A0, A1, A2)> : boost::result_of<meta::floating(A2)>{};

    NT2_FUNCTOR_CALL(3){ return cephes_nbdtrcf(a0, a1, a2); }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A2 is double
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<cephes::nbdtrc_,tag::scalar_(tag::arithmetic_),double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1, class A2>
    struct result<This(A0, A1, A2)> : boost::result_of<meta::floating(A2)>{};

    NT2_FUNCTOR_CALL(3){ return cephes_nbdtrc(a0, a1, a2); }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A2 is long double
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<cephes::nbdtrc_,tag::scalar_(tag::arithmetic_),long double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1, class A2>
    struct result<This(A0, A1, A2)> : boost::result_of<meta::floating(A2)>{};

    NT2_FUNCTOR_CALL(3){ return cephes_nbdtrcl(a0, a1, a2); }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A2 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<cephes::nbdtrc_,tag::scalar_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1, class A2>
    struct result<This(A0, A1, A2)> : boost::result_of<meta::floating(A2)>{};

    NT2_FUNCTOR_CALL(3)
    {
      typedef typename NT2_CALL_RETURN_TYPE(3)::type type;
      return nt2::cephes::nbdtrc((a0), (a1), type(a2));
    }
  };

} }

#endif
/// Revised by jt the 16/11/2010

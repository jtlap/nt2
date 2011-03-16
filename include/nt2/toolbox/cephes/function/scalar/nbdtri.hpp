//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_CEPHES_FUNCTION_SCALAR_NBDTRI_HPP_INCLUDED
#define NT2_TOOLBOX_CEPHES_FUNCTION_SCALAR_NBDTRI_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/include/functions/is_lez.hpp>

extern "C" { extern double cephes_nbdtri(int,int,double); }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A2 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(cephes::tag::nbdtri_, tag::cpu_,
                        (A0)(A1)(A2),
                        (integer_<A0>)(integer_<A1>)(arithmetic_<A2>)
                       )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<cephes::tag::nbdtri_(tag::integer_,tag::integer_,tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1, class A2>
    struct result<This(A0, A1, A2)> : std::tr1::result_of<meta::floating(A2)>{};

    NT2_FUNCTOR_CALL(3)
    {
      typedef typename NT2_RETURN_TYPE(3)::type type;
      return nt2::cephes::nbdtri(a0, a1, double(a2));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A2 is real
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(cephes::tag::nbdtri_, tag::cpu_,
                        (A0)(A1)(A2),
                        (integer_<A0>)(integer_<A1>)(real_<A2>)
                       )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<cephes::tag::nbdtri_(tag::integer_,tag::integer_,tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1, class A2>
    struct result<This(A0, A1, A2)> : meta::strip<A2>{};

    NT2_FUNCTOR_CALL(3)
    {
      if (is_lez(a0)||is_lez(a1)) return nt2::Nan<A2>(); 
      return cephes_nbdtri(a0, a1, double(a2)); }
    };
} }

#endif
// modified by jt the 29/12/2010

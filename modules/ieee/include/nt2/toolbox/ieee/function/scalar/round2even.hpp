//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_ROUND2EVEN_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_ROUND2EVEN_HPP_INCLUDED

#include <nt2/include/functions/bitofsign.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/meta/strip.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::round2even_, tag::cpu_,
                            (A0),
                            (arithmetic_<A0>)
                           )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::round2even_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      return a0;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::round2even_, tag::cpu_,
                            (A0),
                            (real_<A0>)
                           )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::round2even_(tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      const type v = nt2::abs(a0);
       const type t2n = Two2nmb<type>();
       volatile type d0 = (v+t2n);
       volatile type d = (d0-t2n);
       d = (v < t2n)?d:v;
       //      type q =  d;
       return a0 < 0? -d : d; //b_xor(d, nt2::bitofsign(a0));
    }
  };
} }

#endif
// modified by jt the 26/12/2010

//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_MAXMAG_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_MAXMAG_HPP_INCLUDED

#include <nt2/include/functions/abs.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::maxmag_, tag::cpu_,
                        (A0)(A1),
                        (fundamental_<A0>)(fundamental_<A1>)
                       )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::maxmag_(tag::fundamental_,tag::fundamental_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      std::tr1::result_of<meta::arithmetic(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      return (nt2::abs(a0) > nt2::abs(a1)) ? a0 : a1;
    }

  };
} }

#endif
// modified by jt the 26/12/2010

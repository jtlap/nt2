//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_BITINTEGER_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_BITINTEGER_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/meta/as_bits.hpp>

#include <nt2/include/functions/is_positive.hpp>

namespace nt2 { namespace functors
{

  template<class Info>
  struct validate<bitinteger_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
             meta::is_floating_point<A0>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute bitinteger(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<bitinteger_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::as_integer<A0, signed>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_bits<A0, signed>::type type;
      type that = {a0};
      return is_positive(a0) ? that.bits : Signmask<A0>()-that.bits;
    }
  };
} }


      
#endif

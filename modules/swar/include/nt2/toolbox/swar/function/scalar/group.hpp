//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SCALAR_GROUP_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SCALAR_GROUP_HPP_INCLUDED

/////////////////////////////////////////////////////////////////////////////
// group as currently no meaning in scalar mode
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::group_, tag::cpu_,
                        (A0),
                        ((arithmetic_<A0>))
                        ((arithmetic_<A0>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::group_(tag::arithmetic_, 
                          tag::arithmetic_ ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0, A0)> : meta::strip<A0>{}; 

  };
} }
      
#endif
// modified by jt the 26/12/2010
/// No restore -- hand modifications

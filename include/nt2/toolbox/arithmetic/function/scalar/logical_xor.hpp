//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_LOGICAL_XOR_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_LOGICAL_XOR_HPP_INCLUDED

#include <nt2/include/functions/is_nez.hpp>

namespace nt2 { namespace functors
{

  template<class Info>
  struct validate<logical_xor_,tag::scalar_(tag::arithmetic_),Info>
  {
    typedef boost::mpl::true_ result_type;
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute logical_xor(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<logical_xor_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)>  
      {  typedef  bool type; };

    NT2_FUNCTOR_CALL(2)
    {
      return b_xor(is_nez(a0), is_nez(a1));
    }
  };
} }


      
#endif

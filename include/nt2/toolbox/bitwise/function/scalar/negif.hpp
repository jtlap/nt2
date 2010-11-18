//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_NEGIF_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_NEGIF_HPP_INCLUDED


namespace nt2 { namespace functors
{

  /////////////////////////////////////////////////////////////////////////////
  // Compute negif(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////
  
  /////////////////////////////////////////////////////////////////////////////
  // Dispatch is on second parameter
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct dispatch<negif_, tag::scalar_(tag::arithmetic_),Info> : boost::mpl::_2 {};

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<negif_,tag::scalar_(tag::arithmetic_),real_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> : 
      boost::result_of<meta::arithmetic(A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      return a0?-a1:a1; 
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<negif_,tag::scalar_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> : 
      boost::result_of<meta::arithmetic(A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      return a0?-a1:a1; 
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010
/// No restore -- hand modifications

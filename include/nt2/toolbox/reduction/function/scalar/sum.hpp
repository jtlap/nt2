//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SCALAR_SUM_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SCALAR_SUM_HPP_INCLUDED

namespace nt2 { namespace functors
{
  /////////////////////////////////////////////////////////////////////////////
  // Works on bool
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct validate<sum_,tag::scalar_(tag::arithmetic_),Info>
  {
    typedef boost::mpl::true_ result_type;
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Compute prod(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is fundamental_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<sum_,tag::scalar_(tag::arithmetic_),fundamental_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : std::tr1::result_of<meta::arithmetic(A0)>{};
      

    NT2_FUNCTOR_CALL(1)
      {
	return a0;
      }

  };
} }

#endif
/// Revised by jt the 15/11/2010

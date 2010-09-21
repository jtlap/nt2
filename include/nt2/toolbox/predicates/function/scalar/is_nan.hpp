//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_PREDICATES_FUNCTION_SCALAR_IS_NAN_HPP_INCLUDED
#define NT2_TOOLBOX_PREDICATES_FUNCTION_SCALAR_IS_NAN_HPP_INCLUDED
#include <nt2/sdk/details/ignore_unused.hpp>


namespace nt2 { namespace functors
{

  template<class Info>
  struct validate<is_nan_,tag::scalar_(tag::arithmetic_),Info>
  {
    typedef boost::mpl::true_ result_type;
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute is_nan(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<is_nan_,tag::scalar_(tag::arithmetic_),Info>
  {
    typedef bool result_type; 

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      A0,
      (2, (real_,fundamental_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,       real_)
    {
       return (a0 != a0);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, fundamental_)
    {
      details::ignore_unused(a0); 
      return false; 
    }
  };
} }


      
#endif

//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_ABS_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_ABS_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>

namespace nt2 { namespace functors
{

  template<class Info>
  struct validate<abs_,tag::scalar_(tag::arithmetic_),Info>
  {
    typedef boost::mpl::true_ result_type;
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute abs(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<abs_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      meta::strip <A0>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      A0,
      (6, (float,int32_t,unsigned_,signed_,arithmetic_,bool_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,       float)
    {
       return ::fabs(a0);
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1,     int32_t)
    {
      A0 mask = a0 >> (sizeof(int32_t)*8 - 1);
      return (a0 + mask) ^ mask;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1,   unsigned_)
    {
      return a0;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1,     signed_)
    {
      return (a0 > 0)?a0:-a0;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1, arithmetic_)
    {
      return std::abs(a0);
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1, bool_)
    {
      return a0;
    }
  };
} }


      
#endif

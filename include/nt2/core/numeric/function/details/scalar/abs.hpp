/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_NUMERIC_FUNCTION_DETAILS_SCALAR_ABS_HPP_INCLUDED
#define NT2_CORE_NUMERIC_FUNCTION_DETAILS_SCALAR_ABS_HPP_INCLUDED

#include <cmath>

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // Allow abs(bool)
  //////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct validate<abs_,tag::scalar_(tag::arithmetic_),Info>
  {
    typedef boost::mpl::true_ result_type;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Compute abs(v)
  //////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<abs_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>  { typedef A0 type; };

    NT2_FUNCTOR_CALL_DISPATCH ( 1, A0
                              , ( 5,( float,int32_t,bool_,unsigned_, signed_))
                              )

    NT2_FUNCTOR_CALL_EVAL_IF(1, int32_t     )
    {
      A0 const mask = a0 >> 31;
      return (a0 + mask) ^ mask;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1, signed_     ) { return (a0>0) ? a0 : -a0; }
    NT2_FUNCTOR_CALL_EVAL_IF(1, float       ) { return ::fabs(a0);        }
    NT2_FUNCTOR_CALL_EVAL_IF(1, unsigned_   ) { return a0;                }
    NT2_FUNCTOR_CALL_EVAL_IF(1, bool_       ) { return a0;                }
  };
} }

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of abs.hpp
// /////////////////////////////////////////////////////////////////////////////

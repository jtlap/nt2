/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_DETAILS_REAL_CONSTANT_HPP_INCLUDED
#define NT2_SDK_CONSTANT_DETAILS_REAL_CONSTANT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Base class for generating an integral constant
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/functor/category.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Static container for double/float bit patterns
  //////////////////////////////////////////////////////////////////////////////
  template<uint64_t Double, uint32_t Float>
  struct pattern
  {
    BOOST_STATIC_CONSTANT( uint64_t, double_value = Double  );
    BOOST_STATIC_CONSTANT( uint32_t, float_value  = Float   );
  };

  //////////////////////////////////////////////////////////////////////////////
  // For any real target, generate a precise value using a bitfield
  //////////////////////////////////////////////////////////////////////////////
  template<class Values,class Category> struct real_constant;

  //////////////////////////////////////////////////////////////////////////////
  // base overload for arithmetic scalar value
  //////////////////////////////////////////////////////////////////////////////
  template<class Values>
  struct real_constant<Values, tag::scalar_(tag::arithmetic_)>
  {
    template<class Sig> struct result;

    template<class This>
    struct result<This(meta::as_<float>)>  { typedef float type;   };

    template<class This>
    struct result<This(meta::as_<double>)> { typedef double type;  };

    // Let's cheat to reuse FUNCTOR_CALL macros ;)
    typedef real_constant call;

    NT2_FUNCTOR_CALL_DISPATCH(1,typename A0::type,(2,(double,float)) )

    NT2_FUNCTOR_CALL_EVAL_IF(1,double)
    {
      typedef union { uint64_t bits; double val; } type;
      type const that = {Values::double_value};
      return that.val;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1,float)
    {
      typedef union { uint32_t bits; float val; } type;
      type const that = {Values::float_value};
      return that.val;
    }
  };
} }

#endif

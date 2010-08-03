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
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>
#include <boost/type_traits/is_floating_point.hpp>

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
  template<class Values,class Category> struct real_constant
  {
    template< class Target
            , bool EnableIf = boost::is_floating_point<Target>::value
            > struct inner
    {};

    template<class Target> struct inner<Target,true>
    {
      typedef Target type;
    };

    template<class Sig> struct result;

    template<class This,class Target>
    struct result<This(meta::as_<Target>)> : inner<Target> {};

    // Let's cheat to reuse FUNCTOR_CALL macros ;)
    typedef real_constant call;

    NT2_FUNCTOR_CALL_DISPATCH ( 1
                              , typename meta::scalar_of<typename A0::type>::type
                              , (2,(double,float))
                              )

    NT2_FUNCTOR_CALL_EVAL_IF(1,double)
    {
      typedef union { uint64_t bits; double val; } type;
      type const that = {Values::double_value};
      return splat<typename A0::type>(that.val);
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1,float)
    {
      typedef union { uint32_t bits; float val; } type;
      type const that = {Values::float_value};
      return splat<typename A0::type>(that.val);
    }
  };
} }

#endif

/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_NATIVE_HPP_INCLUDED
#define NT2_SDK_SIMD_NATIVE_HPP_INCLUDED

#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/simd/extensions.hpp>
#include <boost/utility/enable_if.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/functor/category.hpp>
#include <nt2/sdk/errors/static_assert.hpp>
#include <nt2/sdk/simd/meta/is_vectorizable.hpp>

/*
#include <nt2/sdk/functor/functor.hpp>
#include <nt2/sdk/aligned/overload.hpp>
#include <nt2/sdk/functor/details/operators.hpp>
*/

namespace nt2 { namespace simd
{
  //////////////////////////////////////////////////////////////////////////////
  /// Platform independant native SIMD type
  //////////////////////////////////////////////////////////////////////////////
  template<class Scalar,class Extension> struct native
  {
    ////////////////////////////////////////////////////////////////////////////
    // Check that Scalar is supported here
    ////////////////////////////////////////////////////////////////////////////
    NT2_STATIC_ASSERT ( (meta::is_vectorizable<Scalar,Extension>::value)
                      , INVALID_SCALAR_TYPE_IN_SIMD_NATIVE_TYPE
                      , (Scalar)
                      );

    ////////////////////////////////////////////////////////////////////////////
    // Various interface typedefs
    ////////////////////////////////////////////////////////////////////////////
    typedef Scalar                                          value_type;
    typedef Extension                                       extension_type;
    typedef functors::simd_<tag::arithmetic_,Extension,1>   nt2_category_tag;
    typedef native<Scalar,Extension>                        self_type;
    typedef typename meta::as_simd<Scalar,Extension>::type  native_type;
    typedef value_type&                                     reference;
    typedef value_type                                      const_reference;
    typedef std::size_t                                     size_type;

    ////////////////////////////////////////////////////////////////////////////
    // vector size
    ////////////////////////////////////////////////////////////////////////////
    BOOST_STATIC_CONSTANT ( size_type
                          , static_size = sizeof(native_type)/sizeof(value_type)
                                        ? sizeof(native_type)/sizeof(value_type)
                                        : 1
                          );

    ////////////////////////////////////////////////////////////////////////////
    // union based type for value extraction
    ////////////////////////////////////////////////////////////////////////////
    union extraction_type { native_type v; value_type s[static_size]; };

    ////////////////////////////////////////////////////////////////////////////
    // SIDM register value
    ////////////////////////////////////////////////////////////////////////////
    native_type data_;

    ////////////////////////////////////////////////////////////////////////////
    // Assignment operator from compatible types
    ////////////////////////////////////////////////////////////////////////////
    template<class S2>
    self_type& operator=(native<S2, extension_type> const& s)
    {
      data_ = native_type(s.data_);
      return *this;
    }

    self_type& operator=(native_type const& s) { data_ = s; return *this;}

    template<class V2>
    typename boost::enable_if_c< meta::is_simd_specific<V2,extension_type>::value
                               , self_type&
                               >::type
    operator=(V2 const& s) { data_ = native_type(s); return *this;}

    ////////////////////////////////////////////////////////////////////////////
    // Const-array like interface
    ////////////////////////////////////////////////////////////////////////////
    static std::size_t size() { return static_size; }

    const_reference  operator[](int i) const
    {
      // we need to return in memory as reinterpret_cast triggers UB
      extraction_type const that = {data_};
      return that.s[i];
    }

    ////////////////////////////////////////////////////////////////////////////
    // Type casting operator for compatibility with intrinsic functions
    ////////////////////////////////////////////////////////////////////////////
    operator native_type() const { return data_; }

    ////////////////////////////////////////////////////////////////////////////
    // new/delete operator to force alignment on heap of native values
    ////////////////////////////////////////////////////////////////////////////
    //NT2_ALIGN_OVERLOAD_NEW_DELETE(NT2_SIMD_BYTES)

    ////////////////////////////////////////////////////////////////////////////
    // self-operator methods
    ////////////////////////////////////////////////////////////////////////////
/*
    NT2_FUNCTION_METHOD_SELF(operator+= ,functors::plus_assign_       , self_type )
    NT2_FUNCTION_METHOD_SELF(operator-= ,functors::minus_assign_      , self_type )
    NT2_FUNCTION_METHOD_SELF(operator*= ,functors::multiplies_assign_ , self_type )
    NT2_FUNCTION_METHOD_SELF(operator/= ,functors::divides_assign_    , self_type )
    NT2_FUNCTION_METHOD_SELF(operator%= ,functors::modulo_assign_     , self_type )
    NT2_FUNCTION_METHOD_SELF(operator&= ,functors::bitwise_and_assign_, self_type )
    NT2_FUNCTION_METHOD_SELF(operator|= ,functors::bitwise_or_assign_ , self_type )
    NT2_FUNCTION_METHOD_SELF(operator^= ,functors::bitwise_xor_assign_, self_type )
    NT2_FUNCTION_METHOD_SELF(operator<<=,functors::shift_left_assign_ , self_type )
    NT2_FUNCTION_METHOD_SELF(operator>>=,functors::shift_right_assign_, self_type )
*/
    self_type const& operator+() const { return *this; }

    ////////////////////////////////////////////////////////////////////////////
    // Pre/Post Increment thingy
    ////////////////////////////////////////////////////////////////////////////
    self_type& operator++() { *this += One<self_type>();  return *this; }
    self_type& operator--() { *this -= One<self_type>();  return *this; }

    self_type  operator++ (int)
    {
      self_type that = *this;
      self_type::operator++();
      return that;
    }

    self_type  operator-- (int)
    {
      self_type that = *this;
      self_type::operator--();
      return that;
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Related components
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/simd/details/native/meta.hpp>
#include <nt2/sdk/simd/details/native/fusion.hpp>
#include <nt2/sdk/simd/details/native/constants.hpp>

/*
#include <nt2/sdk/simd/native/details/operators.hpp>
#include <nt2/sdk/simd/native/details/functions.hpp>
*/


#endif

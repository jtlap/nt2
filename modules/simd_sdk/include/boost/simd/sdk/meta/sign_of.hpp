/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_META_SIGN_OF_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_SIGN_OF_HPP_INCLUDED

//////////////////////////////////////////////////////////////////////////////
// Returns 'signed' if the primitive of the input type is of hierarchy
// signed and 'unsigned' otherwise.
// See: http://nt2.metascale.org/sdk/meta/traits/sign_of.html
//////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/meta/strip.hpp>
#include <boost/simd/sdk/meta/is_signed.hpp>
#include <boost/simd/sdk/meta/hierarchy_of.hpp>
#include <boost/simd/sdk/meta/primitive_of.hpp>
#include <boost/simd/sdk/meta/is_fundamental.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace boost { namespace simd {  namespace meta
{
  template<class T> struct sign_of;
} } }

namespace boost { namespace simd {  namespace details
{
  template<class T, class Enable = void> struct  sign_of
  {
    typedef unsigned type;
  };

  template<class T>
  struct  sign_of < T
                  , typename boost::enable_if< meta::is_signed<T> >::type
                  >
  {
    typedef signed type;
  };
} } }

namespace boost { namespace simd {  namespace meta
{
  template<class T>
  struct  sign_of : details::sign_of < typename meta::strip<T>::type >
  {
    BOOST_SIMD_STATIC_ASSERT
    ( (is_fundamental < typename meta::
                        primitive_of< typename meta::strip<T>::type >::type
                      >::value)
    , BOOST_SIMD_NON_FUNDAMENTAL_PRIMITIVE_USED_IN_META_SIGN_OF
    , "A type with a non-fundamental primitive is used in boost::simd::meta::sign_of."
    );
  };
} } }
#endif

//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_META_ADAPT_TYPE_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_ADAPT_TYPE_HPP_INCLUDED

#include <boost/dispatch/meta/as.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>

namespace boost { namespace simd { namespace meta
{
  /*!
    @brief Type homeomorphic transformation

    Translate a given type into another by keeping similar semantic.

    @par Model:

    @metafunction

    @par Semantic:

    For any type @c T and @c U, the following code:

    @code
    typedef adapt_type<T,U>::type r
    @endcode

    evaluates to a type which verifies:

    @code
    is_same< primitive_of<r>::type, primitive_of<T>::type>::value == true
    @endcode

    and, if @c U is not a SIMD register type:

    @code
    is_same< model_of<r>::type, model_of<U>::type>::value == true
    @endcode

    and

    @code
    cardinal_of<r>::type == cardinal_of<U>::type
    @endcode

    otherwise.

    @tparam New   Type to translate
    @tparam Base  Type to use a semantic reference
  **/
  template<typename New, typename Base>
  struct adapt_type
  {
    typedef New type;
  };

  /// INTERNAL ONLY
  template<typename New, typename Base>
  struct adapt_type<New, dispatch::meta::as_<Base> >
  {
    typedef dispatch::meta::as_< typename adapt_type<New,Base>::type > type;
  };

  /// INTERNAL ONLY
  template<typename New, typename Type, typename Extension>
  struct adapt_type<New, native<Type,Extension> >
  {
    typedef native<Type,Extension>                                    base_t;
    typedef typename meta::vector_of<New, base_t::static_size>::type  type;
  };

  /// INTERNAL ONLY
  template<typename New, typename Type, typename Extension>
  struct adapt_type<New, native<logical<Type>,Extension> >
  {
    typedef native<Type,Extension>                                            base_t;
    typedef typename meta::vector_of<logical<New>,base_t::static_size>::type  type;
  };
} } }

#endif

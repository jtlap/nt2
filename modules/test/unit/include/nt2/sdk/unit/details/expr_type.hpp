//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_DETAILS_EXPR_TYPE_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_EXPR_TYPE_HPP_INCLUDED

#include <nt2/sdk/meta/type_id.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>

namespace nt2 { namespace details
{
  /// INTERNAL ONLY
  /// Wrap a lambda function call into a identity block for display purpose
  template<class Lambda, class T>
  boost::mpl::identity<typename boost::mpl::apply<Lambda, T>::type>
  expr_type(T const&)
  {
    return boost::mpl::identity<typename boost::mpl::apply<Lambda, T>::type>();
  }

  /// INTERNAL ONLY
  /// Return a boolean indicating if a given type T is the same as a given
  /// meta-function class application
  template<class T, class U>
  typename boost::is_same<T, typename U::type>::type is_same_as(U const&)
  {
    return typename boost::is_same<T, typename U::type>::type();
  }

  /// INTERNAL ONLY
  /// Display a type from an identity block
  template<class T> std::string type_id_identity(T const&)
  {
    return nt2::type_id<typename T::type>();
  }
} }

#endif

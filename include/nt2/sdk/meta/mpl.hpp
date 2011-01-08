/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_MPL_HPP_INCLUDED
#define NT2_SDK_META_MPL_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Various memory hierarchy stuff
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/bool.hpp>
#include <boost/mpl/integral_c_tag.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/meta/enable_if_type.hpp>

////////////////////////////////////////////////////////////////////////////////
// Some MPL introspection helpers
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace details
{
  template<class T, class Enable = void>
  struct  has_mpl_tag
        : boost::mpl::false_ {};

  template<class T>
  struct  has_mpl_tag < T
                      , typename meta
                        ::enable_if_type< typename T::tag >::type
                      >
        : boost::mpl::true_ {};

  template<class T, bool EnableIf = has_mpl_tag<T>::value>
  struct  is_mpl_integral : boost::mpl::false_
  {};

  template<class T>
  struct  is_mpl_integral<T,true>
        : boost::is_same<typename T::tag,boost::mpl::integral_c_tag>
  {};
} }

////////////////////////////////////////////////////////////////////////////////
// Specialize hierarchy for mpl integral types
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_HIERARCHY(mpl_integral_)

namespace nt2 { namespace details
{
  template<class T>
  struct  hierarchy_of<T
                      , typename boost
                        ::enable_if_c<details::is_mpl_integral<T>::value>::type
                      >
  {
    typedef typename T::value_type                                    value_type;
    typedef meta::mpl_integral_<typename
                                meta::hierarchy_of<value_type>::type> type;
  };
} }

#endif

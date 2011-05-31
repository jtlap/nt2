//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_DETAILS_AS_UNSIGNED_HPP_INCLUDED
#define NT2_SDK_META_DETAILS_AS_UNSIGNED_HPP_INCLUDED

#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <nt2/sdk/meta/factory_of.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>
#include <nt2/sdk/meta/primitive_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/meta/is_fundamental.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/make_unsigned.hpp>

namespace nt2 { namespace meta { template<class T> struct as_unsigned; } }

namespace nt2 { namespace details
{
  template<class T, class Enable = void>
  struct  as_unsigned_impl
        : boost::mpl::apply < typename meta::factory_of<T>::type
                            , typename meta::
                              as_unsigned < typename meta::primitive_of<T>::type
                                          >::type
                            >
  {};

  template<class T>
  struct  as_unsigned_impl< T
                          , typename boost::enable_if < typename meta::
                                                        is_fundamental<T>::type
                                                      >::type
                          >
        : boost::mpl::eval_if < boost::mpl::
                                bool_ <   boost::is_integral<T>::value
                                      &&  !boost::is_same<bool,T>::value
                                      >
                              , boost::make_unsigned<T>
                              , boost::mpl::identity<T>
                              > {};
} }

#endif

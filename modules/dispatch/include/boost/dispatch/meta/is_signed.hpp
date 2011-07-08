/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_DISPATCH_META_IS_SIGNED_HPP_INCLUDED
#define BOOST_DISPATCH_META_IS_SIGNED_HPP_INCLUDED

//////////////////////////////////////////////////////////////////////////////
// Return false or true depending on whether the primitive of T is signed or not
// See: http://nt2.metascale.org/sdk/meta/traits/is_signed.html
//////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/not.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace boost { namespace dispatch { namespace meta
{
  template<class T>
  struct  is_signed
        : boost::
          is_base_of< meta::
                      scalar_ < meta::
                                signed_<typename meta::primitive_of<T>::type>
                              >
                            , typename meta::
                              hierarchy_of<typename meta::primitive_of<T>::type>::type
                            >
  {};

  template<class T> struct is_unsigned : boost::mpl::not_< is_signed<T> >
  {};
} } }

#endif

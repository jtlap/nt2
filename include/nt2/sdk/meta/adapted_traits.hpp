 /*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_ADAPTED_TRAITS_HPP_INCLUDED
#define NT2_SDK_META_ADAPTED_TRAITS_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/behave_as.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_floating_point.hpp>

namespace nt2 { namespace meta
{
  template<class T>
  struct  is_floating_point
        : behave_as	< boost::is_floating_point<boost::mpl::_>
										, typename strip<T>::type
										> {};

  template<class T>
  struct  is_integral
        : behave_as< boost::is_integral<boost::mpl::_>
										, typename strip<T>::type
										> {};
} }

#endif

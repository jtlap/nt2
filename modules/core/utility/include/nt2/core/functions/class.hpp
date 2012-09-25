//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_CLASS_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_CLASS_HPP_INCLUDED

#include <nt2/sdk/meta/as.hpp>
#include <nt2/sdk/meta/container_traits.hpp>
#include <boost/dispatch/details/ignore_unused.hpp>

namespace nt2
{
  /*!
    @brief Retrieve the numerical class of an object

    For any given object, class returns a meta-descriptor that contains
    informations about the numerical type of values stored inside.

    @par Semantic

    For any given @c t of type @c T:

    @code
    auto x = class_(t);
    @endcode

    is equivalent to

    @code
    nt2::meta::as_<meta::value_type_<T>::type> x;
    @endcode

    @param t Object to extract the numeric class from

    @return A meta-object describing the valeu type of t
   **/
  template<class T> BOOST_FORCEINLINE
  meta::as_<typename meta::value_type_<T>::type>
  class_( T const& t )
  {
    boost::dispatch::ignore_unused(t);
    meta::as_< typename meta::value_type_<T>::type > that;
    return that;
  }
}

#endif

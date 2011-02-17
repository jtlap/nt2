 /*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_MAKE_INTEGER_HPP_INCLUDED
#define NT2_SDK_META_MAKE_INTEGER_HPP_INCLUDED

//////////////////////////////////////////////////////////////////////////////
// Build a standard integer type from a sign and a size in bytes
// As all make_xxx, also provides an optional lambda to apply to the result.
// See: http://nt2.metascale.org/sdk/meta/traits/make_integer.html
//////////////////////////////////////////////////////////////////////////////
#include <boost/integer.hpp>
#include <boost/cstdint.hpp>
#include <boost/mpl/apply.hpp>
#include <nt2/sdk/meta/na.hpp>

namespace nt2 { namespace meta
{
  template< std::size_t Size
          , class Sign      = unsigned
          , class Transform = na_
          >
  struct  make_integer;

  template< std::size_t Size, class Transform>
  struct  make_integer<Size,unsigned,Transform>
        : boost::mpl::apply<Transform,typename boost::uint_t<CHAR_BIT*Size>::fast> {};

  template< std::size_t Size, class Transform >
  struct  make_integer<Size,signed,Transform>
        : boost::mpl::apply<Transform,typename boost::int_t<CHAR_BIT*Size>::fast> {};

  //////////////////////////////////////////////////////////////////////////////
  // Overload for long long to fix lack of boost::integer support
  //////////////////////////////////////////////////////////////////////////////
  template< class Transform >
  struct  make_integer<sizeof(boost::int64_t),unsigned,Transform>
        : boost::mpl::apply<Transform,boost::uint64_t> {};

  template< class Transform >
  struct  make_integer<sizeof(boost::int64_t),signed,Transform>
        : boost::mpl::apply<Transform,boost::int64_t> {};

  //////////////////////////////////////////////////////////////////////////////
  // Overload to prevent useless apply<_,T> template instanciation
  //////////////////////////////////////////////////////////////////////////////
  template< std::size_t Size> struct make_integer<Size,unsigned,na_>
  {
    typedef typename boost::uint_t<CHAR_BIT*Size>::fast type;
  };

  template< std::size_t Size> struct make_integer<Size,signed,na_>
  {
    typedef typename boost::int_t<CHAR_BIT*Size>::fast type;
  };

  template<> struct make_integer<sizeof(boost::int64_t),unsigned,na_>
  {
    typedef boost::uint64_t type;
  };

  template<> struct make_integer<sizeof(boost::int64_t),signed,na_>
  {
    typedef boost::int64_t type;
  };
} }

#endif

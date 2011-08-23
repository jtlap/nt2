//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_DETAILS_BITWISE_CAST_HPP_INCLUDED
#define BOOST_SIMD_SDK_DETAILS_BITWISE_CAST_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the \ref boost::simd::bitwise_cast utility function
 */

#include <boost/dispatch/error/static_assert.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/mpl/identity.hpp>
#include <cstring>

#ifdef BOOST_MSVC
#define BOOST_SIMD_NO_STRICT_ALIASING
#endif

namespace boost { namespace simd
{

#ifndef BOOST_SIMD_NO_STRICT_ALIASING
namespace details
{
  //============================================================================
  // Perform a bitwise cast via memcpy - This is the safe bet
  //============================================================================
  struct memcpy_cast
  {
    template<typename To, typename From>
    static BOOST_DISPATCH_FORCE_INLINE To call(From const& from)
    {
      To to;
      std::memcpy(&to, &from, sizeof(From));
      return to;
    }
  };

  //============================================================================
  // Perform a bitwise cast using an union - Used in some lower level context
  //============================================================================
  struct union_cast
  {
    template<typename To, typename From>
    static BOOST_DISPATCH_FORCE_INLINE To call(From const& from)
    {
      union
      {
          From from;
          To to;
      } u = { from };
      return u.to;
    }
  };

  //============================================================================
  // Perform a bitwise cast using a C-style cast
  //============================================================================
  struct convert_cast
  {
    template<typename To, typename From>
    static BOOST_DISPATCH_FORCE_INLINE To call(From const& from)
    {
      return (To)from;
    }
  };

  //============================================================================
  // By default, use memcpy_cast
  //============================================================================
  template<typename To, typename From, typename Enable = void>
  struct bitwise_cast : memcpy_cast {};
  
}

  //============================================================================
  /*!
   * \ingroup sdk
   * bitwise_cast performs a bitwise conversion of a value of type \c From to a
   * value of type \c To by using the appropriate strategy depending on the
   * relation between \c To and \c From.
   *
   * \tparam To Type to convert to
   *
   * \param from Value to convert
   *
   * \return A value of type \c To which bits pattern is identical to \c from.
   *
   * \par Example Usage:
   *
   * \include bitwise_cast.cpp
   *
   * The expected out put is :
   *
   * \c bf800000
   */
  //============================================================================
  template<typename To, typename From>
  BOOST_DISPATCH_FORCE_INLINE To bitwise_cast(From const& from)
  {
    BOOST_DISPATCH_STATIC_ASSERT( sizeof(From) == sizeof(To)
                     , BOOST_SIMD_TARGET_IS_NOT_SAME_SIZE_AS_SOURCE_IN_BITWISE_CAST
                     , "Target is not same size as source in boost::simd::bitwise_cast"
                     );
    return details::bitwise_cast<To, From>::template call<To>(from);
  }

#else

  template<typename To, typename From>
  BOOST_DISPATCH_FORCE_INLINE To const& bitwise_cast(From const& from)
  {
    BOOST_DISPATCH_STATIC_ASSERT( sizeof(From) == sizeof(To)
                     , BOOST_SIMD_TARGET_IS_NOT_SAME_SIZE_AS_SOURCE_IN_BITWISE_CAST
                     , "Target is not same size as source in boost::simd::bitwise_cast"
                     );
    return reinterpret_cast<To const&>(from);
  }

#endif

  template<typename To>
  BOOST_DISPATCH_FORCE_INLINE To const& bitwise_cast(typename mpl::identity<To>::type const& from)
  {
	return from;
  }

} }
#endif

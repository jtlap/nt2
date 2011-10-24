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

#include <boost/simd/sdk/details/aliasing.hpp>
#include <boost/dispatch/attributes.hpp>
#include <cstring>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace simd
{

namespace details
{
  //============================================================================
  // Perform a bitwise cast via memcpy - This is the safe bet
  //============================================================================
  struct memcpy_cast
  {
    template<class To>
    struct result_of
    {
      typedef To type;
    };
      
    template<typename To, typename From>
    static BOOST_DISPATCH_FORCE_INLINE
    typename result_of<To>::type call(From const& from)
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
    template<class To>
    struct result_of
    {
      typedef To type;
    };
      
    template<typename To, typename From>
    static BOOST_DISPATCH_FORCE_INLINE
    typename result_of<To>::type call(From const& from)
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
  // Perform a bitwise cast using a conversion - Works with few types
  //============================================================================
  struct convert_cast
  {
    template<class To>
    struct result_of
    {
      typedef To type;
    };
      
    template<typename To, typename From>
    static BOOST_DISPATCH_FORCE_INLINE
    typename result_of<To>::type call(From const& from)
    {
      return (To)from;
    }
  };
  
  //============================================================================
  // Perform a bitwise cast using a reinterpret_cast
  //============================================================================
  struct alias_cast
  {
    template<class To>
    struct result_of
    {
      typedef To const& type;
    };
      
    template<typename To, typename From>
    static BOOST_DISPATCH_FORCE_INLINE
    typename result_of<To>::type call(From const& from)
    {
      return reinterpret_cast<To const&>(from);
    }
  };

  //============================================================================
  // By default, use memcpy_cast except for identity
  //============================================================================
  template<typename To, typename From, typename Enable = void>
  struct bitwise_cast : memcpy_cast {};
  
  template<typename T>
  struct bitwise_cast<T, T> : alias_cast {};
  
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
  BOOST_DISPATCH_FORCE_INLINE
#ifndef BOOST_SIMD_NO_STRICT_ALIASING
  typename details::bitwise_cast<To, From>::template result_of<To>::type
#else
  typename details::alias_cast::template result_of<To>::type
#endif
  bitwise_cast(From const& from)
  {
    //==========================================================================
    /*
     * Target is not same size as source in boost::simd::bitwise_cast
     */    
    //==========================================================================
    BOOST_MPL_ASSERT_MSG
    ( (sizeof(From) == sizeof(To))
    , BOOST_SIMD_TARGET_IS_NOT_SAME_SIZE_AS_SOURCE_IN_BITWISE_CAST
    , (From&,To&)
    );  

#ifndef BOOST_SIMD_NO_STRICT_ALIASING    
    return details::bitwise_cast<To, From>::template call<To>(from);
#else
    return details::alias_cast::template call<To>(from);
#endif
  }

} }
#endif

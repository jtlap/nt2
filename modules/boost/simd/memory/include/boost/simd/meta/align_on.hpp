//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_META_ALIGN_ON_HPP_INCLUDED
#define BOOST_SIMD_META_ALIGN_ON_HPP_INCLUDED

/*!
  @file
  @brief Define and implements align_on and align_on_c
**/

#include <boost/simd/meta/is_power_of_2.hpp>
#include <boost/simd/sdk/simd/extensions.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/assert.hpp>
#include <cstddef>

namespace boost { namespace simd {  namespace meta
{
  /*!
    @brief Align compile-time constant on arbitrary boundary

    align_on_c is the static version of align_on. If computes aligned value of an Integral on
    arbitrary alignment boundary.

    @par Semantic

    For any Constant @c Value and any power of 2 @c Align :

    @code
    typedef align_on_c<Value,Align>::type r;
    @endcode

    is equivalent to

    @code
    typedef integral_constant<std::size_t, (Value+Align-1) & ~(Align-1)>::type r;
    @endcode

    @pre @c Align is a power of 2

    @tparam Value Value to align.
    @tparam Align Integral alignment boundary. By default, @c Align is equal to current SIMD
            extension preferred alignment boundary.
  **/
  template<std::size_t Value, std::size_t Align = BOOST_SIMD_CONFIG_ALIGNMENT>
  struct align_on_c
       : boost::mpl::integral_c<std::size_t, (Value+Align-1) & ~(Align-1) >
  {
    #if !defined(DOXYGEN_ONLY)
    //========================================================================
    //               ****BOOST_SIMD_INVALID_ALIGNMENT_VALUE****
    //       If you trigger this assert, you tried to align a value on
    //   a boundary which is not a power of two. Fix your code accordingly.
    //               ****BOOST_SIMD_INVALID_ALIGNMENT_VALUE****
    //========================================================================
    BOOST_MPL_ASSERT_MSG( (meta::is_power_of_2_c<Align>::value)
                        , BOOST_SIMD_INVALID_ALIGNMENT_VALUE
                        , (boost::mpl::int_<Align>)
                        );
    #endif
  };

  /*!
    @brief Align Integral Constant on arbitrary boundary

    For any Integral Constant @c V and any power of 2 @c Align,
    computes Integral Constant @c N so that:

    @code
    N::value >= V::value && N::value % Align = 0
    @endcode

    @pre @c Align is a power of 2

    @tparam Value Value to align
    @tparam Align Integral alignment boundary.
  **/
  template<typename Value, typename Align = boost::mpl::size_t<BOOST_SIMD_CONFIG_ALIGNMENT> >
  struct align_on
       :  boost::mpl::
          integral_c< typename Value::value_type
                    , typename Value::value_type(align_on_c < std::size_t(Value::value)
                                                            , std::size_t(Align::value)
                                                            >::value
                                                )
                    >
  {};
} } }

#endif

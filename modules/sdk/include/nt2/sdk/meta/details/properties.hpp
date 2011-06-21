//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_DETAILS_PROPERTIES_HPP_INCLUDED
#define NT2_SDK_META_DETAILS_PROPERTIES_HPP_INCLUDED

/*!
 * \file
 */

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/meta/details/hierarchy_base.hpp>

namespace nt2 { namespace meta
{
  //============================================================================
  /*!
   * The fundamental_ hierarchy gather all usual C++ base types.
   */
  //============================================================================
  template<class T> struct fundamental_ : unspecified_<T>
  {
    typedef unspecified_<T> parent;
  };

  //============================================================================
  /*!
   * The bool_ hierarchy represents the \c bool C++ type.
   */
  //============================================================================
  template<class T> struct bool_ : fundamental_<T>
  {
    typedef fundamental_<T> parent;
  };

  //============================================================================
  /*!
   * The void_ hierarchy represents the \c void C++ type.
   */
  //============================================================================
  template<class T> struct void_ : fundamental_<T>
  {
    typedef fundamental_<T> parent;
  };

  //============================================================================
  /*!
   * The arithmetic_ hierarchy gather all usual C++ base types except \c bool.
   */
  //============================================================================
  template<class T> struct arithmetic_ : fundamental_<T>
  {
    typedef fundamental_<T>  parent;
  };

  //============================================================================
  /*!
   * The integer_ hierarchy gather all usual C++ integral types except \c bool.
   */
  //============================================================================
  template<class T> struct integer_ : arithmetic_<T>
  {
    typedef arithmetic_<T>  parent;
  };

  //============================================================================
  /*!
   * The unsigned_ hierarchy gather all native unsigned types of C++
   */
  //============================================================================
  template<class T> struct unsigned_ : integer_<T>
  {
    typedef integer_<T> parent;
  };

  //============================================================================
  /*!
   * The signed_ hierarchy gather all native signed types of C++ including
   * floating-points type.
   */
  //============================================================================
  template<class T>
  struct  signed_ : boost::mpl::if_ < meta::is_integral<T>
                                  , integer_<T>
                                  , arithmetic_<T>
                                  >::type
  {
    typedef typename boost::mpl::if_< meta::is_integral<T>
                                    , integer_<T>
                                    , arithmetic_<T>
                                    >::type                 parent;
  };

  //============================================================================
  /*!
   * The real_ hierarchy gathers all C++ floating-point types
   */
  //============================================================================
  template<class T> struct real_ : signed_<T>
  {
    typedef signed_<T>  parent;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Sign based hierarchy - gather integral types of a given signedness
  //////////////////////////////////////////////////////////////////////////////
  NT2_HIERARCHY_CLASS_TPL(int_        , signed_<T>    );
  NT2_HIERARCHY_CLASS_TPL(uint_       , unsigned_<T>  );

  //////////////////////////////////////////////////////////////////////////////
  // Sizeof based hierarchy - gather type which sizeof is equal to a given value
  //////////////////////////////////////////////////////////////////////////////
  NT2_HIERARCHY_CLASS_TPL_META (type8_, (boost::mpl::if_< behave_as<boost::is_signed<boost::mpl::_1>,T>
                                                        , int_<T>
                                                        , uint_<T>
                                                        >
                                    )
                          );

  NT2_HIERARCHY_CLASS_TPL_META (type16_, (boost::mpl::if_< behave_as<boost::is_signed<boost::mpl::_1>,T>
                                                         , int_<T>
                                                         , uint_<T>
                                                         >
                                    )
                          );

  NT2_HIERARCHY_CLASS_TPL_META (type32_
                          , (boost::mpl::if_<meta::is_floating_point<T>
                                            , real_<T>
                                            , typename
                                              boost::mpl::if_
                                              < behave_as<boost::is_signed<boost::mpl::_1>,T>
                                                              , int_<T>
                                                              , uint_<T>
                                                              >::type
                                            >
                                    )
                          );

  NT2_HIERARCHY_CLASS_TPL_META (type64_
                          , (boost::mpl::if_< meta::is_floating_point<T>
                                            , real_<T>
                                            , typename
                                              boost::mpl::if_ < behave_as<boost::is_signed<boost::mpl::_1>,T>
                                                              , int_<T>
                                                              , uint_<T>
                                                              >::type
                                            >
                                    )
                          );

  //////////////////////////////////////////////////////////////////////////////
  // Sizeof based hierarchy of integers
  //////////////////////////////////////////////////////////////////////////////
  NT2_HIERARCHY_CLASS_TPL(ints8_        , type8_<T>       );
  NT2_HIERARCHY_CLASS_TPL(ints16_       , type16_<T>      );
  NT2_HIERARCHY_CLASS_TPL(ints32_       , type32_<T>      );
  NT2_HIERARCHY_CLASS_TPL(ints64_       , type64_<T>      );

  //////////////////////////////////////////////////////////////////////////////
  // Sizeof based hierarchy of signed integers
  //////////////////////////////////////////////////////////////////////////////
  NT2_HIERARCHY_CLASS_TPL(int8_         , ints8_<T>       );
  NT2_HIERARCHY_CLASS_TPL(int16_        , ints16_<T>      );
  NT2_HIERARCHY_CLASS_TPL(int32_        , ints32_<T>      );
  NT2_HIERARCHY_CLASS_TPL(int64_        , ints64_<T>      );

  //////////////////////////////////////////////////////////////////////////////
  // Sizeof based hierarchy of unsigned integers
  //////////////////////////////////////////////////////////////////////////////
  NT2_HIERARCHY_CLASS_TPL(uint8_        , ints8_<T>       );
  NT2_HIERARCHY_CLASS_TPL(uint16_       , ints16_<T>      );
  NT2_HIERARCHY_CLASS_TPL(uint32_       , ints32_<T>      );
  NT2_HIERARCHY_CLASS_TPL(uint64_       , ints64_<T>      );

  //////////////////////////////////////////////////////////////////////////////
  // Native real types hierarchy
  //////////////////////////////////////////////////////////////////////////////
  NT2_HIERARCHY_CLASS_TPL(double_       , type64_<T>      );
  NT2_HIERARCHY_CLASS_TPL(float_        , type32_<T>      );
  NT2_HIERARCHY_CLASS_TPL(long_double_  , fundamental_<T> );

} }

#endif

//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_SIZE_HPP_INCLUDED
#define NT2_CORE_SETTINGS_SIZE_HPP_INCLUDED

#include <cstddef>
#include <boost/array.hpp>
#include <boost/mpl/vector_c.hpp>
#include <nt2/sdk/parameters.hpp>
#include <nt2/core/settings/option.hpp>
#include <nt2/sdk/details/preprocessor.hpp>

namespace nt2 
{ 
  //============================================================================
  /*! of_size_<D0,..,Dn> is a size value containing up to n dimensions
   **/
  //============================================================================
  //template<nt2::uint32_t ID> struct id_ {}; 
  
  namespace tag 
  { 
    //==========================================================================
    /*!
     * Option tag for size_ options
     **/
    //==========================================================================
    struct size_ {}; 
  }

  namespace meta
  {
    //==========================================================================
    // Make options extracting the ID from id_
    //==========================================================================
//    template<nt2::uint32_t ID, class Default>
//    struct option<id_<ID>, options::size_, Default, void>
//    {
//      typedef boost::mpl::string<ID> type;
//    };
  } 
}

//////////////////////////////////////////////////////////////////////////////////
//// Helper macro
//////////////////////////////////////////////////////////////////////////////////
//#define M0(z,n,t)                                           \
//template< BOOST_PP_ENUM_PARAMS(n, std::ptrdiff_t D) >       \
//struct  of_size_<BOOST_PP_ENUM_PARAMS(n,D)>                 \
//      : BOOST_PP_CAT(BOOST_PP_CAT(boost::mpl::vector,n),_c) \
//        <std::ptrdiff_t, BOOST_PP_ENUM_PARAMS(n,D)>         \
//{                                                           \
//  static const std::size_t dimensions = n;                  \
//};                                                          \
///**/
//
//////////////////////////////////////////////////////////////////////////////////
//// 
//// 
//////////////////////////////////////////////////////////////////////////////////
//namespace nt2
//{
//  template< BOOST_PP_ENUM_BINARY_PARAMS ( NT2_MAX_DIMENSIONS
//                                        , std::ptrdiff_t D
//                                        , = -2 BOOST_PP_INTERCEPT
//                                        )
//          >
//  struct  of_size_
//        : BOOST_PP_CAT(BOOST_PP_CAT(boost::mpl::vector,NT2_MAX_DIMENSIONS),_c)
//          <std::ptrdiff_t, BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS,D)>
//  {
//    static const std::size_t dimensions = NT2_MAX_DIMENSIONS;
//  };
//
//  //////////////////////////////////////////////////////////////////////////////
//  // Total specialization for 0D elements
//  //////////////////////////////////////////////////////////////////////////////
//  template<>
//  struct  of_size_<NT2_PP_ENUM_VALUE(NT2_MAX_DIMENSIONS,-2)>
//        : boost::mpl::vector0_c<std::ptrdiff_t>
//  {
//    static const std::size_t dimensions = 0;
//  };
//
//  //////////////////////////////////////////////////////////////////////////////
//  // Other dimensions of_size_
//  //////////////////////////////////////////////////////////////////////////////
//  BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_DIMENSIONS,M0,~)
//}
//
//////////////////////////////////////////////////////////////////////////////////
//// Register of_size has a valid options::id_ type
//////////////////////////////////////////////////////////////////////////////////
//namespace nt2 { namespace meta
//{
//  template< BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D)
//          , class Default
//          >
//  struct option < of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS,D)>
//                , options::size_
//                , Default
//                , void
//                >
//  {
//    typedef of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS,D)> type;
//  };
//} }
//
//////////////////////////////////////////////////////////////////////////////////
//// Defines some usual short-cut for runtime of_size_
//////////////////////////////////////////////////////////////////////////////////
//#define M1(z,n,t)                                                             \
//typedef of_size_<NT2_PP_ENUM_VALUE(n,-1)> BOOST_PP_CAT(BOOST_PP_CAT(_,n),D);  \
///**/
//
//namespace nt2
//{
//  BOOST_PP_REPEAT_FROM_TO(0,BOOST_PP_INC(NT2_MAX_DIMENSIONS),M1,~)
//}
//
//////////////////////////////////////////////////////////////////////////////////
//// Macro clean-up
//////////////////////////////////////////////////////////////////////////////////
//#undef M0
//#undef M1

#endif

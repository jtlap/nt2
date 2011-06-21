//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_DETAILS_HIERARCHY_OF_HPP_INCLUDED
#define NT2_SDK_META_DETAILS_HIERARCHY_OF_HPP_INCLUDED

#include <boost/utility/enable_if.hpp>
#include <nt2/sdk/meta/enable_if_type.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_fundamental.hpp>
#include <boost/type_traits/is_floating_point.hpp>

namespace nt2 { namespace meta
{
  template<class T> struct scalar_;
} }
namespace nt2 { namespace details
{
  //============================================================================
  // implementation details for property_of on integers
  //============================================================================
  template<class T,class Origin,std::size_t Size, bool Signed>
  struct property_of_ints;

  template<class T,class Origin = T, class Enable = void> struct  property_of;

  template<class T,class Origin>
  struct  property_of< T
                      , Origin
                      , typename boost::
                        enable_if_c < boost::is_integral<T>::value>::type
                      >
          : details::property_of_ints < T
                                      , Origin
                                      , sizeof(T)*CHAR_BIT
                                      , boost::
                                        is_signed<T>::value
                                      >
  {};

  //============================================================================
  // Overload for non integral native types
  //============================================================================
  template<class Origin, class Enable>
  struct property_of<void, Origin, Enable>
  {
    typedef meta::void_<Origin> type;
  };

  template<class Origin, class Enable>
  struct property_of<float, Origin, Enable>
  {
    typedef meta::float_<Origin>  type;
  };

  template<class Origin, class Enable>
  struct property_of<double, Origin, Enable>
  {
    typedef meta::double_<Origin> type;
  };

  //============================================================================
  // Overload for fundamental types
  //============================================================================
  template<class T,class Origin>
  struct  hierarchy_of< T
                      , Origin
                      , typename
                        boost::enable_if< boost::is_fundamental<T> >::type
                      >
  {
    typedef meta::scalar_< typename property_of<T,Origin>::type > type;
  };

  //============================================================================
  // implementation details for property_of - overload for bool
  //============================================================================
  template<class Origin>
  struct property_of_ints<bool,Origin,sizeof(bool)*CHAR_BIT,false>
  {
    typedef meta::bool_<Origin>  type;
  };

  //============================================================================
  // implementation details for property_of - overload for integral sized type
  //============================================================================
  template<class T,class Origin> struct property_of_ints<T,Origin,8,true>
  {
    typedef meta::int8_<Origin> type;
  };

  template<class T,class Origin> struct property_of_ints<T,Origin,16,true>
  {
    typedef meta::int16_<Origin> type;
  };

  template<class T,class Origin> struct property_of_ints<T,Origin,32,true>
  {
    typedef meta::int32_<Origin> type;
  };

  template<class T,class Origin> struct property_of_ints<T,Origin,64,true>
  {
    typedef meta::int64_<Origin> type;
  };

  template<class T,class Origin> struct property_of_ints<T,Origin,8,false>
  {
    typedef meta::uint8_<Origin> type;
  };

  template<class T,class Origin> struct property_of_ints<T,Origin,16,false>
  {
    typedef meta::uint16_<Origin> type;
  };

  template<class T,class Origin> struct property_of_ints<T,Origin,32,false>
  {
    typedef meta::uint32_<Origin> type;
  };

  template<class T,class Origin> struct property_of_ints<T,Origin,64,false>
  {
    typedef meta::uint64_<Origin> type;
  };
} }

#endif

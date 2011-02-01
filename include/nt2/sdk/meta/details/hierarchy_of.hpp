/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_DETAILS_HIERARCHY_OF_HPP_INCLUDED
#define NT2_SDK_META_DETAILS_HIERARCHY_OF_HPP_INCLUDED

#include <boost/utility/enable_if.hpp>
#include <nt2/sdk/meta/enable_if_type.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_floating_point.hpp>

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // implementation details for hierarchy_of on integers
  //////////////////////////////////////////////////////////////////////////////
  template<class T,std::size_t Size, bool Signed> struct hierarchy_of_ints;

  template<class T>
  struct  hierarchy_of< T
                      , typename boost::
                        enable_if_c < boost::is_integral<T>::value>::type
                      >
          : details::hierarchy_of_ints< T
                                      , sizeof(T)*CHAR_BIT
                                      , boost::
                                        is_signed<T>::value
                                      >
  {};

  //////////////////////////////////////////////////////////////////////////////
  // Overload for non integral native types
  //////////////////////////////////////////////////////////////////////////////
  template<class Enable>
  struct hierarchy_of<void, Enable>    { typedef meta::void_<void>     type; };
  template<class Enable>
  struct hierarchy_of<float, Enable>   { typedef meta::float_<float>   type; };
  template<class Enable>
  struct hierarchy_of<double, Enable>  { typedef meta::double_<double> type; };

  //////////////////////////////////////////////////////////////////////////////
  // Overload for types with a nt2_hierarchy_tag
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct  hierarchy_of< T
                      , typename
                        meta::enable_if_type<typename T::nt2_hierarchy_tag>::type
                      >
  {
    typedef typename T::nt2_hierarchy_tag type;
  };

  //////////////////////////////////////////////////////////////////////////////
  // implementation details for hierarchy_of - overload for bool
  //////////////////////////////////////////////////////////////////////////////
  template<>
  struct hierarchy_of_ints<bool,sizeof(bool)*CHAR_BIT,false>
  {
    typedef meta::bool_<bool>    type;
  };


  //////////////////////////////////////////////////////////////////////////////
  // implementation details for hierarchy_of - overload for integral sized type
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct hierarchy_of_ints<T,8,true>   { typedef meta::int8_<T>    type; };
  template<class T>
  struct hierarchy_of_ints<T,8,false>  { typedef meta::uint8_<T>   type; };
  template<class T>
  struct hierarchy_of_ints<T,16,true>  { typedef meta::int16_<T>   type; };
  template<class T>
  struct hierarchy_of_ints<T,16,false> { typedef meta::uint16_<T>  type; };
  template<class T>
  struct hierarchy_of_ints<T,32,true>  { typedef meta::int32_<T>   type; };
  template<class T>
  struct hierarchy_of_ints<T,32,false> { typedef meta::uint32_<T>  type; };
  template<class T>
  struct hierarchy_of_ints<T,64,true>  { typedef meta::int64_<T>   type; };
  template<class T>
  struct hierarchy_of_ints<T,64,false> { typedef meta::uint64_<T>  type; };
} }

#endif

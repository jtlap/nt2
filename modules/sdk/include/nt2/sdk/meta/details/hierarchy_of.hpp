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
#include <boost/type_traits/is_floating_point.hpp>

namespace nt2 { namespace details
{
  //============================================================================
  // implementation details for hierarchy_of on integers
  //============================================================================
  template<class T,class Origin,std::size_t Size, bool Signed>
  struct hierarchy_of_ints;

  template<class T,class Origin>
  struct  hierarchy_of< T
                      , Origin
                      , typename boost::
                        enable_if_c < boost::is_integral<T>::value>::type
                      >
          : details::hierarchy_of_ints< T
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
  struct hierarchy_of<void, Origin, Enable>
  {
    typedef meta::generic_< meta::void_<Origin> > type;
  };

  template<class Origin, class Enable>
  struct hierarchy_of<float, Origin, Enable>
  {
    typedef meta::scalar_< meta::float_<Origin> >  type;
  };

  template<class Origin, class Enable>
  struct hierarchy_of<double, Origin, Enable>
  {
    typedef meta::scalar_< meta::double_<Origin> >  type;
  };

  //============================================================================
  // Overload for types with a nt2_hierarchy_tag
  //============================================================================
  template<class T>
  struct  hierarchy_of< T
                      , typename
                        meta::enable_if_type<typename T::nt2_hierarchy_tag>::type
                      >
  {
    typedef typename T::nt2_hierarchy_tag type;
  };

  //============================================================================
  // implementation details for hierarchy_of - overload for bool
  //============================================================================
  template<class Origin>
  struct hierarchy_of_ints<bool,Origin,sizeof(bool)*CHAR_BIT,false>
  {
    typedef meta::scalar_< meta::bool_<Origin> >  type;
  };

  //============================================================================
  // implementation details for hierarchy_of - overload for integral sized type
  //============================================================================
  template<class T,class Origin> struct hierarchy_of_ints<T,Origin,8,true>
  {
    typedef meta::scalar_< meta::int8_<Origin> >  type;
  };

  template<class T,class Origin> struct hierarchy_of_ints<T,Origin,16,true>
  {
    typedef meta::scalar_< meta::int16_<Origin> >  type;
  };

  template<class T,class Origin> struct hierarchy_of_ints<T,Origin,32,true>
  {
    typedef meta::scalar_< meta::int32_<Origin> >  type;
  };

  template<class T,class Origin> struct hierarchy_of_ints<T,Origin,64,true>
  {
    typedef meta::scalar_< meta::int64_<Origin> >  type;
  };

  template<class T,class Origin> struct hierarchy_of_ints<T,Origin,8,false>
  {
    typedef meta::scalar_< meta::uint8_<Origin> >  type;
  };

  template<class T,class Origin> struct hierarchy_of_ints<T,Origin,16,false>
  {
    typedef meta::scalar_< meta::uint16_<Origin> >  type;
  };

  template<class T,class Origin> struct hierarchy_of_ints<T,Origin,32,false>
  {
    typedef meta::scalar_< meta::uint32_<Origin> >  type;
  };

  template<class T,class Origin> struct hierarchy_of_ints<T,Origin,64,false>
  {
    typedef meta::scalar_< meta::uint64_<Origin> >  type;
  };
} }

#endif

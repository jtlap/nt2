/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_FUSION_HPP_INCLUDED
#define NT2_SDK_META_FUSION_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Various Fusion hierarchy stuff
////////////////////////////////////////////////////////////////////////////////
#include <boost/array.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>
#include <boost/fusion/include/is_sequence.hpp>

////////////////////////////////////////////////////////////////////////////////
// Specialize hierarchy for Fusion sequence types
////////////////////////////////////////////////////////////////////////////////
namespace nt2 {namespace meta
{
  template<class T> struct fusion_sequence_ : unspecified_<T>
  {
    typedef unspecified_<T> parent;
    typedef T               origin;
  };

  template<class T, std::size_t N>
  struct array_ : array_<typename T::parent, N>
  {
    typedef array_<typename T::parent, N> parent;
    typedef typename T::origin            origin;
  };

  template<class T, std::size_t N>
  struct array_<unspecified_<T>, N> : fusion_sequence_<T>
  {
    typedef fusion_sequence_<T> parent;
    typedef T                   origin;
  };
} }

namespace nt2 { namespace details
{
  template<class T,class Origin>
  struct  hierarchy_of< T
                      , Origin
                      , typename boost
                        ::enable_if_c < boost::fusion
                                        ::traits::is_sequence<T>::value
                                      >::type
                      >
  {
    typedef meta::fusion_sequence_<T> type;
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Specialize hierarchy for boost::array
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  template<class T, std::size_t N>
  struct  hierarchy_of< boost::array<T,N> >
  {
    typedef meta::
            array_<typename hierarchy_of<T,boost::array<T,N> >::type,N> type;
  };
} }

#endif

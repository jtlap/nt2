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
#include <boost/mpl/bool.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>
#include <boost/fusion/include/is_sequence.hpp>

////////////////////////////////////////////////////////////////////////////////
// Specialize hierarchy for Fusion sequence types
////////////////////////////////////////////////////////////////////////////////
namespace nt2
{
  namespace tag
  {
    struct                                  fusion_sequence_ {};
    template<class T, std::size_t N> struct array_ {};
  }

  namespace meta
  {
    template<class T> struct fusion_sequence_ : unspecified_<T>
    {
      typedef unspecified_<T>       parent;
      typedef tag::fusion_sequence_ type;
    };

    template<class T, std::size_t N>
    struct array_ : array_<typename T::parent, N>
    {
      typedef array_<typename T::parent, N> parent;
      typedef tag::array_<typename T::type, N>             type;
    };

    template<class T, std::size_t N>
    struct array_<unspecified_<T>, N> : fusion_sequence_<T>
    {
      typedef fusion_sequence_<T>                   parent;
      typedef tag::array_<typename parent::type, N> type;
    };
} }

namespace nt2 { namespace details
{
  template<class T>
  struct  hierarchy_of< T
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
    typedef meta::array_<typename hierarchy_of<T>::type,N> type;
  };
} }

#endif

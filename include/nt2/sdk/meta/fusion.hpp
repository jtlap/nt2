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
// Specialize hierarchy for a selection of Fusion sequence types
// TODO : Add vector and other stuff like that
////////////////////////////////////////////////////////////////////////////////
namespace nt2
{
  namespace tag { struct fusion_sequence_ {}; }

  namespace meta
  {
    template<class T> struct fusion_sequence_ : unspecified_<T>
    {
      typedef unspecified_<T>       parent;
      typedef tag::fusion_sequence_ type;
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

#endif

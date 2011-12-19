//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_META_PADDED_SIZE_OF_HPP_INCLUDED
#define NT2_CORE_CONTAINER_META_PADDED_SIZE_OF_HPP_INCLUDED

/**
 * \file
 * \brief Define the nt2::meta::padded_size \metafunction
**/

#include <boost/mpl/int.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/times.hpp>
#include <boost/simd/sdk/memory/meta/align_on.hpp>

namespace nt2 { namespace meta
{
  //============================================================================
  /**
   * Computes the number of elements required to perform a static allocation
   * from an of_size static sequence and two padding values
  **/
  //============================================================================
  template< typename Size, typename GlobalPadding, typename LeadPadding>
  struct padded_size;

  //============================================================================
  // No padding at all, just prod(Size)
  //============================================================================
  template< typename Size >
  struct  padded_size<Size, boost::mpl::int_<1>, boost::mpl::int_<1> >
        : boost::mpl::fold< typename Size::values_type
                          , boost::mpl::int_<1>
                          , boost::mpl::times < boost::mpl::_1
                                              , boost::mpl::_2
                                              >
                          >::type
  {};

  //============================================================================
  // No Lead padding, just align_on<Global>(prod(Size))
  //============================================================================
  template< typename Size, typename GlobalPadding>
  struct  padded_size<Size, GlobalPadding, boost::mpl::int_<1> >
        : boost::simd::meta::
          align_on< padded_size < Size
                                , boost::mpl::int_<1>
                                , boost::mpl::int_<1>
                                >
                  , GlobalPadding
                  >
  {};

  //============================================================================
  // No Global padding at all, just align_on(Size[0]) * prod(tail(Size))
  //============================================================================
  template< typename Size, typename LeadPadding>
  struct  padded_size<Size, boost::mpl::int_<1>, LeadPadding >
        : boost::mpl::times
          < typename  boost::mpl::fold< typename boost::mpl::
                                        pop_front<typename Size::values_type>::type
                                      , boost::mpl::int_<1>
                                      , boost::mpl::times < boost::mpl::_1
                                                          , boost::mpl::_2
                                                          >
                                      >::type
          , boost::simd::meta::align_on
            < typename boost::mpl::at_c<typename Size::values_type,0>::type
            , LeadPadding
            >
          >
  {};

  //============================================================================
  // Both padding
  //============================================================================
  template< typename Size, typename GlobalPadding, typename LeadPadding>
  struct  padded_size
        : boost::simd::meta::
          align_on< padded_size < Size
                                , boost::mpl::int_<1>
                                , LeadPadding
                                >
                  , GlobalPadding
                  >
  {};
} }

#endif

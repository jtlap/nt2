//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_POSITION_FUSION_HPP_INCLUDED
#define NT2_CORE_UTILITY_POSITION_FUSION_HPP_INCLUDED

#include <boost/fusion/support.hpp>
#include <boost/simd/sdk/memory/align_on.hpp>
#include <boost/fusion/sequence/intrinsic.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/simd/sdk/details/at_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
  //============================================================================
  // Register position_ as fusion random access sequence
  //============================================================================
  template<> struct is_sequence_impl<nt2::tag::position_>
  {
    template<typename T> struct apply : mpl::true_ {};
  };

  template<> struct is_view_impl<nt2::tag::position_>
  {
    template<typename Seq> struct apply : mpl::true_ {};
  };

  template<> struct category_of_impl<nt2::tag::position_>
  {
    typedef random_access_traversal_tag type;
  };

  //============================================================================
  // Size of position_ is given by its static_size member
  //============================================================================
  template<> struct size_impl<nt2::tag::position_>
  {
    template<typename Seq> struct apply :
      boost::fusion::result_of::size<typename remove_reference<typename Seq::sequence_type>::type> {};
  };

  //============================================================================
  // at_c value of position_ is given by its static size
  //============================================================================
  template<> struct at_impl<nt2::tag::position_>
  {
    template<class Seq, std::ptrdiff_t N> struct apply_impl;

    template<class Seq, class Index>
    struct  apply : apply_impl< Seq, Index::value> {};

    template<class Seq, std::ptrdiff_t N> struct apply_impl
    {
      typedef typename remove_reference<typename Seq::sequence_type>::type seq_type;
      typedef typename boost::fusion::result_of::at_c<seq_type const,N>::type type;

      static type call(Seq& seq)
      {
        return boost::fusion::at_c<N>(seq.seq_);
      }
    };
  };

  template<> struct value_at_impl<nt2::tag::position_>
  {
    template<class Seq, class Index>
    struct apply
    {
      typedef typename at_impl<nt2::tag::position_>
                       ::template apply<Seq, Index>::type base;
      typedef typename remove_reference<base>::type type;
    };
  };

  //==========================================================================
  // begin returns the inner data_type begin as it is itself a Fusion Sequence
  //==========================================================================
  template<> struct begin_impl<nt2::tag::position_>
  {
    template<typename Sequence> struct apply
    {
      typedef boost::simd::at_iterator<Sequence, 0> type;
      static type call(Sequence& seq) { return type(seq); }
    };
  };

  //==========================================================================
  // end returns the inner data_type end as it is itself a Fusion Sequence
  //==========================================================================
  template<> struct end_impl<nt2::tag::position_>
  {
    template<typename Sequence>
    struct apply
    {
      typedef typename remove_reference<typename Sequence::sequence_type>::type seq_type;
      typedef typename boost::fusion::result_of::size<seq_type>::type size_type;
      typedef boost::simd::at_iterator<Sequence, size_type::value> type;

      static type call(Sequence& seq) { return type(seq); }
    };
  };
} } }

#endif

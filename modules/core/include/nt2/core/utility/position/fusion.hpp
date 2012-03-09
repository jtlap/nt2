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
  // Register position_ as fusion random access view
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

  template<>
  struct size_impl<nt2::tag::position_>
  {
    template<typename Seq>
    struct apply
     : boost::fusion::result_of::size<typename remove_reference<typename Seq::sequence_type>::type>
    {
    };
  };

  template<>
  struct at_impl<nt2::tag::position_>
  {
    template<class Seq, class Index>
    struct apply
    {
      typedef typename remove_reference<typename Seq::sequence_type>::type seq_type;
      typedef typename boost::fusion::result_of::at<seq_type const, Index>::type type;

      static type call(Seq& seq)
      {
        return boost::fusion::at<Index>(seq.seq_);
      }
    };
  };

  template<>
  struct value_at_impl<nt2::tag::position_>
  {
    template<class Seq, class Index>
    struct apply
    {
      typedef typename remove_reference<typename Seq::sequence_type>::type seq_type;
      typedef typename boost::fusion::result_of::value_at<seq_type const, Index>::type type;
    };
  };

  template<>
  struct begin_impl<nt2::tag::position_>
  {
    template<typename Sequence>
    struct apply
    {
      typedef boost::simd::at_iterator<Sequence, 0> type;
      static type call(Sequence& seq)
      {
        return type(seq);
      }
    };
  };

  template<>
  struct end_impl<nt2::tag::position_>
  {
    template<typename Sequence>
    struct apply
    {
      typedef typename boost::fusion::result_of::size<Sequence>::type size_type;
      typedef boost::simd::at_iterator<Sequence, size_type::value> type;
      static type call(Sequence& seq)
      {
        return type(seq);
      }
    };
  };
} } }

#endif

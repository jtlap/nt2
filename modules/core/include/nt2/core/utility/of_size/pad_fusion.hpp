//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_OF_SIZE_PAD_FUSION_HPP_INCLUDED
#define NT2_CORE_UTILITY_OF_SIZE_PAD_FUSION_HPP_INCLUDED

#include <boost/fusion/support.hpp>
#include <boost/simd/sdk/memory/align_on.hpp>
#include <boost/fusion/sequence/intrinsic.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/simd/sdk/details/at_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
  //============================================================================
  // Register padded_sequence_tag as fusion random access sequence
  //============================================================================
  template<> struct is_sequence_impl<nt2::tag::padded_sequence_tag>
  {
    template<typename T> struct apply : mpl::true_ {};
  };

  template<> struct is_view_impl<nt2::tag::padded_sequence_tag>
  {
    template<typename Seq> struct apply : mpl::true_ {};
  };

  template<> struct category_of_impl<nt2::tag::padded_sequence_tag>
  {
    typedef random_access_traversal_tag type;
  };

  //============================================================================
  // Size of padded_sequence_tag is given by its static_size member
  //============================================================================
  template<> struct size_impl<nt2::tag::padded_sequence_tag>
  {
    template<typename Seq>
    struct  apply
          : boost::fusion::result_of::size<typename Seq::sequence_type>
    {};
  };

  //============================================================================
  // at_c value of padded_sequence_tag is given by its static size or dynamic size if -1
  //============================================================================
  template<> struct at_impl<nt2::tag::padded_sequence_tag>
  {
    template<class Seq, std::ptrdiff_t N> struct apply_impl;

    template<class Seq, class Index>
    struct  apply : apply_impl< Seq, Index::value> {};

    template<class Seq> struct apply_impl<Seq, 0>
    {
      typedef typename Seq::sequence_type seq_type;
      typedef typename Seq::value_type    value_type;
      typedef typename boost::fusion::result_of::at_c<seq_type,0>::type base;
      typedef typename boost::dispatch::meta::
              call<boost::simd::tag::align_on_(base,value_type)>::type type;

      static type call(Seq& seq)
      {
        return  boost::simd::memory::
                align_on(boost::fusion::at_c<0>(seq.seq_),seq.value_);
      }
    };

    template<class Seq, std::ptrdiff_t N> struct apply_impl
    {
      typedef typename Seq::sequence_type seq_type;
      typedef typename boost::fusion::result_of::at_c<seq_type,N>::type type;

      static type call(Seq& seq)
      {
        return boost::fusion::at_c<N>(seq.seq_);
      }
    };
  };

  template<> struct value_at_impl<nt2::tag::padded_sequence_tag>
  {
    template<class Seq, class Index>
    struct apply
    {
      typedef typename  at_impl<nt2::tag::padded_sequence_tag>
                        ::template apply<Seq, Index>::type  base;
      typedef typename remove_reference<base>::type         type;
    };
  };

  //==========================================================================
  // begin returns the inner data_type begin as it is itself a Fusion Sequence
  //==========================================================================
  template<> struct begin_impl<nt2::tag::padded_sequence_tag>
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
  template<> struct end_impl<nt2::tag::padded_sequence_tag>
  {
    template<typename Sequence>
    struct apply
    {
      typedef typename boost::fusion::result_of::
              size<typename Sequence::sequence_type>::type      size_;
      typedef boost::simd::at_iterator<Sequence, size_::value>  type;
      static type call(Sequence& seq) { return type(seq); }
    };
  };
} } }

#endif

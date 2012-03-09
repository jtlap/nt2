//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_RELATIVE_VIEW_FUSION_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_RELATIVE_VIEW_FUSION_HPP_INCLUDED

#include <boost/fusion/support.hpp>
#include <boost/fusion/sequence/intrinsic.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/simd/sdk/details/at_iterator.hpp>
#include <nt2/include/functions/relative_index.hpp>

namespace boost { namespace fusion { namespace extension
{
  //============================================================================
  // Register relative_view_ as fusion random access view
  //============================================================================
  template<>
  struct is_sequence_impl<nt2::tag::relative_view_>
  {
    template<typename T> struct apply : mpl::true_ {};
  };

  template<>
  struct is_view_impl<nt2::tag::relative_view_>
  {
    template<typename T> struct apply : mpl::true_ {};
  };

  template<>
  struct category_of_impl<nt2::tag::relative_view_>
  {
    typedef random_access_traversal_tag type;
  };

  template<> struct size_impl<nt2::tag::relative_view_>
  {
    template<typename Pos>
    struct apply :
      boost::fusion::result_of::size<typename remove_reference<typename Pos::pos_type>::type>
    {
    };
  };

  template<>
  struct at_impl<nt2::tag::relative_view_>
  {
    template<class Pos, class Index>
    struct apply
    {
      typedef typename boost::fusion::result_of::at<typename Pos::expr_type const, Index>::type sub_expr_type;
      typedef typename nt2::meta::call<nt2::tag::relative_index_(sub_expr_type, typename Pos::pos_type, Index)>::type type;

      static type call(Pos& pos)
      {
        return nt2::relative_index(boost::fusion::at<Index>(pos.expr_), pos.pos_, Index());
      }
    };
  };

  template<>
  struct value_at_impl<nt2::tag::relative_view_>
  {
    template<class Pos, class Index>
    struct apply
    {
      typedef typename at_impl<nt2::tag::relative_view_>
        ::template apply<Pos, Index>::type base;
      typedef typename remove_reference<base>::type type;
    };
  };

  template<>
  struct begin_impl<nt2::tag::relative_view_>
  {
    template<typename Pos>
    struct apply
    {
      typedef boost::simd::at_iterator<Pos, 0> type;
      static type call(Pos& pos)
      {
        return type(pos);
      }
    };
  };

  template<>
  struct end_impl<nt2::tag::relative_view_>
  {
    template<typename Pos>
    struct apply
    {
      typedef typename boost::fusion::result_of::size<Pos>::type size_type;
      typedef boost::simd::at_iterator<Pos, size_type::value> type;

      static type call(Pos& pos)
      {
        return type(pos);
      }
    };
  };
} } }

#endif

//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TABLE_DETAILS_IS_VECTORIZABLE_INDEXER_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TABLE_DETAILS_IS_VECTORIZABLE_INDEXER_HPP_INCLUDED

#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/core/functions/scalar/colon.hpp>
#include <nt2/sdk/memory/forward/container.hpp>
#include <nt2/core/utility/of_size.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/meta/as.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>

namespace nt2 { namespace ext
{
  template<class It, class End>
  struct mpl_safe_next
       : boost::mpl::next<It>
  {
  };

  template<class It>
  struct mpl_safe_next<It, It>
  {
    typedef It type;
  };

  template<class T>
  struct is_vectorizable_scalar
       : boost::mpl::bool_< T::extent_type::static_size == 0u && !boost::is_same<typename T::proto_tag, nt2::tag::relative_colon_>::value>
  {
  };

  template<>
  struct is_vectorizable_scalar< nt2::container::
                                 expression< boost::proto::
                                             basic_expr< boost::proto::tag::terminal
                                                       , boost::proto::term<nt2::container::colon_>
                                                       , 0l
                                                       >
                                           , nt2::container::colon_
                                           >
                               >
       : boost::mpl::false_
  {
  };

  template<class Id, class Cardinal, class Enable = void>
  struct is_vectorizable_indexer_impl
       : boost::mpl::false_
  {
  };

  template<class Id, class Cardinal>
  struct is_vectorizable_indexer
       : is_vectorizable_indexer_impl<Id, Cardinal>
  {
  };

  // scalar
  template<class Id>
  struct is_vectorizable_indexer_impl< Id, boost::mpl::size_t<1u>, typename boost::enable_if_c< Id::extent_type::static_size == 0u >::type >
       : boost::mpl::true_
  {
  };

  // _(a, b)
  template<class T, std::ptrdiff_t N, class Cardinal>
  struct is_vectorizable_indexer<
    nt2::container::expression<
      boost::proto::basic_expr<
          nt2::tag::colon_
        , boost::proto::list3<
              nt2::box<
                  nt2::of_size_<
                      1l
                    , N
                    , 1l
                    , 1l
                  >
              >
            , nt2::box<
                  nt2::meta::constant_<nt2::tag::unity_colon_, T>
              >
            , nt2::container::expression<
                  boost::proto::basic_expr<
                      boost::proto::tag::terminal
                    , boost::proto::term<
                          boost::dispatch::meta::as_<T>
                      >
                    , 0l
                  >
                , boost::dispatch::meta::as_<T>
              >
          >
        , 3l
      >
    , nt2::memory::container<
          T
        , nt2::settings(
            nt2::of_size_<
                1l
              , N
              , 1l
              , 1l
            >
          )
      >
    >
  , Cardinal
  >
    : boost::mpl::bool_< Cardinal::value && !(std::size_t(N < 0 ? -N : N) % Cardinal::value) >
  {
  };

  // _
  template<class Cardinal>
  struct is_vectorizable_indexer< nt2::container::
                                  expression< boost::proto::
                                              basic_expr< boost::proto::tag::terminal
                                                        , boost::proto::term<nt2::container::colon_>
                                                        , 0l
                                                        >
                                            , nt2::container::colon_
                                            >
                                , Cardinal
                                >
       : boost::mpl::true_
  {
  };

  template<class Children, class Cardinal>
  struct is_vectorizable_indexers_impl
  {
    typedef typename boost::mpl::end<Children>::type seq_end;

    typedef typename boost::mpl::
            find_if< Children
                   , boost::mpl::not_< is_vectorizable_indexer< boost::mpl::_1, Cardinal > >
                   >::type it;

    typedef typename boost::mpl::
            fold < boost::mpl::iterator_range< it, typename mpl_safe_next<it, seq_end>::type >
                 , boost::mpl::true_
                 , boost::mpl::and_< boost::mpl::_1
                                   , is_vectorizable_indexer< boost::mpl::_2, boost::mpl::size_t<1> >
                                   >
                 >::type init;

    typedef typename boost::mpl::
            fold < boost::mpl::iterator_range< typename mpl_safe_next<it, seq_end>::type, seq_end >
                 , init
                 , boost::mpl::and_< boost::mpl::_1
                                   , is_vectorizable_scalar< boost::mpl::_2 >
                                   >
                 >::type type;

    static const bool value = type::value;
  };


  template<class Children, class Data>
  struct is_vectorizable_indexers
       : is_vectorizable_indexers_impl<Children, typename meta::cardinal_of<typename meta::target_value<Data>::type>::type>
  {
  };

  template<class Children>
  struct is_contiguous_indexers
       : is_vectorizable_indexers_impl<Children, boost::mpl::size_t<0> >
  {
  };
} }

#endif

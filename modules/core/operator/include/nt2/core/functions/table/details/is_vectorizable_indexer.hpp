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
#include <boost/fusion/include/as_vector.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/back.hpp>
#include <boost/utility/enable_if.hpp>

namespace nt2 { namespace ext
{
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
    : boost::mpl::bool_< Cardinal::value == 1 || (N != -1 && !(N % Cardinal::value)) >
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

  template<class Children, class Data>
  struct is_vectorizable_indexers
       : boost::mpl::
         and_< boost::mpl::
               fold < typename boost::mpl::pop_back< typename boost::fusion::result_of::as_vector<Children>::type >::type
                    , boost::mpl::true_
                    , boost::mpl::and_< boost::mpl::_1
                                      , is_vectorizable_indexer< boost::mpl::_2, typename meta::cardinal_of<typename meta::target_value<Data>::type>::type >
                                      >
                    >
             , is_vectorizable_indexer< typename boost::mpl::back<Children>::type, boost::mpl::size_t<1u> >
             >
  {
  };
} }

#endif

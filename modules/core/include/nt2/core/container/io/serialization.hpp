//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_IO_SERIALIZATION_HPP_INCLUDED
#define NT2_CORE_CONTAINER_IO_SERIALIZATION_HPP_INCLUDED

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/split_free.hpp>
#include <nt2/table.hpp>
#include <nt2/core/container/dsl/expression.hpp>
#include <nt2/sdk/parameters.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/core/utility/of_size.hpp>
#include <nt2/include/functions/numel.hpp>
#include <boost/proto/traits.hpp>
#include <boost/mpl/assert.hpp>

namespace boost { namespace serialization 
{ 
  //==========================================================================
  // First entry point of the serialization in table<T,S>
  //==========================================================================
  template<class Archive, class T, class S, class D, class E, class R>
  void save(Archive & ar, const nt2::table<T,S,D>& t, unsigned int version)
  {
    ar << boost::serialization::base_object< const nt2::container::expression<E,R> >(t);
  }

  template<class Archive, class T, class S, class D, class E, class R>
  void load(Archive & ar, nt2::table<T,S,D>& t, unsigned int version)
  {
    ar >> boost::serialization::base_object< nt2::container::expression<E,R> >(t);
  }

  template<class Archive, class T, class S, class D>
  inline void serialize( Archive & ar, nt2::table<T,S,D>& t
                       , const unsigned int file_version)
  {
    split_free(ar, t, file_version); 
  }

  //==========================================================================
  // Down in expression, serialized its extent member 
  //==========================================================================
  template<class Archive, class E, class R, class D>
  void save( Archive& ar, const nt2::container::expression<E,R,D>& e
           , const unsigned int& version)
  {
    BOOST_MPL_ASSERT_MSG( (boost::proto::arity_of<E>::value == 0)
                        , NT2_INVALID_ACCESS_TO_RAW_DATA_ON_NON_TERMINAL
                        , (E)
                        );
    typedef typename nt2::container::expression<E,R,D>::extent_type e_t;
    typedef typename nt2::meta::strip<e_t>::type size_type;
    size_type size_ = e.extent(); 
    ar << size_;
    ar << make_array(e.raw(), nt2::numel(e));
  }

  template<class Archive, class E, class R, class D>
  void load( Archive& ar, nt2::container::expression<E,R,D>& e
           , const unsigned int& version)
  {
    BOOST_MPL_ASSERT_MSG( (boost::proto::arity_of<E>::value == 0)
                        , NT2_INVALID_ACCESS_TO_RAW_DATA_ON_NON_TERMINAL
                        , (E)
                        );
    typedef typename nt2::container::expression<E,R,D>::extent_type e_t;
    typedef typename nt2::meta::strip<e_t>::type size_type;
    size_type size_;
    ar >> size_;
    e.resize(size_);
    ar >> make_array(e.raw(), nt2::numel(e));
  }

  template<class Archive, class E, class R, class D>
  inline void serialize( Archive& ar
                       , nt2::container::expression<E,R,D>& e
                       , const unsigned int file_version)
  {
    split_free(ar, e, file_version); 
  }

  //==========================================================================
  // Down in extent, serialization of struct of_size_
  //==========================================================================
  template<class Archive, BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D) >
  void save( Archive& ar
           , const nt2::of_size_< BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D) >& of
           , const unsigned int& version)
  {
    ar << of.data_;
  }

  template<class Archive, BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D) >
  void load( Archive& ar
           , nt2::of_size_< BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D) >& of
           , const unsigned int& version)
  {
    ar >> of.data_;
  }

  template<class Archive, BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D) >
  inline void serialize( Archive& ar
                       , nt2::of_size_< BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D) >& of
                       , const unsigned int file_version)
  {
    split_free(ar, of, file_version);
  }

} }

#endif

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

  template<class Archive, class T, class S, class E, class R>
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

} }

#endif

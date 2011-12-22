//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_COMPOSITE_BUFFER_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_COMPOSITE_BUFFER_HPP_INCLUDED

//==============================================================================
/**
  * \file
  * \brief Defines and implements the \c nt2::memory::composite_buffer class
  **/
//==============================================================================

#include <boost/mpl/size.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <nt2/sdk/memory/adapted/composite_buffer.hpp>

namespace nt2 { namespace memory
{
  //============================================================================
  /**
    * \brief Buffer for composite types
    *
    * composite_buffer allow type registered as composite to automatically be
    * promoted to a structure of array instead of an array of structure.
    *
    * \tparam Buffer Model of the buffer to use as an underlying storage
   **/
  //============================================================================
  template< typename Buffer >
  struct composite_buffer
  {
    typedef typename boost::dispatch::meta::value_of<Buffer>::type      values;
    typedef typename boost::dispatch::meta::model_of<Buffer>::type      model;
    typedef typename boost::fusion::result_of::as_vector<values>::type  types;
    typedef typename boost::mpl::transform<types,model>::type           data_type;

    template<typename Sizes, typename Bases, typename Padding>
    inline void initialize( Sizes const& s, Bases const& b, Padding const& p )
    {
      initialize(s,b,p, typename boost::mpl::size<data_type>::type());
    }

    template<typename Sizes, typename Bases, typename Padding, int N>
    inline void
    initialize( Sizes const& s, Bases const& b
              , Padding const& p, boost::mpl::int_<N> const &
              )
    {
      memory::initialize(boost::fusion::at_c<N-1>(data_),s,b,p);
      initialize(s,b,p, boost::mpl::int_<N-1>());
    }

    template<typename Sizes, typename Bases, typename Padding> inline void
    initialize( Sizes const& /*s*/, Bases const& /*b*/
              , Padding const& /*p*/, boost::mpl::int_<0> const &
              )
    {}

    data_type data_;
  };
} }

#endif

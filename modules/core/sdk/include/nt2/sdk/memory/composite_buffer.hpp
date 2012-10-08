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

#include <boost/mpl/transform.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <nt2/sdk/memory/details/composite_traits.hpp>
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
    * \tparam Buffer Buffer to use as an underlying storage
   **/
  //============================================================================
  template<typename Buffer> class composite_buffer
  {
    public:
    //==========================================================================
    // Extract the value type of Buffer and its meta-model, convert the value
    // to its equivalent fusion tuple and apply a transform to turn each types
    // in this tuple into a buffer of proper model.
    //==========================================================================
    typedef typename boost::dispatch::meta::value_of<Buffer>::type      base_t;
    typedef typename boost::dispatch::meta::model_of<Buffer>::type      model_t;
    typedef typename boost::fusion::result_of::as_vector<base_t>::type  types_t;
    typedef typename boost::mpl::transform<types_t,model_t>::type       data_t;

    //==========================================================================
    // Container types
    //==========================================================================
    typedef types_t                                       value_type;
    typedef typename boost::mpl::
            transform < data_t
                      , details::composite_ref
                      >::type                             reference;
    typedef typename boost::mpl::
            transform < data_t
                      , details::composite_cref
                      >::type                             const_reference;
    typedef typename boost::mpl::
            transform < data_t
                      , details::composite_iterator
                      >::type                             iterator;
    typedef typename boost::mpl::
            transform < data_t
                      , details::composite_citerator
                      >::type                             const_iterator;
    typedef typename boost::mpl::
            transform < data_t
                      , details::composite_riterator
                      >::type                             reverse_iterator;
    typedef typename boost::mpl::
            transform < data_t
                      , details::composite_criterator
                        >::type                           const_reverse_iterator;
    typedef std::size_t                                   size_type;
    typedef std::ptrdiff_t                                difference_type;

    //==========================================================================
    // Container interface
    //==========================================================================

    private:
    data_t data_;
  };
} }

#endif

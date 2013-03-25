//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_FORWARD_CONTAINER_HPP_INCLUDED
#define NT2_SDK_MEMORY_FORWARD_CONTAINER_HPP_INCLUDED

#include <nt2/core/settings/specific_data.hpp>

//==============================================================================
// Forward declaration
//==============================================================================
namespace nt2 { namespace memory
{
  template<class T> struct container_base
  {
    container_base() : specific_() {}

    //==========================================================================
    // Specific data type - Used for per-hardware site special member
    //==========================================================================
    typedef typename specific_data< typename  boost::dispatch::
                                              default_site<T>::type
                                  , T
                                  >::type       specific_data_type;

    //==========================================================================
    /*!
     * @brief Access to the architecture specific container data
     * As the inner structure of a container may change with the hardware
     * configuration, a specific data segment is provided to gather informations
     * that may be required for proper operation on said configuration.
     *
     * @return A reference to the specific data of the container.
     **/
    //==========================================================================
    specific_data_type&  specifics() const { return specific_; }

  private:
    mutable specific_data_type  specific_;
  };

  template<class Type, class Settings, class Semantic>  class container;
  template<class T, class S, class Semantic>                   struct  container_ref;
  template<class T, class S, class Semantic, bool Own = false> struct  container_shared_ref;

  template<class T, class S1, class S2, class Sema1, class Sema2>
  void swap(container<T,S1,Sema1>&, container<T,S2,Sema2>&);
} }

#endif

//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_FORWARD_ID_HPP_INCLUDED
#define NT2_CORE_SETTINGS_FORWARD_ID_HPP_INCLUDED

#include <boost/cstdint.hpp>
#include <boost/mpl/string.hpp>

namespace nt2 
{ 
  //============================================================================
  /*! id_ gives a container with a 32bits ID, either numerical or by using
   *  multi-byte character. This ID is usable to allow deeper compile-time
   * analysis and optimization.
   * 
   * \tparam ID 32 byte multi-bytes character unique identifier
   **/
  //============================================================================
  template<boost::uint32_t ID> struct id_ 
  {
    typedef boost::mpl::string<ID> type;
  }; 
  
  namespace tag 
  { 
    //==========================================================================
    /*!
     * Option tag for id options
     **/
    //==========================================================================
    struct id_ {}; 
  }

}

#endif

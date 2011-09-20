//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_DEREFERENCE_HPP
#define NT2_CORE_CONTAINER_MEMORY_DEREFERENCE_HPP

//==============================================================================
/**
  * \file 
  * \brief Defines and implements the \c nt2::memory::dereference class
  **/
//==============================================================================
#include <boost/fusion/include/at_c.hpp>
#include <nt2/core/container/meta/reference.hpp>

namespace nt2 { namespace details
{
  //============================================================================
  // Recursively apply [] on the buffer
  //============================================================================
  template< std::size_t Level, std::size_t Dims>
  struct dereference
  {
    template<typename Buffer, typename Position>
    static inline typename meta::dereference_<Buffer&,Level>::type 
    apply( Buffer& b, Position const& p )
    {
      return  dereference<Level-1,Dims>
              ::apply(b[boost::fusion::at_c<Level-1>(p)], p);
    }

    template<typename Buffer, typename Position>
    static inline typename meta::dereference_<Buffer const&,Level>::type 
    apply( Buffer const& b, Position const& p )
    {
      return  dereference<Level-1,Dims>
              ::apply(b[boost::fusion::at_c<Level-1>(p)], p);
    }
  };

  template<std::size_t Dims>
  struct dereference<1,Dims>
  {
    template<typename Buffer, typename Position>
    static inline typename meta::dereference_<Buffer&,1UL>::type 
    apply( Buffer& b, Position const& p )
    {
      return b[boost::fusion::at_c<0>(p)];
    }

    template<typename Buffer, typename Position>
    static inline typename meta::dereference_<Buffer const&,1UL>::type 
    apply( Buffer const& b, Position const& p )
    {
      return b[boost::fusion::at_c<0>(p)];
    }
  };
} }

namespace nt2 { namespace memory
{
  //============================================================================
  /**
    *  
   **/
  //============================================================================
  template<std::size_t Level, typename Buffer, typename Position>
  inline typename meta::dereference_<Buffer&,Level>::type 
  dereference( Buffer& b, Position const& p )
  {
    return details::dereference<Level,meta::dimensions_of<Buffer>::value>::apply(b,p);
  }

  template<std::size_t Level, typename Buffer, typename Position>
  inline typename meta::dereference_<Buffer const&,Level>::type 
  dereference( Buffer const& b, Position const& p )
  {
    return details::dereference<Level,meta::dimensions_of<Buffer>::value>::apply(b,p);
  }
} }

#endif

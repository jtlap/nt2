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

namespace nt2 { namespace details
{
  //============================================================================
  // Recursively apply [] on the buffer
  //============================================================================
  template<typename Buffer, std::size_t Level>
  struct dereference
  {
    template<typename Position>
    static inline typename meta::dereference_<Buffer&,Level>::type 
    apply( Buffer& b, Position const& p )
    {
      typedef typename meta::dereference_<Buffer,1>::type base;
      return  dereference<base,Level-1>
              ::apply(b[boost::fusion::at_c<Level-1>(p)], p);
    }

    template<typename Position>
    static inline typename meta::dereference_<Buffer const&,Level>::type 
    apply( Buffer const& b, Position const& p )
    {
      typedef typename meta::dereference_<Buffer,1>::type base;
      return  dereference<base,Level-1>
              ::apply(b[boost::fusion::at_c<Level-1>(p)], p);
    }
  };

  template<typename Buffer>
  struct dereference<Buffer,1>
  {
    template<typename Position>
    static inline typename meta::dereference_<Buffer&,1>::type 
    apply( Buffer& b, Position const& p )
    {
      return b[boost::fusion::at_c<0>(p)];
    }

    template<typename Position>
    static inline typename meta::dereference_<Buffer const&,1>::type 
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
    return details::dereference < Buffer,Level >::apply(b,p);
  }

  template<std::size_t Level, typename Buffer, typename Position>
  inline typename meta::dereference_<Buffer const&,Level>::type 
  dereference( Buffer const& b, Position const& p )
  {
    return details::dereference < Buffer,Level >::apply(b,p);
  }
} }

#endif

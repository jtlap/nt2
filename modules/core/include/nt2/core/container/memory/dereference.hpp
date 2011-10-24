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
#include <boost/mpl/size.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/adapted/array.hpp>

namespace nt2 { namespace details
{
  //============================================================================
  // Recursively apply [] on the buffer
  //============================================================================
  template<typename Buffer, std::size_t Level, std::size_t Start>
  struct dereference
  {
    template<typename Position>
    static inline typename meta::dereference_<Buffer&,Level>::type 
    apply( Buffer& b, Position const& p )
    {
      typedef boost::mpl::size<Position> base;
      typedef typename meta::dereference_<Buffer,1>::type base_type;
      return  dereference<base_type,Level-1,Start>
              ::apply ( b[boost::fusion::at_c<(Level-1)+(base::value-Start)>(p)]
                      , p
                      );
    }

    template<typename Position>
    static inline typename meta::dereference_<Buffer const&,Level>::type 
    apply( Buffer const& b, Position const& p )
    {
      typedef boost::mpl::size<Position> base;
      typedef typename meta::dereference_<Buffer,1>::type base_type;
      return  dereference<base_type,Level-1,Start>
              ::apply ( b[boost::fusion::at_c<(Level-1)+(base::value-Start)>(p)]
                      , p
                      );
    }
  };

  template<typename Buffer, std::size_t Start>
  struct dereference<Buffer,1,Start>
  {
    template<typename Position>
    static inline typename meta::dereference_<Buffer&,1>::type 
    apply( Buffer& b, Position const& p )
    {
      typedef boost::mpl::size<Position> base;
      return b[boost::fusion::at_c<base::value-Start>(p)];
    }

    template<typename Position>
    static inline typename meta::dereference_<Buffer const&,1>::type 
    apply( Buffer const& b, Position const& p )
    {
      typedef boost::mpl::size<Position> base;
      return b[boost::fusion::at_c<base::value-Start>(p)];
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
    return details::dereference<Buffer,Level,Level>::apply(b,p);
  }

  template<std::size_t Level, typename Buffer, typename Position>
  inline typename meta::dereference_<Buffer const&,Level>::type 
  dereference( Buffer const& b, Position const& p )
  {
    return details::dereference<Buffer,Level,Level>::apply(b,p);
  }
} }

#endif

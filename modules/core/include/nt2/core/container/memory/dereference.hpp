//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_DEREFERENCE_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_DEREFERENCE_HPP_INCLUDED

//==============================================================================
/**
  * \file
  * \brief Defines and implements the \c nt2::memory::dereference class
  **/
//==============================================================================
#include <nt2/core/settings/details/fusion.hpp>

namespace nt2 { namespace details
{
  //============================================================================
  // Recursively apply [] on the buffer
  //============================================================================
  template<typename Buffer, std::size_t Level, std::size_t Start>
  struct dereference
  {
    template<typename Position>
    static BOOST_DISPATCH_FORCE_INLINE
    typename meta::dereference_<Buffer&,Level>::type
    apply( Buffer& b, Position const& p )
    {
      typedef typename meta::dereference_<Buffer,1>::type base_type;
      return  dereference<base_type,Level-1,Start>
              ::apply ( b[safe_at_c<(Level-1)>(p)]
                      , p
                      );
    }

    template<typename Position>
    static BOOST_DISPATCH_FORCE_INLINE
    typename meta::dereference_<Buffer const&,Level>::type
    apply( Buffer const& b, Position const& p )
    {
      typedef typename meta::dereference_<Buffer,1>::type base_type;
      return  dereference<base_type,Level-1,Start>
              ::apply ( b[safe_at_c<(Level-1)>(p)]
                      , p
                      );
    }
  };

  template<typename Buffer, std::size_t Start>
  struct dereference<Buffer,1,Start>
  {
    template<typename Position>
    static BOOST_DISPATCH_FORCE_INLINE
    typename meta::dereference_<Buffer&,1>::type
    apply( Buffer& b, Position const& p )
    {
      return b[safe_at_c<0>(p)];
    }

    template<typename Position>
    static BOOST_DISPATCH_FORCE_INLINE
    typename meta::dereference_<Buffer const&,1>::type
    apply( Buffer const& b, Position const& p )
    {
      return b[safe_at_c<0>(p)];
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
  BOOST_DISPATCH_FORCE_INLINE
  typename meta::dereference_<Buffer&,Level>::type
  dereference( Buffer& b, Position const& p )
  {
    details::check_all_equal(details::pop_front_c<Level>(p), 1);
    return details::dereference<Buffer,Level,Level>::apply(b,p);
  }

  template<std::size_t Level, typename Buffer, typename Position>
  BOOST_DISPATCH_FORCE_INLINE
  typename meta::dereference_<Buffer const&,Level>::type
  dereference( Buffer const& b, Position const& p )
  {
    details::check_all_equal(details::pop_front_c<Level>(p), 1);
    return details::dereference<Buffer,Level,Level>::apply(b,p);
  }
} }

#endif

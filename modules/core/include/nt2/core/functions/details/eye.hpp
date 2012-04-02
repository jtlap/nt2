//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DETAILS_EYE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_EYE_HPP_INCLUDED

#include <boost/fusion/include/at.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/enumerate.hpp>

namespace nt2 { namespace details
{
  //============================================================================
  // eye actual functor
  //============================================================================
  struct eye
  {
    template<class Pos, class Size, class Target>
    typename Target::type
    operator()(Pos const& p, Size const& sz, Target const&) const
    {
      typedef typename Target::type                                   type;
      typedef typename meta::as_integer<type>::type                   i_t;
      typedef typename meta::call<nt2::tag::ind2sub_(_2D,Pos)>::type  sub_t;

      // Retrieve 2D position from the linear index
      sub_t const pos = ind2sub(sz,p);

      // Return a diagonal of 1
      return nt2::if_else ( nt2::eq ( nt2::enumerate<i_t>( pos[0] )
                                    , nt2::splat<i_t>( pos[1] )
                                    )
                          , One<type>()
                          , Zero<type>()
                          );
    }
  };
} }

#endif

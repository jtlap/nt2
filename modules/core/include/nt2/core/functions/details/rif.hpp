//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DETAILS_RIF_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_RIF_HPP_INCLUDED

#include <boost/fusion/include/at.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2 { namespace details
{
  //============================================================================
  // rif actual functor 
  //============================================================================
  struct rif
  {
    rif() {}

    template<class Pos, class Size, class Target>
    typename Target::type
    operator()(Pos const& p, Size const&, Target const&) const
    {
      static const int b = One<int>(); //- boost::mpl::at_c< typename Pos::index_type, 0>::type::value; 
      typedef typename Target::type type;
      return nt2::enumerate<type>(boost::fusion::at_c<0>(p)+b); 
    }

  };

} }

#endif

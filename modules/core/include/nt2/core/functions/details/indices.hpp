//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DETAILS_INDICES_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_INDICES_HPP_INCLUDED

#include <boost/fusion/include/at.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2 { namespace details
{
  //============================================================================
  // indices actual functor 
  //============================================================================
  struct indices
  {
    indices() {}
    template <class T>
    indices(const T & dim) : dim_(dim-1), base_(1){}
    template <class T>
    indices(const T & dim, int32_t base) : dim_(dim-1), base_(base){}

    template<class Pos, class Size, class Target>
    typename Target::type
    operator()(Pos const& p, Size const&sz, Target const&) const
    {
      typedef typename Target::type                                     type;
      typedef typename meta::call<nt2::tag::ind2sub_(Size,Pos)>::type  sub_t;

      sub_t const pos = ind2sub(sz,p);
      if (dim_ >= pos.size())
        return nt2::splat<type>(base_); 
      else if (dim_)
        return nt2::splat<type>(pos[dim_]+base_-1);
      else
        return nt2::enumerate<type>(pos[dim_]+base_-1);    
    }
  private:
    size_t dim_;
    int32_t base_; 
  };

} }

#endif

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

#include <nt2/core/utility/as_value.hpp>
#include <nt2/include/functions/ind2sub.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/enumerate.hpp>

namespace nt2 { namespace details
{
  //============================================================================
  // indices actual functor
  //============================================================================
  struct indices
  {
    indices() {}
    template <class T> indices(const T & d) : dim_(d-1), base_(1) {}
    template <class T> indices(const T & d, int32_t b) : dim_(d-1), base_(b)  {}

    template<class Pos, class Size, class Target>
    typename Target::type
    operator()(Pos const& p, Size const&sz, Target const&) const
    {
      typedef typename Target::type                                         type;
      typedef typename meta::as_integer<type>::type                         i_t;
      typedef typename meta::
                       call<nt2::tag::enumerate_(Pos,meta::as_<i_t>)>::type p_t;
      typedef typename meta::call<nt2::tag::ind2sub_(Size,p_t)>::type       s_t;;

      s_t const pos = ind2sub(sz,nt2::enumerate<i_t>(p));
      return (dim_ >= pos.size()) ? nt2::splat<type>(base_)
                                  : as_value<type>(pos[dim_]+base_-1);
    }

    private:
    size_t dim_;
    int32_t base_;
  };

} }

#endif

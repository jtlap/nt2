//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DETAILS_DELTAF_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_DELTAF_HPP_INCLUDED

#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/enumerate.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/sdk/meta/constant_adaptor.hpp>
#include <nt2/core/utility/as_subscript.hpp>
#include <nt2/core/utility/of_size.hpp>
#include <nt2/sdk/meta/as_index.hpp>

namespace nt2 { namespace tag { struct deltaf_; } }

namespace nt2 { namespace meta
{
  /// INTERNAL ONLY
  /// Functor used to generate deltaf values
  template<class Base> struct constant_<nt2::tag::deltaf_, Base>
  {
    typedef Base                                                    result_type;

    constant_ () {}
    template <class I0, class J0>
    constant_(const I0& i, const J0& j)  : i_(i-1), j_(j-1){}
    template<class Pos, class Size, class Target>
    BOOST_FORCEINLINE typename Target::type
    operator()(Pos const& p, Size const& sz, Target const&) const
    {
      typedef typename Target::type                                         type;
      typedef typename meta::as_index<type>::type                            i_t;
      typedef typename meta::call<tag::enumerate_(Pos,meta::as_<i_t>)>::type p_t;
      typedef typename nt2::result_of::as_subscript<Size,p_t>::type          s_t;
      typedef typename s_t::value_type                                       v_t;

      // Retrieve 2D position from the linear index
      s_t const pos = as_subscript(sz,nt2::enumerate<i_t>(p));
      // Return a 1 where it belongs
      BOOST_AUTO_TPL(ii, nt2::splat<v_t>(i_));
      BOOST_AUTO_TPL(jj, nt2::splat<v_t>(j_));
      return nt2::if_else(nt2::logical_and(nt2::eq(pos[0],ii),
                                           nt2::eq(pos[1],jj)),
                          nt2::One<type>(), nt2::Zero<type>());
    }

     private:
     ptrdiff_t i_, j_;
  };
} }

#endif

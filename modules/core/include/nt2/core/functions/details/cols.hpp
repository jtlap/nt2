//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DETAILS_COLS_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_COLS_HPP_INCLUDED

#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/ind2sub.hpp>
#include <nt2/include/functions/enumerate.hpp>

namespace nt2 { namespace details
{
  //============================================================================
  // cols actual functor
  //============================================================================
  template<class T>
  struct cols
  {
    cols()                : start_(T())  {}
    cols(const T & start) : start_(start){}

    template<class Pos, class Size, class Target>
    typename Target::type
    operator()(Pos const& p, Size const&sz, Target const& ) const
    {
      typedef typename Target::type                 type;
      typedef typename meta::as_integer<type>::type i_t;

      return splat<type>( ind2sub(sz,enumerate<i_t>(p))[1] - 1) + start_ ;
    }

    private :
    T start_;
  };

  template<class T, class T1>
  struct cols_scaled
  {
    cols_scaled() : start_(T()), fact_(One<T1>())  {}
    cols_scaled(const T & start, const T1 & f)  : start_(start), fact_(f)  {}

    template<class Pos, class Size, class Target>
    typename Target::type
    operator()(Pos const& p, Size const&sz, Target const& ) const
    {
      typedef typename Target::type                 type;
      typedef typename meta::as_integer<type>::type i_t;

      return fact_*splat<type>(ind2sub(sz,enumerate<i_t>(p))[1] - 1) + start_;
    }

    private :
    T start_;
    T fact_;
  };
} }

#endif

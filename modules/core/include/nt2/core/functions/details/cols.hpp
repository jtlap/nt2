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

#include <boost/fusion/include/at.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2 { namespace details
{
  //============================================================================
  // cols actual functor 
  //============================================================================
  template < class T>
  struct cols
  {
    cols()                : start_(T())  {}
    cols(const T & start) : start_(start){}
    template<class Pos, class Size, class Target>
    typename Target::type
    operator()(Pos const& p, Size const&sz, Target const& ) const
    {
      typedef typename Target::type                                     type;
      typedef typename meta::call<nt2::tag::ind2sub_(Size,Pos)>::type  sub_t;

      sub_t const pos = ind2sub(sz,p);
      return nt2::splat<type>(pos[1]-1+start_);
    }
  private :
    T start_; 
  };

  template < class T, class T1>
  struct cols_scaled
  {
    cols_scaled()                         : start_(T()), h_(One<T>()){}
    cols_scaled(const T & start, const T1 & h) : start_(start), h_(h){}
    template<class Pos, class Size, class Target>
    typename Target::type operator()(Pos const& p, Size const&sz, Target const& ) const
    {
      typedef typename Target::type                                     type;
      typedef typename meta::call<nt2::tag::ind2sub_(Size,Pos)>::type  sub_t;
      
      sub_t const pos = ind2sub(sz,p);
      return nt2::splat<type>(h_*(pos[1]-1)+start_);
    }
  private :
    T start_;
    T h_;
  };
} }

#endif

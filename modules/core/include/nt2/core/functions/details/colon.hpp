//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DETAILS_COLON_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_COLON_HPP_INCLUDED

#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/core/container/extremum/extremum.hpp>

namespace nt2 { namespace details
{
  //============================================================================
  // Factorized code for colon size evaluation
  //============================================================================
  template<class L, class S, class U>
  BOOST_FORCEINLINE std::size_t
  colon_size(L const& l, S const& s, U const& u)
  {
    return s ? ( ((u>l)==(s>0)) ? (u-l+s)/s : 0) : u;
  }

  //============================================================================
  // Factorized code for colon evaluation
  //============================================================================
  template<class T, class Pos, class Target>
  BOOST_FORCEINLINE typename Target::type
  colon_value(T const& l, T const& s, Pos const& p, Target const&)
  {
    typedef typename Target::type type;
    return nt2::fma ( nt2::enumerate<type>(p)
                    , nt2::splat<type>(s), nt2::splat<type>(l)
                    );
  }

  //============================================================================
  // Factorized code for unity colon size evaluation
  //============================================================================
  template<class L, class U>
  BOOST_FORCEINLINE std::size_t unity_colon_size(L const& l, U const& u)
  {
    return (u>=l) ? std::size_t(u-l+1) : 0;
  }

  //============================================================================
  // Factorized code for unity colon evaluation
  //============================================================================
  template<class T, class Pos, class Target>
  BOOST_FORCEINLINE typename Target::type
  unity_colon_value(T const& l, Pos const& p, Target const&)
  {
    typedef typename Target::type type;
    return  nt2::enumerate<type>(p+l);
  }

  //============================================================================
  // Storage for relative colon info
  //============================================================================
  template<class Begin, class End> struct relative_colon
  {
    typedef typename meta::is_extremum<Begin>::type is_begin_t;
    typedef typename meta::is_extremum<End>::type   is_end_t;

    Begin begin_;
    End   end_;

    // Computations of lower & upper have to take care of all
    // begin/end or end/begin combinations
    template<class B, class S> B lower(B const& b, S const& s) const
    {
      return lower(b,s,is_begin_t());
    }

    template<class B, class S> B upper(B const& b, S const& s) const
    {
      return upper(b,s,is_end_t());
    }

    private:
    // lower/upper computations for scalar extremum
    template<class B, class S>
    B lower(B const&, S const&, boost::mpl::false_ const&) const
    {
      return begin_;
    }

    template<class B, class S>
    B upper(B const&, S const&, boost::mpl::false_ const&) const
    {
      return end_;
    }

    // lower/upper computations for begin_/end_
    template<class B, class S>
    B lower(B const& b, S const& s, boost::mpl::true_ const&) const
    {
      return begin_.index(b,s);
    }

    template<class B, class S>
    B upper(B const& b, S const& s, boost::mpl::true_ const&) const
    {
      return end_.index(b,s);
    }
  };
} }

#endif

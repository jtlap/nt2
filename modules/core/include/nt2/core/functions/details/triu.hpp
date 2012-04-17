//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DETAILS_TRIU_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_TRIU_HPP_INCLUDED

#include <boost/fusion/include/at.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/enumerate.hpp>

namespace nt2 { namespace details
{
  //============================================================================
  // triu functor:
  // triu(a)(i, j) == (i <= j) ? a(i, j) : 0
  //============================================================================
  struct triu
  {
    template<class Sig> struct result;

    template<class This, class Pos,class Target>
    struct result<This(Pos,Target)>
    {
      typedef typename meta::strip<Target>::type::type        base;
      typedef typename meta::as_integer<base>::type           in;
      typedef typename meta::call<tag::is_less_(in,in)>::type type;
    };

    template<class Pos,class Target> BOOST_FORCEINLINE
    typename result<triu(Pos const&, Target const&)>::type
    operator()(Pos const& p, Target const& t) const
    {
      typedef typename result<triu(Pos const&, Target const&)>::in type;

      return le ( nt2::enumerate<type>( boost::fusion::at_c<0>(p) )
                , nt2::splat<type>    ( boost::fusion::at_c<1>(p) )
                );
    }
  };

  //============================================================================
  // triu with offset functor
  //  triu(a, k)(i, j)   is equal to: (i <= j+k)  ? a(i, j) : 0
  //============================================================================
  struct offset_triu
  {
    offset_triu() {}
    offset_triu(std::ptrdiff_t k) : k_(k) {}

    std::ptrdiff_t k_;

    template<class Sig> struct result;

    template<class This, class Pos,class Target>
    struct result<This(Pos,Target)>
    {
      typedef typename meta::strip<Target>::type::type        base;
      typedef typename meta::as_integer<base>::type           in;
      typedef typename meta::call<tag::is_less_(in,in)>::type type;
    };

    template<class Pos,class Target> BOOST_FORCEINLINE
    typename result<triu(Pos const&, Target const&)>::type
    operator()(Pos const& p, Target const& t) const
    {
      typedef typename result<triu(Pos const&, Target const&)>::in type;

      return le ( nt2::enumerate<type>( boost::fusion::at_c<0>(p)     )
                , nt2::splat<type>    ( boost::fusion::at_c<1>(p)+k_  )
                );
    }
  };
} }

#endif

//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DETAILS_COLON_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_COLON_HPP_INCLUDED

#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/enumerate.hpp>
#include <nt2/core/container/extremum/extremum.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/is_signed.hpp>
#include <nt2/sdk/meta/constant_adaptor.hpp>
#include <boost/mpl/bool.hpp>

namespace nt2 { namespace tag
{
  struct colon_;
  struct unity_colon_;
} }

namespace nt2 { namespace details
{
  /// INTERNAL ONLY
  /// Factorized code for colon size evaluation
  template<class L, class S, class U>
  BOOST_FORCEINLINE std::size_t
  colon_size(L const& l, S const& s, U const& u)
  {
    typedef typename meta::as_signed<L>::type ltype;
    typedef typename meta::as_signed<U>::type utype;
    return s ? ( ((u>l)==(s>0)) ? (utype(u)-ltype(l)+s)/s : (u == l)) : u;
  }

  /// INTERNAL ONLY
  /// Factorized code for colon evaluation
  template<class L, class S, class Pos, class Target>
  BOOST_FORCEINLINE typename Target::type
  colon_value(L const& l, S const& s, Pos const& p, Target const&)
  {
    typedef typename Target::type type;
    return nt2::fma ( nt2::enumerate<type>(p)
                    , nt2::splat<type>(s), nt2::splat<type>(l)
                    );
  }

  /// INTERNAL ONLY
  /// Same sign helper unity_colon_size
  template<class L, class U, bool B> BOOST_FORCEINLINE std::size_t
  unity_helper( L const& l, U const& u
              , boost::mpl::bool_<B> const&
              , boost::mpl::bool_<B> const&
              )
  {
    return (u >= l) ? static_cast<std::size_t>(u-l+1) : 0u;
  }

  /// INTERNAL ONLY
  /// signed/unsigned helper unity_colon_size
  template<class L, class U> BOOST_FORCEINLINE std::size_t
  unity_helper( L const& l, U const& u
              , const boost::mpl::true_&
              , const boost::integral_constant<bool, false>&
              )
  {
    return (l <= 0) ? static_cast<std::size_t>(u-l+1)
                    : ( u >= static_cast<U>(l)  ? static_cast<std::size_t>(u-l+1)
                                                : 0u
                      );
  }

  /// INTERNAL ONLY
  /// unsigned/signed helper unity_colon_size
  template<class L, class U> BOOST_FORCEINLINE std::size_t
  unity_helper( L const& l, U const& u
              , const boost::integral_constant<bool, false>&
              , const boost::integral_constant<bool, true>&
              )
  {
    return (u <= 0) ? 0u
                    : ( static_cast<L>(u) >= l  ? static_cast<std::size_t>(u-l+1)
                                                : 0u
                      );
  }

  /// INTERNAL ONLY
  /// Factorized code for unity colon size evaluation
  template<class L, class U>
  BOOST_FORCEINLINE std::size_t unity_colon_size(L const& l, U const& u)
  {
    return unity_helper ( l , u
                        , typename nt2::meta::is_signed<L>::type()
                        , typename nt2::meta::is_signed<U>::type()
                        );
  }

  /// INTERNAL ONLY
  /// Factorized code for unity colon evaluation
  template<class T, class Pos, class Target>
  BOOST_FORCEINLINE typename Target::type
  unity_colon_value(T const& l, Pos const& p, Target const&)
  {
    typedef typename Target::type type;
    return  nt2::enumerate<type>(p+l);
  }

  /// INTERNAL ONLY
  /// Storage for relative colon info
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
    std::ptrdiff_t upper(B const&, S const&, boost::mpl::false_ const&) const
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

namespace nt2 { namespace meta
{
  /// INTERNAL ONLY
  /// colon actual functor : precompute step and just iterate over
  template<class Base> struct constant_<nt2::tag::colon_, Base>
  {
    typedef Base                                          result_type;

    constant_() {}
    constant_( Base const& l, Base const& s) : lower_(l), step_(s) {}

    template<class Pos, class Size,class Target>
    BOOST_FORCEINLINE typename Target::type
    operator()(Pos const& p, Size const&sz, Target const& t) const
    {
      return details::colon_value(lower_,step_,p,t);
    }

    private:
    Base lower_, step_;
  };

  /// INTERNAL ONLY
  /// unity_colon actual functor : just forward form lower bound
  template<class Base> struct constant_<nt2::tag::unity_colon_, Base>
  {
    typedef Base                                          result_type;

    constant_() {}
    constant_( Base const& l ) : lower_(l) {}

    template<class Pos, class Size,class Target>
    BOOST_FORCEINLINE typename Target::type
    operator()(Pos const& p, Size const&sz, Target const& t) const
    {
      return details::unity_colon_value(lower_,p,t);
    }

    private:
    Base lower_;
  };
} }

#endif

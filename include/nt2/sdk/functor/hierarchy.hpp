/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_HIERARCHY_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_HIERARCHY_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Pre-made types hierarchy used for internal tag dispatching.
// Documentation: http://nt2.lri.fr/sdk/functor/hierarchy.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/vector.hpp>
#include <nt2/sdk/meta/set.hpp>
#include <nt2/sdk/meta/join.hpp>
#include <nt2/sdk/meta/any.hpp>
#include <nt2/sdk/config/types.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/arithmetic.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/equal_to.hpp>

namespace nt2 { namespace details
{

template<std::size_t N>
struct is_bitsize
{
  template<typename T>
  struct apply
    : boost::mpl::equal_to<
        boost::mpl::times<
          boost::mpl::sizeof_<T>
        , boost::mpl::size_t<CHAR_BIT>
        >
      , boost::mpl::size_t<N>
    >
  {
  };
};

// boost::is_integral considers bool to be integral
template<typename T>
struct is_integral
  :  meta::any<
       boost::is_same<boost::mpl::_, T>
     , boost::mpl::vector11< char, signed char, unsigned char
                           , short, unsigned short
                           , int, unsigned int
                           , long, unsigned long
                           , long long, unsigned long long
       >
    >   
{
};

template<std::size_t N>
struct int_is_bitsize
{
  template<typename T>
  struct apply
    : boost::mpl::and_<
        is_integral<T>
      , typename is_bitsize<N>::template apply<T>
      >
  {
  };
};

}}

namespace nt2 { namespace functors
{
  typedef meta::set<>                                       empty_;
  typedef meta::set<bool>                                   bool_;
  typedef meta::lambda_set< details::int_is_bitsize<8> >    int8_;
  typedef meta::lambda_set< details::int_is_bitsize<16> >   int16_;
  typedef meta::lambda_set< details::int_is_bitsize<32> >   int32_;
  typedef meta::lambda_set< details::int_is_bitsize<64> >   int64_;
  typedef int8_                                             types8_;
  typedef int16_                                            types16_;
  typedef meta::join< int32_, meta::set<float> >            types32_;
  typedef meta::join< int64_, meta::set<double> >           types64_;
  typedef meta::lambda_set< boost::mpl::and_<
    boost::mpl::not_< boost::is_signed<boost::mpl::_> >
  , details::is_integral<boost::mpl::_>
  > >                                                       uint_;
  typedef meta::lambda_set< boost::mpl::and_<
    boost::is_signed<boost::mpl::_>
  , details::is_integral<boost::mpl::_>
  > >                                                       int_;
  typedef meta::set<float, double>                          real_;
  typedef meta::join<real_, int_>                           signed_;
  typedef uint_                                             unsigned_;
  typedef meta::join<uint_        , int_  >                 integer_;
  typedef meta::join<integer_     , real_ >                 arithmetic_;
  typedef meta::join<arithmetic_  , bool_ >                 fundamental_;

  //////////////////////////////////////////////////////////////////////////////
  // Ordered universal list of hierarchies
  // Modify if you added a new hierarchy
  //////////////////////////////////////////////////////////////////////////////
  typedef boost::mpl::vector14< functors::int8_
                              , functors::int16_
                              , functors::int32_
                              , functors::int64_
                              , functors::types32_
                              , functors::types64_
                              , functors::uint_
                              , functors::int_
                              , functors::real_
                              , functors::signed_
                              , functors::integer_
                              , functors::arithmetic_
                              , functors::bool_
                              , functors::fundamental_
                              > hierarchies;
} }

#endif

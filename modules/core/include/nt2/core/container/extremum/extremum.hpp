//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_EXTREMUM_EXTREMUM_HPP_INCLUDED
#define NT2_CORE_CONTAINER_EXTREMUM_EXTREMUM_HPP_INCLUDED

namespace nt2 { namespace container
{
  //==========================================================================
  // extremum is an helper class that handles end_ and begin_ behavior
  //==========================================================================
  template<bool isEnd> struct extremum
  {
    std::ptrdiff_t offset_;

    template<class B, class Sz>
    BOOST_FORCEINLINE std::ptrdiff_t index(B const& b, Sz const& s) const
    {
      return index(b,s,boost::mpl::bool_<isEnd>());
    }

    private:
    template<class B, class Sz>
    BOOST_FORCEINLINE
    std::ptrdiff_t index(B const& b, Sz const& s, boost::mpl::true_) const
    {
      return s + b - 1 + offset_;
    }

    template<class B, class Sz>
    BOOST_FORCEINLINE
    std::ptrdiff_t index(B const& b, Sz const&, boost::mpl::false_) const
    {
      return b + offset_;
    }
  };

  //==========================================================================
  // Handles the end_ - i scenario by storing the offset in a new end_
  //==========================================================================
  template<class T>
  BOOST_FORCEINLINE extremum<true> operator-(extremum<true> const& e, T o)
  {
    extremum<true> that = { e.offset_ - o };
    return that;
  }

  //==========================================================================
  // Handles the begin_ + i scenario by storing the offset in a new begin_
  //==========================================================================
  template<class T>
  BOOST_FORCEINLINE extremum<false> operator+(extremum<false> const& e, T o)
  {
    extremum<false> that = { e.offset_ + o };
    return that;
  }

  template<class T>
  BOOST_FORCEINLINE extremum<false> operator+(T o, extremum<false> const& e)
  {
    extremum<false> that = { e.offset_ + o };
    return that;
  }
} }

namespace nt2 { namespace meta
{
  template<class T>
  struct  is_extremum
        : boost::mpl::false_
  {};

  template<bool B>
  struct  is_extremum< container::extremum<B> >
        : boost::mpl::true_
  {};
} }

namespace nt2
{
  //============================================================================
  /*!
   * end_ acts as the latest index of a container along a given dimension in
   * array indexing
   **/
  //============================================================================
  container::extremum<true>   const end_    = {0};

  //============================================================================
  /*!
   * begin_ acts as the first index of a container along a given dimension in
   * array indexing
   **/
  //============================================================================
  container::extremum<false>  const begin_  = {0};
}

#endif

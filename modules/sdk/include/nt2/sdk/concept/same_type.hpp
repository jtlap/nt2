/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONCEPT_SAME_TYPE_HPP_INCLUDED
#define NT2_SDK_CONCEPT_SAME_TYPE_HPP_INCLUDED

#include <nt2/sdk/error/concepts.hpp>
#include <boost/type_traits/is_same.hpp>

////////////////////////////////////////////////////////////////////////////////
// SameType concept
// This helpers concept helps checking that two types are the same
////////////////////////////////////////////////////////////////////////////////
namespace nt2
{
  template<class T1,class T2, bool EnableIf = boost::is_same<T1,T2>::value>
  struct SameType
  {
    BOOST_CONCEPT_USAGE(SameType) {}
  };

  template<class T1,class T2> struct SameType<T1,T2,false>
  {
    void types_are_not_the_same();
    BOOST_CONCEPT_USAGE(SameType) { types_are_not_the_same(t1,t2); }

    private:
    T1 t1;
    T2 t2;
  };
}

#endif

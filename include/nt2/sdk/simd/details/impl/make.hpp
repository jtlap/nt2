//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_MAKE_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_MAKE_HPP_INCLUDED

#include <boost/array.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <nt2/sdk/simd/preprocessor/include.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

namespace nt2 { namespace functors
{
  template<class T> struct make_ {};

  //////////////////////////////////////////////////////////////////////////////
  // make perform type dispatching based on the category of its target type
  // Hence, we need a specialized functor all together.
  //////////////////////////////////////////////////////////////////////////////
  template<class T, class Info>
  struct functor< make_<T>, Info >
  {
    ////////////////////////////////////////////////////////////////////////////
    // functor call is valid only if the amount of parameters equals the
    // vector cardinal
    ////////////////////////////////////////////////////////////////////////////
    struct validate
    {
      template<class Sig> struct result;
      template<class This,class A>
      struct result<This(A)>
        : boost::mpl::bool_ <   meta::cardinal_of<T>::value
                            ==  meta::strip<A>::type::static_size
                            >
      {};
    };

    template<class Sig> struct result;
    template<class This,class A> struct result<This(A)>
    {
      typedef typename meta::category_of<T>::type::tag      dominant;
      typedef functors::call<make_<T>,dominant,Info>        callee;
      typedef typename std::tr1::result_of<callee(A)>::type type;
    };

    template<class A> inline
    typename meta::enable_call<make_<T>(A)>::type
    operator()(A const& a) const
    {
      typedef typename meta::category_of<T>::type::tag  dominant;
      functors::call<make_<T>,dominant,Info>            callee;
      return callee(a);
    }
  };
} }

// TODO : Remove make_native
namespace nt2
{
  #define NT2_LOCAL(z,d,n)                                                      				\
  template<class T, class A> inline                                             				\
  typename meta::enable_call<functors::make_<T>(boost::array<A,n>)>::type       				\
  make( BOOST_PP_ENUM_PARAMS(n,A const& a) )                                    				\
  {                                                                             				\
    functors::functor< functors::make_<T> > callee;                             				\
    boost::array<A,n> data = {BOOST_PP_ENUM_PARAMS(n,a)};                       				\
    return callee(data);                                                        				\
  }                                                                             				\
	namespace simd																																				\
	{																																											\
		template<class T, class X> inline																										\
		typename meta::enable_call<functors::make_< native<T,X> >(boost::array<T,n>)>::type	\
		make_native( BOOST_PP_ENUM_PARAMS(n,T const& a) )																		\
		{                                                                           				\
			return nt2::make< native<T,X> >(BOOST_PP_ENUM_PARAMS(n,a));												\
		}                                                                           				\
	}																																											\
  /**/

  BOOST_PP_SEQ_FOR_EACH(NT2_LOCAL, ~, NT2_SIMD_CARDINALS)
  #undef NT2_LOCAL
}

#include NT2_SIMD_INCLUDE(make.hpp)

#endif

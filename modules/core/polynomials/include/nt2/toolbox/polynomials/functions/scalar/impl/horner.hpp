//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_POLYNOMIALS_FUNCTIONS_SCALAR_IMPL_HORNER_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOMIALS_FUNCTIONS_SCALAR_IMPL_HORNER_HPP_INCLUDED

#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/pop_back.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/include/functions/scalar/fma.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/digits.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>
#include <boost/dispatch/preprocessor/strip.hpp>

namespace nt2
{
  //////////////////////////////////////////////////////////////////////////////
  // static unrollign of horner scheme
  // Coefficients are given in decreasing powers and hexadecimal form
  // horner< NT2_HORNER_COEFF(float,3,(0x3f800000,0x40000000,0x40400000))>(2.0f)
  // means ((1*x+2)*x+3) or x^2+2x+3
  //////////////////////////////////////////////////////////////////////////////
  namespace details
    {
    template<int N, class Seq> struct static_horner_
    {
      template<class Sig> struct result;
      template<class This,class T> struct result<This(T)> : meta::strip<T> {};

      template<class T> inline
      typename meta::result_of<static_horner_(T)>::type
      operator()(T const& x) const
      {
        static_horner_<N-1,typename boost::mpl::pop_back<Seq>::type> callee;
        return fma( x
                  , callee(x)
                  , Const<T,boost::mpl::at_c<Seq,N-1>::type::value>()
                  );
      }
    };

    template<class Seq> struct static_horner_<1,Seq>
    {
      template<class Sig> struct result;
      template<class This,class T> struct result<This(T)> : meta::strip<T> {};

      template<class T> inline
      typename meta::result_of<static_horner_(T)>::type
      operator()(T const& ) const
      {
        return Const<T, boost::mpl::at_c<Seq,0>::type::value >();
      }
    };
  }

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Static Horner scheme
  //////////////////////////////////////////////////////////////////////////////
  template<class Coeff,class Type>
  static inline Type horner( Type const& x )
  {
    details::static_horner_<boost::mpl::size<Coeff>::value,Coeff> callee;
    return callee(x);
  }
}

#define NT2_COEFF_GEN(z,n,text)                                           \
boost::mpl::integral_c< BOOST_DISPATCH_PP_STRIP(BOOST_PP_TUPLE_ELEM(3,0,text))       \
                      , BOOST_PP_TUPLE_ELEM(BOOST_PP_TUPLE_ELEM(3,1,text) \
                                           ,n                             \
                                           ,BOOST_PP_TUPLE_ELEM(3,2,text) \
                                           )                              \
                      >                                                   \
/**/

////////////////////////////////////////////////////////////////////////////////
// Horner coefficient building macro
////////////////////////////////////////////////////////////////////////////////
#define NT2_HORNER_COEFF(Type, Size, Seq)                                     \
boost::mpl::vector< BOOST_PP_ENUM(Size                                        \
                                 ,NT2_COEFF_GEN                               \
                                 ,((nt2::meta::as_integer<Type, unsigned>::type),Size,Seq)\
                                 ) >                                          \
/**/

////////////////////////////////////////////////////////////////////////////////
// Horner coefficient building macro for template dependant Type
////////////////////////////////////////////////////////////////////////////////
#define NT2_HORNER_COEFF_T(Type, Size, Seq)                                   \
boost::mpl::vector< BOOST_PP_ENUM(Size                                        \
                                 ,NT2_COEFF_GEN                               \
                                 ,((typename nt2::meta::as_integer<Type, unsigned>::type)\
                                  ,Size                                       \
                                  ,Seq)                                       \
                                 ) >                                          \
/**/





#endif

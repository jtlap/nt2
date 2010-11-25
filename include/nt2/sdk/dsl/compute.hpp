/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_DSL_COMPUTE_HPP_INCLUDED
#define NT2_SDK_DSL_COMPUTE_HPP_INCLUDED

#include <boost/proto/transform.hpp>
#include <nt2/sdk/functor/functor.hpp>
#include <nt2/sdk/dsl/proto/unpack.hpp>

////////////////////////////////////////////////////////////////////////////////
// compile take any NT2 AST to a given target with a given transform
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace functors
{
  struct madd_;
}}

namespace nt2 { namespace dsl
{
  template <class Transform, class Locality> struct compile;

  template<class LocalizedTransform> struct _left;
  template<class LocalizedTransform> struct _right;

  template<class T, class L>
  struct  _left<T(L)>
        : boost::proto::call<compile<T,L>(boost::proto::_left)> {};

  template<class T, class L>
  struct  _right<T(L)>
        : boost::proto::call<compile<T,L>(boost::proto::_right)> {};

  template <typename Locality, typename Tag, typename Dummy = void>
  struct compute;

  template<class Transform, typename Tag, typename Locality>
  struct  functor_dispatch
        : boost::proto::
          unpack< boost::proto::
                  call< functors::functor<Tag, Locality> >(compile< Transform
                                                                  , Locality
                                                                  >
                                                          )
        >
  {};

    typedef compute<boost::mpl::_1,boost::mpl::_2,boost::mpl::_3> compute_;

    template <typename Locality, typename Tag, typename Dummy>
    struct compute
        : functor_dispatch<compute_,Tag, Locality>
    {};

    template<typename Locality>
    struct compute<Locality, functors::terminal_>
        : boost::proto::
          call<
            functors::functor<functors::terminal_,Locality>(
                boost::proto::_value
              , boost::proto::_state
              , boost::proto::_data
            )
        >
    {};

    template<typename Locality>
    struct  compute<Locality, functors::plus_>
          : boost::proto
                  ::or_ < boost::proto
                                ::when< boost::proto::plus< boost::proto::_
                                                          , boost::proto::multiplies<boost::proto::_,boost::proto::_>
                                                          >
                                      , boost::proto::
                                                call<
                                                  functors::functor<functors::madd_,Locality>(
                                                      _left<compute_(Locality)>(boost::proto::_right)
                                                    , _right<compute_(Locality)>(boost::proto::_right)
                                                    , _left<compute_(Locality)>()
                                                  )
                                              >
                                      >
                          ,  boost::proto
                                ::when< boost::proto::plus< boost::proto::multiplies<boost::proto::_,boost::proto::_>
                                                          , boost::proto::_
                                                          >
                                      , boost::proto::
                                                call<
                                                  functors::functor<functors::madd_,Locality>(
                                                      _left<compute_(Locality)>(boost::proto::_left)
                                                    , _right<compute_(Locality)>(boost::proto::_left)
                                                    , _right<compute_(Locality)>()
                                                  )
                                              >
                                      >
                        , boost::proto
                                ::when< boost::proto::plus<boost::proto::_,boost::proto::_>
                                      , boost::proto::
                                                call<
                                                  functors::functor<functors::plus_,Locality>(
                                                      _left<compute_(Locality)>()
                                                    , _right<compute_(Locality)>()
                                                  )
                                              >
                                      >
                        >
    {};

    template<class Transform,class Locality>
    struct compile
        : boost::proto::switch_<compile<Transform,Locality> >
    {
      template <typename Tag, typename Dummy = void>
      struct case_
          : boost::proto::
            otherwise < typename boost::mpl::
                        apply3<Transform,Locality,Tag,Dummy>::type
                      >
      {};
    };
} }

namespace boost { namespace proto
{
  template<class Transform,class Locality>
  struct  is_callable<nt2::dsl::compile<Transform,Locality> >
        : boost::mpl::true_  {};

  template<class LocalizedTransform>
  struct  is_callable<nt2::dsl::_left<LocalizedTransform> >
        : boost::mpl::true_  {};

  template<class LocalizedTransform>
  struct  is_callable<nt2::dsl::_right<LocalizedTransform> >
        : boost::mpl::true_  {};

  template<typename Tag, typename Locality, typename Dummy>
  struct  is_callable<nt2::dsl::compute<Tag, Locality, Dummy> >
        : boost::mpl::true_  {};
} }

#endif

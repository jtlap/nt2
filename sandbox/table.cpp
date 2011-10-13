#include <nt2/sdk/details/type_id.hpp>
#include <iostream>

#include <nt2/core/container/dsl.hpp>
#include <nt2/core/container/category.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/settings/size.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/run.hpp>
#include <boost/proto/debug.hpp>
#include <nt2/toolbox/operator/functions.hpp>

#include <boost/fusion/include/size.hpp>
#include <boost/fusion/include/array.hpp>
#include <cstdio>

namespace nt2
{
    // loop nest generator
    template<std::size_t N>
    struct for_each_impl
    {
        template<class Bases, class Sizes, class Position, class F>
        BOOST_DISPATCH_FORCE_INLINE
        static void call(Bases const& bases, Sizes const& sz, Position& pos, F const& f)
        {
            for(pos[N-1] = bases[N-1]; pos[N-1] != bases[N-1] + sz[N-1]; ++pos[N-1])
                for_each_impl<N-1>::call(bases, sz, pos, f);
        }
    };

    template<>
    struct for_each_impl<0>
    {
        template<class Bases, class Sizes, class Position, class F>
        static void call(Bases const&, Sizes const&, Position& pos, F const& f)
        {
            return f(pos);
        }
    };

    template<class Bases, class Sizes, class F>
    BOOST_DISPATCH_FORCE_INLINE
    void for_each(Bases const& bases, Sizes const& sz, F const& f)
    {
        static const std::size_t nb_dims = boost::fusion::result_of::size<Sizes>::value;

        boost::array<std::size_t, nb_dims> position;
        for_each_impl<nb_dims>::call(bases, sz, position, f);
    }

    // To replace with appropriate stuff
    template<class T>
    boost::array<std::size_t, NT2_MAX_DIMENSIONS> base_indices(T const&)
    {
      boost::array<std::size_t, NT2_MAX_DIMENSIONS> sz = { BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, 1 BOOST_PP_INTERCEPT) };
      return sz;
    }
}

template<class A0>
struct call_compute
{
    call_compute(A0 a0_) : a0(a0_) {}

    typedef void result_type;

    template<class Position>
    result_type operator()(Position const& pos) const
    {
        nt2::run(a0, pos);
    }

    A0 a0;
};

struct lhs_terminal
  : boost::proto::or_<
      boost::proto::when< boost::proto::terminal< boost::proto::_ >, boost::proto::_ >
    , boost::proto::when< boost::proto::nary_expr< boost::proto::_ >, lhs_terminal ( boost::proto::_child0 ) >
    >
{
};

#include <boost/dispatch/meta/identity.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::extent_, tag::cpu_
                            , (A0)(S0)
                            , ((table_< unspecified_<A0>, S0>))
                            )
  {
    typedef typename A0::size_type const& result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0& a0) const
    {
      return a0.extent();
    }
  };


  // terminal, does load / store
  NT2_FUNCTOR_IMPLEMENTATION_TPL( nt2::tag::terminal_, tag::cpu_
                            , (class A0)(class S0)(class State)(std::size_t N)
                            , ((ast_<table_< unspecified_<A0>, S0 > >))
                              ((array_< scalar_< integer_<State> >, N>))
                            )
  {
    typedef typename boost::dispatch::meta::
    scalar_of< typename boost::dispatch::meta::
               semantic_of<A0>::type
             >::type                                        result_type;

    template<class A0_>
    result_type operator()(A0_& a0, State const& state) const
    {
       std::cout << "access to table " << (void*)&boost::proto::value(a0) << " in " << state[0] << std::endl;
       static typename boost::remove_reference<result_type>::type r;
       return r;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION_TPL( nt2::tag::terminal_, tag::cpu_
                            , (class A0)(class State)(std::size_t N)
                            , ((ast_<table_< unspecified_<A0>, nt2::of_size_<1> > >))
                              ((array_< scalar_< integer_<State> >, N>))
                            )
  {
    typedef typename boost::dispatch::meta::
    scalar_of< typename boost::dispatch::meta::
               semantic_of<A0>::type
             >::type                                       result_type;

    template<class A0_>
    result_type operator()(A0_& a0, State const& state) const
    {
       std::cout << "access to scalar-like table " << (void*)&boost::proto::value(a0) << " in " << state[0] << std::endl;
       static typename boost::remove_reference<result_type>::type r;
       return r;
    }
  };

  NT2_REGISTER_DISPATCH_TO_TPL( nt2::tag::terminal_, tag::cpu_
                            , (class A0)(class State)(std::size_t N)
                            , ((ast_<scalar_< unspecified_<A0> > >))
                              ((array_< scalar_< integer_<State> >, N>))
                            , identity
                            )

  // An assignment table expression is ran by running it for every position
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(S0)
                            , ((expr_<table_< unspecified_<A0>, S0 >, nt2::container::domain, nt2::tag::assign_>))
                            )
  {
    typedef typename boost::dispatch::meta::
    terminal_of< typename boost::dispatch::meta::
                 semantic_of<A0>::type
               >::type                                     result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(A0 const& a0) const
    {
      for_each(base_indices(a0), extent(a0), call_compute<A0 const&>(a0));
      return lhs_terminal()(a0);
    }
  };

  // Another table expression is ran by reducing it to an assignment
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(S0)
                            , ((ast_<table_< unspecified_<A0>, S0 > >))
                            )
  {
    typedef typename boost::
    remove_reference< typename boost::dispatch::meta::
                      terminal_of< typename boost::dispatch::meta::
                                   semantic_of<A0>::type
                                 >::type
                    >::type                                result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(A0 const& a0) const
    {
      result_type tmp;
      run(assign(tmp, a0));
      return tmp;
    }
  };

} }

int main()
{
  using nt2::container::table;

  table<double, nt2::of_size_<5, 10> > a, b, c;

  std::cout << "a = " << (void*)&a << std::endl;
  std::cout << "b = " << (void*)&b << std::endl;
  std::cout << "c = " << (void*)&c << std::endl;

  a = b + 1.;
#if 1
  a = b + c*c/a;
  std::cout << std::endl;
  b += c;
  std::cout << std::endl;
  c += -a;
  std::cout << std::endl;
#endif
  /* c(a) += a; // function undefined
  c(a) = b(c) + c(a)*b(a);*/
}

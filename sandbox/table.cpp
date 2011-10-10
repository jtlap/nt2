#include <nt2/core/container/dsl.hpp>
#include <nt2/core/container/category.hpp>
#include <nt2/core/settings/size.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/details/type_id.hpp>
#include <nt2/include/functions/run.hpp>
#include <iostream>
#include <boost/proto/debug.hpp>
#include <boost/dispatch/dsl/category.hpp>

#include <nt2/toolbox/operator/functions.hpp>

template<class T>
struct block
{
  boost::array<T, 4096> data;
};

namespace nt2 { namespace container
{
    
template<class Block>
struct table_container
{
    Block block;
};

template<class T>
struct is_container< table_container<T> >
  : boost::mpl::true_
{
};

} }

namespace boost { namespace dispatch { namespace meta
{
  template<class T>
  struct value_of< nt2::container::table_container<T> >
  {
    typedef T type;
  };
    
  template<class T>
  struct value_of< ::block<T> >
  {
    typedef T type;
  };
    
  template<class T, class Origin>
  struct hierarchy_of< nt2::container::table_container<T>, Origin >
  {
    typedef table_< typename property_of<typename value_of<T>::type, Origin>::type, int > type;
  };
    
} } }

namespace nt2 { namespace container
{

template<class T, class S>
struct make_block
{
  typedef ::block<T> type;
};

template<class T, class S>
struct table 
: expression< typename boost::proto::terminal< table_container< typename make_block<T, S>::type > >::type
            , table_container< typename make_block<T, S>::type >&
            >
{
  typedef
  expression< typename boost::proto::terminal< table_container< typename make_block<T, S>::type > >::type
            , table_container< typename make_block<T, S>::type >&
            > parent;
  
  table() {}

  template<class Xpr,class Result> 
  BOOST_DISPATCH_FORCE_INLINE 
  table(expression<Xpr,Result> const& xpr) { static_cast<parent&>(*this) = xpr; }
};

} }

namespace boost { namespace dispatch { namespace meta
{
  template<class T, class S>
  struct semantic_of<nt2::container::table<T, S> >
    : semantic_of<typename nt2::container::table<T, S>::parent>
  {
  };
} } }

namespace nt2 { namespace ext
{
  // Functions for logical type deduction 
  // - need to deal with bool
  // - need to take care of case where first operand is not a table
  // - should fill in size correctly
  #define M1(z,n,t) (A##n)
  #define M2(z,n,t) generic_<unspecified_<A##n> >
  #define M3(z,n,t) (generic_< unspecified_<A##n> >)
  #define M4(z,n,t) typedef typename meta::scalar_of<_A##n>::type s##n;
  
  #define M0(z,n,t)                                                                                \
  NT2_FUNCTOR_IMPLEMENTATION_IF(boost::simd::tag::map_, tag::cpu_                                  \
                            , (F)BOOST_PP_REPEAT(n, M1, ~)                                         \
                            , (any< nt2::container::is_container<boost::mpl::_>                    \
                                  , BOOST_PP_ENUM_PARAMS(n, A)                                     \
                                  >                                                                \
                              )                                                                    \
                            , (boost::simd::tag::map_(unspecified_<F>, BOOST_PP_ENUM(n, M2, ~)))   \
                            , (unspecified_<F>)BOOST_PP_REPEAT(n, M3, ~)                           \
                            )                                                                      \
  {                                                                                                \
    template<class Sig>                                                                            \
    struct result;                                                                                 \
                                                                                                   \
    template<class This, class F_, BOOST_PP_ENUM_PARAMS(n, class _A)>                              \
    struct result<This(F_, BOOST_PP_ENUM_PARAMS(n, _A))>                                           \
    {                                                                                              \
        BOOST_PP_REPEAT(n, M4, ~)                                                                  \
        typedef typename meta::result_of<F_(BOOST_PP_ENUM_PARAMS(n, s))>::type stype;              \
        typedef typename meta::factory_of<_A0>::type factory;                                      \
        typedef typename factory::template apply<stype>::type type;                                \
    };                                                                                             \
                                                                                                   \
    template<BOOST_PP_ENUM_PARAMS(n, class _A)>                                                    \
    typename result<implement(F const&, BOOST_PP_ENUM_BINARY_PARAMS(n, _A, & BOOST_PP_INTERCEPT))>::type \
    operator()(F const&, BOOST_PP_ENUM_BINARY_PARAMS(n, _A, & BOOST_PP_INTERCEPT)) const;          \
  };
  
  BOOST_PP_REPEAT_FROM_TO(1, BOOST_DISPATCH_MAX_ARITY, M0, ~)
  
  #undef M0
  #undef M1
  #undef M2
  #undef M3
  #undef M4
} }

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
    boost::array<std::size_t, 1> sizes(T const&) { boost::array<std::size_t, 1> sz = { 4 }; return sz; }
    
    template<class T>
    boost::array<std::size_t, 1> base_indices(T const&) { boost::array<std::size_t, 1> sz = { 1 }; return sz; }
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
      boost::proto::when< boost::proto::terminal< boost::proto::_ >, boost::proto::_value >
    , boost::proto::when< boost::proto::nary_expr< boost::proto::_ >, lhs_terminal ( boost::proto::_child0 ) >
    >
{
};

#include <boost/dispatch/meta/identity.hpp>

namespace nt2 { namespace ext
{
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
             >::type                                       result_type;
    
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
    semantic_of<A0>::type                                   result_type;
    
    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(A0 const& a0) const
    {
      for_each(base_indices(a0), sizes(a0), call_compute<A0 const&>(a0));
      return lhs_terminal()(a0);
    }
  };
  
  // Another table expression is ran by reducing it to an assignment
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(S0)
                            , ((ast_<table_< unspecified_<A0>, S0 > >))
                            )
  {
    typedef typename boost::dispatch::meta::
    semantic_of<A0>::type                                   result_type;
    
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
    
  table<double> a, b, c;
  a = b;
#if 1
  a = b + c*c/a;
  b += c;
#endif
  //c += !a; // problem with bool
  /*c(a) += a; // function undefined
  c(a) = b(c) + c(a)*b(a);*/
}

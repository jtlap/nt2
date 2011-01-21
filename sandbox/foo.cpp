#include <iostream>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/min_max.hpp>
#include <boost/proto/core.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/context.hpp>
#include <boost/proto/transform.hpp>
namespace mpl = boost::mpl;
namespace proto = boost::proto;
using proto::_;

// Will be used to define the placeholders _1 and _2
template<typename I> struct placeholder : I {};

// This grammar basically says that a calculator expression is one of:
//   - A placeholder terminal
//   - Some other terminal
//   - Some non-terminal whose children are calculator expressions
// In addition, it has transforms that say how to calculate the
// expression arity for each of the three cases.
struct CalculatorGrammar
  : proto::or_<

        // placeholders have a non-zero arity ...
        proto::when< proto::terminal< placeholder<_> >, proto::_value >

        // Any other terminals have arity 0 ...
      , proto::when< proto::terminal<_>, mpl::int_<0>() >
        // For any non-terminals, find the arity of the children and
        // take the maximum. This is recursive.
      , proto::when< proto::nary_expr<_, proto::vararg<_> >
             , proto::fold<_, mpl::int_<0>(), mpl::max<CalculatorGrammar, proto::_state>() > >

    >
{};

// Simple wrapper for calculating a calculator expression's arity.
// It specifies mpl::int_<0> as the initial state. The data, which
// is not used, is mpl::void_.
template<typename Expr>
struct calculator_arity
  : boost::result_of<CalculatorGrammar(Expr, mpl::int_<0>, mpl::void_)>
{};

// For expressions in the calculator domain, operator ()
// will be special; it will evaluate the expression.
struct calculator_domain;
struct numeric_domain;

// Wrap all calculator expressions in this type, which defines
// operator () to evaluate the expression.
template<typename Expr>
struct calculator_expression
  : proto::extends<Expr, calculator_expression<Expr>, calculator_domain>
{
    typedef
        proto::extends<Expr, calculator_expression<Expr>, calculator_domain>
    base_type;

    explicit calculator_expression(Expr const &expr = Expr())
      : base_type(expr)
    {}

    BOOST_PROTO_EXTENDS_USING_ASSIGN(calculator_expression)
};

// Tell proto how to generate expressions in the calculator_domain
struct numeric_domain
    : proto::domain<proto::generator<calculator_expression> >
  {};
struct calculator_domain
  : proto::domain<proto::generator<calculator_expression>, _, numeric_domain >
{};

// Define some placeholders (notice they're wrapped in calculator_expression<>)
calculator_expression<proto::terminal< placeholder< mpl::int_<1> > >::type> const _p1;
calculator_expression<proto::terminal< placeholder< mpl::int_<2> > >::type> const _p2;
calculator_expression<proto::terminal< float >::type> const _pf;
calculator_expression<proto::terminal< unsigned short >::type> const _pus;
calculator_expression<proto::terminal< bool >::type> const _pb;




#include <nt2/sdk/details/type_id.hpp>
#include <nt2/sdk/functor/operators.hpp>

namespace nt2 { namespace tag
{
  struct expr_ {};
} }

namespace nt2 { namespace meta
{
  template<class T,class Domain>
  struct expr_ : expr_<T,typename Domain::parent>
  {
    typedef expr_<T,typename Domain::parent> parent;
    typedef tag::expr_      type(typename Domain::type);
  };

  template<class T,class Domain>
  struct expr_<T,unspecified_<Domain> > : unspecified_<T>
  {
    typedef unspecified_<T> parent;
    typedef tag::expr_      type(typename unspecified_<Domain>::type);
  };

  template<class T>
  struct domain_ : domain_<typename T::proto_super_domain>
  {
    typedef domain_<typename T::proto_super_domain> parent;
    typedef T      type;
  };

  template<>
  struct  domain_<boost::proto::detail::not_a_domain>
        : unspecified_<boost::proto::detail::not_a_domain>
  {
    typedef unspecified_<boost::proto::detail::not_a_domain> parent;
    typedef boost::proto::detail::not_a_domain      type;
  };
} }

namespace nt2 { namespace details
{
  template<class T>
  struct hierarchy_of < T
                      , typename T::proto_is_expr_
                      >
  {
    typedef typename boost::proto::domain_of<T>::type domain_type;
    typedef meta::expr_<T, typename meta::hierarchy_of<domain_type>::type> type;
  };


  template<class T>
  struct hierarchy_of < T
                      , typename T::proto_is_domain_
                      >
  {
    typedef meta::domain_<T> type;
  };

} }


template<class X> void
tag_from(X const& )
{
  std::cout << nt2::type_id<typename X::type>() << "\n";
  tag_from(typename X::parent());
}

template<class X> void
tag_from(nt2::meta::unknown_<X> const& )
{
  std::cout << ".\n\n";
}

template<class X> void
info(X const& x)
{
  tag_from(typename nt2::meta::hierarchy_of<X>::type() );
}

int main()
{
  // terminals
  info(_p1);
  info(_pf);
  info(_pus);
  info(_pb);

  // unary node
  info(-_p1);
  info(+_pf);
  info(!_pus);
  info(~_pb);

  info(-!-+_pb);

  info(_pb+_pb);

  info(_pus + _pus + _pus + _pus + _pus
            + _pus * _pus + _pus + _pus
            + _pus - _pus + !!!_pus
      );
  return 0;
}

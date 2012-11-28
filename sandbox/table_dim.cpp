#include <iostream>
#include <typeinfo>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/min_max.hpp>
#include <boost/proto/core.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/context.hpp>
#include <boost/proto/transform.hpp>
#include <nt2/sdk/details/type_id.hpp>

namespace mpl = boost::mpl;
namespace proto = boost::proto;
using proto::_;

template<class N, template<typename,typename> class Extends>
struct table_generator
{
	template<typename Sig>
	struct result;
	
	template<typename This, typename Expr>
	struct result<This(Expr)>
	{
		typedef Extends<N,Expr> type;
	};
	
	template<typename This, typename Expr>
	struct result<This(Expr &)>
	{
		typedef Extends<N,Expr> type;
	};
	
	template<typename This, typename Expr>
	struct result<This(Expr const &)>
	{
		typedef Extends<N,Expr> type;
	};
	
	/// \param expr A Proto expression
	/// \return Extends<Expr>(expr)
	template<typename Expr>
	Extends<N,Expr> operator ()(Expr const &e) const
	{
		return Extends<N,Expr>(e);
	}
};

struct tables_domain;
template<class  N> struct table_domain;
struct matrix_domain;
struct vector_domain; 

template<typename Expr>
struct tables_expression
: proto::extends<Expr, tables_expression<Expr>, tables_domain>
{
	typedef
	proto::extends<Expr, tables_expression<Expr>, tables_domain>
	base_type;
	
	explicit tables_expression(Expr const &expr = Expr())
	: base_type(expr)
	{}
};


template<class N,typename Expr>
struct table_expression
: proto::extends<Expr, table_expression<N,Expr>, table_domain<N> >
{
	typedef
	proto::extends<Expr, table_expression<N,Expr>, table_domain<N> >
	base_type;
	
	explicit table_expression(Expr const &expr = Expr())
	: base_type(expr)
	{}
};


template<typename Expr>
struct matrix_expression
: proto::extends<Expr, matrix_expression<Expr>, matrix_domain>
{
	typedef
	proto::extends<Expr, matrix_expression<Expr>, matrix_domain>
	base_type;
	
	explicit matrix_expression(Expr const &expr = Expr())
	: base_type(expr)
	{}
};

template<typename Expr>
struct vector_expression
: proto::extends<Expr, vector_expression<Expr>, vector_domain>
{
	typedef
	proto::extends<Expr, vector_expression<Expr>, vector_domain>
	base_type;
	
	explicit vector_expression(Expr const &expr = Expr())
	: base_type(expr)
	{}
};

struct tables_domain : proto::domain<proto::generator<tables_expression>, _ > {};

template<class N>
struct table_domain 
: proto::domain<table_generator<N,table_expression>, _, table_domain< boost::mpl::int_<1+N::value> > > {};

template<>
struct table_domain< boost::mpl::int_<4> > 
: proto::domain<table_generator< boost::mpl::int_<4> ,table_expression>, _, tables_domain > {};

struct matrix_domain 
: proto::domain<proto::generator<matrix_expression>, _, table_domain<boost::mpl::int_<2> > > {};

struct vector_domain 
: proto::domain<proto::generator<vector_expression>, _, table_domain<boost::mpl::int_<1> > > {};


template<int N>
typename boost::proto::result_of
::make_expr< boost::proto::tag::terminal
, table_domain<boost::mpl::int_<N> >
, int const

>::type
make_table()
{
	return	boost::proto::
	make_expr<boost::proto::tag::terminal,table_domain<boost::mpl::int_<N> > >(N);
}

boost::proto::result_of
::make_expr< boost::proto::tag::terminal
, matrix_domain
, int const

>::type
make_matrix()
{
	return	boost::proto::
	make_expr<boost::proto::tag::terminal,matrix_domain >(20);
}

boost::proto::result_of
::make_expr< boost::proto::tag::terminal
, vector_domain
, int const

>::type
make_vector()
{
	return	boost::proto::
	make_expr<boost::proto::tag::terminal,vector_domain >(10);
}

template<class X> void
type_from(X const& )
{
  std::cout << nt2::type_id<typename boost::proto::domain_of<X>::type >() << "\n";
}

int main()
{
	type_from(make_table<1>()+make_table<2>());
	type_from(make_table<1>() + make_table<1>());
	type_from(make_vector()+make_vector());
  type_from(make_matrix()+make_matrix());
  type_from(make_vector()+make_matrix());
}

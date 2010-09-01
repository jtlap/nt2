
namespace nt2 { namespace $self.tb_name$
{
  template<class Dummy>
  struct call<$self.name$_,scalar_<native_>,Dummy>
  {
    template<class Sig> struct result;
    template<class This,$self.class_list$>
    struct result<This(A0)> : 
      boost::result_of<meta::floating($self.type_list$)>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      $self.arity$,
      A0,
      (2, (real_,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF( $self.arity$, real_)
    {
      return ???;
    }
    NT2_FUNCTOR_CALL_EVAL_IF( $self.arity$, arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE($self.arity$)::type type;
      return $self.name$(type(a0));
    }

  };
} }

#endif

      
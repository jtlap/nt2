
namespace nt2 { namespace $self.tb_name$
{
  template<class Dummy>
  struct call<$self.name$_,tag::scalar_(tag::arithmetic_),Dummy>
  {
    template<class Sig> struct result;

    // see documentation http://nt2.lri.fr/extension/custom_function.html
    // for writing the functor implementation code 
    // with or without type dispatching

  };
} }

#endif

      
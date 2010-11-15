

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is fundamental_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<group_,tag::scalar_(tag::arithmetic_),fundamental_,Info> : callable
  {
    typedef bool result_type;


  };
} }

#endif
/// Revised by jt the 15/11/2010

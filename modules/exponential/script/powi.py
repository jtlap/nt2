[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' :['Power function for scalar integer a1: \f${a_0}^{a_1}\f$','\par',
                         '\f$0^0\f$ returns 1'] ,  
         'param_1' : ['must be of scalar integer type'],   
         'arity' : '2',
         'call_types' : ['T', 'iT'],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_floating<T>::type',
            },
         'type_defs' : [],
         'types' : ['real_'],
         'simd_types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 08/12/2010',
             'cover_included' : ['extern "C" { long double cephes_powil(long double,int); }'],
             'notes' : [],
             'stamp' : 'modified by jt the 14/12/2010',
            },
         'ranges' : {
             'real_' : [['T(-10)', 'T(10)'], ['T(-10)', 'T(10)']],
             'signed_int_' : [['-100', '100'], ['-100', '100']],
             'unsigned_int_' : [['0', '100'], ['0', '100']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'nt2::Inf<T>(),3' : 'nt2::Inf<r_t>()',
                 'nt2::Minf<T>(),3' : 'nt2::Minf<r_t>()',
                 'nt2::Mone<T>(),3' : 'nt2::Mone<r_t>()',
                 'nt2::Nan<T>(),3' : 'nt2::Nan<r_t>()',
                 'nt2::One<T>(),3' : 'nt2::One<r_t>()',
                 'nt2::Zero<T>(),3' : 'nt2::Zero<r_t>()',
                 'nt2::Inf<T>(),4' : 'nt2::Inf<r_t>()',
                 'nt2::Minf<T>(),4' : 'nt2::Inf<r_t>()',
                 'nt2::Mone<T>(),4' : 'nt2::One<r_t>()',
                 'nt2::Nan<T>(),4' : 'nt2::Nan<r_t>()',
                 'nt2::One<T>(),4' : 'nt2::One<r_t>()',
                 'nt2::Zero<T>(),4' : 'nt2::Zero<r_t>()',
                },
             'signed_int_' : {
                 'nt2::Mone<T>(),3' : 'nt2::Mone<r_t>()',
                 'nt2::One<T>(),3' : 'nt2::One<r_t>()',
                 'nt2::Zero<T>(),3' : 'nt2::Zero<r_t>()',
                 'nt2::Mone<T>(),4' : 'nt2::One<r_t>()',
                 'nt2::One<T>(),4' : 'nt2::One<r_t>()',
                 'nt2::Zero<T>(),4' : 'nt2::Zero<r_t>()',
                },
             'unsigned_int_' : {
                 'nt2::One<T>(),3' : 'nt2::One<r_t>()',
                 'nt2::Zero<T>(),3' : 'nt2::Zero<r_t>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : [],
                 'real_' : ['nt2::powi(a0,a1)', 'nt2::powi(a0,nt2::Two<iT>())', 'nt2::powi(a0,nt2::Three<iT>())'],
                },
             'property_value' : {
                 'default' : [],
                 'real_' : ['cephes_powil(a0,a1)', 'nt2::sqr(a0)', 'a0*nt2::sqr(a0)'],
                },
             'ulp_thresh' : {
                 'default' : ['2','2', '2'],
                },
            },
        },
     'version' : '0.1',
    },
]

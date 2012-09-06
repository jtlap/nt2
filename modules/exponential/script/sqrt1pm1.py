[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' :['\\\\f$\sqrt{1+a_0}-1\\\\f$','\par',
                         'result is accurate even for small a0'] ,  
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_floating<T>::type',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 01/12/2010',
             'cover_included' : [],
             'notes' : [],
             'stamp' : 'modified by jt the 13/12/2010',
            },
         'ranges' : {
             'real_' : [['T(-10)', 'T(10)']],
             'signed_int_' : [['-100', '100']],
             'unsigned_int_' : [['0', '100']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'nt2::Inf<T>()' : 'nt2::Inf<r_t>()',
                 'nt2::Minf<T>()' : 'nt2::Nan<r_t>()',
                 'nt2::Mone<T>()' : 'nt2::Mone<r_t>()',
                 'nt2::Nan<T>()' : 'nt2::Nan<r_t>()',
                 'nt2::One<T>()' : ['nt2::Sqrt_2<r_t>()-nt2::One<r_t>()', '2'],
                 'nt2::Zero<T>()' : 'nt2::Zero<r_t>()',
                },
             'signed_int_' : {
                 'nt2::Mone<T>()' : 'nt2::Mone<r_t>()',
                 'nt2::One<T>()' : ['nt2::Sqrt_2<r_t>()-nt2::One<r_t>()', '2'],
                 'nt2::Zero<T>()' : 'nt2::Zero<r_t>()',
                },
             'unsigned_int_' : {
                 'nt2::One<T>()' : ['nt2::Sqrt_2<r_t>()-nt2::One<r_t>()', '2'],
                 'nt2::Zero<T>()' : 'nt2::Zero<r_t>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::sqrt1pm1(a0)'],
                },
             'property_value' : {
                 'default' : ['nt2::sqrt1pm1(a0)'],
                },
             'ulp_thresh' : {
                 'default' : ['2'],
                },
            },
        },
     'version' : '0.1',
    },
]

[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::common_type<T,T>::type',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_', 'signed_int_', 'unsigned_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 28/11/2010',
             'included' : [],
             'notes' : [],
             'stamp' : 'modified by jt the 13/12/2010',
            },
         'ranges' : {
             'default' : [['nt2::Valmin<T>()/2', 'nt2::Valmax<T>()/2'], ['nt2::Valmin<T>()', 'nt2::Valmax<T>()']],
             'double' : [['-10.0', '10.0'], ['-10.0', '10.0']],
             'float' : [['-10.0f', '10.0f'], ['-10.0f', '10.0f']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'nt2::Inf<T>()' : 'nt2::Nan<T>()',
                 'nt2::Inf<T>(),nt2::Minf<T>()' : 'nt2::Inf<T>()',     
                 'nt2::Minf<T>()' : 'nt2::Nan<T>()',
                 'nt2::Mone<T>()' : 'nt2::Zero<T>()',
                 'nt2::Nan<T>()' : 'nt2::Nan<T>()',
                 'nt2::One<T>()' : 'nt2::Zero<T>()',
                 'nt2::One<T>(),nt2::Two<T>()' : 'nt2::One<T>()',
                 'nt2::Two<T>(),nt2::One<T>()' : 'nt2::One<T>()',
                 'nt2::Zero<T>()' : 'nt2::Zero<T>()',
                },
             'signed_int_' : {
                 'nt2::Mone<T>()' : 'nt2::Zero<T>()',
                 'nt2::One<T>()' : 'nt2::Zero<T>()',
                 'nt2::Zero<T>()' : 'nt2::Zero<T>()',
                 'nt2::One<T>(),nt2::Two<T>()' : 'nt2::One<T>()',
                 'nt2::Two<T>(),nt2::One<T>()' : 'nt2::One<T>()',
                },
             'unsigned_int_' : {
                 'nt2::One<T>()' : 'nt2::Zero<T>()',
                 'nt2::Zero<T>()' : 'nt2::Zero<T>()',
                 'nt2::One<T>(),nt2::Two<T>()' : 'nt2::One<T>()',
                 'nt2::Two<T>(),nt2::One<T>()' : 'nt2::One<T>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::dist(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['a0>a1 ? a0-a1 : a1-a0'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]

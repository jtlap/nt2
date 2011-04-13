[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0', 
         'rturn' : {
             'default' : 'bool',
            },
         'special' : ['predicate'],
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 01/12/2010',
             'included' : [],
             'notes' : [],
             'stamp' : 'modified by jt the 13/12/2010',
            },
         'ranges' : {
             'real_' : [['T(-10)', 'T(10)'], ['T(-10)', 'T(10)']],
             'signed_int_' : [['-100', '100'], ['-100', '100']],
             'default' : [['0', '100'], ['0', '100']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'T(0),T(1)' : 'true',
                 'T(3),T(0)' : 'true',
                 'nt2::Inf<T>()' : 'false',
                 'nt2::Minf<T>()' : 'false',
                 'nt2::Mone<T>()' : 'false',
                 'nt2::Nan<T>()' : 'false',
                 'nt2::One<T>()' : 'false',
                 'nt2::Zero<T>()' : 'false',
                },
             'signed_int_' : {
                 'nt2::Mone<T>()' : 'false',
                 'nt2::One<T>()' : 'false',
                 'nt2::Zero<T>()' : 'false',
                },
             'unsigned_int_' : {
                 'nt2::One<T>()' : 'false',
                 'nt2::Zero<T>()' : 'false',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::logical_xor(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['(a0!=0)^(a1!=0)'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]

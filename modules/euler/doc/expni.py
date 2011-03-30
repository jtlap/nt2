[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : ['iT', 'T'],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'type_defs' : [],
         'types' : ['real_'],
         'simd_types' : ['real_']   
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 08/12/2010',
             'included' : [],
             'notes' : [],
             'stamp' : 'modified by jt the 14/12/2010',
            },
         'ranges' : {
             'real_' : [['T(-10)', 'T(10)'], ['T(-10)', 'T(10)']],
             'signed_int_' : [['-100', '100'], ['-100', '100']],
             'unsigned_int_' : [['0', '100'], ['0', '100']],
            },
         'specific_values' : {
             'real_' : {
                 '1,nt2::Inf<T>()' : 'nt2::Zero<r_t>()',
                 '1,nt2::Minf<T>()' : 'nt2::Nan<r_t>()',
                 '1,nt2::Mone<T>()' : 'nt2::Nan<r_t>()',
                 '1,nt2::Nan<T>()' : 'nt2::Nan<r_t>()',
                 '1,nt2::Zero<T>()' : 'nt2::Inf<r_t>()',
                },
            },
          'verif_test' : {
             'property_call' : {
                 'default' : [],
                 'real_' : ['nt2::expni(a0,a1)'],
                },
             'property_value' : {
                 'default' : [],
                 'real_' : ['nt2::expni(a0,a1)'],
                },
             'ulp_thresh' : {
                 'real_' : ['10'],
                },
            },
         },
     'version' : '0.1',
    },
]

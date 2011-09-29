[ ## this file was manually modified by jt
    {
     'functor' : {
            'description' :['exponential integral function','\par Formula',
                            '\\\\f[ E_a_0(a_1)=\int_0^\infty \frac{e^{-a_1t)}{t^a_0}dt\\\\f]'],
            'param_0': ['must be scalar integer'],
            'param_1': ['must be non negative'],
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
             'included' : ['extern "C" double cephes_expn(int,double);'],
             'notes' : [],
             'stamp' : 'modified by jt the 14/12/2010',
            },
         'ranges' : {
             'real_' : [['iT(0)', 'iT(10)'], ['T(0)', 'T(10)']],
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
                 'real_' : ['cephes_expn(a0,a1)'],
                },
             'ulp_thresh' : {
                 'real_' : ['10'],
                },
            },
         },
     'version' : '0.1',
    },
]

[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['digamma function'
                          '\par Formula',
                          '\\\\f[\Psi(a_0) = \\\\frac{\Gamma^\prime(a_0)}{\Gamma(a_0}\\\\f]',
                             ],
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_floating<T>::type',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 22/02/2011',
             'included' : [],
             'notes' : [],
             'stamp' : 'modified by jt the 22/02/2011',
            },
         'ranges' : {
             'real_' : [['T(1)', 'T(2)']],
            },
         'specific_values' : {
             'real_' : {
                 'nt2::One<T>()' : {'result' : 'T(-0.57721566490153286555)','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'default' : ['nt2::digamma(a0)'],
                },
             'property_value' : {
                 'default' : ['nt2::digamma(a0)'],
                },
             'ulp_thresh' : {
                 'default' : ['0.5'],
                },
            },
        },
    },
]

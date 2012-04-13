[ ## this file was manually modified by jt
    {
     'functor' : {
            'description' :['Stirling formula for the gamma function','\par Formula',
                            '\\\\f[\Gamma(a_0) \\\\approx \sqrt{2 \pi} a_0^{a_0-\\\\frac12} e^{-a_0} ( 1 + \\\\frac1{a_0} P(\\\\frac1{a_0}))\\\\f]',
                            'Where P is a polynomial.','\par'
                            'The formula implementation is usable for a0 between 33 and 172, according cephes'],
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
             'default' : [['nt2::Valmin<T>()', 'nt2::Valmax<T>()']],
             'real_' : [['T(-100)', 'T(100)']],
             'signed_int_' : [],
             'unsigned_int_' : [],
            },
         'specific_values' : {
             'real_' : {
                },
            },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'default' : ['nt2::stirling(a0)'],
                },
             'property_value' : {
                 'default' : ['nt2::stirling(a0)'],
                },
             'ulp_thresh' : {
                 'default' : ['0.5'],
                },
            },
        },
    },
]

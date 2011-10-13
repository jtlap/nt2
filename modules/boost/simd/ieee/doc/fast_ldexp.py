[ ## this file was manually modified by jt
    {
     'functor' : {
          'description' : ["The function multiply a floating entry \f$a_0\f$",
                          "by \f$2^a_1\f$",'\par',
                          "The fast prefix indicates that for speed sake",
                          "the result may be incorrect for limiting values:",
                          "inf, -inf nan and zero that deserve special treatment."
                          "If you are not sure use \c ldexp, at the expense",
                          "of some more machine cycles."],
        'module' : 'boost',
         'arity' : '2',
         'call_types' : ['T', 'iT'],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : ['real_'],
         'type_defs' : ['typedef typename boost::dispatch::meta::as_integer<T>::type iT;'],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 04/12/2010',
             'included' : [],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 12/12/2010',
            },
         'ranges' : {
             'real_' : [['T(-10)', 'T(10)'], ['iT(-10)', 'iT(10)']],
            },
         'specific_values' : {
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::fast_ldexp(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['(a1>=0) ? a0*(1<<a1) : a0/(1<<(-a1))'],
                },
             'ulp_thresh' : '0',
            },
        },
     'version' : '0.1',
    },
]

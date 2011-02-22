[  ## list of dictionnaries for different arities of the same functor
{
    'functor' : {      ## intrinsics values related to ellint_1
            'arity'      : '2',  ## functor number of parameters
            'ret_arity'  : '0',            ## must be '0' or omitted or None if not a tuple 
            'types'      : [ 'real_' ],  ## list of types for which a specific test will be generated
            'rturn'      : {'default': 'typename boost::result_of<nt2::meta::floating(T)>::type'},  ## dictionnary of calls return types for each of <types>
            'call_types' : [  ],  ## list of types for one call [] default to 'T'
            'type_defs'  : [  ],  ## list of additional typedef needed (for examples for <call_types>,
    },
    'unit'    : { ## informations for creating unit tests
        'global_header' : { ## properties needed to construct header of ellint_1.cpp
            'first_stamp' : 'created  by jt the 21/02/2011', ## creation stamp
            'stamp'       : 'modified by jt the 21/02/2011', ## modification stamp
            'included' : ['extern "C" {long double cephes_elliel(long double,long double);}',
                           '#include <nt2/toolbox/trigonometric/include/constants.hpp>'],
                           'notes'       : [],   ## list of strings that will be included in a global comment
        },
        'specific_values' : { ## parameters/values pairs to be asserted
                              ## one parameter (no commas) is replicated else use comma separated string
                              ## a specific ulp for a value can be introduced in the string result after a comma
                              ## or in a dictionnary {'result' : '...','ulp_thresh','...'}
            'real_'       : {
               'nt2::Pio_2<T>(),0' :  {'result' : 'nt2::Pio_2<r_t>()' ,'ulp_thresh':'0'},
               'nt2::One<T>(),0' :  {'result' : 'nt2::One<r_t>()' ,'ulp_thresh':'0'},
               'nt2::Zero<T>(),0':  {'result' : 'nt2::Zero<r_t>()','ulp_thresh':'0'},
           },    
        },
        'ranges' :  { ## test ranges
            'default'       : [['nt2::Valmin<T>()', 'nt2::Valmax<T>()']], 
            'real_'         : [['T(-10)','T(10)'],['T(0)','T(1)']],   
            'signed_int_'   : [],
            'unsigned_int_' : [],        
        },
        'verif_test' : { ## assert result of property call equal to property values
                         ## up to ulp_threshold (0 means strict equality) for random
                         ## values uniformly distributed in ranges
            'property_call' : { 'default' :  ['nt2::ellie(a0,a1)'], },
            'property_value' :{ 'default' :  ['::cephes_elliel(a0,a1)'], },
            'ulp_thresh'     :{ 'default' :   ['1.0'], }, 
            'nb_rand'        :{ 'default' : 'NT2_NB_RANDOM_TEST' },  ## number of generated tests 
        },
    },
},
]

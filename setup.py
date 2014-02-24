from distutils.core import setup, Extension

skein_hash_module = Extension('skein_hash',
                               sources = ['skeinmodule.c',
                                          'skein.c',
										  'sha3/skein.c'],
                               include_dirs=['.', './sha3'])

setup (name = 'skein_hash',
       version = '1.0',
       description = 'Bindings for skein proof of work used by Skeincoin',
       ext_modules = [skein_hash_module])

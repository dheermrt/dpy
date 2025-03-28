from setuptools import setup, Extension
module =Extension(
    "array_module",
    sources=['arraymodule.c']
)
setup( 
    name="array_module",
    ext_modules=[module]

)


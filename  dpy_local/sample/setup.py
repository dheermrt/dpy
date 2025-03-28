from setuptools import setup, Extension

module= Extension(
    "add_module",
    sources=["samplemodule.c"]


)
setup(
    name="add_module",
    ext_modules=[module]
)

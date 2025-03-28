from setuptools import setup, Extension
module=Extension("dpy",
                 sources=["array_add.c"])
setup(
    name="dpy",
    ext_modules=[module]
)
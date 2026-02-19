from setuptools import setup, Extension
import pybind11

ext_modules = [
    Extension(
        "calculus.calculus_core",
        ["calculus_core.cpp"],
        include_dirs=[pybind11.get_include()],
        language="c++",
        extra_compile_args=["/O2"]
    )
]

setup(
    name="calculus",
    version="0.1.0",
    packages=["calculus"],
    ext_modules=ext_modules,
)

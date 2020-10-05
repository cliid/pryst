from setuptools import setup, find_packages

setup(
    name='Pryst Language',
    version='0.1',
    author='Jiwu Jang',
    author_email='cliid@gmail.com',
    description='Pryst is an explicit, weak, static typed, Rust-like language with a beautiful syntax.',
    classifiers=[
        "Development Status :: 1 - Pre",
        'Intended Audience :: Developers',
        'Programming Language :: Python :: 3.8',
    ],
    install_requires=['setuptools-git'],
    include_package_data=True,
    packages=find_packages(),
    entry_points={
        'console_scripts': ['pryst = pryst.prystapp:main']
    },
    test_suite='pryst.run_tests.get_suite',

)

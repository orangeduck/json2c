from setuptools import setup

setup(
    name='json2c',
    version='0.9',
    description='Convert JSON to C data literals',
    author='Daniel Holden',
    author_email='contact@theorangeduck.com',
    license='BSD',
    url='https://github.com/orangeduck/json2c',
    py_modules=['json2c'],
    entry_points = {'console_scripts': ['json2c = json2c:main']}
)
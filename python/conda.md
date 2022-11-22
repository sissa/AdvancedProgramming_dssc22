### conda

the best way to install Python and manage the environments is using `conda`. You can choose between `anaconda` and `miniconda`, the latter being preferable as it's much smaller (doesn't install much by default).

For windows, look for "anaconda prompt". 

Once installed, to make sure you have the latest version, run

```
conda update conda`
```

To create an environment, do:

```
conda create --name my_new_env
```

To activate:

```
conda activate my_new_env
```

To install packages (for example, numpy):

```
conda install numpy
```

To see what you have installed:

```
conda list
```

To deactivate an environment:

```
conda deactivate
```

To view all the environments:

```
conda env list
```








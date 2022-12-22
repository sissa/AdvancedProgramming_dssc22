### One of the C++ options for doing what pandas does: DataFrame library

here is [a link](https://github.com/hosseinmoein/DataFrame) for repository.

We won't do real exercise with this, as you will only need it if you actually work on something that becomes slow, but I would like you to at least install the library and try to understand it's "hello world", so that you could come back to it if needed for work.

Clone the repository, go into the folder, then run

```
mkdir Release #create a folder
cd [Debug | Release]
cmake -DCMAKE_BUILD_TYPE=Release -DHMDF_BENCHMARKS=1 -DHMDF_EXAMPLES=1 -DHMDF_TESTING=1 .. #don't forget those ..
make
make install

```

Now, if you go to DataFrame/examples folder, you should be able to compile the hello world example with

```
g++ -o hello_dataframe.x -std=c++17 hello_world.cc -lDataFrame
```

If it starts complaining about the missing includes, then something went wrong at the installation stage, you might have to see where it got actually installed and compile with `-I/PATH_TO_HEADERS -L/PATH_TO_LIBRARY`.

However, this hello world example was supposed to be run from the root folder, so before you can use it, fix the path to the data-files it's trying to open (you will see an error opening files, find those paths in code fix them, then recompile).








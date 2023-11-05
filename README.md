# list-random

## ** Note this project was created, to help me learn c++. There are better tools out there that can do similar things. **

### Description
This program accepts a file or piped input, and outputs a random sample of the input where each element is split by line.

### Instalation
Example compilation:
```bash
g++ list-random.cpp -o list-random
```
Add to folder in path for full instalation.

### Usage
Can accept a piped input or a file with -f. Defaults to a sample size of 1 if not specified through -c. Note that this does not work with large files.

#### Examples
Get a sample of 10 elements from file and output to new file.
```bash
list-random -f dataset.csv -c 10 > sample.csv
```

Sample from file with random seed
```bash
list-random -f dataset.csv -c 10 -s 12345
```

Sample of 50 from csv ignoring the header row and outputing to a new file.
```bash
tail -n +2 dataset.csv | list-random -c 50 > sample.csv
```

Get a random file/directory from current directory.
```bash
ls | list-random
```



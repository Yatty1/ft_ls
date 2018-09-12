## ft_ls
- Reimplementation of unix command `ls`

#### Allowed functions

- write
- opendir
- readdir
- closedir
- stat
- lstat
- getpwuid
- getgrgid
- malloc
- free
- perror
- strerror
- exit
- listxattr
- getxattr
- readlink
- time
- ctime

#### Requirement

- `-r` `-l` `-a` `-R` `-t` flags
- basic `ls` functions

- `-a` : Include directory entries whose names begin with a dot (.).
- `-l` : List in long format. If the output is to a terminal, a total sum for all the file sizes is output on a line before the long listing.
- `-r` : Reverse the order of the sort to get reverse lexicographical order or the oldest entries first
- `-R` : Recursively list subdirectroies encountered.
- `-t` : Sort by time modified (most recently modified first) before sorting the operands by lexicographical order.

#### Run

```
$ make
```

#### Usage

```
$ ./ft_ls -G .
```

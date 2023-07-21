# Irvings-algorithm

It is an efficient algorithm to solve the stable roommates problem.

To run the program,
`gcc irving.c -o out`
`./out`

- The first line of input should be the number of members n which has to be even.
- Next n lines contain preference order for roommate for each member.
- Members are numbered from 0 to n-1.
- For example:
6
3 5 1 4 2
5 2 4 0 3
3 4 0 5 1
1 5 4 0 2
3 1 2 5 0
4 0 3 1 2
- The output is the resultant stable matching if it is possible to have one.

Reference: [An efficient algorithm for the “stable roommates” problem](https://doi.org/10.1016/0196-6774(85)90033-1)
factor out test to separate file per test case / suite

Once we end up hardcoding 3 cases, we move to a hash solution for storing the
if-else hierarchy.  Hence TDD ends up triggering the RUle of Three through the
specification of multiple data points.

 He uses `unordered_map` which is somewhat interesting.
`unordered_map` is faster for the many-reads few-write situation.

Now the question becomes, do we need to write test cases for every consonant
we support?
The most important consideration is that we are **test-driving**, not testing.
So we don't need to exhaustively analyze the problem/solution space, as a 
rigorous tester whose goal was to eliminate defects would.  Rather our goal is
to specify enough to get us to a correct solution.

"TDD represents more of a sufficiency mentality" -- You write only as many tests
as you need to get the necessary code and don't write any more.

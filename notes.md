Langr - LOTDD

factor out test to separate file per test case / suite

2017-12-18

Once we end up hardcoding 3 cases, we move to a hash solution for storing the
if-else hierarchy.  Hence TDD ends up triggering the Rule of Three through the
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


2017-12-21

How to answer unknown questions?  Langr suggests to ask the customer, but if not
find an existing similar item and just copy that.
Basically this is handling exceptional, non-happy-path cases

This test will then crash, because it tries to dereference a null pointer.
We solve it by returning an empty string in this case.

You can disable a test by prepending DISABLED_ to the name

    TEST_F(SoundexEncoding, DISABLED_ReplacesMultipleConsonantsWithDigits) {

Then it will ... disable these tests.

He uses `word.front` function, presumably a method on the string?
This returns a reference ot the first character of the string.

2018-01-07

suffix U indicates an unsigned int.
Strings can be iterated over by letter.

Oops, an exception happened.

He introduces the command line argument `--gtest_catch_exceptions=0`
This will cause the test runner to abort when an unhandled exception happens.
We can see std::length_error.
We can see that problem is in zeroPad from reading the gdb trace.
Honestly i don't see what could cause this?  Perhaps a negative length being passed?
Max code length is inited to 4.
Therefore zeroPad will try to create a zero length string I suppose.
How?
actually it overflows!  Because `zerosNeeded` is of type `size_t`

Note that he encounters a case where he needs to demonstrate something
lower-level about the algorithm.  He chooses to just make the method in question
public.  Langr explains that this is a calculated risk based on the idea that
the benefit to the tests justifies the broadening of the interface.

It's worth noting that this code is very distinctive: it's not obvious how to
translate this to any other lang I can think of.

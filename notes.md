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

Note that the string class constants can't be static.

The solution to the first-letter-also-must-collapse-adjacent-duplicates rule is
just to pass the entire string in to the encoding algorithm and lop off the
front afterward.  Quite great, in fact.

He eventually goes for a hybrid approach with some mutating functions, which
is... interesting.

He also has to resort to an index-based for loop.  He also notes that this style
can induce frustration in some readers!  Worth considering.


## ch3 - TDD Foundations

Unit tests take the form: Arrange / Act / Assert.

There's no necessary relation between fixture (test class) and the class under
test.  Some fixtures may test multiple classes.

Each test should produce the smallest meaningful increment possible.

The ideal test has only 3 lines and a single assertion.

It's more important to make sure to test-drive everything than to make sure that you are 100% pure.

Burning the TDD cycle into your brain: red / green / refactor.  Once you no
longer have to think about the cycle, you can focus on code design.

Do NOT write extra code once your test is passing.

Getting green on red: This is when you write a test that you think should fail,
but in fact it passes.
You must ALWAYS observe test failure before continuing!
You can fall into silly errors like running your suite with your new test
accidentally disabled if you don't frequently observe failure.

Alternatively, the system may already contain the behaviour you specified.
Perhaps it's provided transitively as a result of using a third-party component.

Sometimes you have two interfaces to a component that reflect the same internal
state.  For instance, isEmpty() and size() are inextricably linked.  Therefore
if you've updated one, the other will change.  You want to avoid adding these
linked assertions for every test.

There are two "good" approaches that avoid the duplication:

1.  Create a custom assertion in your test framework that explicitly asserts
both and use that assertion instead of duplicating in each test.

2.  Create another explicit test that documents the behaviour of the link in full, eg:

    TEST_F(MyCollection, IsEmptyWhenSizeIsZero) {
        // initialize collection
        ASSERT_THAT(collection.size(), Eq(0u));
        ASSERT_TRUE(collection.isEmpty());
    }

    TEST_F(MyCollection, IsNotEmptyWhenSizeIsNonzero) {
        collection.add("foo");
        ASSERT_THAT(collection.size(), Gt(1u));
        ASSERT_TRUE(collection.isEmpty());
    } 

The tests here demonstrate the link.  The assertions on size() are not the
primary point but are included for readability.
After this test, you just assume that this link holds and always test just
size(), or whichever one is clearer.

"Testing for Confidence": This is when you write a test that you *expect* to
immediately pass.  It's a symptom that you *may* be going too fast.


Test Behaviour, Not Methods!  You don't wanna test "add", because it's both too
much and too little. Too much because you actually need several assertions to
verify addd.  Rather we focus on a higher level concern, eg, does this
RetweetCollection successfully ignore duplicate tweets?  Obviously this assumes 
that you are writing a higher-level business focused thing like this.

Langr advises KISS regarding "speculation", a well known problem.

What's the next test?  A good concept from Bob Martin:

    All transformations are prioritized from simplest (highest priority) to most
    complex (lowest priority).  Your job is to choose the transformation with the
    highest-priority order and write the test that generates that transformation.

Don't test drive: getters, setters, constructors because they don't have
meaningful behaviour.
To address this you can try to code exceptional cases first.

Langr makes the suggestion to actually revert you attempt to make the test pass
after 10 minutes!  This is quite hardcore.  Would be interesting to use a timer
for this.

Always first write regression tests for new defects found.

Disable tests using the test framework tool so that you don't forget to discard it.

## ch4 -- Test Construction

Don't make header files for tests.
It's fine to name tests based on behaviour descriptions rather than individual
classes.

We can define setup and teardown fixtures by defining a class for a test.

It seems that there is no sample code provided, so let's write a really
simple implementation so that we can comfortable refactor our tests.

Fixture not in scope: means that you forgot to use TEST_F.

Fixture vars can't be private, they have to be public.



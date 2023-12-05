Langr - LOTDD

factor out test to separate file per test case / suite

# 2017-12-18

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


# 2017-12-21

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

# 2018-01-07

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


# ch3 - TDD Foundations

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

> All transformations are prioritized from simplest (highest priority) to most
> complex (lowest priority).  Your job is to choose the transformation with the
> highest-priority order and write the test that generates that transformation.

Don't test drive: getters, setters, constructors because they don't have
meaningful behaviour.
To address this you can try to code exceptional cases first.

Langr makes the suggestion to actually revert you attempt to make the test pass
after 10 minutes!  This is quite hardcore.  Would be interesting to use a timer
for this.

Always first write regression tests for new defects found.

Disable tests using the test framework tool so that you don't forget to discard it.

# ch4 -- Test Construction

Don't make header files for tests.
It's fine to name tests based on behaviour descriptions rather than individual
classes.

We can define setup and teardown fixtures by defining a class for a test.

It seems that there is no sample code provided, so let's write a really
simple implementation so that we can comfortable refactor our tests.

Fixture not in scope: means that you forgot to use TEST_F.

Fixture vars can't be private, they have to be public.

Sometimes you may need to store intermediate results in a fixture.  In this case
you might need to store pointers and then delete them in a TearDown() function.

You can use smart pointers, eliminating the need to delete them.  Smart pointers
are dereferenced in the same way as a regular pointer.  Langr uses shared_ptr.

It still seems to work with a unique_ptr, so not sure why a shared one is used.

You can use gtest filters to run test subsets, basically don't do this though.

You can use a "nonfatal assertion" during test development to probe a bunch of
assumptions and get output.  These should probably be removed before you merge
the tests to production.  These are prefixed with `EXPECT`, eg `EXPECT_THAT`.

Demos using AllOf to match multiple hamcrest matchers.  

    string actual = string("al") + "pha";
    ASSERT_THAT(
        actual,
        AllOf(StartsWith("al"), EndsWith("ha"), Ne("aloha"))
    );

Rule of thumb: use the most explicit assertion that you can, so don't say Gt(0)
if it has to equal exactly 3.  And you should generally know this from the test.
You should use Eq most of the time.  Not using Eq is sort of a code smell.

When comparing floats, you must use DoubleEq which will use 'ULP' equality.

He gives a demo of making an exception type, it looks like so:

    class InvalidUserException: public invalid_argument {
    public:
        InvalidUserException(const string& user): invalid_argument(user) {}
    };

I don't really understand what's going on with the initializer list here.

If you need to verify exception status, you can use the less magical form.

    try {
        Tweet tweet("msg", invalidUser);
        FAIL();
    } catch (const InvalidUserException& expected) {
        ASSERT_STREQ(Eq("notStartingWith@"), expected.what());
    }

See this https://stackoverflow.com/questions/27404680/c-exception-return-type-why-char
for the explanation of the use of ASSERT_STREQ()

Don't expose data only in order to assert on it.

Boost has a date type, under boost::gregorian::date.  This comes from the header
lib `<boost/date_time/gregorian/gregorian_types.hpp>`.  The debian package
is `libboost-date-time-dev`.  But we can't use this c7 code yet because Langr
doesn't provide any tests for it, so we just need to read the section and try to
get the gist.

It revolves around the question: as you refactor private methods, should you
test them?  and how?  Basically no, if you want to start testing private
methods, you probably violate SRP.  So private methods are often a sign of
a class that tries to do too much.  And large classes suck.

TDD is again a sufficiency mentality.

You can do parameterized tests but you probably shouldn't.  But if you need to,
you derive your fixture class from TestWithParam<MyWrapper>, define MyWrapper to
contain all inputs and expected outputs, define your test with TEST_P.  Inside
the test, use `GetParam()` to get your `MyWrapper` instance.  Declare your
dynamic data and then call `INSTANTIATE_TEST_CASE_P` with your array of
`MyWrapper`.  You could do something like create a spec from a spreadsheet using
this.  You'd write a Python script or similar to generate a bunch of static
`MyWrapper(input, expected)` declarations and instantiate a `TEST_P` using them.
But bear in mind this ain't TDD!

## ch5 - test doubles

He shows the method of stubbing that we are familiar with.  Polymorphism using 
a base-class pointer.

He demos adding a verification method to ensure that the SUT passes correct
arguments to the collaborator.

You can define constants for use in tests as actual constants in the test
fixture.

You can only use ASSERT_* macros in functions that return void, so you need
to break out private methods whenever you do assertions in stub classes like this.

He mentions the fact that the expectation in the test matches the production
code, and says he'll talk about it later, in 'Implicit Meaning' section.

If we have this, 
    ASSERT_THAT(description, Eq("21 Fake Street, Brighton, East Sussex, GB"));

That later matches something returned by a stub, but it's present in two places.
We modify it so the test patches a public class member variable.

He changes the stub to accept the passed-in stuff as an intent of the test,
which admittedly elongates the test substantially... And finally starts talking
about mocking tools.

lotdd - using mock tools

we delete existing implemetnations and decide to re-test drive them again.

When does the assertion happen -- Google Mock does verification against
expectations once the mock object goes out of scope.  Therefore it's equivalent
to putting an implicit assertion at the end of the test.

You can use this line to force expectations to convert to assertions instead
of the implicitness.

    Mock::VerifyAndClearExpectations(&httpStub);

Returning to this chapter in 2021.

NiceMock is a template that allows wrapping mocks and tells them to only track
cases where calls are expected, rather than tracking every call.  NiceMock is
caveatted that there should be some caution

Order doesn't matter by default???  Seems odd.  But simply by declaring
InSequence you force the calls to be in the correct order.  What a crazy API.
If it wasn't C++ I'd say it was bad and too magical.  Apparently there are also
less weird APIs within gmock, though.

"Interactions with collaborators are a key aspect of [the design of the
system]...  Having tests that describe those interactions will be of high value
to other developers." -- I'm not totally sure that I buy this, but fair.

Brace initialization widely used -- this is actually a better convention to
adopt everywhere as it's stricter.

<https://stackoverflow.com/questions/18222926/>

Ex16: Demonstrate "override getter".

PlaceDescriptionService constructor gains a constructor with an implementation.
PlaceDescriptionService gains a private shared_ptr<Http>.
This will be initialized in the constructor.  The test will continue to override
the factory method.
This is in addition to the httpService() factory method.
What does this gain us?
Even though we use a derived class for the test stub, our base class no-arg
constructor is automatically called, meaning that the code that was previously
part of the "factory":

    make_shared<CurlHttp>()

does end up being called now, where before (with plain "Override Factory
Method") this code would never be exercised at all.

Ex18: demonstrate "introduce via factory"

Here we create a factory class.  We make TWO derived classes from the test class.
I'm not sure if this is strictly necessary...

### Ex19: Introduce via Template Parameter

The basic technique:

typedef your production class like so:

    using PlaceDescriptionService = PlaceDescriptionServiceTemplate<Http>;

In test, use the template directly with the stub class:

    PlaceDescriptionServiceTemplate<HttpStub> service;

Crucially this causes the instantiation of the mock to actually take place
within the template's code itself (as part of the class's default constructor, I
think).  Hence the public accessor needs to be made otherwise there would be no
way to verify calls on the stub at all.

    T& http() { return http_; }

### Injection Tools

Autumn Framework is a C++ DI tool from 2007.
Qt IOC Container is still around on sourceforge, but not updated since 2006.

http://qtioccontainer.sourceforge.net/

This almost certainly doesn't work anymore though as it uses Qt MOC.


### 5.8 -- Design Will Change

The example here is a great example of what I mean when Sandi Metz talks about
the trade-off between concrete & easy-to-change.

The concrete curl class segfaults with an error if it's not declared as static.
In this call:

    curl_easy_setopt(
        curl, CURLOPT_WRITEFUNCTION, &PlaceDescriptionService::writeCallback
    );

`PlaceDescriptionService::writeCallback` MUST be static, otherwise Curl ends up
calling it in the wrong way!  Basically gets miscompiled.  `this` gets passed as
an implicit first argument by the compiler, throwing the argument stack out by
1.

Needed to change the build process to allow embedding a "real" mapquest API key.

> Longer functions like this promote unnecessary duplication. Other services
> are likely to need some of the same cURL logic, for example. Developers will
> often re-code the three lines related to cURL rather than try to reuse them.
> Reuse begins with isolation of reusable constructs that other programmers
> can readily identify. As long as the potentially reusable chunks of code lay
> buried in a Long Method, reuse won’t happen.

Interesting take here.  In Fox, for instance, reuse just doesn't happen
full-stop.

### 5.9 Strategies for Using Test Doubles

Reading this 2022-04-28.

> Many of the mocks for controller-level code verified sequences of events by
> expecting that methods were called in a certain order. (Worse, the tool they
> used required method expectations to be represented as strings. Renaming a
> method meant you had to remember to update the string literals used by the
> mocks.)

Yuck!

> Having tests highly dependent on implementation specifics—which methods are
> called in which order—created significant problems. But in hindsight, the far
> larger problem was our inadequate system design. We might have had an easier
> time had we factored away duplication across tests.

This describes the frustrations of maintaining tests during heavy refactoring.
I would likely have disabled tests at this point.

_Growing Object-Oriented Software, Guided By Tests_ uses mockist TDD.

Tell-Don't-Ask means we don't interrogate state of objects, rather we let the
object handle its own state.

The classicist school avoids mocks until forced to use them.  Kent Beck's text
"TDD By Example" uses this approach.

Regarding test doubles:

> *Recognize the concession to unit testing coverage.* A test double represents a
> hole of sorts in your system’s coverage. The lines of logic that your test
> double supplants is code that your unit tests will not execute. You _must_
> ensure that other tests cover that logic.

> Refactor your tests as much as you refactor your production code!  Encapsulate
> expectation declarations in common helper methods to improve abstraction, reduce
> the extent of the dependency, and minimize duplicate code.

I don't agree with this necessarily but it is good to aim at this.

> Having multiple levels of mocks is usually a recipe for headaches.

Yeah, this would clearly seem to be the case.  If I saw this I would seriously
rethink the design.

## 5.10 Miscellaneous Test Double Topics

A fake is a small clone of some production class that has the same interface.
Clearly there's not really a bright line between a stub and a fake, but imagine
trying to implement an in memory database using hash tables.  This seems very
silly when you could just mock out the specific DB calls required.  If you use
fakes it's appropriate to unit test them.

> Remember that changes to the production interface will break tests that use
> derived test doubles. If you’re all on the same team and following collective
> code ownership guidelines (everyone has to right to change any code), the
> developer changing the production interface is responsible for running all
> tests and fixing any that break. In other circumstances, sending out a message
> that clearly communicates the change (and implications) is prudent.

Interesting guideline here, although how does it interact with the PR process?

Vtables and performance: This involves making certain methods virtual to enable
polymorphism.  Could mean a perf discussion.  Obviously not the case in
Python/Java.

> If the measured degradation is unacceptable, consider a different mocking form
> (perhaps a template-based solution), rework the design (and possibly recoup the
> performance loss by optimizing elsewhere), or introduce integration tests to
> compensate for the loss of the ability to unit test.

# CHAPTER 6 -- Incremental Design

This is the next chapter.

Simple Design: A set of rules for clean code

* Readability and expressiveness is priority #1
* Eliminating duplication is priority #2
* Not adding unnecessary stuff is #3


Duplication can have multiple forms.  Repeated expressions is one, but
"algorithmic" duplication is another one, i.e. redundancy in the actual
representation of data within a class.  e.g. a class that tracks its
empty/non-empty status with a boolean contains 'algorithmic' duplication.  I
would say that algorithmic duplication surely implies redundancy at a textual
level as well.  Algorithmic duplication would seem to be a worse issue than
expression duplication.

Next exercise: use an unordered_map to implement the next round of tests.

Story: Show purchase history

Start off by hardcoding the date object, this enables writing tests, while
avoiding the need to change all the method signatures.

Introduces the notion of parameter defaulting, which is perhaps a C++11
addition.

    void purchase(
        const std::string& symbol,
        unsigned int shareCount,
        const boost::gregorian::date& transactionDate=Portfolio::FIXED_PURCHASE_DATE
    );

The `=` sign in declaration refers to something which I presume must be
constructible at compile-time.

We could adjust all tests to pass in the date, but this would violate "test
abstraction".  All tests should only manifestly/textually care about what they
directly care about.

The answer is basically to create a test utility that calls the method in
question.

> As a rule of thumb, avoid hiding Act (see Arrange-Act-Assert [...])

So he agrees with me.

## More Duplication

We need to represent negative numbers in the purchase record, but we can only
purchase unsigned values obviously.  The correct response is to change
everything to be ints and add runtime checks, probably.

The alternative would be to accept unsigned int, but then you're accepting
double the range and have to do a complicated range check at all times which
seems slow and impractical.

* Purchase should prevent purchasing x<1 share.
* Sell should prevent selling more than we have, so holdings can never drop
  below zero.
* This means that shareCount can never drop below zero.  So it can be unsigned

Actually, good practice in c++ is to always use signed values because unsigned
is weird.


## Finishing the Functionality

We see this odd syntax.

    add(symbol, {shareChange, transactionDate});

This is C++11 specific and it creates a 'temporary'.  Temporaries have actually
been in the language since C++98.  The temporary exists for the compiler.

    void Portfolio::add(const string& symbol, PurchaseRecord&& record) {
        purchaseRecords[symbol].push_back(record);
    }

This uses the `&&` rvalue syntax to take ownership of the temporary.  You can
write it as `const PurchaseRecord& record` as well.  Basically the push_back()
method has a version that takes a `T&&` argument that moves the value into the
vector.  So this is a zero-copy version unlike the `const T&` version.  Also
note that `struct` provides a default move constructor that delegates to all of
the constituent fields.

I learned that you can't define an operator / free function in a header file as
it will be included into all units multiple times.

I like this quote:

> TDD is a means of addressing design on a continual basis. Consider that you
> are taking all the time saved in initial detailed design efforts and spreading
> it out across the rest of the product’s life span.

So agile is not necessarily to move faster but rather to redistribute effort to
enable change.

Don't sweat the details of design.  Just "focus on class names, dependencies,
and maybe a few key public behaviors."  What are the main elements of the system
and the main interactions between them?

Regarding the least-access principle (public vs private members):

> However, if you need to relax access to allow tests to verify that things
> actually work as intended, you shouldn’t worry most of the time. If everything
> is tested, the tests will likely protect your system against
> stupidity. Knowing the system works is far more compelling than over- doting
> on a vague concern about future abuse.

So we have a similar attitude here to Python's one.

> With the notion of using simple, incremental design as your primary design
> driver, the refactoring step is where much of the real work gets done. Anything
> that keeps you from refactoring easily, or even from wanting to refactor, is
> bad. Very bad. When you stop refactoring incrementally, your system will
> start degrading quickly.

So we aim to prevent all the mental blockers from refactoring.  (Adjusting tests
presumably not being one of them!)

## Refactoring Inhibitors

> Premature performance obsession: Many of the ideas promoted in this
> book about design center around small classes and functions, which
> incurs the overhead of creating additional objects and calling extra
> methods. Many developers resist such changes and are content with
> longer functions and classes.
>
> Ensure you first create a clean, maintainable design. Profile the proper
> design to determine whether it exhibits performance deficiencies. Optimize
> the code only if absolutely necessary. Most optimizations increase the
> difficulty of understanding and maintaining the code.

This is quite amusing and true.  I probably have been guilty of this.

Of course this is the absolute doozy that we've all seen:

> Short-sighted infatuation with speed: “Just ship it. Stop spending time on
> refactoring.” Can you blame a project manager for not understanding the
> importance of keeping your system’s design clean? Sure, it might look
> like you’re speedy for a while, but you’ll eventually suffer dramatically
> (sometimes devastatingly) for letting your system’s quality slide.
>
> Just say no, and otherwise keep your refactoring to yourself. Work to
> keep your code clean every few minutes as part of the TDD cycle. If asked,
> you can say “This is how I work as a responsible professional.”
> 
> You must take advantage of the opportunity that each passing test pro-
> vides you; otherwise, code cruft will build up quickly and begin to slow
> the rate of development. You might even feel compelled to ask for a
> refactoring iteration. Don’t! Nontechnical folks have no idea what refactor-
> ing is. They will simply translate your request as “The programmers just
> want to play around with the software, and I won’t get any business value
> this iteration.”
>
> Unfortunately, no matter how hard you try, you will inevitably have itera-
> tions where a new feature doesn’t fit easily into the code, causing you to
> deliver the feature later than expected. When this occurs, ask for forgive-
> ness, and run an honest investigation into how you might have prevented
> the additional effort. Don’t let it happen habitually.

# CHAPTER 7 - Quality Tests


FIRST --
Fast
Isolated
Repeatable
Self-verifying
Timely

Build times are a big issue in C++ because we need to compile and link for every
test change.  Need to follow the I in SOLID: interface segregation principle.
That will minimize rebuilds naturally, two birds with one stone.

Likewise if we use DI and pure virtual void classes, then clients don't need to
rebuild when we change the implementation of some given interface.

There is something called PIMPL: Pointer to Implementation.

> Extract your concrete class to a separate implementation class.  Delegate to
> the implementation as needed from the implementation functions.

This is equivalent to having e.g. TwitterService and TwitterServiceImpl in
Java.  I guess the point is that you can add private methods ad-hoc within
TwitterServiceImpl, but if client code only uses TwitterService then it won't be
forced to rebuild.

Pimpl uses a weird syntax: here's a reasonable example
https://www.geeksforgeeks.org/pimpl-idiom-in-c-with-examples/
This uses nested classes, a language feature I didn't know about.
https://en.cppreference.com/w/cpp/language/nested_types

Pimpl uses a single unique_ptr to a nested class.

Try to run all the tests in your whole project, or failing that, run all the
tests in a given file.  Don't run single tests habitually (I'm guilty of this).


Isolated and repeatable:

> Any test that uses static data runs the risk of failing because of stale data.

This means that any code that manipulates/relies on ambient state can fail for
that reason.  We prefer to fix this by minimizing such state where possible.  So
isolated means isolated from systemwide state as well as dependencies.

Isolate from: static system state, external services, concurrency.  There's a
whole chapter on concurrency.

Self-verifying: everything that fails should be directly testable through
assertions.  This is stronger than saying "every test should have an assertion"
because it means that to debug failing tests you should be relying on specific
more focused unit tests and using assertions!  It relies on your testing
framework being able to print values in a sane way.

Timely: everything is incremental.  You write the smallest possible variant at
every time.



## One Assert per Test

> Should you ever have more than one assert per test?  Strive hard to have only
> one.  Sometimes it makes sense to have more, though. [...] If multiple
> assertions are required to describe a single behaviour, you can justify a
> second assertion in a test.

There are a couple of other exceptional cases but mostly one-assert-per-test is
a good rule.

## Test Abstraction

> Abstraction is as important in your tests as it is in object-oriented design.
> Since you want to be able to read your tests as documentation, they must cut
> to the chase, declaring their intent as clearly and simply as possible.

Langr suggests using fixture functions to abstract most of the cruft.

It's not clear if the library code from example 7.3 will ever be returned to?  I
hope it will!  As we didn't do any of the implementation.  We are now focused on
a completely separate "line reader" test.

There's no way to go from a file descriptor to an `fstream` in standard C++, so
we have to do something even more bizarre:

Boost can wrap a file descriptor in an fstream.  We might have to prototype this
separately.

7.8 -- Slight erratum here as we already removed the fd variable.  Langr shows
factoring all test state into the test class.

Langr thinks nothing of creating a helper function to wrap a custom assert.  I
might possibly avoid this, or maybe not (it might be more appropriate in C++).

## Unnecessary Test Code

TEST_P -- This is used for paramterized tests.  The test parameter is accessed
using GetParam() method.

Parameterized tests are created using

    INSTANTIATE_TEST_CASE_P(
        KeyedMemory, PersistenceTest,
        Values(&KeyedMemoryPersistenceTest::CreatePersistence)
    );

Instead of using auto_ptr, we use unique_pr.

TEST_P was actually briefly mentioned back in Chapter 3, with a big ol' proviso
on it saying that you shouldn't often use it.

In this function:

    virtual unique_ptr<T> get(const string& id) const {
        auto it = contents.find(id);

        if (it == contents.end()) {
            return nullptr;
        } else {
            return make_unique<T>(contents.at(id));
        }
    }

It's interesting that you can just return nullptr and it doesn't have to be
wrapped in any way, I am not sure why this is the case.

Assert not null: When you use raw pointers, you have the option to check them
using something like `ASSERT_THAT(foo, NotNull())`.  This will create a test
failure instead of a segfault when you try to use a null pointer which may be
more meaningful.  You can get around coding this by explicitly handling the null
case in a different test, and then "let it crash" (it never should).  Raw
pointers should be avoided anyway so one way to approach this is just to not use
them.

Google Test provides a "Pointee" macro that will allow checking equality and
pointer not nullness at the same time:

> Pointee(m) matches a pointer if and only if m matches the value the pointer
> points to...  One nice thing about Pointee() is that it treats a NULL pointer as
> a match failure.

    ASSERT_THAT(found, Pointee(*objectWithId1));

You always need to pass the VALUE as the second part, so in this case we still
have to manually dereference the second pointer.

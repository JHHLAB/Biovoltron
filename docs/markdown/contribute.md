Contribute
==========

[TOC]

Reporting Bugs
--------------
1. Check FAQ.
2. Check opened issues.
3. Open an issue (make sure the bug is reproducable).

Setup Development Environment
-----------------------------
Dev dependencies:

* g++ 11.1.0+
* boost 1.74.0+
* zlib 1.2.11+
* tbb 2020.3+
* range-v3 0.11.0+
* cmake 3.16+

```sh
$ git clone REPO_URL
$ cd Biovoltron
$ mkdir build && cd build
$ cmake ..
$ make
$ ./tests/biovoltron-test
```
Extra dependencies for coverage report:

* gcovr
* Make sure your gcov is the same version as your gcc compiler.

```sh
$ mkdir build && cd build
$ cmake .. -DGCOV=ON
$ make
$ ./tests/biovoltron-test
$ gcovr --html-details coverage.html --root ../include/biovoltron/ .
# Open coverage.html in your browser.
```

Extra dependencies for building documentation:

* doxygen
* sphinx
* sphinx_material
* breathe

```bash
# install Doxygen on your system.
$ pip install sphinx breathe sphinx-material
$ mkdir build && cd build
$ cmake .. -DBIOVOLTRON_DOC=ON
$ make Sphinx
# Open doc/sphinx/index.html in your browser.
```

Development Workflow
--------------------
* Pick a issue to work on.
* Create a branch and work on your issue.

```bash
$ git checkout -b YOUR_BRANCH
```

* Write unit test first (test is your spec).
* Start work on you code.
* Make sure all the test pass.
* Write doxygen documentation.
* Before you merge: clean your commit history and rebase.

```bash
$ git fetch --prune
$ git checkout master
$ git merge
$ git checkout YOUR_BRANCH
$ git rebase master
# Resove conflict if any then git rebase --continue
# Clean your commit history
$ git push -f origin YOUR_BRANCH
```

* Submit a merge request (delete source branch when merged).
* Get merged or need some fix.

C++ Coding Guidelines
---------------------
* AAA: Almost Always Auto.
* Use STL instead of complex nested raw loop.
* Stateless class/struct member function declare ``static``.
* Use ``const`` as much as possible.
* Move instead of copy.

Git style
---------

### Commit Message
Commit message can be break into three part

* Commit message token
  * ``[FEAT]`` Whenever you implement something new and shiny.
  * ``[FIX]`` Whenever you fix some wrong code in the source.
  * ``[DOC]`` Whenever you do something only(!) related to the documentation.
  * ``[INFRA]``   Whenever you change something of the build system or CI related.
  * ``[TEST]`` Whenever you do something related to the tests (unit or benchmark).
  * ``[MISC]`` Whenever it does not fit to any of the above.
* Short description: less than 50 characters.
* Detail description (optional): less than 72 character per line.

An example

```
[FIX] Short (50 chars or fewer) summary of changes

More detailed explanatory text, if necessary. Wrap it to
72 characters. The blank line separating the
summary from the body is critical (unless you omit the body
entirely)

Further paragraphs come after blank lines.

- Bullet points are okay, too

- Use a hyphen or an asterisk for the bullet,
  followed by a single space, with blank lines in
  between

The pointers to your related resources can serve as a footer
for your commit message. Here is an example that is referencing
issues in a bug tracker:

Resolves: #56, #78
See also: #12, #34

Source http://tbaggery.com/2008/04/19/a-note-about-git-commit-messages.html
```

### Other Git Guidelines
1. Rebase before merge.
2. Merge small and often.
3. Squash your commits into one before merge.
4. Do not work on same branch.

Doxygen Comment Guide
---------------------
1. ``class``/``struct``: Provide a brief description.
2. Public interface (members, member functions) must have documentation.
3. Description must be concise (short and clear).

An example
\code{.unparsed}
```cpp
/**
 * A class that does nothing.
 *
 * A more detail description. This is optional.
 * This class realy does nothing.
 */
Class Foo {
  public:

    /**
     * A person's age.
     */
    int age;

    /**
     * Get the age after some years.
     *
     * @tparam T Year type.
     * @param years Some years.
     * @throw std::out_of_range When the years > 1000.
     * @return Age after some years.
     */
    template<typename T>
    auto age_after_years(T years) {
      if (years > 1000)
        throw std::out_of_range("Too old.");
      return age + years;
    }

  private:
    int weight;
    auto bar() {
      return 0;
    }
};
```
\endcode

# Contribute {#contribute}

Welcome to Biovoltron's community! Whether you're interested in reporting a bug, setting up your development environment, or contributing code, this guide will help you get started.

[TOC]

## Bug Reporting {#contribute-bug-reporting}
1. Check if the issue you've encountered has already been reported in our [issue tracker](https://github.com/JHHLAB/Biovoltron/issues).
2. If it hasn't been reported, create a new issue, ensuring that you provide enough details for others to reproduce the bug.

## Environment Setup {#contribute-setup}
### Development Dependencies
Ensure you have the following dependencies installed:
- g++ >= 11.1.0
- boost >= 1.71.0
- zlib >= 1.2.11
- cmake >= 3.16

Clone the Biovoltron repository with submodules
```bash
git clone --recurse-submodules git@github.com:JHHLAB/Biovoltron.git
cd Biovoltron
```

Install pre-commit for code formatting
```bash
pip install pre-commit
pre-commit install
```

Create a build directory and configure the project
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

Build the project and run tests
```bash
make
./tests/biovoltron-test
```

### Coverage Report Dependencies
- gcovr (Ensure your gcov version matches your gcc compiler version.)

Create a build directory for coverage report
```bash
mkdir build && cd build
```

Configure the project for coverage report
```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug -DGCOV=ON
```

Build the project and run tests
```bash
make
./tests/biovoltron-test
```

Generate coverage report in HTML format
```bash
gcovr --html-details coverage.html --root ../include/biovoltron/ .
```

Open `coverage.html` in your browser.

### Documentation Building Dependencies
- doxygen >= 1.9.4

Create a build directory for documentation
```bash
mkdir build && cd build
```

Configure the project for documentation generation
```bash
cmake .. -DBIOVOLTRON_DOC=ON
```

Build the project
```
make
```

Open the generated documentation `docs/doxygen/html/index.html` in your browser

## Development Workflow {#contribute-development-workflow}
- Select an issue to work on.
- Create a branch and start working on your issue.
```bash
git checkout -b YOUR_BRANCH
```
- Write unit tests first (tests serve as your specifications).
- Begin working on your code.
- Ensure that all tests pass.
- Document your code using Doxygen.
- Before merging, clean up your commit history and rebase.

```bash
git fetch --prune
git checkout master
git merge
git checkout YOUR_BRANCH
git rebase master
```
Resove conflict if any then git rebase --continue, clean your commit history
```bash
git push -f origin YOUR_BRANCH
```

- Submit a merge request (delete the source branch when merged).
- Get your code merged or make necessary fixes.

## C++ Coding Guidelines {#contribute-coding-guideline}
- Use "Almost Always Auto" (AAA) for type inference.
- Prefer using the Standard Template Library (STL) over complex nested raw loops.
- Declare member functions of stateless classes/structs as static.
- Utilize const whenever possible.
- Use move semantics instead of copying.

## Git style {#contribute-git-style}
### Commit Message
A commit message should be divided into three parts:

- Commit message token:
  - ``[FEAT]`` for implementing new features.
  - ``[FIX]`` for fixing issues or bugs in the source code.
  - ``[DOC]`` for documentation-related changes.
  - ``[INFRA]`` for changes to the build system or CI.
  - ``[TEST]`` for modifications related to tests (unit or benchmark).
  - ``[MISC]`` for changes that do not fit into any of the above categories.
- Short description: A summary of fewer than 50 characters.
- Detailed description (optional): Detailed explanation, with each line limited to 72 characters.

Here's an example:
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
1. Rebase before merging.
2. Merge small changes frequently.
3. Squash your commits into one before merging.
4. Avoid working on the same branch simultaneously.

## Doxygen Comment Guidelines {#contribute-doxygen}
1. For ``class`` and ``struct``, provide a brief description.
2. All public interfaces (members and member functions) should have documentation.
3. Keep descriptions concise (short and clear).

Here's an example:
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

Feel free to reach out if you have any questions or need further guidance on contributing to Biovoltron!

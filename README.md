# relational-database-cs236-byu
A relational database management system (RDBMS) maintains data sets called relations. A relation has a name, a schema, and a set of tuples. A schema is a set of attributes. A tuple is a set of attribute/value pairs. An attribute is the name associated with each data value in a tuple entry. Relations are used as operands in relational operations such as rename, selection, projection, union, and join. The goal of this project is to build a relational database system from a Datalog file, and then answer queries using relational algebra.

### Table of Contents
- [Project Description](#project-description)
- [Requirements](#requirements)
    + [Part 1](#part-1)
    + [Part 2](#part-2)
- [Examples](#examples)
- [FAQs](#faqs)
- [Submission](#submission)
- [Passoff](#passoff)



### Project Description
A Datalog Program can be represented by a Database. Each scheme in a Datalog Program defines a relation in the Database. The scheme defines the name of the relation, and the attribute list of the scheme defines the schema of the relation. Each fact in the Datalog Program defines a tuple in a relation. The fact name identifies a relation to which the tuple belongs. The basic data structure is a database consisting of relations, each with their own name, schema, and set of tuples. How you choose and use your data structures effects the difficulty of the project. Inheritance and polymorphism are always useful. Each data structure implementation has its benefits, drawbacks and obstacles to overcome.

Your program must convert every Datalog query into a sequence of select, project, and rename operations. As you prepare to write your program, take out a piece of paper, convert each of the queries in the given examples into a relational expression, and carry out these expressions. Your program should create these same expressions.

### Requirements
The project is divided into two parts representing different aspects of the final solution: part 1 implements a relation class and how it is used to answer queries and part 2 connects the relation class to the datalog program object created by the parser.

##### Part 1
(relation class with tests)

Create a relation object that includes methods implementing select, project, and rename operations. The relation and its methods must follow the mathematical definitions described in class and in the textbook. For example, the operators must not produce relations which have duplicate tuples or duplicate names in the schema.

Implement at least 10 tests to validate the select, project, and rename methods:

- At least 4 of the 10 tests must mimic a datalog query in that they use a sequence of select, project, and rename to answer the query (as explained below in the FAQ).
- The tests must be testing either a select, project, rename, or a query; they may not test if the relation you create is structured properly (i.e. proper sorting, no duplicates, etc.; while these things are important, they are not what should be tested).
    - Both types of selects must be implemented.
- The tests must be documented and justified: what does the test accomplish?
    - Each test must be marked with comments explaining what operation is being performed and why.
    - For the 4 tests that mimic a query, the comments must include the actual query that is being mimicked.
- Each of the tests must test something different; if one test case tests the same thing as another, it isn't telling you anything new, and therefore it won't be counted as one of the 10 tests.

Further, all the tests must be automatic; automatic means the tests run without any user input and reports to the console the status of every test: pass or fail.

- *Command line*: no command line arguments
- *Output*: A *pass/fail* report for each test. (see below for further details on these tests)
The only text that needs to be outputted to the console is the test number and whether it passed or not (but you may definitely output more!). The TAs will look at your code to make sure the test cases do what you say they are doing in the comments. They will also make sure you implemented the select, project, and rename functions.

For this project, each test case you create should pass. The pass/fail report of a test is based on a comparison between the expected result and the actual result of each test. The comparison must be made automatically by your tester. This means that your tester must have the expected output in the code to compare with the actual output in an if-else statement; the actual output is the relation that is created after performing the select, project, and/or rename operations, while the expected output is what you calculate the relation should be after performing the operations. Common ways to check if they are equal include creating a method that tests if two relations have the same name, schema, and tuples; or creating a toString function for the relation class and comparing the strings for each relation. It is up to you how to do this, but what is not allowed is always outputting that each test passed without actually checking that the code does what it is supposed to do.

The pass-off is based on the quality of tests and whether or not the solution passes. If a test does not automatically compare actual and expected out as described above, it won't be counted. If more than one test case tests the same thing, only the first test case will be counted.

##### Part 2
(RDBMS -based interpreter)

Write an RDBMS-based interpreter for a Datalog Program. Given a Datalog Program object from the datalog parser, your interpreter should create an instance of a database object holding relations and then compute and print the result for each query using only the facts form the input (interpretation of the rules will be added in Project 4). Your design should include a class for the database and use your relation from part 1. Queries must be implemented by performing the appropriate relational operations as in the tests from part 1 (select, project, and rename). *As a reminder, use the datalog object from the parser to initialize the database object, and then interpret the queries in that same object to generate the output*. Queries should become a series of select, rename, and project calls on one of the relations in the database.

To format the output for pass-off, you must make it look like the examples below. Note the following: The queries are to be evaluated in the order listed in the Datalog Program. For each query, print the query and a space. Then, if the query's resulting relation is empty, output “No”; and if the resulting relation is not empty, output “Yes(n)” where n is the number of tuples in the resulting relation. If there are free variables in the query, print the tuples of the resulting relation, one per line and indented by two spaces, according to the following directions. Each tuple should be a comma-space separated list of pairs–(variable, string-value)–ordered according to the order of variable appearance in the query. The format of a pair is v= 's', where v is the variable and 's' is the string value. Sort the tuples alphabetically based on string values in the tuples' variables (sort with the first sort key as the first variable (in order of appearance in the query), the second sort key as the second variable, and so on).

The focus of this project is on interpreting 236-Datalog (without rules)–not on building an industrial-strength interpreter. Thus, to retain the central focus and keep the amount of coding within a reasonable bound, you may assume:

- The arity (number of parameters) of all schemes, facts, rules and queries that have the same name are guaranteed to match. You do not have to check for matching arity.
- No two attributes in the same scheme will have the same name. You do not have to check for this.
- No two schemes in the scheme list will have the same name. You do not have to check for this.
- Every scheme (or relation) referenced in a fact, rule head, predicate, or query will have been defined in the scheme section.

Interface requirements:

- *Command line*: a single argument indicating the input file
- *Input*: a valid datalog program
- *Output*: see the output specifications and examples

Part 2 is scored on a set of private tests at submission.

### Examples
These are not sufficient to completely test your program. Your program must have output formatted exactly like the example outputs below. Example Input:

*Input*
```
Schemes:
  SK(A,B)
Facts:
  SK('a','c').
  SK('b','c').
  SK('b','b').
  SK('b','c').
Rules:
  DoNothing(Z) :- Stuff(Z).
Queries:
  SK(A,'c')?
  SK('b','c')?
  SK(X,X)?
  SK(A,B)?
```
*Output*
```
SK(A,'c')? Yes(2)
  A='a'
  A='b'
SK('b','c')? Yes(1)
SK(X,X)? Yes(1)
  X='b'
SK(A,B)? Yes(3)
  A='a', B='c'
  A='b', B='b'
  A='b', B='c'
```

---
*Input*
```
Schemes:
	ab(A,B)
Facts:
	ab('joe','bob').
	ab('jim','bob').
	ab('joe','jim').
	ab('bob','bob').
Rules:

Queries:
	ab('joe','jim')?
	ab( who, 'bob')?
	ab('joe', anyone)?
	ab(X,X)?
	ab(X,Y)?
```
*Output*
```
ab('joe','jim')? Yes(1)
ab(who,'bob')? Yes(3)
  who='bob'
  who='jim'
  who='joe'
ab('joe',anyone)? Yes(2)
  anyone='bob'
  anyone='jim'
ab(X,X)? Yes(1)
  X='bob'
ab(X,Y)? Yes(4)
  X='bob', Y='bob'
  X='jim', Y='bob'
  X='joe', Y='bob'
  X='joe', Y='jim'
```

---
*Input*
```
Schemes:
	dc(D,C)
Facts:
	dc('ralph','howard').
Rules:

Queries:
	dc('ralph', X)?
	dc('bob','bob')?
	dc(X,Y)?
```
*Output*
```
dc('ralph',X)? Yes(1)
  X='howard'
dc('bob','bob')? No
dc(X,Y)? Yes(1)
  X='ralph', Y='howard'
```

---
*Input*
```
Schemes:
  Student(name, age, class)
Facts:
  Student('Sean','21','Sophomore').
  Student('Arthur','19','Freshman').
  Student('Sidney','19','Sophomore').
  Student('Nicole','23','Senior').
Rules:
Queries:
  Student(A,'19',B)?
  Student(M,M,M)?
  Student('Nicole',howOld,'Senior')?
```

*Output*
```
Student(A,'19',B)? Yes(2)
  A='Arthur', B='Freshman'
  A='Sidney', B='Sophomore'
Student(M,M,M)? No
Student('Nicole',howOld,'Senior')? Yes(1)
  howOld='23'
```

---
In the next example, notice that the rules are not evaluated, but the queries are still answered using only the facts included in the file.

*Input*
```
Schemes:
	people(person1,person2)
	employer(boss,employee)
Facts:
	people('joe','bob').
	people('jim','bob').
	people('joe','jim').
	employer('ralph','howard').
	people('bob','bob').
Rules:
	employer(X,Y):- people(Y,X).
	employer(X,Y):- people(X,Z),employer(Z,Y).
	people(X,Y):- people(Y,X).
Queries:
	people('joe','jim')?
	people( who, 'bob')?
	people('joe', anyone)?
	people(X,X)?
	people(X,Y)?
	employer('ralph', X)?
	employer('bob','bob')?
	employer(X,Y)?
```
*Output*
```
people('joe','jim')? Yes(1)
people(who,'bob')? Yes(3)
  who='bob'
  who='jim'
  who='joe'
people('joe',anyone)? Yes(2)
  anyone='bob'
  anyone='jim'
people(X,X)? Yes(1)
  X='bob'
people(X,Y)? Yes(4)
  X='bob', Y='bob'
  X='jim', Y='bob'
  X='joe', Y='bob'
  X='joe', Y='jim'
employer('ralph',X)? Yes(1)
  X='howard'
employer('bob','bob')? No
employer(X,Y)? Yes(1)
  X='ralph', Y='howard'
```

### FAQs

*How should we refer to parts of a query?*

Consider the query SNAP('s',X,X,Y)?

SNAP is the name of the relation that pertains to this query.
's', X, and Y are the parameters of this query.
's' is a constant. A select must be performed.
X and Y are variables. Because X occurs more than once, a select must be performed.


*When should I select, project, or rename in a query?*

Here is a simple strategy to consider when deciding how to evaluate queries:

Iterate through every parameter of the query and perform a select for every constant and every variable that has occurred before. It may be the case that no select takes place on a certain variable or any variable in a query, which is fine!
Once all the select operations have been completed, project the relation to include only columns with identifiers in the query (only the first instance of each variable, leaving out the columns that were selected for constants and the columns that were selected as the duplicate instances of variables)
After projecting, rename those attributes to their new names as given in the query.
The functions must be called in this order: any selects, followed by a project, followed by a rename. While it is possible in some circumstances to do it in a different order, such attempts will often lead to errors, so you need to execute these functions in the proper order.


*What does the select operation do?*

The select operation finds tuples in a relation that meet certain criteria. It can do this in two different ways:

It can find all the tuples that have a constant in a certain column.
It can find all the tuples that have the same value in two columns (doesn't matter what that value is, as long as the two columns both have it).
The schema stays the same.


*If the select operation finds when two columns have the same value, should it also find when two columns have different values?*

No. If a query has two different variables in it, that does not mean the select must find tuples with different values in those columns. Consider the last query of the first example:

```
SK(A,B)? Yes(3)
  A='a', B='c'
  A='b', B='b'
  A='b', B='c'

```
While A and B are different variables, the query still includes when the values are the same in the tuple (the second result where both A and B equal 'b').


*What does the project operation do?*

The project operation changes the number and order of columns in a relation. The resulting relation will have either the same number of or fewer columns. This affects the schema and all of the tuples in that relation.

*Why can the project operation also re-order the tuple?*

The output for the lab requires that tuples follow the order declared in the query. Although not apparent right now, the later labs will implement a natural join operation. In such an operation, the order becomes less clear. A project-method can ensure the tuples follow the correct order as part of its operation with some little thought and foresight.

*What does the rename operation do?*

The rename operation changes the relation's schema. The resulting relation will have all the same tuples.

*Should rename only change one attribute at a time or the entire attribute list at once?*

Renaming the entire attribute list at once is simpler and avoids any issues with replacing A with B and then replacing B with A on the relation with attributes (A,B). That said, the test inputs are careful to never create such a situation.

*What should the select, project, and rename functions return?*

These functions should create a new relation that reflects the changes made to the original relation. Then they return that new relation. These functions should not modify the original relations, as many queries could be made and it would not work if the original relation kept changing.

Note that the new relation will always have the same name as the original relation, but the schema, number of tuples, and number of columns might change depending on the operation.

### Submission
Review the project standards for creating a zip archive.

Navigate to Learning Suite, select 'CS 236', and click on 'Assignments' on the course home page. Click on the link to the relevant project and at the bottom of the description click on 'View/Submit'. Use the resulting upload dialog to upload your zip archive.

### Passoff
Pass-off your project directly to a TA during normal TA hours. TAs help students on a first-come/first-serve basis and are under no obligation to stay later than designated hours so plan accordingly. Please review the syllabus and the project standards for the pass-off requirements including the published time bound.

[Back to Top](#relational-database-cs236-byu)

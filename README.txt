* INTRODUCTION

An ASK System is a series of hypermedia stories that are linked by
the questions they answer and the questions they raise. For example, a
story about high population growth in Kenya might raise the question,
"Does this growth cause any problems for Kenya?" which is answered by
a story on how high population levels have put a strain on the
economy of Kenya. This method of linking stories by questions raised/
questions answered has a further refinement: typically, the questions
are placed in categories based on Roger Schank's "Conversational
Associative Categories" or CAC-links.


* ASSIGNMENT

Your assignment is to read in a data file of information about an ASK
system, and then build a text-based browser. All of the stories will
be text only.

For example, the form:

  (def-ask-system :countries "Countries of the World")

defines an ASK system entitled "Countries of the World," with
":countries" being an internal name for the ASK system.

CAC links are defined by:

  (def-cac-link <Name> <Type> <Title>)

where Name is the internal name of the ASK system, Type is the
internal name of the CAC link, and Title is the title of the CAC
link. For example,

  (def-cac-link :countries :specifics "Specifics")

defines a :specifics CAC link in :countries.

Questions are defined by:

  (def-question <Ask-System-Name> <Number> <Cac-Link-Name> <Text>)

where Ask-System-Name is the internal Name of the ASK system, Number
is a reference number by which the question can later be referred,
Cac-Link-Name is the type of CAC link involved, and Text is the text
of the question.

For example,

  (def-question :countries 5 :results "Does this growth cause any problems for Kenya?")

defines a question in :countries numbered 5. Its text is "Does this
growth cause any problems for Kenya?" and is a :results question.

Finally, stories are defined by:

  (def-story <Ask-System-Name> <Number>
    <Title>
    <Question-Raised-List>
    <Questions-Answered-List>
    <Text>)

where the new fields are Title (a textual title for the story), and
questions-raised and answered, which are lists of the numbers of
questions raised and answered by this story. For example:

  (def-story :countries  2
    "Kenya's Population Problem"
    (5 7)
    (6)
    "In the early 1980's, it was estimated that Kenya's population was growing at the rate of about 4 percent a year, one of the highest in the world.")

The one exception to the above story format is that the first story that 
the browser should display will not have a number value.

* GOAL OF THIS EXERCISE

What we will be looking for will be good modularity in the code, good
legibility and clarity, and, of course, that it works correctly. Write
the best code you can-- code you would be proud to have someone else
read.


* DATA FILE

The data file attached at the end of this document should give you
enough information to support the following sample run of the
text-based ASK system.

See countries.sx for the data file you should read, which is in
"sexpr" format.  A parser for sexpr format has been provided in the
files SExprReader.cpp and SExprReader.hpp, which define two classes:
SExprReader, which reads sexpr format, and SExprObject, which
represents the parsed version.  You may also find it useful to look at
test.cpp, which demonstrates how to use the parser.  (Note that you
should write your code the way you think it should be written, not
based on the conventions or styles used in any of the supplied code.)


* EXAMPLE OUTPUT

Example run...

Welcome to the Countries Ask System

Welcome to the Countries Ask System. Choose from one of the countries below.

SPECIFICS

1.  Tell me about China..
2.  Tell me about Kenya..

Enter a number and hit [Enter]: 1

PRC: Introduction

China is a country in Asia ...

ANALOGIES AND SIMILARTIES

1.  What other countries are there?.

SPECIFICS

2.  What is unique about China?.

Enter a number and hit [Enter]: 2

China's Population Problem

The People's Republic of China has the largest population of any country on earth.

ANALOGIES AND SIMILARTIES

1.  Are there other countries beside China with population problems?.

Enter a number and hit [Enter] ('q' to quit): 1

Kenya's Population Problem

In the early 1980's, it was estimated that Kenya's population was growing at the rate of about 4 percent a year, one of the highest in the world.

LATER EVENTS AND RESULTS

1.  Does this growth cause any problems for Kenya?.

ANALOGIES AND SIMILARTIES

2.  Are there other countries beside Kenya with population problems?.

Enter a number and hit [Enter]: 

etc...

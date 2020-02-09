# Course Grade Calculator
## The input

The program's input is to be read from the standard input (i.e., std::cin). It is separated into four sections:

- A description of a course's graded artifacts, defining both a number of points possible and a relative weight for each.
- A description of the students in the course, listing a student ID, a grade option, and a name for each.
- A list of the raw scores received on each graded artifact by students in the course.
- A list of cutpoint sets, describing the total score required to receive an A, B, C, or D, respectively.
Each section is described in more detail below.

### Graded artifacts

The section describing graded artifacts begins with a positive integer, alone on a line, specifying the number of graded artifacts. This is followed, on another line, by a sequence of positive integers separated by spaces, indicating the total points possible on each graded artifact. Finally, on one more line, there will be a sequence of positive integers separated by spaces, indicating the relative weight of each graded artifact.

An example of this section would be:\
7\
15 15 15 15 15 50 50\
12 12 12 12 12 15 25

This example describes seven graded artifacts, the first five having 15 points possible and relative weights of 12, the sixth having 50 points possible and a relative weight of 15, and the last having 50 points possible and a relative weight of 25. Note that, in this example, the relative weights add up to 100; in general, however, this will not always be the case.

# Students

The next section of input describes the students enrolled in the course. It begins with a positive integer, alone on a line, specifying the number of students enrolled. Given that positive integer n, there will be n additional lines, each consisting of a non-negative integer student ID, followed by a space, followed by the student's grade option (G for "letter grade" or P for "Pass/NotPass"), followed by another space, followed by the student's name. Every character on the line after the grade option and space is considered to be part of the student's name. (It's important to note that the space following the grade option is not part of a student's name.) An example of this section would be:

5
123 G Alex Thornton
234 G Boo Thornton
345 G Jane Student
456 P Joe Student
567 G Too-Many Courses
Student IDs do not necessarily have to be three digits, and they do not necessarily all have to be the same number of digits.

### Raw scores

The next section of input describes the raw scores earned by students on each graded artifact. The section begins with a positive integer, alone on a line, specifying the number of students for which raw scores are listed. Given that positive integer n, there will be n additional lines, each consisting of a sequence of non-negative integers separated by spaces, the first of which is a student ID, and the rest of which are raw scores for each graded artifact. If there are m graded artifacts, you can assume each of these lines will contain m + 1 integers (one student ID, followed by m raw scores), and that the scores correspond, in order, to the graded artifacts listed in the first section. Example:

5
345 14 14 14 14 14 45 45
123 13 10 8 14 12 50 37
456 12 9 15 13 11 38 26
234 15 15 15 15 15 50 50
567 8 4 0 10 0 24 12
It is possible for a student to be listed in the previous section but not to be listed in this section. In that case, assume that the student's raw scores are all 0. It is also possible for a student to be listed in this section who does not appear in the previous section; in that case, ignore the student's raw scores, as the student is assumed to have dropped the course.

It is also possible for a raw score to be higher than the number of points possible on a graded artifact. This is to be interpreted as extra credit, and fits into the formula below as-is.

# Cutpoint sets

The last section of input is the cutpoint sets. This section begins with a positive integer, alone on a line, specifying the number of cutpoint sets. Given that positive integer n, the next n lines will consist of four non-negative numeric values (possibly including a decimal point and additional digits) that specify, respectively, the total points required for an A, B, C, or D in the course. Example:

3
90.0 80.0 70.0 60.0
85.0 75.0 65.0 55.0
80.0 70.0 60.0 50.0
Note that these are not percentages, necessarily; they indicate a total number of points necessary — this is described in more detail later in this write-up.

You may assume that each of the cutpoint values can safely be read into a variable of type double, and that the cutpoint values on each line will be non-ascending (e.g., the total points required for a higher grade like A will never be less than the total points required for a lower grade like B or C).

## The output

While reading the input, there are specified points at which output will be generated and printed to the standard output (i.e., std::cout). These are specified, along with the format of that output, below.

# Student roster

After reading the raw scores on all graded artifacts, but before reading the next section of the input, total scores are printed for all students. The format for this output is as follows:

The words TOTAL SCORES, alone on a line
For each student enrolled in the course, the student ID, followed by a space, followed by the student's name, followed by a space, followed by the student's total score
Example:

TOTAL SCORES
123 Alex Thornton 79.1
234 Boo Thornton 100
345 Jane Student 92
456 Joe Student 72.4
567 Too-Many Courses 30.8
It is not necessary to format the total score to a particular number of decimal places, though you should not truncate it or round it to an integer. Whatever way the C++ iostream library formats a double value by default is fine here.

# Course grades

After reading each cutpoint set, but before reading the next part of the input, final course grades for that cutpoint set are printed. For the purposes of this output, cutpoint sets are numbered consecutively starting from 1. The format of this output is as follows:

The words CUTPOINT SET n, alone on a line, where n is replaced by the cutpoint set number (1 for the first cutpoint set, 2 for the second, and so on)
For each student enrolled in the course, the student ID, followed by a space, followed by the student's name, followed by a space, followed by the student's grade
Example:

CUTPOINT SET 1
123 Alex Thornton C
234 Boo Thornton A
345 Jane Student A
456 Joe Student P
567 Too-Many Courses F

**How to use:**

While in the folder of FinancialSimulation.c file, use command: (Note you must enter a second arg for the outputFileName or else a segfault error will occur).
gcc && ./a.out inputFileName.txt outputFileName.txt

Where inputFileName and outputFileName are the names of your pre-existing input
and output files you wish to use. The output of the program will be printed to
the output file.

The input file should have the following format:
  string name (do not use "" here or the name will include "" in the output)
  int isFL (where 0 is not financially literate, and 1 is financially literate)
  int mortgageTerm
  int yearsWithDebt
  int yearsRented
  double savings
  double checkings
  double debt
  double loan
  double debtPaid
  double savingsIR
  double debtIR
  double houseIR
  double addlPay
  double rentAmt
  double mortgageAmount
  double yearlySalary

See input files for examples of correctly formatted input files.

**Explanation:**

This program is designed to model the wealth of a person who is or is not
financially literate over 40 years, where wealth = savings + checking - debt - loan.

In this program, the main difference is that FL (financially literate) people will
buy a house with 20% of the mortgage down payment, such that they do not have to
pay the extra .5% interest on their mortgage for mortgage insurance.

Other values such as savings interest rate (savingsIR), debt interest rate (debtIR),
additional debt payment (addlPay) etc. will need to be inputted by the user.
Although FL people will typically have higher savingsIR and addlPay.

The output file will display the amount of wealth outputted every year, with
year 40 displaying the final wealth of the person at the end of 40 years, and
the amount of debt in total paid, and over how many years this person was in
debt (not counting the loan on the house).

**Extensions and Limitations:**

In addition to all the functions added for the project, I also included a
printPerson function, which will print the person's savings, checkings, debt, and
loan amount. Which was created for bug fixing.

The limitations of the program is that the user must already have an input file
and output file in their FinancialSimulation directory, as the program will not
work without these two arguments, although the names of the input and output
of the file do not matter, I would recommend that these files are of type .txt
as that is what I have used.

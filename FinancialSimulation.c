#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
/*
 * Function creates financialIdentity with attributes below, can be called as person.
 */
typedef struct financialIdentity{
  char name[128];
  int isFL; //0 = NFL, 1 = FL
  int mortgageTerm;
  int yearsWithDebt;
  int yearsRented;
  double savings;
  double checkings;
  double debt;
  double loan;
  double debtPaid;
  double savingsIR;
  double debtIR;
  double houseIR;
  double addlPay;
  double rentAmt;
  double mortgageAmount;
  double yearlySalary;




} Person; //Does not have to be same name as struct name.

int wealthArray[41]; //initialize array for simulate

void printPerson(struct financialIdentity *person){
  printf("Savings: %lf\nCheckings: %lf\nDebt: %lf\nLoan: %lf\n", person->savings, person->checkings, person->debt, person->loan);
}

/*
* Funcction increases money in savings by multiplying savings by the interest rate + 1
* @param *person the struct person who is saving
* @param interestRate interest rate of the savings acccount
*/
void savingsPlacement(struct financialIdentity *person, double interestRate){

    person->savings = person->savings * (1 + interestRate);
}
/*
* Function pays debt over 1 year, in 1 month increments
* @param *person the struct person who has debt
* @param interestRate interest rate of the debt
* @param addlPay how much extra the person pays on their debt
*/
void debt(struct financialIdentity *person, double interestRate, double addlPay){
  double debtAfterMonth;
  double debtPaid;
  double flDebtAfterMonth;
  double flDebtPaid;
  for(int i = 0; ((person->debt > 0) && (i < 12)); i++){
    debtPaid = (person->debt * interestRate) + addlPay;
    person->debtPaid += debtPaid;
    debtAfterMonth = (person->debt * (1 - interestRate)) - addlPay;

    if(person->debt < addlPay){ //if debt < addlPay, subtract remaining debt and break loop, so debt is not > 0.
      if(person->checkings > 0){
        person->checkings -= person->debt;
        person->debt = 0;
      }
      if(person->checkings < 0){
        person->savings -= person->debt;
        person->debt = 0;
    }
    break;
  }


      if(person->checkings > 0){
        person->checkings -= debtPaid;
      }
      if(person->checkings < 0){
        person->savings -= debtPaid;
      }
      person->debt = debtAfterMonth;
    }

  if(person->debt > 0){
    person->yearsWithDebt++;
    person->debt = person->debt * 1.2;
  }
}

/*
* Function pays rent
* @param *person the struct person who is renting
* @param rentAmt rent cost per month
*/
void rent(struct financialIdentity *person, double rentAmt){
  if(person->checkings < 0){
    person->savings -= rentAmt;
  }
  if(person->checkings > 0){
    person->checkings -= rentAmt;
  }
  person->yearsRented++;
}
/*
* Function pays house mortgage off
* @param *person the struct person who is renting
* @param mortgageAmount total mortgage - down payment
* @param interestRate house Interest rate
* @param mortgageTerm how long the mortgage is
*/
 void house(struct financialIdentity *person, double mortgageAmount, double interestRate, int mortgageTerm){ //house payment will be the same forever
   int n = mortgageTerm * 12; //or just 360 if for 30 years
   double i = interestRate / 12.0;
   double discountFactor = (pow((1 + i), n) - 1) / ((i) * (pow((1 + i), n)));
   double monthlyPayment = mortgageAmount / discountFactor;


   for(int i = 0; i < 12; i++){
     if(person->loan <= monthlyPayment){

       if(person->checkings > 0){
         person->checkings -= person->loan;
       }
       if(person->checkings < 0){
         person->savings -= person->loan;
       }
       person->loan = 0;
       break;
     }
     else{
       person->loan -= monthlyPayment;

       if(person->checkings > 0){
         person->checkings -= monthlyPayment;
       }
       if(person->checkings < 0){
         person->savings -= monthlyPayment;
       }
   }


   }
    person->loan = person->loan * (1 + interestRate);
 }

 /*
 * Function simulates person's total wealth over 40 years
 * @param *person the struct person who is renting
 * @param yearlySalary person's yearly income
 * @param financiallyLiterate is the person financiallyLiterate
 */
int* simulate(struct financialIdentity *person, double yearlySalary, bool financiallyLiterate){
  int initialWealth = person->savings - person->debt;
  wealthArray[0] = initialWealth;
  int wealth;
  bool hasHouse = false;
  double houseAmt = person->mortgageAmount;

  for(int i = 1; i < 41; i++){

    savingsPlacement(person, person->savingsIR);
    debt(person, person->debtIR, person->addlPay);

    if(hasHouse == false && person->isFL == 0 && person->savings > (houseAmt * .05)){
      hasHouse = true;
      person->loan = houseAmt * .95; //nonFL person
      person->savings -= houseAmt * .05;
    }
    if(hasHouse == false && person->isFL == 1 && person->savings > (houseAmt * .2)){
      hasHouse = true;
      person->loan = houseAmt * .80;
      person->savings -= houseAmt * .20;
    }
    if(hasHouse == false){
      rent(person, person->rentAmt);
    }
    if(hasHouse == true && person->loan > 0 && person->isFL == 1 ){
      house(person, houseAmt * .80, person->houseIR, person->mortgageTerm);
    }
    if(hasHouse == true && person->loan > 0 && person->isFL == 0){
      house(person, houseAmt * .95, person->houseIR, person->mortgageTerm);
    }
    wealth = person->checkings + person->savings - person->debt - person->loan;
    person->checkings += .3 * yearlySalary;
    person->savings += .2 * yearlySalary;
    wealthArray[i] = wealth;
    

 }
 return wealthArray;
}

/*
* Function runs program injunction with the other functions
* @param argc needed
* @param argv command line arguments for input
*/
int main(int argc, char* argv[]){
  Person *person = malloc(sizeof(*person)); //Create person, allocate memory for them.

  char const* const fileNameRead = argv[1]; /* First arg is input file */
  char const* const fileNameWrite = argv[2]; /* Second arg is output file */
  FILE* fileR = fopen(fileNameRead, "r");
  FILE* fileW = fopen(fileNameWrite, "w");

  fscanf(fileR, "%s %d %d %d %d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", person->name, &person->isFL, &person->mortgageTerm, &person->yearsWithDebt, &person->yearsRented, &person->savings, &person->checkings, &person->debt, &person->loan, &person->debtPaid, &person->savingsIR, &person->debtIR, &person->houseIR, &person->addlPay, &person->rentAmt, &person->mortgageAmount,  &person->yearlySalary);
  // ^scans in all values in input txt file

  int *wealthArr = simulate(person, person->yearlySalary, (person->isFL == 1)); //if person isFL person->isFL value = 1, and is true, else it is false.
  fprintf(fileW,"%s Wealth Over Time:\n", person->name);
  for(int i = 0; i < 41; i++){
    fprintf(fileW,"Year: %d Wealth Amount: %d\n", i, wealthArr[i]);
  }
  fprintf(fileW,"%lf Debt Paid Over 40 years:\n", person->debtPaid);
  fprintf(fileW,"%d Years in debt Over Time:\n", person->yearsWithDebt);

  fclose(fileR);
  fclose(fileW);
  free(person);
}

// Compute a load payment schedule

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

// house $306,000.00 * 0.9 = 275,400.00
//
// closing cost
// 2,000 earnest money is given back


// taxes and insurance $222 / month
// mortgage insurance $66.55 / month til < 80% of house cost

// All money amounts in pennies
static const int64_t cost_of_house = 30600000;

static const int64_t start_principle = 27540000; // 10% down
static const double rate = 0.03375/12.0;
static int64_t default_payment = 400000; // pennies

// added charges // pennies
static const int64_t mortgage_insure = 6655; // til at %80 or lower
static const int64_t tax_insure = 22200;


static inline
int64_t get_payment(int32_t month)
{
    return default_payment;
}

static inline
int64_t charges(int64_t princple)
{
    double d;
    d = princple * rate + tax_insure;
    if(princple > 30600000 * 0.80)
        d += mortgage_insure;

    // round up pennies greater than one half
    int64_t i;
    i = d + 0.5;
    return i;
}


static inline
void print(int32_t month,
        int month_num, int year,
        int64_t payment,
        int64_t princple_paid,
        int64_t princple_forward,
        int64_t total)
{
    //          months      years
    printf("%3.2" PRId32", %6.3lf, "
            // month_num  year
            "%3.2d, %4d "
            // pay  princ_paid
            "%8.2lf, %8.2lf, "
            // pric_forward  total_paid
            "%9.2lf, %9.2lf\n",
            month,
            month/12.0,
            month_num, year,
            payment * 0.01,
            princple_paid * 0.01,
            princple_forward * 0.01,
            total * 0.01);
 
}

int main(int argc, char **argv)
{
    if(argc == 2) {

        int64_t in;
        in = strtol(argv[1], NULL, 10);
        if(in < 10)
            in = 10000;
        else if(in > start_principle)
            in = start_principle;
        default_payment = in;
    }

    int32_t month = 0; // time starts at 0 with balance start_principle
    int64_t principle = start_principle; // balance left
    int64_t total = 0;   // pennies total paid
    // Initialize date
    static int month_num = 2; // 1 - 12
    static int year = 2017; // 2017 to 2040 or whatever

    printf("months, years, month, year, payment, princ_paid,"
            " principle, total_paid\n");

    print(month++, 0, 0, 0, 0, principle, total);
    

    while(principle > 0) {

        int64_t payoff;  // pennies cut off the principle in the month
        int64_t charge;  // pennies charged in the month
        int64_t payment; // pennies

        charge = charges(principle);
        
        payment = get_payment(month);
        payoff = payment - charge;

        if(principle < payoff) {
            payment = charge + principle;
            payoff = payment - charge;
        }

        total += payment;

        print(month++, month_num, year,
                payment, payoff, principle - payoff, total);
        principle -= payoff;

        // next month and year
        month_num++;
        if(month_num > 12) {
            month_num = 1;
            year++;
        }

    }

    return 0;
}


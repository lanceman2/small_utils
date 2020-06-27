// Compute a load payment schedule

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

// All numbers in pennies.

static const int64_t start_principle = 17084286; // pennies
 
static const double rate = 0.03625/12.0; // /12 ==> monthly
static int64_t default_payment = 750000; // pennies

// added charges // pennies
static const int64_t constant_payment = 29407; // pennies cost every month

static inline
int64_t get_payment(int32_t month)
{
    return default_payment;
}

static inline
int64_t charges(int64_t princple)
{
    double d;
    d = princple * rate + constant_payment;

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
            "%3.2d, %4d, "
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

/*

months, years, month, year, payment, princ_paid, principle, total_paid
 00,  0.000,  02, 2020,     0.00,     0.00, 187319.65,      0.00
 01,  0.083,  03, 2020,  2471.81,  1611.88, 185707.77,   2471.81
 02,  0.167,  04, 2020,  2471.81,  1616.75, 184091.02,   4943.62
 03,  0.250,  05, 2020,  2471.81,  1621.63, 182469.39,   7415.43
 04,  0.333,  06, 2020,  2471.81,  1626.53, 180842.86,   9887.24
 05,  0.417,  07, 2020,  2471.81,  1631.44, 179211.42,  12359.05
 06,  0.500,  08, 2020,  2471.81,  1636.37, 177575.05,  14830.86
 07,  0.583,  09, 2020,  2471.81,  1641.32, 175933.73,  17302.67
 08,  0.667,  10, 2020,  2471.81,  1646.27, 174287.46,  19774.48
 09,  0.750,  11, 2020,  2471.81,  1651.25, 172636.21,  22246.29
 10,  0.833,  12, 2020,  2471.81,  1656.23, 170979.98,  24718.10
 11,  0.917,  01, 2021,  2471.81,  1661.24, 169318.74,  27189.91
 12,  1.000,  02, 2021,  2471.81,  1666.26, 167652.48,  29661.72

 13,  1.083,  03, 2021,  6471.81,  5660.36, 161992.12,   6471.81
 14,  1.167,  04, 2021,  6471.81,  5677.46, 156314.66,  12943.62
 15,  1.250,  05, 2021,  6471.81,  5694.61, 150620.05,  19415.43
 16,  1.333,  06, 2021,  6471.81,  5711.81, 144908.24,  25887.24
 17,  1.417,  07, 2021,  6471.81,  5729.07, 139179.17,  32359.05
 18,  1.500,  08, 2021,  6471.81,  5746.37, 133432.80,  38830.86
 19,  1.583,  09, 2021,  6471.81,  5763.73, 127669.07,  45302.67
 20,  1.667,  10, 2021,  6471.81,  5781.14, 121887.93,  51774.48
 21,  1.750,  11, 2021,  6471.81,  5798.61, 116089.32,  58246.29
 22,  1.833,  12, 2021,  6471.81,  5816.12, 110273.20,  64718.10
 23,  1.917,  01, 2022,  6471.81,  5833.69, 104439.51,  71189.91
 24,  2.000,  02, 2022,  6471.81,  5851.32,  98588.19,  77661.72
 25,  2.083,  03, 2022,  6471.81,  5868.99,  92719.20,  84133.53
 26,  2.167,  04, 2022,  6471.81,  5886.72,  86832.48,  90605.34
 27,  2.250,  05, 2022,  6471.81,  5904.50,  80927.98,  97077.15
 28,  2.333,  06, 2022,  6471.81,  5922.34,  75005.64, 103548.96
 29,  2.417,  07, 2022,  6471.81,  5940.23,  69065.41, 110020.77
 30,  2.500,  08, 2022,  6471.81,  5958.17,  63107.24, 116492.58
 31,  2.583,  09, 2022,  6471.81,  5976.17,  57131.07, 122964.39
 32,  2.667,  10, 2022,  6471.81,  5994.23,  51136.84, 129436.20
 33,  2.750,  11, 2022,  6471.81,  6012.33,  45124.51, 135908.01
 34,  2.833,  12, 2022,  6471.81,  6030.50,  39094.01, 142379.82
 35,  2.917,  01, 2023,  6471.81,  6048.71,  33045.30, 148851.63
 36,  3.000,  02, 2023,  6471.81,  6066.99,  26978.31, 155323.44
 37,  3.083,  03, 2023,  6471.81,  6085.31,  20893.00, 161795.25
 38,  3.167,  04, 2023,  6471.81,  6103.70,  14789.30, 168267.06
 39,  3.250,  05, 2023,  6471.81,  6122.13,   8667.17, 174738.87
 40,  3.333,  06, 2023,  6471.81,  6140.63,   2526.54, 181210.68
 41,  3.417,  07, 2023,  2839.17,  2526.54,      0.00, 184049.85

   */


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
    static int month_num = 6; // 1 - 12
    static int year = 2020; // 2017 to 2040 or whatever

    printf("months, years, month, year, payment, princ_paid,"
            " principle, total_paid\n");

    print(month++, month_num++, year, 0, 0, principle, total);
    

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


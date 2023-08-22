#include <stdio.h>
#include <math.h> ///include library for calculating root of a discriminant
#include <assert.h> ///include library for checking coefficients and roots for real values

const double eps = 0.000001; /*!
                                  \brief Epsilon
                                  \details The most approximate number to zero
                                  \details for comparisons of double numbers
                                */

enum number_of_roots {///Enumeration for number of roots and detect errors
    none_solution, ///< indicates that there is not root
    one_solution,  ///< indicates that there is one root
    two_solution,  ///< indicates that there are two roots
    any_solution,  ///< indicates that there are an infinite number of roots
    ERR            ///< indicates that there is an error
};

number_of_roots solve_a_linear_equation(double b, double c, double* x1);
number_of_roots solve_a_quadratic_equation(double a, double b, double c, double* x1, double* x2);

bool check_equality(double x, double y); /// function for checking equality two double numbers
void get_input(double* a, double* b, double* c); ///function for input coefficients from keyboard
void output(number_of_roots, double x1, double x2); ///function for output roots on display
/*!
    \brief The main file in this project
    \author Usoltsev Ivan
    \version 1.0
    \date 22.08.2023
    \warning Input is not prepared for incorrect input
    This file contains algorithm for solving quadratic equations

    */
int main(){

    printf("# Square equation solver\n"
           "# (c) Ded, 2023\n"); ///some words about the program

    double a = 0, b = 0, c = 0; ///declaring coefficients of a quadratic equation

    get_input(&a, &b, &c); ///getting coefficients values

    double x1 = 0, x2 = 0; ///declaring roots
    number_of_roots nRoots = solve_a_quadratic_equation(a, b, c, &x1, &x2); ///calling a function to calculate roots

    output(nRoots, x1, x2); ///output roots to the display

    return 0;
}
/*!
    \brief function for input coefficients from keyboard
    \details this function gets addresses of the coefficients from keyboard and declare values to it
    \param *a, *b, *c are coefficients of the equation
    */
void get_input(double* a, double* b, double* c){
    printf("Enter a, b, c:\n"); ///advice to the user
    scanf("%lg %lg %lg", &*a, &*b, &*c); ///input coefficients from keyboard
}
/*!
    this function gets number of roots and roots and output it on display with short message in relation to number of roots
    \param nRoot  calculate number of roots or detect error
    \param x1, x2 are roots of the equation
    */
void output(number_of_roots nRoots, double x1, double x2){ ///output roots to the display


    switch(nRoots){

        case none_solution: printf("No Roots\n");
                break;

        case one_solution: printf("x = %lf\n", x1);
                break;

        case two_solution: printf("x1 = %lf, x2 = %lf\n", x1, x2);
                break;

        case any_solution: printf("Any number\n");
                break;

        case ERR: printf("There is an ERROR in program\n");
                break;

        default: printf("main(): ERROR: nRoots = %d\n", nRoots);
                break;
        }

    printf("The equation is solved!\n");
}
/*!
    \brief the function for calculate number of roots and roots
    \detail This function gets coefficients and addresses of roots, checking it for correctness and then calculate number of roots and roots
    \param a, b, c are coefficients of the quadratic equation
    \param *x1, *x2 are addresses of roots
    \return {number of roots}
    */

number_of_roots solve_a_quadratic_equation(double a, double b, double c, double* x1, double* x2){
    /*!
        checking coefficients for realness
        */
    assert (isfinite (a));
    assert (isfinite (b));
    assert (isfinite (c));
    /*
        checking addresses of roots for realness and equality
        */
    assert (x1 != NULL);
    assert (x2 != NULL);
    assert (x1 != x2);

    if (check_equality(a, 0.0)){ ///if a is zero it means that the equation is linear
        return solve_a_linear_equation(b, c, x1); ///solving a linear equation
    } else {

        double D = b * b - 4 * a * c; ///calculating a discriminant

        if (D < 0){ ///checking for the availability of roots
            return none_solution;
        } else if (check_equality(D, 0)){ ///if there is inly one roots, we calculate it with using this formula
            *x1 = -b/(2*a);
            return one_solution;
        } else {
            double sD = sqrt(D); ///calculation root of the discriminant with using math.h library
            *x1 = (-b + sD)/(2*a);
            *x2 = (-b - sD)/(2*a);
            return two_solution;
        }
    }

    return ERR; ///if none of the returns operated we return ERR witch means error in code
}

/*!

    This function gets b and c coefficients and address of root. Than calculate number of roots (0, 1 or infinity) and return it
    \param b, c are coefficients of the linear equation
    \param x1 is root of the equation
    \return {number of roots}
    */

number_of_roots solve_a_linear_equation(double b, double c, double* x1){

    if (check_equality(b, 0.0)){

        if (check_equality(c, 0.0)){
            return any_solution;
        } else {
            return none_solution;
        }

    } else {
        *x1 = -c/b;
        return one_solution;
    }

    return ERR;
}

/*!
    this program check equality of two double numbers with taking into account the calculation error
    \param x, y to comparing
    \return {bool variable true or false}
    */

bool check_equality(double x, double y){

    if ((x > (y - eps)) && (x < (y + eps))){ ///Is x about y? Checking taking into account the calculation error
        return true;
    } else {
        return false;
    }
}

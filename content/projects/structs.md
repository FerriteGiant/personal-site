+++
date = "2018-02-18T22:45:06-06:00"
title = "C Structs"
showonlyimage = false
image = "projects/structs/LinkImage_Structs.png"
draft = false

+++
An overview of declaring and accessing structs.
<!--more-->

A collection of examples for quick reference. For more info I recommend the [tutorialspoint](https://www.tutorialspoint.com/cprogramming/c_structures.htm) page and section 6.7.2.1 "Structure and union specifiers" in the [current C11 standard](http://www.open-std.org/JTC1/SC22/WG14/www/docs/n1570.pdf). 

The following code can be run and forked at [https://onlinegdb.com/HyJkapYvG](https://onlinegdb.com/HyJkapYvG).

``` c
#include <stdio.h>

int main()
{
    ////////////////////////////////////////
    // Declaring a struct without typedef //
    ////////////////////////////////////////
    
    /// Method 1 ///
    
    /* The form of the stuct is defined and given the identifier _vectorA */
    /* The vectorA variable is then declared to be a struct of form _vectorA */
    /* (The underscore has no special meaning here.) */
    struct _vectorA {
        int x;
        int y;
    };
    struct _vectorA vectorA;
    
    /* Members x and y are accessed using the '.' operator */
    vectorA.x = 10;
    vectorA.y = 20;
    printf("vectorA: (%d,%d)\n",vectorA.x,vectorA.y);
    
    
    /// Method 2 ///
    
    /* The form of the struct is included in the declaration statement */
    /* for vectorB. The form identifier can be reused later to declare */
    /* additional structs with the same form, such as vectorB2 */
    
    struct _vectorB {
        int x;
        int y;
    } vectorB;
    
    struct _vectorB vectorB2;
    
    vectorB.x = 30;
    vectorB.y = 33;
    vectorB2.x = 36;
    vectorB2.y = 37;
    printf("vectorB: (%d,%d)\n",vectorB.x,vectorB.y);
    printf("vectorB2: (%d,%d)\n",vectorB2.x,vectorB2.y);
    
    /// Method 3 - variation ///
    
    /* If the struct form is combined with the declaration, the form */
    /* identifier is optional. Of course without it, no additional stucts */
    /* of the same form can be declared later on. */
    
    struct {
        int x;
        int y;
    } vectorC;
    
    vectorC.x = 40;
    vectorC.y = 44;
    printf("vectorC: (%d,%d)\n",vectorC.x,vectorC.y);
    
    ///Method 4///
    
    /* In addition to declaring a variable as a struct, a variable may be */
    /* declared as a pointer to a struct. Multiple struct variables and */
    /* pointers to structs may be declared at the same time */
    /* (Once again, the struct identifier _vectorD is optional) */
    struct _vectorD {
        int x;
        int y;
    } vectorD, *vectorD_ptr=NULL;
    vectorD_ptr = &vectorD;
    
    vectorD.x = 50;
    vectorD.y = 55;
    printf("vectorD: (%d,%d)\n",vectorD.x,vectorD.y);
    
    /* When accessing a struct member via a pointer, one must use '->' */
    vectorD_ptr->x = 56;
    vectorD_ptr->y = 59;
    printf("vectorD: (%d,%d) ",vectorD_ptr->x,vectorD_ptr->y);
    printf("//Set and accessed via pointer\n");
    
    
    
    //////////////////////////////////////
    // Declaring a struct using typedef //
    //////////////////////////////////////
    
    /* A new variable type may be defined using typedef, which can then be */
    /* used to declare variables and pointers to variables, etc... just like */
    /* any other data type.  */
    typedef struct _vectorE { //Or just: typedef struct {
        int x;
        int y;
    } vectorE_type;
    
    /* Decare vectorE and vectorE_ptr which will hold the address of vectorE */
    vectorE_type vectorE, *vectorE_ptr=NULL;
    vectorE_ptr = &vectorE;
    
    vectorE.x = 60;
    vectorE.y = 66;
    printf("vectorE: (%d,%d)\n",vectorE.x,vectorE.y);
    
    vectorE_ptr->x = 63;
    vectorE_ptr->y = 65;
    printf("vectorE: (%d,%d) ",vectorE_ptr->x,vectorE_ptr->y);
    printf("//Set and accessed via pointer\n");
    
    
    return 0;
}
```
Console output:

```
vectorA: (10,20)
vectorB: (30,33)
vectorB2: (36,37)
vectorC: (40,44)
vectorD: (50,55)
vectorD: (56,59) //Set and accessed via pointer
vectorE: (60,66)
vectorE: (63,65) //Set and accessed via pointer
```

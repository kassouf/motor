#include "util_obj.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define IS_NULL(x)(((x) == NULL))

#ifndef PMK_MOTOR_UTIL_OBJ_H
#error "INCLUDE Directory is messed up... check makefile and command line settings"
#endif 
 
MOTOR_FUNCTION Convert_abc_to_alfabeta(const double *i_src, double *i_dest){
  if (unlikely(IS_NULL(i_src) || IS_NULL(i_dest))){
    return MOTOR_NULL_VECTOR_ERROR;
  }else{
    register double ia, ib;
    ia = i_src[IA];
    ib = i_src[IB];

    i_dest[IALFA]= 1.5 * ia;
    i_dest[IBETA]= SQRT_3_2 * (ia + 2.0 * ib);
  }
  return MOTOR_NO_ERROR;
}


MOTOR_FUNCTION Convert_alfabeta_to_dq(const double *i_src, double theta, double *i_dest){

  if (unlikely(IS_NULL(i_src) || IS_NULL(i_dest))){
    return MOTOR_NULL_VECTOR_ERROR;
  }else{
    register double i_alfa, i_beta;
    i_alfa = i_src[IALFA];
    i_beta = i_src[IBETA];

    i_dest[ID] = i_alfa * cos(theta) + i_beta * sin(theta);
    i_dest[IQ] = -i_alfa * sin(theta) + i_beta * cos(theta);
  }
  return MOTOR_NO_ERROR;
}

MOTOR_FUNCTION Convert_dq_to_alfabeta(const double *i_src, double theta, double *i_dest){
  if (unlikely(IS_NULL(i_src) || IS_NULL(i_dest))){
    return MOTOR_NULL_VECTOR_ERROR;
  }else{
    register double id, iq;
    id = i_src[ID];
    iq = i_src[IQ];

    i_dest[IALFA] = id * cos(theta) - iq * sin(theta);
    i_dest[IBETA] = +id * sin(theta) + iq * cos(theta);
  }
  return MOTOR_NO_ERROR;
}

MOTOR_FUNCTION Convert_alfabeta_to_abc(const double *i_src, double *i_dest){
  if (unlikely(IS_NULL(i_src) || IS_NULL(i_dest))){
    return MOTOR_NULL_VECTOR_ERROR;
  }else{
    register double ialfa, ibeta;
    ialfa = i_src[IALFA];
    ibeta = i_src[IBETA];

    i_dest[IA]= 2.0 * ialfa / 3.0;
    i_dest[IB]= 2.0 * ((-ialfa/2.0) + SQRT_3_2 * ibeta) / 3.0;
    i_dest[IC]= 2.0 * ((-ialfa/2.0) - SQRT_3_2 * ibeta) / 3.0;
  }
  return MOTOR_NO_ERROR;  
}


void Parse_Error(motor_err_t error, char *function, int quiet){
  if(error == 0){
    if (unlikely(quiet==0)){
      printf("Error Report:\n\tError Code: 0x%08x\n",(int)error);
      printf("\tNo Error Detected in %s\n",function);
    }
    return;
  }
  printf("Error Report:\n\tError Code: 0x%08x\n",(int)error);
  if(error && MOTOR_NULL_VECTOR_ERROR){
    printf("\tMOTOR_NULL_VECTOR_ERROR: ");
    printf("One of the vectors passed to %s was null.\n", function);
  }

  exit(-1);
}



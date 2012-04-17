#include <stdio.h>
#include "motor.h"

#define QUIET 1

int main(){
  double i_abc[3], i_alfabeta[2], i_dq[2];
  double i_alfabeta_prime[2], i_dq_prime[2];
  motor_err_t err;

  double theta;
  int i;
  
 
  //open loop simulation
  i_dq[ID]=0.0;
  i_dq[IQ]=1.0; //1 Amp for example
  
  printf("Header\n");
  printf("i, theta, id, iq, ialfa, ibeta, ia, ib, ic, ialfa_prime, ibeta_prime, id_prime, iq_prime\n");
  for (i=0; i<360; i++){
    theta = TO_RADIANS(i);
    
    err = Convert_dq_to_alfabeta(i_dq, theta, i_alfabeta);
    Parse_Error(err, "Convert_dq_to_alfabeta", QUIET);

    err = Convert_alfabeta_to_abc(i_alfabeta, i_abc);
    Parse_Error(err, "Convert_dq_to_alfabeta", QUIET);
   
    err = Convert_abc_to_alfabeta(i_abc, i_alfabeta_prime);
    Parse_Error(err, "Convert_dq_to_alfabeta", QUIET);
    
    err = Convert_alfabeta_to_dq(i_alfabeta_prime, theta, i_dq_prime);
    Parse_Error(err, "Convert_dq_to_alfabeta", QUIET);

    printf("%d, %2.5f; %2.5f, %2.5f; %2.5f, %2.5f; %2.5f, %2.5f, %2.5f; %2.5f, %2.5f; %2.5f, %2.5f\n",
	   i, theta, 
	   i_dq[ID], i_dq[IQ],
	   i_alfabeta[IALFA], i_alfabeta[IBETA],
	   i_abc[IA], i_abc[IB], i_abc[IC],
	   i_alfabeta_prime[IALFA], i_alfabeta_prime[IBETA],
	   i_dq_prime[ID], i_dq_prime[IQ]);
  }
  return 0;
}

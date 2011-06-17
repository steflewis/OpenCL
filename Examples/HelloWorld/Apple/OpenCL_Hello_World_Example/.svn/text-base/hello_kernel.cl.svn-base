// OpenCL kernel from Apple HelloWorld example
/*
 * I'm using this as a testbed for OpenCL capabilities
 * 
 * */

// This seems to work after a fashion
#define W 16
#define H 16
//#define BSZ 256 //(W*H)
#define BSZ (W*H)

//Surprisingly, this works too
typedef short PixVal; 
typedef float Entropy;
typedef struct {
    PixVal threshold;
    Entropy entropy;
} ThresholdEntropy ;

// This works OK
float compute(float val) {

    ThresholdEntropy te;
    te.threshold=2;
    te.entropy=1.0;
    return (te.threshold-te.entropy)*val*val;

}
float getVal(__global float* input, int i) {
	return input[i];
}
// This breaks OpenCL!
/*
//int addArray (int a[BSZ]) { // this is not the reason
int addArray (__private int *a) {
    int tot=0;
    int i;
    for (i=0;i<BSZ;i++) {
        int tmp=i;
//        int tmp=a[i]; // this breaks
        tot+=tmp;
    }
    return tot;
}
*/

// This seems to work
__local short a[W][H];
// But this is broken:
//__private Pixval a[BSZ];

short addArrayG(void);

__kernel void square(                                                       
   __global float* input,                                              
   __global float* output,                                             
   const unsigned int count)                                           
{                                                                      
   int i = get_global_id(0); 
    short tot=0;
    int j,k;
    for (j=0;j<W;j++) {
        for (k=0;k<H;k++) {
        a[j][k]=j;
        tot+=j;
        }
    }
    short res=addArrayG();
    res-=tot;
       //output[i] = input[i] * input[i];                                
    output[i] =res+compute( getVal(input,i) );                                
}   

short addArrayG(void) {
    short tot=0;
    int i;
    int j,k;
      for (j=0;j<W;j++) {
          for (k=0;k<H;k++) {
          short tmp = a[j][k];
          tot+=tmp;
          }
      }    
    return tot;
}



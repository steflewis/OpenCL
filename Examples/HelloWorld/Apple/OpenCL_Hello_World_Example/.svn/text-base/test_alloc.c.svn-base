#include <stdlib.h>

#define DATA_SIZE (2*1024*1024) 

int main (void) {
    float data[DATA_SIZE];              // original data set given to device
// Fill our data set with random float values
                        //
//    float* data=(float*)malloc(sizeof(float)*DATA_SIZE);
    const unsigned int count = DATA_SIZE;
    unsigned int i;
    for(i = 0; i < count; i++)
        data[i] = rand() / (float)RAND_MAX;
    return 0;

}

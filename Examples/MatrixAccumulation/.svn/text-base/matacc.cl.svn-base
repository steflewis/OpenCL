/*
 A simple float matrix multiplication from scratch, on a 1024x1024 matrix
 The first version computes from global memory
 The second tries to use the local memory
 I have 16KB so I can store 4K floats, means I can load 2 rows and 2 cols at once, that is not much
 The third version uses SIMD, but with 2 rows and 2 cols that is rather limited. I can use float2 bit not float2


First, I need to work out a partitioning strategy, but for 1. this is trivial, for 2. the memory determines it

Then I write it in C-ish , then in proper OpenCL
*/
// By row
__kernel void mataccKernel1 (
    __global float *mA,
    __global float *mC,
    const unsigned int mWidth) {
	unsigned int g_id = get_group_id(0);
	unsigned int nunits=get_num_groups(0);
    float elt=0.0;
    for (unsigned int i=0;i<mWidth/nunits;i++) {    
    	for (unsigned int j=0;j<mWidth;j++) {
        	elt+=mA[i*mWidth+j];
        }
    }
    mC[g_id]=elt;

}
// by col
__kernel void mataccKernel2 (
    __global float *mA,
    __global float *mC,
    const unsigned int mWidth) {
	unsigned int g_id = get_group_id(0);
	unsigned int nunits=get_num_groups(0);
    float elt=0.0;
    for (unsigned int i=0;i<mWidth/nunits;i++) {    
        for (unsigned int j=0;j<mWidth;j++) {
        	elt+=mA[j*mWidth+i];
        }
    }
    mC[g_id]=elt;

}
// By block 64x64
__kernel void mataccKernel3 (
    __global float *mA,
    __global float *mC,
    const unsigned int mWidth) {
	unsigned int g_id = get_group_id(0);
	unsigned int nunits=get_num_groups(0);
    const unsigned int bWidth=64;
    const unsigned int bSize=4096;
    unsigned int bs = mWidth/bWidth;
    float elt=0.0;
    for (unsigned int br=0;br<bs/nunits;br++) {
    	for (unsigned int bc=0;bc<bs;bc++) {   
			for (unsigned int i=0;i<bWidth;i++) {    
				for (unsigned int j=0;j<bWidth;j++) {
					elt+=mA[br*bWidth*mWidth+bc*bWidth+j+mWidth*i];
				}
			}
    	}
    }
    mC[g_id]=elt;

}
// linear, float4
__kernel void mataccKernel4 (
    __global float4 *mA,
    __global float *mC,
    const unsigned int mWidth) {
	unsigned int g_id = get_group_id(0);
	unsigned int nunits=get_num_groups(0);
    float4 elt=(float4)(0.0);
    for (unsigned int idx=0;idx<mWidth*mWidth/4/nunits;idx++) {    
//    for (unsigned int i=0;i<mWidth;i++) {
//    	for (unsigned int j=0;j<mWidth/4;j++) {
//    		unsigned int idx=i*mWidth/4+j;
    		float4 mAtmp=mA[idx];//*mWidth+j];
        	elt.s0+=mAtmp.s0;
        	elt.s1+=mAtmp.s1;
        	elt.s2+=mAtmp.s2;
        	elt.s3+=mAtmp.s3;
//        }
    }
    mC[g_id]=elt.s0+elt.s1+elt.s2+elt.s3;

}

// linear, float8

__kernel void mataccKernel5 (
    __global float8 *mA,
    __global float *mC,
    const unsigned int mWidth) {
	unsigned int g_id = get_group_id(0);
	unsigned int nunits=get_num_groups(0);
    float8 elt=(float8)(0.0);
    for (unsigned int idx=0;idx<mWidth*mWidth/8/nunits;idx++) {    
    		float8 mAtmp=mA[idx];
        	elt.s0+=mAtmp.s0;
        	elt.s1+=mAtmp.s1;
        	elt.s2+=mAtmp.s2;
        	elt.s3+=mAtmp.s3;
        	elt.s4+=mAtmp.s4;
        	elt.s5+=mAtmp.s5;
        	elt.s6+=mAtmp.s6;
        	elt.s7+=mAtmp.s7;

    }
    mC[g_id]=elt.s0+elt.s1+elt.s2+elt.s3+elt.s4+elt.s5+elt.s6+elt.s7;

}

// linear, float16

__kernel void mataccKernel6 (
    __global float16 *mA,
    __global float *mC,
    const unsigned int mWidth) {
	unsigned int g_id = get_group_id(0);
	unsigned int nunits=get_num_groups(0);
    float16 elt=(float16)(0.0);
    for (unsigned int idx=0;idx<mWidth*mWidth/16/nunits;idx++) {    
    		float16 mAtmp=mA[idx];
    		elt.s0+=mAtmp.s0;
    		elt.s1+=mAtmp.s1;
    		elt.s2+=mAtmp.s2;
    		elt.s3+=mAtmp.s3;
    		elt.s4+=mAtmp.s4;
    		elt.s5+=mAtmp.s5;
    		elt.s6+=mAtmp.s6;
    		elt.s7+=mAtmp.s7;
    		elt.s8+=mAtmp.s8;
    		elt.s9+=mAtmp.s9;
    		elt.sA+=mAtmp.sA;
    		elt.sB+=mAtmp.sB;
    		elt.sC+=mAtmp.sC;
    		elt.sD+=mAtmp.sD;
    		elt.sE+=mAtmp.sE;
    		elt.sF+=mAtmp.sF;

    }
    mC[g_id]=elt.s0+elt.s1+elt.s2+elt.s3+elt.s4+elt.s5+elt.s6+elt.s7+elt.s8+elt.s9+elt.sA+elt.sB+elt.sC+elt.sD+elt.sE+elt.sF;

}

// by block, float16

// This is the fastest single-threaded kernel, but with block-based access
__kernel void mataccKernel11 (
	__global float16 *mA,
	__global float *mC,
	const unsigned int mWidth) {
	unsigned int g_id = get_group_id(0);
	unsigned int nunits=get_num_groups(0);
	  const unsigned int bWidth=64/16;
	  const unsigned int bHeigth=64;
	  const unsigned int bSize=4096/16;
	  unsigned int vmWidth=mWidth/16;
	  unsigned int mSize=vmWidth*mWidth/nunits;
	  unsigned int bs = vmWidth/bWidth;
	float16 elt=(float16)(0.0);
 
	  for (unsigned int br=0;br<bs/nunits;br++) {
		    	for (unsigned int bc=0;bc<bs;bc++) {   
					for (unsigned int i=0;i<bHeigth;i++) {    
						for (unsigned int j=0;j<bWidth;j++) {	
		unsigned int idx=br*bHeigth*vmWidth+bc*bWidth+j+vmWidth*i;
			float16 mAtmp=mA[idx+g_id*mSize];
			elt.s0+=mAtmp.s0;
			elt.s1+=mAtmp.s1;
			elt.s2+=mAtmp.s2;
			elt.s3+=mAtmp.s3;
			elt.s4+=mAtmp.s4;
			elt.s5+=mAtmp.s5;
			elt.s6+=mAtmp.s6;
			elt.s7+=mAtmp.s7;
			elt.s8+=mAtmp.s8;
			elt.s9+=mAtmp.s9;
			elt.sA+=mAtmp.sA;
			elt.sB+=mAtmp.sB;
			elt.sC+=mAtmp.sC;
			elt.sD+=mAtmp.sD;
			elt.sE+=mAtmp.sE;
			elt.sF+=mAtmp.sF;

	}}}}
	mC[g_id]=elt.s0+elt.s1+elt.s2+elt.s3+elt.s4+elt.s5+elt.s6+elt.s7+elt.s8+elt.s9+elt.sA+elt.sB+elt.sC+elt.sD+elt.sE+elt.sF;

}	
// The kernels below use threads
// float8, 16 threads
__kernel void mataccKernel7 (
    __global float8 *mA,
    __global float *mC,
    const unsigned int mWidth) {
	const int nthreads=16;
	unsigned int nunits=get_num_groups(0);
	unsigned int mSize= mWidth*mWidth/8/nthreads/nunits;
	unsigned int g_id = get_group_id(0);
	unsigned int l_id = get_local_id(0);
	__local float mCtmp[16];
    float8 elt=(float8)(0.0);
    for (unsigned int idx=mSize*l_id;idx<mSize*(l_id+1);idx++) {    
    		float8 mAtmp=mA[idx+g_id*mSize];
        	elt.s0+=mAtmp.s0;
        	elt.s1+=mAtmp.s1;
        	elt.s2+=mAtmp.s2;
        	elt.s3+=mAtmp.s3;
        	elt.s4+=mAtmp.s4;
        	elt.s5+=mAtmp.s5;
        	elt.s6+=mAtmp.s6;
        	elt.s7+=mAtmp.s7;
    }
    mCtmp[l_id]=elt.s0+elt.s1+elt.s2+elt.s3+elt.s4+elt.s5+elt.s6+elt.s7;
    barrier(CLK_LOCAL_MEM_FENCE);
    mC[g_id]=mCtmp[0]+mCtmp[1]+mCtmp[2]+mCtmp[3]+mCtmp[4]+mCtmp[5]+mCtmp[6]+mCtmp[7]+mCtmp[8]+mCtmp[9]+mCtmp[10]+mCtmp[11]+mCtmp[12]+mCtmp[13]+mCtmp[14]+mCtmp[15];	
}
// float16, 16 threads
__kernel void mataccKernel8 (
    __global float16 *mA,
    __global float *mC,
    const unsigned int mWidth) {
	const int nthreads=16;
	const int nunits=get_num_groups(0);
	unsigned int mSize= mWidth*mWidth/16/nthreads/nunits;
	unsigned int g_id = get_group_id(0);
	unsigned int l_id = get_local_id(0);
	__local float mCtmp[16];
	float16 elt=(float16)(0.0);
    for  (unsigned int idx=mSize*l_id;idx<mSize*(l_id+1);idx++) {    
    	float16 mAtmp=mA[idx+g_id*mSize];
    		elt.s0+=mAtmp.s0;
    		elt.s1+=mAtmp.s1;
    		elt.s2+=mAtmp.s2;
    		elt.s3+=mAtmp.s3;
    		elt.s4+=mAtmp.s4;
    		elt.s5+=mAtmp.s5;
    		elt.s6+=mAtmp.s6;
    		elt.s7+=mAtmp.s7;
    		elt.s8+=mAtmp.s8;
    		elt.s9+=mAtmp.s9;
    		elt.sA+=mAtmp.sA;
    		elt.sB+=mAtmp.sB;
    		elt.sC+=mAtmp.sC;
    		elt.sD+=mAtmp.sD;
    		elt.sE+=mAtmp.sE;
    		elt.sF+=mAtmp.sF;

    }
    mCtmp[l_id]=elt.s0+elt.s1+elt.s2+elt.s3+elt.s4+elt.s5+elt.s6+elt.s7+elt.s8+elt.s9+elt.sA+elt.sB+elt.sC+elt.sD+elt.sE+elt.sF;
    barrier(CLK_LOCAL_MEM_FENCE);
    mC[g_id]=mCtmp[0]+mCtmp[1]+mCtmp[2]+mCtmp[3]+mCtmp[4]+mCtmp[5]+mCtmp[6]+mCtmp[7]+mCtmp[8]+mCtmp[9]+mCtmp[10]+mCtmp[11]+mCtmp[12]+mCtmp[13]+mCtmp[14]+mCtmp[15];	
}


// float16, 32 threads
__kernel void mataccKernel9 (
    __global float16 *mA,
    __global float *mC,
    const unsigned int mWidth) {
	const int nthreads=32;
	const int nunits=get_num_groups(0);
	unsigned int mSize= mWidth*mWidth/16/nthreads/nunits;
	unsigned int g_id = get_group_id(0);
	unsigned int l_id = get_local_id(0);
	__local float mCtmp[32];
    float16 elt=(float16)(0.0);
    for  (unsigned int idx=mSize*l_id;idx<mSize*(l_id+1);idx++) {    
    		float16 mAtmp=mA[idx+g_id*mSize];
    		elt.s0+=mAtmp.s0;
    		elt.s1+=mAtmp.s1;
    		elt.s2+=mAtmp.s2;
    		elt.s3+=mAtmp.s3;
    		elt.s4+=mAtmp.s4;
    		elt.s5+=mAtmp.s5;
    		elt.s6+=mAtmp.s6;
    		elt.s7+=mAtmp.s7;
    		elt.s8+=mAtmp.s8;
    		elt.s9+=mAtmp.s9;
    		elt.sA+=mAtmp.sA;
    		elt.sB+=mAtmp.sB;
    		elt.sC+=mAtmp.sC;
    		elt.sD+=mAtmp.sD;
    		elt.sE+=mAtmp.sE;
    		elt.sF+=mAtmp.sF;

    }
    mCtmp[l_id]=elt.s0+elt.s1+elt.s2+elt.s3+elt.s4+elt.s5+elt.s6+elt.s7+elt.s8+elt.s9+elt.sA+elt.sB+elt.sC+elt.sD+elt.sE+elt.sF;
    barrier(CLK_LOCAL_MEM_FENCE);
    mC[g_id]=0.0;
    for (int i=0;i<32;i++) {
    	mC[g_id]+=mCtmp[i];	
    }
}


// float16, 16 threads
__kernel void mataccKernel10 (
    __global float16 *mA,
    __global float *mC,
    const unsigned int mWidth) {
	const int nthreads=16;
	const int nunits=get_num_groups(0);
	unsigned int mSize= mWidth*mWidth/16/nthreads/nunits;
	unsigned int g_id = get_group_id(0);
	unsigned int l_id = get_local_id(0);
	__local float mCtmp[16];
    float16 elt=(float16)(0.0);
    for  (unsigned int idx=mSize*l_id;idx<mSize*(l_id+1);idx++) {    
    		float16 mAtmp=mA[idx+g_id*mSize];
    		elt.s0+=mAtmp.s0;
    		elt.s1+=mAtmp.s1;
    		elt.s2+=mAtmp.s2;
    		elt.s3+=mAtmp.s3;
    		elt.s4+=mAtmp.s4;
    		elt.s5+=mAtmp.s5;
    		elt.s6+=mAtmp.s6;
    		elt.s7+=mAtmp.s7;
    		elt.s8+=mAtmp.s8;
    		elt.s9+=mAtmp.s9;
    		elt.sA+=mAtmp.sA;
    		elt.sB+=mAtmp.sB;
    		elt.sC+=mAtmp.sC;
    		elt.sD+=mAtmp.sD;
    		elt.sE+=mAtmp.sE;
    		elt.sF+=mAtmp.sF;

    }
    mCtmp[l_id]=elt.s0+elt.s1+elt.s2+elt.s3+elt.s4+elt.s5+elt.s6+elt.s7+elt.s8+elt.s9+elt.sA+elt.sB+elt.sC+elt.sD+elt.sE+elt.sF;   
    barrier(CLK_LOCAL_MEM_FENCE);
    mC[g_id]=mCtmp[0]+mCtmp[1]+mCtmp[2]+mCtmp[3]+mCtmp[4]+mCtmp[5]+mCtmp[6]+mCtmp[7]+mCtmp[8]+mCtmp[9]+mCtmp[10]+mCtmp[11]+mCtmp[12]+mCtmp[13]+mCtmp[14]+mCtmp[15];	

}

// float16, 64 threads
__kernel void mataccKernel13 (
    __global float16 *mA,
    __global float *mC,
    const unsigned int mWidth) {
	const int nthreads=64;
	const int nunits=get_num_groups(0);
	unsigned int mSize= mWidth*mWidth/16/nthreads/nunits;
	unsigned int g_id = get_group_id(0);
	unsigned int l_id = get_local_id(0);
	__local float mCtmp[64];
    float16 elt=(float16)(0.0);
    for  (unsigned int idx=mSize*l_id;idx<mSize*(l_id+1);idx++) {    
    		float16 mAtmp=mA[idx+g_id*mSize];
    		elt.s0+=mAtmp.s0;
    		elt.s1+=mAtmp.s1;
    		elt.s2+=mAtmp.s2;
    		elt.s3+=mAtmp.s3;
    		elt.s4+=mAtmp.s4;
    		elt.s5+=mAtmp.s5;
    		elt.s6+=mAtmp.s6;
    		elt.s7+=mAtmp.s7;
    		elt.s8+=mAtmp.s8;
    		elt.s9+=mAtmp.s9;
    		elt.sA+=mAtmp.sA;
    		elt.sB+=mAtmp.sB;
    		elt.sC+=mAtmp.sC;
    		elt.sD+=mAtmp.sD;
    		elt.sE+=mAtmp.sE;
    		elt.sF+=mAtmp.sF;

    }
    mCtmp[l_id]=elt.s0+elt.s1+elt.s2+elt.s3+elt.s4+elt.s5+elt.s6+elt.s7+elt.s8+elt.s9+elt.sA+elt.sB+elt.sC+elt.sD+elt.sE+elt.sF;   
    barrier(CLK_LOCAL_MEM_FENCE);
    mC[g_id]=0.0;
    for (int i=0;i<nthreads;i++) {
    	mC[g_id]+=mCtmp[i];	
    }    	

}

// This is a vectorised, multi-threaded kernel but with block-based access
__kernel void mataccKernel12 (
    __global float16 *mA,
    __global float *mC,
    const unsigned int mWidth) {
	const int nthreads=16;
	unsigned int nunits=get_num_groups(0);
	unsigned int g_id = get_group_id(0);
	unsigned int l_id = get_local_id(0);
	__local float mCtmp[16];
	
	const unsigned int bWidth=4; // 64/16 for float16
	const unsigned int bHeigth=64/nthreads;
	const unsigned int bSize=256;
	unsigned int vmWidth=mWidth/16;
	unsigned int bs = vmWidth/bWidth;
	unsigned int mSize=vmWidth*mWidth/nunits;
	float16 elt=(float16)(0.0);
 
	  for (unsigned int br=0;br<bs/nunits;br++) {
		    	for (unsigned int bc=0;bc<bs;bc++) {   
					for (unsigned int i=l_id*bHeigth;i<(l_id+1)*bHeigth;i++) {    
						for (unsigned int j=0;j<bWidth;j++) {	
		unsigned int idx=br*bHeigth*vmWidth+bc*bWidth+j+vmWidth*i;

    		float16 mAtmp=mA[idx+g_id*mSize];
    		elt.s0+=mAtmp.s0;
    		elt.s1+=mAtmp.s1;
    		elt.s2+=mAtmp.s2;
    		elt.s3+=mAtmp.s3;
    		elt.s4+=mAtmp.s4;
    		elt.s5+=mAtmp.s5;
    		elt.s6+=mAtmp.s6;
    		elt.s7+=mAtmp.s7;
    		elt.s8+=mAtmp.s8;
    		elt.s9+=mAtmp.s9;
    		elt.sA+=mAtmp.sA;
    		elt.sB+=mAtmp.sB;
    		elt.sC+=mAtmp.sC;
    		elt.sD+=mAtmp.sD;
    		elt.sE+=mAtmp.sE;
    		elt.sF+=mAtmp.sF;

    }}}}
    mCtmp[l_id]=elt.s0+elt.s1+elt.s2+elt.s3+elt.s4+elt.s5+elt.s6+elt.s7+elt.s8+elt.s9+elt.sA+elt.sB+elt.sC+elt.sD+elt.sE+elt.sF;   
    barrier(CLK_LOCAL_MEM_FENCE);
    mC[g_id]=mCtmp[0]+mCtmp[1]+mCtmp[2]+mCtmp[3]+mCtmp[4]+mCtmp[5]+mCtmp[6]+mCtmp[7]+mCtmp[8]+mCtmp[9]+mCtmp[10]+mCtmp[11]+mCtmp[12]+mCtmp[13]+mCtmp[14]+mCtmp[15];	

}




import os
import re
import commands
import sys
import os.path
from SCons.Variables import Variables
from SCons.Environment import Environment

def getOpt(optname,desc,default):

    global opts
    opts.Add(optname,desc,default)
    optionl = filter (lambda x: x.key==optname,opts.options)
    if optionl:
        option=optionl[0]
        if opts.args.has_key(optname) and opts.args[optname]!=option.default:
            return opts.args[option.key]
        else: 
            return option.default
    else:
        print "No such option: "+optname
    

def build(appname,sources):

    global opts
    
    help = """
    Options:
    plat=AMD|NVIDIA [NVIDIA]
    dev=CPU|GPU [GPU] device
    kernel=<number> [1]   
    w=<number> [1024]   matrix width
    ref=0|1|2 [1]     reference 2=ref only
    v=0|1 [1]         verbose
    mode=0|1|2   COPY|COPY+ALLOC|USE 
    info=0|1
    gpu=-1|0|1 [-1, means automatic selection]
    """
    if commands.getoutput("uname") == "Darwin":
        OSX=1
        OSFLAG='-DOSX'
    else:
        OSX=0
        OSFLAG='-D__LINUX__'

    OPENCL_DIR=os.environ['OPENCL_DIR']
    opts=Variables()        

    args=sys.argv[1:]
    #import getopt
    #rest = getopt.getopt(args,"hABCD")
    for arg in args:
        if re.match("(\w+)=(\w+)",arg):
            (k,v)=arg.split('=')
            opts.args[k]=v
    
    dev=getOpt('dev','Device','GPU')
    plat=getOpt('plat','Platform','NVIDIA')
    if plat=='AMD':      
        print 'AMD platform'
        AMD_SDK_PATH=os.environ['AMDAPPSDKROOT']
    else:    
        NVIDIA_SDK_PATH=os.environ['NVSDKCUDA_ROOT']
        if os.environ['OPENCL_GPU']!='NVIDIA':
            print 'No NVIDIA platform, defaulting to AMD CPU'
            AMD_SDK_PATH=os.environ['AMDAPPSDKROOT']
            plat='AMD'
            dev='CPU'
    
    gpu=getOpt('gpu','GPU','-1')
    devidxflag='-DDEVIDX='+gpu
    if gpu!='-1':
        dev='GPU'
        
    kernel=getOpt('kernel','Kernel','1')
    width=getOpt('w','Width','1024')
    ref=getOpt('ref','Reference','1')
    refflag='-DREF'
    verbose=getOpt('v','Verbose','0')
    vflag='-DVERBOSE'
    if verbose=='0':
        vflag=''
    mode=getOpt('mode','Mode','1')
    memreadflag='-DMRMODE='+mode
    devinfo=getOpt('info','DeviceInfo','0')
    devinfoflag=''
    platinfoflag=''
    if devinfo=='1':
        devinfoflag='-DDEVINFO'
        platinfoflag='-DPLATINFO'
    DEVFLAGS=['-D'+dev,devidxflag,'-DKERNEL='+kernel,'-DWIDTH='+width,'-DREF='+ref,vflag, memreadflag,devinfoflag,platinfoflag]
    if commands.getoutput("uname") == "Darwin":
        DEVFLAGS+=['-DOSX']    
        
    oclsources=['../Timing.cc','../DeviceInfo.cc','../PlatformInfo.cc','../OclWrapper.cc']
        
    env = Environment( CC = 'g++', CXXFLAGS = ['-Wall','-g',DEVFLAGS]) 
    env.Help(help)
    
    if OSX==1:
        env['FRAMEWORKS'] = ['OpenCL']
        env['CPPPATH']=[OPENCL_DIR]
    else:    
        env['LIBS']=['OpenCL']
        if plat=='AMD':
            env['CPPPATH']=[OPENCL_DIR,AMD_SDK_PATH+'/include']
            env['LIBPATH']=[AMD_SDK_PATH+'/lib/x86_64']
        else:
            env['CPPPATH']=[OPENCL_DIR,NVIDIA_SDK_PATH+'/OpenCL/common/inc']
            
    env.Program(appname,oclsources+sources)

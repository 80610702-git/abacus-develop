# This is the Makefile of ABACUS

include Makefile.system
include Makefile.Objects

VPATH=./src_global\
:./src_parallel\
:./src_external/src_pdiag\
:./src_pw\
:./src_lcao\
:./src_ions\
:./src_external/src_pdiag/MRRR\
:./\

#==========================
# Define HONG
#==========================
#(1)no mpi
HONG_SER = -D__FP ${HONG_FFTW} 
HONG_SER_SELINV = -D__FP ${HONG_FFTW} -D__SELINV
HONG_GDB = -g -D__FP ${HONG_FFTW}
#(2)mpi
HONG_MPI = -D__FP ${HONG_FFTW} -D__MPI 
HONG_MPI_SELINV = -D__FP ${HONG_FFTW} -D__MPI -D__SELINV -DMETIS
#(3)memory
HONG_MEM = ${HONG_FFTW} -D__FP -D_MCD_CHECK -DWIN32 -DMCD_VERBOSE

#!!!!!!!!!!!!!!!!!!!! CHANE HERE IF YOU LIKE !!!!!!!!!!!!!!
#! change series version or parallel version~~~
HONG=${HONG_MPI_SELINV}
#HONG=${HONG_SER_SELINV}
#!!!!!!!!!!!!!!!!!!!! CHANE HERE IF YOU LIKE !!!!!!!!!!!!!!

#==========================
# OPTIMIZE OPTIONS
#==========================
#OPTS = -I/global/u2/m/mohan/software/boost_1_39_0/ -I../src_siao/
#OPTS = -I/home/xiaohui/lib/boost_1_39_0/ -O3
#OPTS = -I/home/mohan/software/boost_1_39_0/ -O3
#(1)gdb
#xiaohui modify 2013-12-27
OPTS_GDB = -g -W -I/home/mohan/software/boost_1_39_0/ 
#(2)gprof
#POTS = -pg

#==========================
# OBJECTS NEEDED
#==========================
FP_OBJS_0=$(OBJS_OTHER)\
$(OBJS_FIRST_PRINCIPLE)\
$(OBJS_PARALLEL)\
$(OBJS_TOOLS) \
$(OBJS_ONSCALING)\
$(OBJS_SELINV)\
$(OBJS_CG)\
$(OBJS_WANNIER)\
$(OBJS_COMMON)\
$(OBJS_MLWF)\
main.o\

FP_OBJS=$(patsubst %.o, ${OBJ_DIR}/%.o, ${FP_OBJS_0})
PDIAG_OBJS=$(patsubst %.o, ${OBJ_DIR}/%.o, ${OBJS_PDIAG})
PDIAG_MR=$(patsubst %.o, ${OBJ_DIR}/%.o, ${PDIAG_MR_0})

#==========================
# MAKING OPTIONS
#==========================
fp_mpi : 
	@ make init
	@ make -j $(NP) parallel

fp : 
	@ make init
	@ make -j $(NP) serial

fp_gbd : 
	@ make init
	@ make -j $(NP) serial_gbd

fp_gprof : 
	@ make init
	@ make -j $(NP) serial_gprof

fp_mem : 
	@ make init
	@ make -j $(NP) serial_mem

init :
	@ if [ ! -d $(OBJ_DIR) ]; then mkdir $(OBJ_DIR); fi
	@ if [ ! -d $(OBJ_DIR)/README ]; then echo "This directory contains all of the .o files" > $(OBJ_DIR)/README; fi
	@ if [ ! -d ../bin ]; then mkdir ../bin; fi

parallel : ${FP_OBJS} ${PDIAG_OBJS} ${PDIAG_MR} ${HEADERS}
	${CPLUSPLUS_MPI} ${OPTS} ${OPTS_MPI} $(FP_OBJS) ${PDIAG_OBJS} ${PDIAG_MR} ${LIBS} -o  ../bin/${VERSION}.mpi

serial : ${FP_OBJS} ${HEADERS} 
	${CPLUSPLUS} ${OPTS} $(FP_OBJS) ${LIBS} -o ${VERSION}.fp.x 

serial_gdb : ${FP_OBJS} ${HEADERS}
	${CPLUSPLUS} ${OPTS_GDB} $(FP_OBJS) ${LIBS} -o ${VERSION}.fp_gdb.x

serial_gprof : ${FP_OBJS} ${HEADERS} 
	${CPLUSPLUS} ${OPTS} $(FP_OBJS) ${LIBS} -o ${VERSION}.fp_gprof.x 

serial_mem : ${FP_OBJS} ../src_parallel/mcd.o ${HEADERS}
	${CPLUSPLUS} $(FP_OBJS) ../src_parallel/mcd.o ${LIBS} -o ${VERSION}.fp_mem.x

#==========================
# rules
#==========================
${OBJ_DIR}/%.o:%.cpp
	${CPLUSPLUS_MPI} ${OPTS} ${OPTS_MPI} -c ${HONG} $< -o $@
${OBJ_DIR}/%.o:%.f
	${FORTRAN} -c ${HONG} $< -o $@	 

.PHONY:clean
clean:
	@ if [ -d $(OBJ_DIR) ]; then rm -rf $(OBJ_DIR); fi
	@ if [ -d ../bin ]; then rm -rf ../bin; fi

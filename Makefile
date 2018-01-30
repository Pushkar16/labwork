PYTHON_VERSION = 2.7
PYTHON_INCLUDE = /usr/include/python$(PYTHON_VERSION)

# location of the Boost Python include files and library
BOOST_INC = /usr/include
BOOST_LIB = /usr/lib

TARGET = ctffind
TARGET2=ctffind3_cpp
CFLAGS = --std=c++11
 
$(TARGET).so: $(TARGET).o
	g++ -shared -Wl,--export-dynamic $(TARGET).o CTFEstimate.o ctffind3_cpp.o ioc.o iof2.o -fopenmp -lgfortran -L$(BOOST_LIB) -l:libboost_python-py$(subst .,,$(PYTHON_VERSION)).so -L/usr/lib/python$(PYTHON_VERSION)/config -lpython$(PYTHON_VERSION) -o $(TARGET).so $(CFLAGS)

$(TARGET).o: $(TARGET).cpp
	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -fPIC -c $(TARGET).cpp  CTFEstimate.cpp $(CFLAGS)
	gfortran -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -fPIC -c iof2.f ctffind3_cpp.f
	gcc -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -fPIC -O3 -DPROTOTYPE -Dalliant -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -w -fopenmp -c ioc.c


all: $(TARGET).so

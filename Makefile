CXX = cc
CFLAGS = -Wall
INCLUDE = -I/usr/local/include -I/usr/include
LDFLAGS = -L/usr/local/lib -I/usr/lib
LDLIBS = -lcurl

SOURCES = src/c_sms.c
OUT = c_sms

all: build

build: $(SOURCES)
	$(CXX) -o $(OUT) $(INCLUDE) $(LDFLAGS) $(CFLAGS) $(SOURCES) $(LDLIBS)

clean:
	rm -rf c_sms

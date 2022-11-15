ENV := gdb-debug
ENV := valgrind-debug
ENV := no-debug

VALGRIND_TOOL=helgrind
VALGRIND_TOOL=memcheck --leak-check=full --show-leak-kinds=all
VALGRIND_TOOL=memcheck --track-origins=yes --leak-check=full --show-leak-kinds=all --track-fds=yes -s
VALGRIND_TOOL=memcheck --track-origins=yes --leak-check=full --track-fds=yes -s

libcca_path=./lib/include
# libigen3_path=/usr/include/eigen3
# libtorch_path=../libtorch

GPP := g++
GCC := gcc

# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib

ifeq ($(ENV),gdb-debug)
GPP += -Wall -g -O0 -lm -lcurl -lssl 
GCC += -Wall -g -O0 -lm -lcurl -lssl 
else
ifeq ($(ENV),valgrind-debug)
GPP += -Wall -g -O0 -lm -lcurl -lssl 
GCC += -Wall -g -O0 -lm -lcurl -lssl 
else
GPP += -Wall -lm -lcurl -lssl 
GCC += -Wall -lm -lcurl -lssl
endif
endif
# GPP += -Wno-pointer-arith

# sdl_cflags := $(shell pkg-config --cflags sdl2 SDL2_mixer SDL2_image SDL2_ttf)
# # # # # sdl_libs := $(shell pkg-config --libs sdl2 SDL2_mixer SDL2_image SDL2_ttf)
# GPP += $(sdl_cflags)
# GPP += $(sdl_libs)

# torch_cflags := -D_GLIBCXX_USE_CXX11_ABI=0 -std=gnu++17
# torch_libs := -std=c++17 -L${libtorch_path}/lib -Wl,-R${libtorch_path}/lib -ltorch -ltorch_cpu -lc10
# GPP += $(torch_cflags)
# GPP += $(torch_libs)

HEADERS := \
	-I $(libcca_path)/ \
	# -I ${libtorch_path}/lib \
	# -I ${libtorch_path}/include/ \
	# -I ${libtorch_path}/include/torch/csrc/api/include

# -I $(libigen3_path)/ \
# -I $(libcca_path)/ \

m_clean:
	rm -f ./build/*.o
	rm -f ./build/*.ccax


m_main:
	$(GPP) $(HEADERS) \
	$(libcca_path)/../main.cpp -o ./build/cca.ccax

m_test:
	$(GPP) $(HEADERS) \
	$(libcca_path)/../test.cpp -o ./build/test.ccax

main:
	make m_clean
	make m_main
	echo "running[main]..."
ifeq ($(ENV),gdb-debug)
	gdb ./build/cca.ccax
else
ifeq ($(ENV),valgrind-debug)
	valgrind --tool=$(VALGRIND_TOOL) ./build/cca.ccax
else
	./build/cca.ccax
endif
endif

test:
	make m_clean
	make m_test
	echo "running[test]..."
ifeq ($(ENV),gdb-debug)
	gdb ./build/test.ccax
else
ifeq ($(ENV),valgrind-debug)
	valgrind --tool=$(VALGRIND_TOOL) ./build/test.ccax
else
	./build/test.ccax
endif
endif
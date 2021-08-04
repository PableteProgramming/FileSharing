build_dir= ../make-build/server
out_dir= $(build_dir)/out
obj_dir= $(build_dir)/obj

CXX= g++

src_dir= src
inc_dir= include

src_files= $(shell find $(src_dir) -maxdepth 1 -type f -name *.cpp)
obj_files= $(patsubst $(src_dir)/%.cpp, $(obj_dir)/%.o, $(src_files))

out_name= server
out_file= $(out_dir)/$(out_name)

all: $(out_file)

$(out_file): $(obj_files)
	mkdir -p $(out_dir)
	$(CXX) -o $(out_file) $(obj_files)

$(obj_files): $(obj_dir)/%.o: $(src_dir)/%.cpp
	mkdir -p $(obj_dir)
	$(CXX) -c -o $@ $< -I$(inc_dir)
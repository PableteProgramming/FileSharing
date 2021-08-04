build_dir= ../make-build/server
out_dir= $(build_dir)/out
obj_dir= $(build_dir)/obj
func_obj_dir= $(build_dir)/../func

CXX= g++

src_dir= src
inc_dir= include
func_inc_dir= ../include
func_src_dir= ../src


func_src_files= $(shell find $(func_src_dir) -maxdepth 1 -type f -name *.cpp)
func_obj_files= $(patsubst $(func_src_dir)/%.cpp, $(func_obj_dir)/%.o, $(func_src_files))
src_files= $(shell find $(src_dir) -maxdepth 1 -type f -name *.cpp)
obj_files= $(patsubst $(src_dir)/%.cpp, $(obj_dir)/%.o, $(src_files))

out_name= server
out_file= $(out_dir)/$(out_name)

all: $(out_file)

$(out_file): $(func_obj_files) $(obj_files)
	mkdir -p $(out_dir)
	$(CXX) -o $(out_file) $(obj_files) $(func_obj_files)

$(func_obj_files): $(func_obj_dir)/%.o: $(func_src_dir)/%.cpp
	mkdir -p $(func_obj_dir)
	$(CXX) -c -o $@ $< -I$(inc_dir) -I$(func_inc_dir)

$(obj_files): $(obj_dir)/%.o: $(src_dir)/%.cpp
	mkdir -p $(obj_dir)
	$(CXX) -c -o $@ $< -I$(inc_dir) -I$(func_inc_dir)
# setup for opencv
git submodule add https://github.com/opencv/opencv.git external/opencv
cd external/opencv
git submodule update --init --recursive
mkdir build
cd build
cmake ..
cmake --build .
pwd

cd ../../.. 
# setup for onnxruntime
git submodule add https://github.com/Microsoft/onnxruntime.git external/onnxruntime
cd external/onnxruntime
git submodule update --init --recursive
bash ./build.sh --config RelWithDebInfo --build_shared_lib --parallel 1 --compile_no_warning_as_error --skip_submodule_sync
# bash ./build.sh --config RelWithDebInfo --build_shared_lib --compile_no_warning_as_error --skip_submodule_sync
    # --skip_tests 
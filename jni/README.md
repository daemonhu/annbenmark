Swig 生成供JNI使用的代码

------------



1. 生成efanna2e库
   1. `git clone https://github.com/ZJULearning/efanna_graph.git`
   2. 进入 `src`目录，修改`CMakeLists.txt` 增加动态库目标
   3. 生成`libefanna2e`, cmake需要增加`-DCMAKE_BUILD_TYPE=Release`
2. 编写swig.i，文件参考 [swig.i](nsg_ann/src/com/nsg/test/swig.i)
   1. 生成Java代码 `swig -c++ -java -package com.nsg.test swig.i`
3. 生成供JVM load的动态库
   1. `g++ -I/usr/lib/jvm/default/include -I/usr/lib/jvm/default/include/linux -I/run/media/tx/1ADC3E81DC3E56EB/TDDOWNLOAD/github/annb
      enmark/ann -I/run/media/tx/1ADC3E81DC3E56EB/TDDOWNLOAD/github/annbenmark/external/efanna_graph/include -I/run/media/tx/1ADC3E81DC3E56EB
      /TDDOWNLOAD/github/annbenmark/external/nsg/include -L/run/media/tx/1ADC3E81DC3E56EB/TDDOWNLOAD/github/annbenmark/build/CMakeFiles/test_
      ann.dir/ann -L/run/media/tx/1ADC3E81DC3E56EB/TDDOWNLOAD/github/annbenmark/build/CMakeFiles/test_ann.dir/util -L/run/media/tx/1ADC3E81DC
      3E56EB/TDDOWNLOAD/github/efanna_graph/src -fopenmp  -lpthread -std=c++11 -O3 -march=native -Wall -fpic -lefanna2e_d /run/media/tx/1ADC3E
      81DC3E56EB/TDDOWNLOAD/github/annbenmark/external/nsg/src/index_nsg.cpp /run/media/tx/1ADC3E81DC3E56EB/TDDOWNLOAD/github/annbenmark/exte
      rnal/nsg/src/index.cpp /run/media/tx/1ADC3E81DC3E56EB/TDDOWNLOAD/github/annbenmark/ann/Nsg.cpp /run/media/tx/1ADC3E81DC3E56EB/TDDOWNLOA
      D/github/annbenmark/ann/AnnBase.cpp /run/media/tx/1ADC3E81DC3E56EB/TDDOWNLOAD/github/annbenmark/util/SiftUtil.cpp ./swig_**wra**p.cxx -shar
      ed -o libnsgann.so`

4. 修改JAVA load library部分

   1. ```java
       try {
            System.loadLibrary("efanna2e_d");
            System.loadLibrary("nsgann");
          } catch (UnsatisfiedLinkError e) {
            System.err.println("Native code library failed to load. \n" + e);
            System.exit(1);
       }
      ```

测试代码见 `nsgtest.java`

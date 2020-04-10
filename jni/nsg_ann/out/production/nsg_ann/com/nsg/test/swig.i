%module(directors="1") nsgann

%include "std_string.i"
%include "std_deque.i"
%include "std_vector.i"


%{
#include "Nsg.h"
#include "AnnBase.h"
#include "efanna2e/index.h"
#include "efanna2e/index_nsg.h"
#include "efanna2e/distance.h"
#include "efanna2e/exceptions.h"
#include "efanna2e/neighbor.h"
#include "efanna2e/parameters.h"
#include "efanna2e/util.h"
using namespace efanna2e;
%}

%template(VectorOfNeighbor) std::vector<efanna2e::Neighbor>;
%template(VectorOfFloat) std::vector<float>;
%template(VecVecFloat) std::vector<std::vector<float>>;

%include cpointer.i
%pointer_functions(int, intp);
%pointer_functions(double, doublep);

%pragma(java) jniclasscode=%{
  static {
    try {
        System.loadLibrary("nsgann");
    } catch (UnsatisfiedLinkError e) {
      System.err.println("Native code library failed to load. \n" + e);
      System.exit(1);
    }
  }
%}

%include "neighbor.h"
%include "/run/media/tx/1ADC3E81DC3E56EB/TDDOWNLOAD/github/annbenmark/ann/AnnBase.h"
%include "/run/media/tx/1ADC3E81DC3E56EB/TDDOWNLOAD/github/annbenmark/ann/Nsg.h"

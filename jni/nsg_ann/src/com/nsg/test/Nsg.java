/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.1
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.nsg.test;

public class Nsg extends AnnBase {
  private transient long swigCPtr;

  protected Nsg(long cPtr, boolean cMemoryOwn) {
    super(nsgannJNI.Nsg_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Nsg obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  @SuppressWarnings("deprecation")
  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        nsgannJNI.delete_Nsg(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public Nsg(String base_file_path, String query_file_path, String groundtruth_file_path) {
    this(nsgannJNI.new_Nsg__SWIG_0(base_file_path, query_file_path, groundtruth_file_path), true);
  }

  public Nsg(int dim, long K, long L1, long iter, long S, long R1, long L2, long R2, long C) {
    this(nsgannJNI.new_Nsg__SWIG_1(dim, K, L1, iter, S, R1, L2, R2, C), true);
  }

  public int build(long nnK, long nnL, long nnIter, long nnS, long nnR, String nn_graph_file, long L, long R, long C) {
    return nsgannJNI.Nsg_build__SWIG_0(swigCPtr, this, nnK, nnL, nnIter, nnS, nnR, nn_graph_file, L, R, C);
  }

  public int build() {
    return nsgannJNI.Nsg_build__SWIG_1(swigCPtr, this);
  }

  public int addAll(VecVecFloat queries) {
    return nsgannJNI.Nsg_addAll(swigCPtr, this, VecVecFloat.getCPtr(queries), queries);
  }

  public int save_index(String file_name) {
    return nsgannJNI.Nsg_save_index(swigCPtr, this, file_name);
  }

  public int get_nn_by_vec(SWIGTYPE_p_float vec, int n, int K, SWIGTYPE_p_std__vectorT_int_t closest) {
    return nsgannJNI.Nsg_get_nn_by_vec(swigCPtr, this, SWIGTYPE_p_float.getCPtr(vec), n, K, SWIGTYPE_p_std__vectorT_int_t.getCPtr(closest));
  }

  public int load(String data_path, String nsg_path) {
    return nsgannJNI.Nsg_load(swigCPtr, this, data_path, nsg_path);
  }

  public int close() {
    return nsgannJNI.Nsg_close(swigCPtr, this);
  }

  public int optimizeGraph() {
    return nsgannJNI.Nsg_optimizeGraph(swigCPtr, this);
  }

  public int save(String data_path, String nsg_path) {
    return nsgannJNI.Nsg_save(swigCPtr, this, data_path, nsg_path);
  }

  public VectorOfNeighbor search(VectorOfFloat query, long L, long K) {
    return new VectorOfNeighbor(nsgannJNI.Nsg_search(swigCPtr, this, VectorOfFloat.getCPtr(query), query, L, K), true);
  }

  public VectorOfNeighbor searchWithOptGraph(VectorOfFloat query, long L, long K) {
    return new VectorOfNeighbor(nsgannJNI.Nsg_searchWithOptGraph(swigCPtr, this, VectorOfFloat.getCPtr(query), query, L, K), true);
  }

  public VectorOfFloat data() {
    return new VectorOfFloat(nsgannJNI.Nsg_data(swigCPtr, this), false);
  }

}

/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.1
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.nsg.test;

public class AnnBase {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected AnnBase(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(AnnBase obj) {
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
        nsgannJNI.delete_AnnBase(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public int get_nn_by_vec(SWIGTYPE_p_float vec, int nn_num, int search_para, SWIGTYPE_p_std__vectorT_int_t closest) {
    return nsgannJNI.AnnBase_get_nn_by_vec(swigCPtr, this, SWIGTYPE_p_float.getCPtr(vec), nn_num, search_para, SWIGTYPE_p_std__vectorT_int_t.getCPtr(closest));
  }

  public int save_index(String file_name) {
    return nsgannJNI.AnnBase_save_index(swigCPtr, this, file_name);
  }

  public int precision(SWIGTYPE_p_std__vectorT_int_t limits, int search_para, SWIGTYPE_p_int times, SWIGTYPE_p_std__mapT_int_double_t prec_sum, SWIGTYPE_p_std__mapT_int_double_t time_sum) {
    return nsgannJNI.AnnBase_precision(swigCPtr, this, SWIGTYPE_p_std__vectorT_int_t.getCPtr(limits), search_para, SWIGTYPE_p_int.getCPtr(times), SWIGTYPE_p_std__mapT_int_double_t.getCPtr(prec_sum), SWIGTYPE_p_std__mapT_int_double_t.getCPtr(time_sum));
  }

}

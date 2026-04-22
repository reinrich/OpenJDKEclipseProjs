/* AUTOMATICALLY GENERATED FILE - DO NOT EDIT */

#ifndef JFRFILES_JFRTYPES_HPP
#define JFRFILES_JFRTYPES_HPP

#include "utilities/macros.hpp"
#if INCLUDE_JFR

#include <string.h>
#include "memory/allocation.hpp"

enum JfrTypeId {
  TYPE_VIRTUALSPACE = 173,
  TYPE_OBJECTSPACE = 174,
  TYPE_METASPACESIZES = 175,
  TYPE_COPYFAILED = 176,
  TYPE_G1EVACUATIONSTATISTICS = 177,
  TYPE_CALLEEMETHOD = 178,
  TYPE_SHENANDOAHHEAPREGIONSTATE = 179,
  TYPE_DEOPTIMIZATIONREASON = 180,
  TYPE_DEOPTIMIZATIONACTION = 181,
  TYPE_VMTHREADSTATE = 182,
  TYPE_BYTECODE = 183,
  TYPE_COMPILERTYPE = 184,
  TYPE_ZPAGETYPETYPE = 185,
  TYPE_ZSTATISTICSCOUNTERTYPE = 186,
  TYPE_ZSTATISTICSSAMPLERTYPE = 187,
  TYPE_NETWORKINTERFACENAME = 188,
  TYPE_THREAD = 189,
  TYPE_THREADGROUP = 190,
  TYPE_CLASS = 191,
  TYPE_CLASSLOADER = 192,
  TYPE_METHOD = 193,
  TYPE_SYMBOL = 194,
  TYPE_THREADSTATE = 195,
  TYPE_GCNAME = 196,
  TYPE_GCCAUSE = 197,
  TYPE_GCWHEN = 198,
  TYPE_G1HEAPREGIONTYPE = 199,
  TYPE_G1YCTYPE = 200,
  TYPE_GCTHRESHOLDUPDATER = 201,
  TYPE_REFERENCETYPE = 202,
  TYPE_METADATATYPE = 203,
  TYPE_METASPACEOBJECTTYPE = 204,
  TYPE_NARROWOOPMODE = 205,
  TYPE_VMOPERATIONTYPE = 206,
  TYPE_COMPILERPHASETYPE = 207,
  TYPE_FLAGVALUEORIGIN = 208,
  TYPE_CODEBLOBTYPE = 209,
  TYPE_INFLATECAUSE = 210,
  TYPE_MODULE = 211,
  TYPE_PACKAGE = 212,
  TYPE_STACKTRACE = 213,
  TYPE_FRAMETYPE = 214,
  TYPE_OLDOBJECTROOTSYSTEM = 215,
  TYPE_OLDOBJECTROOTTYPE = 216,
  TYPE_OLDOBJECTGCROOT = 217,
  TYPE_OLDOBJECTARRAY = 218,
  TYPE_OLDOBJECTFIELD = 219,
  TYPE_OLDOBJECT = 220,
  TYPE_REFERENCE = 221,
  TYPE_STACKFRAME = 222,
  TYPE_CHUNKHEADER = 223,
  TYPE_NMTTYPE = 224,
  TYPE_JAVAMONITORADDRESS = 225,
  TYPE_SAFEPOINTID = 226,
  TYPE_GCID = 227,
  TYPE_COMPILEID = 228,
  TYPE_SWEEPID = 229,
  TYPE_FLUSHID = 230,
  TYPE_CLASSREDEFINITIONID = 231,
  TYPE_LONG = 232,
  TYPE_INT = 233,
  TYPE_SHORT = 234,
  TYPE_BYTE = 235,
  TYPE_DOUBLE = 236,
  TYPE_FLOAT = 237,
  TYPE_BOOLEAN = 238,
  TYPE_CHAR = 239,
  TYPE_STRING = 240,
};

static const JfrTypeId FIRST_TYPE_ID = TYPE_VIRTUALSPACE;
static const JfrTypeId LAST_TYPE_ID = TYPE_STRING;

class JfrType : public AllStatic {
 public:
  static jlong name_to_id(const char* type_name) {
    if (strcmp(type_name, "java.lang.Class") == 0) {
      return TYPE_CLASS;
    }
    if (strcmp(type_name, "java.lang.Thread") == 0) {
      return TYPE_THREAD;
    }
    if (strcmp(type_name, "long") == 0) {
      return TYPE_LONG;
    }
    if (strcmp(type_name, "int") == 0) {
      return TYPE_INT;
    }
    if (strcmp(type_name, "short") == 0) {
      return TYPE_SHORT;
    }
    if (strcmp(type_name, "byte") == 0) {
      return TYPE_BYTE;
    }
    if (strcmp(type_name, "double") == 0) {
      return TYPE_DOUBLE;
    }
    if (strcmp(type_name, "float") == 0) {
      return TYPE_FLOAT;
    }
    if (strcmp(type_name, "boolean") == 0) {
      return TYPE_BOOLEAN;
    }
    if (strcmp(type_name, "char") == 0) {
      return TYPE_CHAR;
    }
    if (strcmp(type_name, "java.lang.String") == 0) {
      return TYPE_STRING;
    }
    if (strcmp(type_name, "jdk.types.StackTrace") == 0) {
      return TYPE_STACKTRACE;
    }
    return -1;
  }
};

#endif // INCLUDE_JFR
#endif // JFRFILES_JFRTYPES_HPP

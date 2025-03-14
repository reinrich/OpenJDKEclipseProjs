/* AUTOMATICALLY GENERATED FILE - DO NOT EDIT */

#ifndef JFRFILES_JFRTYPES_HPP
#define JFRFILES_JFRTYPES_HPP

#include "utilities/macros.hpp"
#if INCLUDE_JFR

#include <string.h>
#include "memory/allocation.hpp"

enum JfrTypeId {
  TYPE_VIRTUALSPACE = 167,
  TYPE_OBJECTSPACE = 168,
  TYPE_METASPACESIZES = 169,
  TYPE_COPYFAILED = 170,
  TYPE_G1EVACUATIONSTATISTICS = 171,
  TYPE_CALLEEMETHOD = 172,
  TYPE_SHENANDOAHHEAPREGIONSTATE = 173,
  TYPE_DEOPTIMIZATIONREASON = 174,
  TYPE_DEOPTIMIZATIONACTION = 175,
  TYPE_BYTECODE = 176,
  TYPE_COMPILERTYPE = 177,
  TYPE_ZPAGETYPETYPE = 178,
  TYPE_ZSTATISTICSCOUNTERTYPE = 179,
  TYPE_ZSTATISTICSSAMPLERTYPE = 180,
  TYPE_NETWORKINTERFACENAME = 181,
  TYPE_THREAD = 182,
  TYPE_THREADGROUP = 183,
  TYPE_CLASS = 184,
  TYPE_CLASSLOADER = 185,
  TYPE_METHOD = 186,
  TYPE_SYMBOL = 187,
  TYPE_THREADSTATE = 188,
  TYPE_GCNAME = 189,
  TYPE_GCCAUSE = 190,
  TYPE_GCWHEN = 191,
  TYPE_G1HEAPREGIONTYPE = 192,
  TYPE_G1YCTYPE = 193,
  TYPE_GCTHRESHOLDUPDATER = 194,
  TYPE_REFERENCETYPE = 195,
  TYPE_METADATATYPE = 196,
  TYPE_METASPACEOBJECTTYPE = 197,
  TYPE_NARROWOOPMODE = 198,
  TYPE_VMOPERATIONTYPE = 199,
  TYPE_COMPILERPHASETYPE = 200,
  TYPE_FLAGVALUEORIGIN = 201,
  TYPE_CODEBLOBTYPE = 202,
  TYPE_INFLATECAUSE = 203,
  TYPE_MODULE = 204,
  TYPE_PACKAGE = 205,
  TYPE_STACKTRACE = 206,
  TYPE_FRAMETYPE = 207,
  TYPE_OLDOBJECTROOTSYSTEM = 208,
  TYPE_OLDOBJECTROOTTYPE = 209,
  TYPE_OLDOBJECTGCROOT = 210,
  TYPE_OLDOBJECTARRAY = 211,
  TYPE_OLDOBJECTFIELD = 212,
  TYPE_OLDOBJECT = 213,
  TYPE_REFERENCE = 214,
  TYPE_STACKFRAME = 215,
  TYPE_CHUNKHEADER = 216,
  TYPE_NMTTYPE = 217,
  TYPE_JAVAMONITORADDRESS = 218,
  TYPE_SAFEPOINTID = 219,
  TYPE_GCID = 220,
  TYPE_COMPILEID = 221,
  TYPE_SWEEPID = 222,
  TYPE_FLUSHID = 223,
  TYPE_CLASSREDEFINITIONID = 224,
  TYPE_LONG = 225,
  TYPE_INT = 226,
  TYPE_SHORT = 227,
  TYPE_BYTE = 228,
  TYPE_DOUBLE = 229,
  TYPE_FLOAT = 230,
  TYPE_BOOLEAN = 231,
  TYPE_CHAR = 232,
  TYPE_STRING = 233,
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

/* AUTOMATICALLY GENERATED FILE - DO NOT EDIT */

#ifndef JFRFILES_JFRTYPES_HPP
#define JFRFILES_JFRTYPES_HPP

#include "utilities/macros.hpp"
#if INCLUDE_JFR

#include <string.h>
#include "memory/allocation.hpp"

enum JfrTypeId {
  TYPE_VIRTUALSPACE = 166,
  TYPE_OBJECTSPACE = 167,
  TYPE_METASPACESIZES = 168,
  TYPE_COPYFAILED = 169,
  TYPE_G1EVACUATIONSTATISTICS = 170,
  TYPE_CALLEEMETHOD = 171,
  TYPE_SHENANDOAHHEAPREGIONSTATE = 172,
  TYPE_DEOPTIMIZATIONREASON = 173,
  TYPE_DEOPTIMIZATIONACTION = 174,
  TYPE_BYTECODE = 175,
  TYPE_COMPILERTYPE = 176,
  TYPE_ZPAGETYPETYPE = 177,
  TYPE_ZSTATISTICSCOUNTERTYPE = 178,
  TYPE_ZSTATISTICSSAMPLERTYPE = 179,
  TYPE_NETWORKINTERFACENAME = 180,
  TYPE_THREAD = 181,
  TYPE_THREADGROUP = 182,
  TYPE_CLASS = 183,
  TYPE_CLASSLOADER = 184,
  TYPE_METHOD = 185,
  TYPE_SYMBOL = 186,
  TYPE_THREADSTATE = 187,
  TYPE_GCNAME = 188,
  TYPE_GCCAUSE = 189,
  TYPE_GCWHEN = 190,
  TYPE_G1HEAPREGIONTYPE = 191,
  TYPE_G1YCTYPE = 192,
  TYPE_GCTHRESHOLDUPDATER = 193,
  TYPE_REFERENCETYPE = 194,
  TYPE_METADATATYPE = 195,
  TYPE_METASPACEOBJECTTYPE = 196,
  TYPE_NARROWOOPMODE = 197,
  TYPE_VMOPERATIONTYPE = 198,
  TYPE_COMPILERPHASETYPE = 199,
  TYPE_FLAGVALUEORIGIN = 200,
  TYPE_CODEBLOBTYPE = 201,
  TYPE_INFLATECAUSE = 202,
  TYPE_MODULE = 203,
  TYPE_PACKAGE = 204,
  TYPE_STACKTRACE = 205,
  TYPE_FRAMETYPE = 206,
  TYPE_OLDOBJECTROOTSYSTEM = 207,
  TYPE_OLDOBJECTROOTTYPE = 208,
  TYPE_OLDOBJECTGCROOT = 209,
  TYPE_OLDOBJECTARRAY = 210,
  TYPE_OLDOBJECTFIELD = 211,
  TYPE_OLDOBJECT = 212,
  TYPE_REFERENCE = 213,
  TYPE_STACKFRAME = 214,
  TYPE_CHUNKHEADER = 215,
  TYPE_NMTTYPE = 216,
  TYPE_JAVAMONITORADDRESS = 217,
  TYPE_SAFEPOINTID = 218,
  TYPE_GCID = 219,
  TYPE_COMPILEID = 220,
  TYPE_SWEEPID = 221,
  TYPE_FLUSHID = 222,
  TYPE_CLASSREDEFINITIONID = 223,
  TYPE_LONG = 224,
  TYPE_INT = 225,
  TYPE_SHORT = 226,
  TYPE_BYTE = 227,
  TYPE_DOUBLE = 228,
  TYPE_FLOAT = 229,
  TYPE_BOOLEAN = 230,
  TYPE_CHAR = 231,
  TYPE_STRING = 232,
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

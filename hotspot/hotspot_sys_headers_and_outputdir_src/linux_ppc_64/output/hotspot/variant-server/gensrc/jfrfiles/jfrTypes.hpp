/* AUTOMATICALLY GENERATED FILE - DO NOT EDIT */

#ifndef JFRFILES_JFRTYPES_HPP
#define JFRFILES_JFRTYPES_HPP

#include "utilities/macros.hpp"
#if INCLUDE_JFR

#include <string.h>
#include "memory/allocation.hpp"

enum JfrTypeId {
  TYPE_VIRTUALSPACE = 153,
  TYPE_OBJECTSPACE = 154,
  TYPE_METASPACESIZES = 155,
  TYPE_COPYFAILED = 156,
  TYPE_G1EVACUATIONSTATISTICS = 157,
  TYPE_CALLEEMETHOD = 158,
  TYPE_SHENANDOAHHEAPREGIONSTATE = 159,
  TYPE_DEOPTIMIZATIONREASON = 160,
  TYPE_DEOPTIMIZATIONACTION = 161,
  TYPE_BYTECODE = 162,
  TYPE_COMPILERTYPE = 163,
  TYPE_ZPAGETYPETYPE = 164,
  TYPE_ZSTATISTICSCOUNTERTYPE = 165,
  TYPE_ZSTATISTICSSAMPLERTYPE = 166,
  TYPE_NETWORKINTERFACENAME = 167,
  TYPE_THREAD = 168,
  TYPE_THREADGROUP = 169,
  TYPE_CLASS = 170,
  TYPE_CLASSLOADER = 171,
  TYPE_METHOD = 172,
  TYPE_SYMBOL = 173,
  TYPE_THREADSTATE = 174,
  TYPE_GCNAME = 175,
  TYPE_GCCAUSE = 176,
  TYPE_GCWHEN = 177,
  TYPE_G1HEAPREGIONTYPE = 178,
  TYPE_G1YCTYPE = 179,
  TYPE_GCTHRESHOLDUPDATER = 180,
  TYPE_REFERENCETYPE = 181,
  TYPE_METADATATYPE = 182,
  TYPE_METASPACEOBJECTTYPE = 183,
  TYPE_NARROWOOPMODE = 184,
  TYPE_VMOPERATIONTYPE = 185,
  TYPE_COMPILERPHASETYPE = 186,
  TYPE_FLAGVALUEORIGIN = 187,
  TYPE_CODEBLOBTYPE = 188,
  TYPE_INFLATECAUSE = 189,
  TYPE_MODULE = 190,
  TYPE_PACKAGE = 191,
  TYPE_STACKTRACE = 192,
  TYPE_FRAMETYPE = 193,
  TYPE_OLDOBJECTROOTSYSTEM = 194,
  TYPE_OLDOBJECTROOTTYPE = 195,
  TYPE_OLDOBJECTGCROOT = 196,
  TYPE_OLDOBJECTARRAY = 197,
  TYPE_OLDOBJECTFIELD = 198,
  TYPE_OLDOBJECT = 199,
  TYPE_REFERENCE = 200,
  TYPE_STACKFRAME = 201,
  TYPE_CHUNKHEADER = 202,
  TYPE_JAVAMONITORADDRESS = 203,
  TYPE_SAFEPOINTID = 204,
  TYPE_GCID = 205,
  TYPE_COMPILEID = 206,
  TYPE_SWEEPID = 207,
  TYPE_FLUSHID = 208,
  TYPE_CLASSREDEFINITIONID = 209,
  TYPE_LONG = 210,
  TYPE_INT = 211,
  TYPE_SHORT = 212,
  TYPE_BYTE = 213,
  TYPE_DOUBLE = 214,
  TYPE_FLOAT = 215,
  TYPE_BOOLEAN = 216,
  TYPE_CHAR = 217,
  TYPE_STRING = 218,
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

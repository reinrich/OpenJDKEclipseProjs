/* AUTOMATICALLY GENERATED FILE - DO NOT EDIT */

#ifndef JFRFILES_JFRTYPES_HPP
#define JFRFILES_JFRTYPES_HPP

#include "utilities/macros.hpp"
#if INCLUDE_JFR

#include <string.h>
#include "memory/allocation.hpp"

enum JfrTypeId {
  TYPE_VIRTUALSPACE = 150,
  TYPE_OBJECTSPACE = 151,
  TYPE_METASPACESIZES = 152,
  TYPE_COPYFAILED = 153,
  TYPE_G1EVACUATIONSTATISTICS = 154,
  TYPE_CALLEEMETHOD = 155,
  TYPE_SHENANDOAHHEAPREGIONSTATE = 156,
  TYPE_DEOPTIMIZATIONREASON = 157,
  TYPE_DEOPTIMIZATIONACTION = 158,
  TYPE_BYTECODE = 159,
  TYPE_COMPILERTYPE = 160,
  TYPE_ZPAGETYPETYPE = 161,
  TYPE_ZSTATISTICSCOUNTERTYPE = 162,
  TYPE_ZSTATISTICSSAMPLERTYPE = 163,
  TYPE_NETWORKINTERFACENAME = 164,
  TYPE_THREAD = 165,
  TYPE_THREADGROUP = 166,
  TYPE_CLASS = 167,
  TYPE_CLASSLOADER = 168,
  TYPE_METHOD = 169,
  TYPE_SYMBOL = 170,
  TYPE_THREADSTATE = 171,
  TYPE_GCNAME = 172,
  TYPE_GCCAUSE = 173,
  TYPE_GCWHEN = 174,
  TYPE_G1HEAPREGIONTYPE = 175,
  TYPE_G1YCTYPE = 176,
  TYPE_GCTHRESHOLDUPDATER = 177,
  TYPE_REFERENCETYPE = 178,
  TYPE_METADATATYPE = 179,
  TYPE_METASPACEOBJECTTYPE = 180,
  TYPE_NARROWOOPMODE = 181,
  TYPE_VMOPERATIONTYPE = 182,
  TYPE_COMPILERPHASETYPE = 183,
  TYPE_FLAGVALUEORIGIN = 184,
  TYPE_CODEBLOBTYPE = 185,
  TYPE_INFLATECAUSE = 186,
  TYPE_MODULE = 187,
  TYPE_PACKAGE = 188,
  TYPE_STACKTRACE = 189,
  TYPE_FRAMETYPE = 190,
  TYPE_OLDOBJECTROOTSYSTEM = 191,
  TYPE_OLDOBJECTROOTTYPE = 192,
  TYPE_OLDOBJECTGCROOT = 193,
  TYPE_OLDOBJECTARRAY = 194,
  TYPE_OLDOBJECTFIELD = 195,
  TYPE_OLDOBJECT = 196,
  TYPE_REFERENCE = 197,
  TYPE_STACKFRAME = 198,
  TYPE_CHUNKHEADER = 199,
  TYPE_JAVAMONITORADDRESS = 200,
  TYPE_SAFEPOINTID = 201,
  TYPE_GCID = 202,
  TYPE_COMPILEID = 203,
  TYPE_SWEEPID = 204,
  TYPE_FLUSHID = 205,
  TYPE_CLASSREDEFINITIONID = 206,
  TYPE_LONG = 207,
  TYPE_INT = 208,
  TYPE_SHORT = 209,
  TYPE_BYTE = 210,
  TYPE_DOUBLE = 211,
  TYPE_FLOAT = 212,
  TYPE_BOOLEAN = 213,
  TYPE_CHAR = 214,
  TYPE_STRING = 215,
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

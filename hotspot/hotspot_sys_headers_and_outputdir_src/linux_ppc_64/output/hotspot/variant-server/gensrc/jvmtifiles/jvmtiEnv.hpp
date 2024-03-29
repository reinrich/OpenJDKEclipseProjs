/*
 Copyright (c) 2002, 2022, Oracle and/or its affiliates. All rights reserved.
 DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.

 This code is free software; you can redistribute it and/or modify it
 under the terms of the GNU General Public License version 2 only, as
 published by the Free Software Foundation.

 This code is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 version 2 for more details (a copy is included in the LICENSE file that
 accompanied this code).

 You should have received a copy of the GNU General Public License version
 2 along with this work; if not, write to the Free Software Foundation,
 Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.

 Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 or visit www.oracle.com if you need additional information or have any
 questions.
 */

 /* AUTOMATICALLY GENERATED FILE - DO NOT EDIT */

    

#ifndef GENERATED_JVMTIFILES_JVMTIENV_HPP
#define GENERATED_JVMTIFILES_JVMTIENV_HPP

#include "prims/jvmtiEnvBase.hpp"
#include "prims/jvmtiImpl.hpp"

enum {
    JVMTI_INTERNAL_CAPABILITY_COUNT = 45
};


class JvmtiEnv : public JvmtiEnvBase {

private:
    
    JvmtiEnv(jint version);
    ~JvmtiEnv();

public:

    static JvmtiEnv* create_a_jvmti(jint version);


  // Memory Management functions
    jvmtiError Allocate(jlong size, unsigned char** mem_ptr);
    jvmtiError Deallocate(unsigned char* mem);

  // Thread functions
    jvmtiError GetThreadState(jthread thread, jint* thread_state_ptr);
    jvmtiError GetCurrentThread(jthread* thread_ptr);
    jvmtiError GetAllThreads(jint* threads_count_ptr, jthread** threads_ptr);
    jvmtiError SuspendThread(jthread thread);
    jvmtiError SuspendThreadList(jint request_count, const jthread* request_list, jvmtiError* results);
    jvmtiError SuspendAllVirtualThreads(jint except_count, const jthread* except_list);
    jvmtiError ResumeThread(jthread thread);
    jvmtiError ResumeThreadList(jint request_count, const jthread* request_list, jvmtiError* results);
    jvmtiError ResumeAllVirtualThreads(jint except_count, const jthread* except_list);
    jvmtiError StopThread(jthread thread, jobject exception);
    jvmtiError InterruptThread(jthread thread);
    jvmtiError GetThreadInfo(jthread thread, jvmtiThreadInfo* info_ptr);
    jvmtiError GetOwnedMonitorInfo(jthread thread, jint* owned_monitor_count_ptr, jobject** owned_monitors_ptr);
    jvmtiError GetOwnedMonitorStackDepthInfo(jthread thread, jint* monitor_info_count_ptr, jvmtiMonitorStackDepthInfo** monitor_info_ptr);
    jvmtiError GetCurrentContendedMonitor(jthread thread, jobject* monitor_ptr);
    jvmtiError RunAgentThread(jthread thread, jvmtiStartFunction proc, const void* arg, jint priority);
    jvmtiError SetThreadLocalStorage(jthread thread, const void* data);
    jvmtiError GetThreadLocalStorage(jthread thread, void** data_ptr);

  // Thread Group functions
    jvmtiError GetTopThreadGroups(jint* group_count_ptr, jthreadGroup** groups_ptr);
    jvmtiError GetThreadGroupInfo(jthreadGroup group, jvmtiThreadGroupInfo* info_ptr);
    jvmtiError GetThreadGroupChildren(jthreadGroup group, jint* thread_count_ptr, jthread** threads_ptr, jint* group_count_ptr, jthreadGroup** groups_ptr);

  // Stack Frame functions
    jvmtiError GetStackTrace(jthread thread, jint start_depth, jint max_frame_count, jvmtiFrameInfo* frame_buffer, jint* count_ptr);
    jvmtiError GetAllStackTraces(jint max_frame_count, jvmtiStackInfo** stack_info_ptr, jint* thread_count_ptr);
    jvmtiError GetThreadListStackTraces(jint thread_count, const jthread* thread_list, jint max_frame_count, jvmtiStackInfo** stack_info_ptr);
    jvmtiError GetFrameCount(jthread thread, jint* count_ptr);
    jvmtiError PopFrame(jthread thread);
    jvmtiError GetFrameLocation(jthread thread, jint depth, jmethodID* method_ptr, jlocation* location_ptr);
    jvmtiError NotifyFramePop(jthread thread, jint depth);

  // Force Early Return functions
    jvmtiError ForceEarlyReturnObject(jthread thread, jobject value);
    jvmtiError ForceEarlyReturnInt(jthread thread, jint value);
    jvmtiError ForceEarlyReturnLong(jthread thread, jlong value);
    jvmtiError ForceEarlyReturnFloat(jthread thread, jfloat value);
    jvmtiError ForceEarlyReturnDouble(jthread thread, jdouble value);
    jvmtiError ForceEarlyReturnVoid(jthread thread);

  // Heap functions
    jvmtiError FollowReferences(jint heap_filter, jclass klass, jobject initial_object, const jvmtiHeapCallbacks* callbacks, const void* user_data);
    jvmtiError IterateThroughHeap(jint heap_filter, jclass klass, const jvmtiHeapCallbacks* callbacks, const void* user_data);
    jvmtiError GetTag(jobject object, jlong* tag_ptr);
    jvmtiError SetTag(jobject object, jlong tag);
    jvmtiError GetObjectsWithTags(jint tag_count, const jlong* tags, jint* count_ptr, jobject** object_result_ptr, jlong** tag_result_ptr);
    jvmtiError ForceGarbageCollection();

  // Heap (1.0) functions
    jvmtiError IterateOverObjectsReachableFromObject(jobject object, jvmtiObjectReferenceCallback object_reference_callback, const void* user_data);
    jvmtiError IterateOverReachableObjects(jvmtiHeapRootCallback heap_root_callback, jvmtiStackReferenceCallback stack_ref_callback, jvmtiObjectReferenceCallback object_ref_callback, const void* user_data);
    jvmtiError IterateOverHeap(jvmtiHeapObjectFilter object_filter, jvmtiHeapObjectCallback heap_object_callback, const void* user_data);
    jvmtiError IterateOverInstancesOfClass(oop k_mirror, jvmtiHeapObjectFilter object_filter, jvmtiHeapObjectCallback heap_object_callback, const void* user_data);

  // Local Variable functions
    jvmtiError GetLocalObject(jthread thread, jint depth, jint slot, jobject* value_ptr);
    jvmtiError GetLocalInstance(jthread thread, jint depth, jobject* value_ptr);
    jvmtiError GetLocalInt(jthread thread, jint depth, jint slot, jint* value_ptr);
    jvmtiError GetLocalLong(jthread thread, jint depth, jint slot, jlong* value_ptr);
    jvmtiError GetLocalFloat(jthread thread, jint depth, jint slot, jfloat* value_ptr);
    jvmtiError GetLocalDouble(jthread thread, jint depth, jint slot, jdouble* value_ptr);
    jvmtiError SetLocalObject(jthread thread, jint depth, jint slot, jobject value);
    jvmtiError SetLocalInt(jthread thread, jint depth, jint slot, jint value);
    jvmtiError SetLocalLong(jthread thread, jint depth, jint slot, jlong value);
    jvmtiError SetLocalFloat(jthread thread, jint depth, jint slot, jfloat value);
    jvmtiError SetLocalDouble(jthread thread, jint depth, jint slot, jdouble value);

  // Breakpoint functions
    jvmtiError SetBreakpoint(Method* checked_method, jlocation location);
    jvmtiError ClearBreakpoint(Method* checked_method, jlocation location);

  // Watched Field functions
    jvmtiError SetFieldAccessWatch(fieldDescriptor* fdesc_ptr);
    jvmtiError ClearFieldAccessWatch(fieldDescriptor* fdesc_ptr);
    jvmtiError SetFieldModificationWatch(fieldDescriptor* fdesc_ptr);
    jvmtiError ClearFieldModificationWatch(fieldDescriptor* fdesc_ptr);

  // Module functions
    jvmtiError GetAllModules(jint* module_count_ptr, jobject** modules_ptr);
    jvmtiError GetNamedModule(jobject class_loader, const char* package_name, jobject* module_ptr);
    jvmtiError AddModuleReads(jobject module, jobject to_module);
    jvmtiError AddModuleExports(jobject module, const char* pkg_name, jobject to_module);
    jvmtiError AddModuleOpens(jobject module, const char* pkg_name, jobject to_module);
    jvmtiError AddModuleUses(jobject module, jclass service);
    jvmtiError AddModuleProvides(jobject module, jclass service, jclass impl_class);
    jvmtiError IsModifiableModule(jobject module, jboolean* is_modifiable_module_ptr);

  // Class functions
    jvmtiError GetLoadedClasses(jint* class_count_ptr, jclass** classes_ptr);
    jvmtiError GetClassLoaderClasses(jobject initiating_loader, jint* class_count_ptr, jclass** classes_ptr);
    jvmtiError GetClassSignature(oop k_mirror, char** signature_ptr, char** generic_ptr);
    jvmtiError GetClassStatus(oop k_mirror, jint* status_ptr);
    jvmtiError GetSourceFileName(oop k_mirror, char** source_name_ptr);
    jvmtiError GetClassModifiers(oop k_mirror, jint* modifiers_ptr);
    jvmtiError GetClassMethods(oop k_mirror, jint* method_count_ptr, jmethodID** methods_ptr);
    jvmtiError GetClassFields(oop k_mirror, jint* field_count_ptr, jfieldID** fields_ptr);
    jvmtiError GetImplementedInterfaces(oop k_mirror, jint* interface_count_ptr, jclass** interfaces_ptr);
    jvmtiError GetClassVersionNumbers(oop k_mirror, jint* minor_version_ptr, jint* major_version_ptr);
    jvmtiError GetConstantPool(oop k_mirror, jint* constant_pool_count_ptr, jint* constant_pool_byte_count_ptr, unsigned char** constant_pool_bytes_ptr);
    jvmtiError IsInterface(oop k_mirror, jboolean* is_interface_ptr);
    jvmtiError IsArrayClass(oop k_mirror, jboolean* is_array_class_ptr);
    jvmtiError IsModifiableClass(oop k_mirror, jboolean* is_modifiable_class_ptr);
    jvmtiError GetClassLoader(oop k_mirror, jobject* classloader_ptr);
    jvmtiError GetSourceDebugExtension(oop k_mirror, char** source_debug_extension_ptr);
    jvmtiError RetransformClasses(jint class_count, const jclass* classes);
    jvmtiError RedefineClasses(jint class_count, const jvmtiClassDefinition* class_definitions);

  // Object functions
    jvmtiError GetObjectSize(jobject object, jlong* size_ptr);
    jvmtiError GetObjectHashCode(jobject object, jint* hash_code_ptr);
    jvmtiError GetObjectMonitorUsage(jobject object, jvmtiMonitorUsage* info_ptr);

  // Field functions
    jvmtiError GetFieldName(fieldDescriptor* fdesc_ptr, char** name_ptr, char** signature_ptr, char** generic_ptr);
    jvmtiError GetFieldDeclaringClass(fieldDescriptor* fdesc_ptr, jclass* declaring_class_ptr);
    jvmtiError GetFieldModifiers(fieldDescriptor* fdesc_ptr, jint* modifiers_ptr);
    jvmtiError IsFieldSynthetic(fieldDescriptor* fdesc_ptr, jboolean* is_synthetic_ptr);

  // Method functions
    jvmtiError GetMethodName(Method* checked_method, char** name_ptr, char** signature_ptr, char** generic_ptr);
    jvmtiError GetMethodDeclaringClass(Method* checked_method, jclass* declaring_class_ptr);
    jvmtiError GetMethodModifiers(Method* checked_method, jint* modifiers_ptr);
    jvmtiError GetMaxLocals(Method* checked_method, jint* max_ptr);
    jvmtiError GetArgumentsSize(Method* checked_method, jint* size_ptr);
    jvmtiError GetLineNumberTable(Method* checked_method, jint* entry_count_ptr, jvmtiLineNumberEntry** table_ptr);
    jvmtiError GetMethodLocation(Method* checked_method, jlocation* start_location_ptr, jlocation* end_location_ptr);
    jvmtiError GetLocalVariableTable(Method* checked_method, jint* entry_count_ptr, jvmtiLocalVariableEntry** table_ptr);
    jvmtiError GetBytecodes(Method* checked_method, jint* bytecode_count_ptr, unsigned char** bytecodes_ptr);
    jvmtiError IsMethodNative(Method* checked_method, jboolean* is_native_ptr);
    jvmtiError IsMethodSynthetic(Method* checked_method, jboolean* is_synthetic_ptr);
    jvmtiError IsMethodObsolete(Method* checked_method, jboolean* is_obsolete_ptr);
    jvmtiError SetNativeMethodPrefix(const char* prefix);
    jvmtiError SetNativeMethodPrefixes(jint prefix_count, char** prefixes);

  // Raw Monitor functions
    jvmtiError CreateRawMonitor(const char* name, jrawMonitorID* monitor_ptr);
    jvmtiError DestroyRawMonitor(JvmtiRawMonitor * rmonitor);
    jvmtiError RawMonitorEnter(JvmtiRawMonitor * rmonitor);
    jvmtiError RawMonitorExit(JvmtiRawMonitor * rmonitor);
    jvmtiError RawMonitorWait(JvmtiRawMonitor * rmonitor, jlong millis);
    jvmtiError RawMonitorNotify(JvmtiRawMonitor * rmonitor);
    jvmtiError RawMonitorNotifyAll(JvmtiRawMonitor * rmonitor);

  // JNI Function Interception functions
    jvmtiError SetJNIFunctionTable(const jniNativeInterface* function_table);
    jvmtiError GetJNIFunctionTable(jniNativeInterface** function_table);

  // Event Management functions
    jvmtiError SetEventCallbacks(const jvmtiEventCallbacks* callbacks, jint size_of_callbacks);
    jvmtiError SetEventNotificationMode(jvmtiEventMode mode, jvmtiEvent event_type, jthread event_thread,   ...);
    jvmtiError GenerateEvents(jvmtiEvent event_type);

  // Extension Mechanism functions
    jvmtiError GetExtensionFunctions(jint* extension_count_ptr, jvmtiExtensionFunctionInfo** extensions);
    jvmtiError GetExtensionEvents(jint* extension_count_ptr, jvmtiExtensionEventInfo** extensions);
    jvmtiError SetExtensionEventCallback(jint extension_event_index, jvmtiExtensionEvent callback);

  // Capability functions
    jvmtiError GetPotentialCapabilities(jvmtiCapabilities* capabilities_ptr);
    jvmtiError AddCapabilities(const jvmtiCapabilities* capabilities_ptr);
    jvmtiError RelinquishCapabilities(const jvmtiCapabilities* capabilities_ptr);
    jvmtiError GetCapabilities(jvmtiCapabilities* capabilities_ptr);

  // Timers functions
    jvmtiError GetCurrentThreadCpuTimerInfo(jvmtiTimerInfo* info_ptr);
    jvmtiError GetCurrentThreadCpuTime(jlong* nanos_ptr);
    jvmtiError GetThreadCpuTimerInfo(jvmtiTimerInfo* info_ptr);
    jvmtiError GetThreadCpuTime(jthread thread, jlong* nanos_ptr);
    jvmtiError GetTimerInfo(jvmtiTimerInfo* info_ptr);
    jvmtiError GetTime(jlong* nanos_ptr);
    jvmtiError GetAvailableProcessors(jint* processor_count_ptr);

  // Class Loader Search functions
    jvmtiError AddToBootstrapClassLoaderSearch(const char* segment);
    jvmtiError AddToSystemClassLoaderSearch(const char* segment);

  // System Properties functions
    jvmtiError GetSystemProperties(jint* count_ptr, char*** property_ptr);
    jvmtiError GetSystemProperty(const char* property, char** value_ptr);
    jvmtiError SetSystemProperty(const char* property, const char* value_ptr);

  // General functions
    jvmtiError GetPhase(jvmtiPhase* phase_ptr);
    jvmtiError DisposeEnvironment();
    jvmtiError SetEnvironmentLocalStorage(const void* data);
    jvmtiError GetEnvironmentLocalStorage(void** data_ptr);
    jvmtiError GetVersionNumber(jint* version_ptr);
    jvmtiError GetErrorName(jvmtiError error, char** name_ptr);
    jvmtiError SetVerboseFlag(jvmtiVerboseFlag flag, jboolean value);
    jvmtiError GetJLocationFormat(jvmtiJlocationFormat* format_ptr);

  // Heap Monitoring functions
    jvmtiError SetHeapSamplingInterval(jint sampling_interval);

};

#endif // GENERATED_JVMTIFILES_JVMTIENV_HPP

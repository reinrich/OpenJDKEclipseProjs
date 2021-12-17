/* AUTOMATICALLY GENERATED FILE - DO NOT EDIT */

#ifndef JFRFILES_JFR_NATIVE_EVENTSETTING_HPP
#define JFRFILES_JFR_NATIVE_EVENTSETTING_HPP

#include "utilities/macros.hpp"
#if INCLUDE_JFR
#include "jfrfiles/jfrEventIds.hpp"

/**
 * Event setting. We add some padding so we can use our
 * event IDs as indexes into this.
 */

struct jfrNativeEventSetting {
  jlong  threshold_ticks;
  jlong  cutoff_ticks;
  u1     stacktrace;
  u1     enabled;
  u1     large;
  u1     pad[5]; // Because GCC on linux ia32 at least tries to pack this.
};

union JfrNativeSettings {
  // Array version.
  jfrNativeEventSetting bits[NUMBER_OF_EVENTS];
  // Then, to make it easy to debug,
  // add named struct members also.
  struct {
    jfrNativeEventSetting pad[NUMBER_OF_RESERVED_EVENTS];
    jfrNativeEventSetting Duration;
    jfrNativeEventSetting Instant;
    jfrNativeEventSetting Value;
    jfrNativeEventSetting Text;
    jfrNativeEventSetting ZThreadDebug;
    jfrNativeEventSetting ThreadStart;
    jfrNativeEventSetting ThreadEnd;
    jfrNativeEventSetting ThreadSleep;
    jfrNativeEventSetting ThreadPark;
    jfrNativeEventSetting JavaMonitorEnter;
    jfrNativeEventSetting JavaMonitorWait;
    jfrNativeEventSetting JavaMonitorInflate;
    jfrNativeEventSetting SyncOnValueBasedClass;
    jfrNativeEventSetting ReservedStackActivation;
    jfrNativeEventSetting ClassLoad;
    jfrNativeEventSetting ClassDefine;
    jfrNativeEventSetting ClassRedefinition;
    jfrNativeEventSetting RedefineClasses;
    jfrNativeEventSetting RetransformClasses;
    jfrNativeEventSetting ClassUnload;
    jfrNativeEventSetting IntFlagChanged;
    jfrNativeEventSetting UnsignedIntFlagChanged;
    jfrNativeEventSetting LongFlagChanged;
    jfrNativeEventSetting UnsignedLongFlagChanged;
    jfrNativeEventSetting DoubleFlagChanged;
    jfrNativeEventSetting BooleanFlagChanged;
    jfrNativeEventSetting StringFlagChanged;
    jfrNativeEventSetting VirtualSpace;
    jfrNativeEventSetting ObjectSpace;
    jfrNativeEventSetting GCHeapSummary;
    jfrNativeEventSetting MetaspaceSizes;
    jfrNativeEventSetting MetaspaceSummary;
    jfrNativeEventSetting MetaspaceGCThreshold;
    jfrNativeEventSetting MetaspaceAllocationFailure;
    jfrNativeEventSetting MetaspaceOOM;
    jfrNativeEventSetting MetaspaceChunkFreeListSummary;
    jfrNativeEventSetting PSHeapSummary;
    jfrNativeEventSetting G1HeapSummary;
    jfrNativeEventSetting GarbageCollection;
    jfrNativeEventSetting SystemGC;
    jfrNativeEventSetting ParallelOldGarbageCollection;
    jfrNativeEventSetting YoungGarbageCollection;
    jfrNativeEventSetting OldGarbageCollection;
    jfrNativeEventSetting G1GarbageCollection;
    jfrNativeEventSetting G1MMU;
    jfrNativeEventSetting EvacuationInformation;
    jfrNativeEventSetting GCReferenceStatistics;
    jfrNativeEventSetting CopyFailed;
    jfrNativeEventSetting ObjectCountAfterGC;
    jfrNativeEventSetting G1EvacuationStatistics;
    jfrNativeEventSetting G1EvacuationYoungStatistics;
    jfrNativeEventSetting G1EvacuationOldStatistics;
    jfrNativeEventSetting G1BasicIHOP;
    jfrNativeEventSetting G1AdaptiveIHOP;
    jfrNativeEventSetting PromoteObjectInNewPLAB;
    jfrNativeEventSetting PromoteObjectOutsidePLAB;
    jfrNativeEventSetting PromotionFailed;
    jfrNativeEventSetting EvacuationFailed;
    jfrNativeEventSetting ConcurrentModeFailure;
    jfrNativeEventSetting GCPhasePause;
    jfrNativeEventSetting GCPhasePauseLevel1;
    jfrNativeEventSetting GCPhasePauseLevel2;
    jfrNativeEventSetting GCPhasePauseLevel3;
    jfrNativeEventSetting GCPhasePauseLevel4;
    jfrNativeEventSetting GCPhaseConcurrent;
    jfrNativeEventSetting GCPhaseConcurrentLevel1;
    jfrNativeEventSetting GCPhaseParallel;
    jfrNativeEventSetting AllocationRequiringGC;
    jfrNativeEventSetting TenuringDistribution;
    jfrNativeEventSetting G1HeapRegionTypeChange;
    jfrNativeEventSetting Compilation;
    jfrNativeEventSetting CompilerPhase;
    jfrNativeEventSetting CompilationFailure;
    jfrNativeEventSetting CalleeMethod;
    jfrNativeEventSetting CompilerInlining;
    jfrNativeEventSetting SweepCodeCache;
    jfrNativeEventSetting CodeCacheFull;
    jfrNativeEventSetting Deoptimization;
    jfrNativeEventSetting SafepointBegin;
    jfrNativeEventSetting SafepointStateSynchronization;
    jfrNativeEventSetting SafepointCleanup;
    jfrNativeEventSetting SafepointCleanupTask;
    jfrNativeEventSetting SafepointEnd;
    jfrNativeEventSetting ExecuteVMOperation;
    jfrNativeEventSetting Shutdown;
    jfrNativeEventSetting ObjectAllocationInNewTLAB;
    jfrNativeEventSetting ObjectAllocationOutsideTLAB;
    jfrNativeEventSetting ObjectAllocationSample;
    jfrNativeEventSetting OldObjectSample;
    jfrNativeEventSetting DumpReason;
    jfrNativeEventSetting DataLoss;
    jfrNativeEventSetting JVMInformation;
    jfrNativeEventSetting OSInformation;
    jfrNativeEventSetting VirtualizationInformation;
    jfrNativeEventSetting InitialSystemProperty;
    jfrNativeEventSetting InitialEnvironmentVariable;
    jfrNativeEventSetting SystemProcess;
    jfrNativeEventSetting CPUInformation;
    jfrNativeEventSetting CPUTimeStampCounter;
    jfrNativeEventSetting CPULoad;
    jfrNativeEventSetting ThreadCPULoad;
    jfrNativeEventSetting ThreadContextSwitchRate;
    jfrNativeEventSetting NetworkUtilization;
    jfrNativeEventSetting JavaThreadStatistics;
    jfrNativeEventSetting ClassLoadingStatistics;
    jfrNativeEventSetting ClassLoaderStatistics;
    jfrNativeEventSetting SymbolTableStatistics;
    jfrNativeEventSetting StringTableStatistics;
    jfrNativeEventSetting PlaceholderTableStatistics;
    jfrNativeEventSetting LoaderConstraintsTableStatistics;
    jfrNativeEventSetting ProtectionDomainCacheTableStatistics;
    jfrNativeEventSetting ThreadAllocationStatistics;
    jfrNativeEventSetting PhysicalMemory;
    jfrNativeEventSetting ExecutionSample;
    jfrNativeEventSetting NativeMethodSample;
    jfrNativeEventSetting ThreadDump;
    jfrNativeEventSetting NativeLibrary;
    jfrNativeEventSetting ModuleRequire;
    jfrNativeEventSetting ModuleExport;
    jfrNativeEventSetting CompilerStatistics;
    jfrNativeEventSetting CompilerConfiguration;
    jfrNativeEventSetting CodeCacheStatistics;
    jfrNativeEventSetting CodeCacheConfiguration;
    jfrNativeEventSetting CodeSweeperStatistics;
    jfrNativeEventSetting CodeSweeperConfiguration;
    jfrNativeEventSetting IntFlag;
    jfrNativeEventSetting UnsignedIntFlag;
    jfrNativeEventSetting LongFlag;
    jfrNativeEventSetting UnsignedLongFlag;
    jfrNativeEventSetting DoubleFlag;
    jfrNativeEventSetting BooleanFlag;
    jfrNativeEventSetting StringFlag;
    jfrNativeEventSetting ObjectCount;
    jfrNativeEventSetting G1HeapRegionInformation;
    jfrNativeEventSetting GCConfiguration;
    jfrNativeEventSetting GCSurvivorConfiguration;
    jfrNativeEventSetting GCTLABConfiguration;
    jfrNativeEventSetting GCHeapConfiguration;
    jfrNativeEventSetting YoungGenerationConfiguration;
    jfrNativeEventSetting ZAllocationStall;
    jfrNativeEventSetting ZPageAllocation;
    jfrNativeEventSetting ZRelocationSet;
    jfrNativeEventSetting ZRelocationSetGroup;
    jfrNativeEventSetting ZStatisticsCounter;
    jfrNativeEventSetting ZStatisticsSampler;
    jfrNativeEventSetting ZThreadPhase;
    jfrNativeEventSetting ZUncommit;
    jfrNativeEventSetting ZUnmap;
    jfrNativeEventSetting ShenandoahHeapRegionStateChange;
    jfrNativeEventSetting ShenandoahHeapRegionInformation;
    jfrNativeEventSetting Flush;
    jfrNativeEventSetting HeapDump;
    jfrNativeEventSetting GCLocker;
    jfrNativeEventSetting FinalizerStatistics;
    jfrNativeEventSetting StackFrame;
  } ev;
};

#endif // INCLUDE_JFR
#endif // JFRFILES_JFR_NATIVE_EVENTSETTING_HPP

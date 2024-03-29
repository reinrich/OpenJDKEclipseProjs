/* AUTOMATICALLY GENERATED FILE - DO NOT EDIT */

#ifndef JFRFILES_JFREVENTIDS_HPP
#define JFRFILES_JFREVENTIDS_HPP

#include "utilities/macros.hpp"
#if INCLUDE_JFR

enum JfrEventId {
  JfrMetadataEvent = 0,
  JfrCheckpointEvent = 1,
  JfrDurationEvent = 2,
  JfrInstantEvent = 3,
  JfrValueEvent = 4,
  JfrTextEvent = 5,
  JfrZThreadDebugEvent = 6,
  JfrThreadStartEvent = 7,
  JfrThreadEndEvent = 8,
  JfrThreadSleepEvent = 9,
  JfrThreadParkEvent = 10,
  JfrJavaMonitorEnterEvent = 11,
  JfrJavaMonitorWaitEvent = 12,
  JfrJavaMonitorInflateEvent = 13,
  JfrSyncOnValueBasedClassEvent = 14,
  JfrReservedStackActivationEvent = 15,
  JfrClassLoadEvent = 16,
  JfrClassDefineEvent = 17,
  JfrClassRedefinitionEvent = 18,
  JfrRedefineClassesEvent = 19,
  JfrRetransformClassesEvent = 20,
  JfrClassUnloadEvent = 21,
  JfrIntFlagChangedEvent = 22,
  JfrUnsignedIntFlagChangedEvent = 23,
  JfrLongFlagChangedEvent = 24,
  JfrUnsignedLongFlagChangedEvent = 25,
  JfrDoubleFlagChangedEvent = 26,
  JfrBooleanFlagChangedEvent = 27,
  JfrStringFlagChangedEvent = 28,
  JfrGCHeapSummaryEvent = 29,
  JfrMetaspaceSummaryEvent = 30,
  JfrMetaspaceGCThresholdEvent = 31,
  JfrMetaspaceAllocationFailureEvent = 32,
  JfrMetaspaceOOMEvent = 33,
  JfrMetaspaceChunkFreeListSummaryEvent = 34,
  JfrPSHeapSummaryEvent = 35,
  JfrG1HeapSummaryEvent = 36,
  JfrGarbageCollectionEvent = 37,
  JfrSystemGCEvent = 38,
  JfrParallelOldGarbageCollectionEvent = 39,
  JfrYoungGarbageCollectionEvent = 40,
  JfrOldGarbageCollectionEvent = 41,
  JfrG1GarbageCollectionEvent = 42,
  JfrG1MMUEvent = 43,
  JfrEvacuationInformationEvent = 44,
  JfrGCReferenceStatisticsEvent = 45,
  JfrObjectCountAfterGCEvent = 46,
  JfrG1EvacuationYoungStatisticsEvent = 47,
  JfrG1EvacuationOldStatisticsEvent = 48,
  JfrG1BasicIHOPEvent = 49,
  JfrG1AdaptiveIHOPEvent = 50,
  JfrPromoteObjectInNewPLABEvent = 51,
  JfrPromoteObjectOutsidePLABEvent = 52,
  JfrPromotionFailedEvent = 53,
  JfrEvacuationFailedEvent = 54,
  JfrConcurrentModeFailureEvent = 55,
  JfrGCPhasePauseEvent = 56,
  JfrGCPhasePauseLevel1Event = 57,
  JfrGCPhasePauseLevel2Event = 58,
  JfrGCPhasePauseLevel3Event = 59,
  JfrGCPhasePauseLevel4Event = 60,
  JfrGCPhaseConcurrentEvent = 61,
  JfrGCPhaseConcurrentLevel1Event = 62,
  JfrGCPhaseParallelEvent = 63,
  JfrAllocationRequiringGCEvent = 64,
  JfrTenuringDistributionEvent = 65,
  JfrG1HeapRegionTypeChangeEvent = 66,
  JfrCompilationEvent = 67,
  JfrCompilerPhaseEvent = 68,
  JfrCompilationFailureEvent = 69,
  JfrCompilerInliningEvent = 70,
  JfrSweepCodeCacheEvent = 71,
  JfrCodeCacheFullEvent = 72,
  JfrDeoptimizationEvent = 73,
  JfrSafepointBeginEvent = 74,
  JfrSafepointStateSynchronizationEvent = 75,
  JfrSafepointCleanupEvent = 76,
  JfrSafepointCleanupTaskEvent = 77,
  JfrSafepointEndEvent = 78,
  JfrExecuteVMOperationEvent = 79,
  JfrShutdownEvent = 80,
  JfrObjectAllocationInNewTLABEvent = 81,
  JfrObjectAllocationOutsideTLABEvent = 82,
  JfrObjectAllocationSampleEvent = 83,
  JfrOldObjectSampleEvent = 84,
  JfrDumpReasonEvent = 85,
  JfrDataLossEvent = 86,
  JfrJVMInformationEvent = 87,
  JfrOSInformationEvent = 88,
  JfrVirtualizationInformationEvent = 89,
  JfrInitialSystemPropertyEvent = 90,
  JfrInitialEnvironmentVariableEvent = 91,
  JfrSystemProcessEvent = 92,
  JfrCPUInformationEvent = 93,
  JfrCPUTimeStampCounterEvent = 94,
  JfrCPULoadEvent = 95,
  JfrThreadCPULoadEvent = 96,
  JfrThreadContextSwitchRateEvent = 97,
  JfrNetworkUtilizationEvent = 98,
  JfrJavaThreadStatisticsEvent = 99,
  JfrClassLoadingStatisticsEvent = 100,
  JfrClassLoaderStatisticsEvent = 101,
  JfrSymbolTableStatisticsEvent = 102,
  JfrStringTableStatisticsEvent = 103,
  JfrPlaceholderTableStatisticsEvent = 104,
  JfrLoaderConstraintsTableStatisticsEvent = 105,
  JfrProtectionDomainCacheTableStatisticsEvent = 106,
  JfrThreadAllocationStatisticsEvent = 107,
  JfrPhysicalMemoryEvent = 108,
  JfrExecutionSampleEvent = 109,
  JfrNativeMethodSampleEvent = 110,
  JfrThreadDumpEvent = 111,
  JfrNativeLibraryEvent = 112,
  JfrModuleRequireEvent = 113,
  JfrModuleExportEvent = 114,
  JfrCompilerStatisticsEvent = 115,
  JfrCompilerConfigurationEvent = 116,
  JfrCodeCacheStatisticsEvent = 117,
  JfrCodeCacheConfigurationEvent = 118,
  JfrCodeSweeperStatisticsEvent = 119,
  JfrCodeSweeperConfigurationEvent = 120,
  JfrIntFlagEvent = 121,
  JfrUnsignedIntFlagEvent = 122,
  JfrLongFlagEvent = 123,
  JfrUnsignedLongFlagEvent = 124,
  JfrDoubleFlagEvent = 125,
  JfrBooleanFlagEvent = 126,
  JfrStringFlagEvent = 127,
  JfrObjectCountEvent = 128,
  JfrG1HeapRegionInformationEvent = 129,
  JfrGCConfigurationEvent = 130,
  JfrGCSurvivorConfigurationEvent = 131,
  JfrGCTLABConfigurationEvent = 132,
  JfrGCHeapConfigurationEvent = 133,
  JfrYoungGenerationConfigurationEvent = 134,
  JfrZAllocationStallEvent = 135,
  JfrZPageAllocationEvent = 136,
  JfrZRelocationSetEvent = 137,
  JfrZRelocationSetGroupEvent = 138,
  JfrZStatisticsCounterEvent = 139,
  JfrZStatisticsSamplerEvent = 140,
  JfrZThreadPhaseEvent = 141,
  JfrZUncommitEvent = 142,
  JfrZUnmapEvent = 143,
  JfrShenandoahHeapRegionStateChangeEvent = 144,
  JfrShenandoahHeapRegionInformationEvent = 145,
  JfrFlushEvent = 146,
  JfrHeapDumpEvent = 147,
  JfrGCLockerEvent = 148,
  JfrFinalizerStatisticsEvent = 149,
};
typedef enum JfrEventId JfrEventId;

static const JfrEventId FIRST_EVENT_ID = JfrDurationEvent;
static const JfrEventId LAST_EVENT_ID = JfrFinalizerStatisticsEvent;
static const int NUMBER_OF_EVENTS = 148;
static const int NUMBER_OF_RESERVED_EVENTS = 2;
#endif // INCLUDE_JFR
#endif // JFRFILES_JFREVENTIDS_HPP
